#include "faustcreator.hpp"
#include "faustcreator-constants.hpp"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/editormanager/editormanager.h>
#include <projectexplorer/compileoutputwindow.h>
#include <projectexplorer/toolchainmanager.h>
#include <projectexplorer/projectmanager.h>
#include <extensionsystem/pluginmanager.h>

#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>
#include <QDir>
#include <QFile>

using namespace ProjectExplorer;

namespace Faust {
namespace Internal {

FaustPlugin::FaustPlugin() :
    m_svg_proc(new QProcess(this)),
    m_cmp_proc(new QProcess(this)),
    m_run_proc(new QProcess(this))
{
    connect(m_cmp_proc, &QProcess::readyReadStandardOutput, this, &FaustPlugin::onCompilerOutput);
    connect(m_svg_proc, &QProcess::readyReadStandardOutput, this, &FaustPlugin::onSvgOutput);
    connect(m_svg_proc, SIGNAL(finished(int)), this, SLOT(onSvgFinished(int)));
    connect(m_cmp_proc, SIGNAL(finished(int)), this, SLOT(onCompilerFinished(int)));
}

FaustPlugin::~FaustPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
    ExtensionSystem::PluginManager::removeObject(m_outputs);
    ExtensionSystem::PluginManager::removeObject(m_options);
    delete m_outputs;
    delete m_options;
}

bool FaustPlugin::initialize(QStringList const& arguments, QString *errorString)
{
    // Register objects in the plugin manager's object pool
    // Load settings
    // Add actions to menus
    // Connect to other plugins' signals
    // In the initialize function, a plugin can be sure that the plugins it
    // depends on have initialized their members.
    Q_UNUSED(arguments)
    Q_UNUSED(errorString)    
    m_outputs = new FaustOutputPane;
    m_options = new FaustOptionsPage;
    ExtensionSystem::PluginManager::addObject(m_outputs);
    ExtensionSystem::PluginManager::addObject(m_options);   

    Core::EditorManager::instance();
    connect(Core::EditorManager::instance(), &Core::EditorManager::saved,
            this, &FaustPlugin::onDocumentSaved);
    connect(Core::EditorManager::instance(), &Core::EditorManager::documentOpened,
            this, &FaustPlugin::onDocumentOpened);
    connect(Core::EditorManager::instance(), &Core::EditorManager::documentClosed,
            this, &FaustPlugin::onDocumentClosed);

    ToolChainManager::registerLanguage(Constants::C_FAUST_LANGUAGE_ID,
                                       Constants::C_FAUST_DISPLAY_NAME);
    ProjectManager::registerProjectType<FaustProject>(Constants::C_FAUST_MIME_TYPE);

    auto action = new QAction(tr("run"), this);
    Core::Command *cmd = Core::ActionManager::registerAction(action, Constants::C_FAUST_ACTION_RUN_ID,
                                              Core::Context(Core::Constants::C_GLOBAL));
    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+R")));
    connect(action, &QAction::triggered, this, &FaustPlugin::triggerAction);

    m_menu = Core::ActionManager::createMenu(Constants::C_FAUST_MENU_ID);
    m_menu->menu()->setTitle(tr("Faust Compiler"));
    m_menu->addAction(cmd);

    collectTargets();
    Core::ActionManager::actionContainer(Core::Constants::M_TOOLS)->addMenu(m_menu);
    return true;
}

void FaustPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

void FaustPlugin::compileSvg(QString path)
{
    QStringList arguments;
    QString bin("/usr/bin/faust2svg");
    arguments << path;
    m_svg_proc->start(bin, arguments);
}

inline bool faustFile(QString const& file)
{
    return file.endsWith(".dsp") || file.endsWith(".lib");
}

void FaustPlugin::onDocumentOpened(Core::IDocument* doc)
{  
    if (faustFile(doc->displayName()))
        compileSvg(doc->filePath().toString());
}

void FaustPlugin::onDocumentSaved(Core::IDocument* doc)
{
    if (faustFile(doc->displayName()))
        compileSvg(doc->filePath().toString());
}

void FaustPlugin::onDocumentClosed(Core::IDocument* doc)
{
    QString docname = doc->displayName();
    if (faustFile(doc->displayName()))
        m_outputs->clearContents();
}

void FaustPlugin::onSvgOutput()
{
    QByteArray out = m_svg_proc->readAllStandardOutput();
}

void FaustPlugin::onSvgFinished(int excode)
{
    QString path = m_svg_proc->arguments()[0];
    path.replace(".dsp", "-svg");
    path.append("/process.svg");
    m_outputs->displaySvg(path);
}

void FaustPlugin::onCompilerOutput()
{
    QByteArray out = m_cmp_proc->readAllStandardOutput();
}

void FaustPlugin::onCompilerFinished(int excode)
{

}

void FaustPlugin::collectTargets()
{
    QDir bin("/usr/bin");
    for (const auto& exec : bin.entryList()) {
        if (exec.startsWith("faust2")) {
            m_targets.append(exec);
            QString& target = m_targets.last();
            auto action = new QAction(target, this);
            Core::Command* cmd = Core::ActionManager::registerAction(action, target.toStdString().c_str(),
                                                      Core::Context(Core::Constants::C_GLOBAL));
            connect(action, &QAction::triggered, this, &FaustPlugin::triggerAction);
            ////    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+A")));
            m_menu->addAction(cmd);
        }
    }
}

void FaustPlugin::run()
{

}

ExtensionSystem::IPlugin::ShutdownFlag FaustPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    disconnect(m_cmp_proc, &QProcess::readyReadStandardOutput, this, &FaustPlugin::onCompilerOutput);
    disconnect(m_svg_proc, &QProcess::readyReadStandardOutput, this, &FaustPlugin::onSvgOutput);
    disconnect(m_svg_proc, SIGNAL(finished(int)), this, SLOT(onSvgFinished(int)));
    disconnect(m_cmp_proc, SIGNAL(finished(int)), this, SLOT(onCompilerFinished(int)));
    return SynchronousShutdown;
}

void FaustPlugin::triggerAction()
{
    QAction* sender = qobject_cast<QAction*>(QObject::sender());
    QString process = sender->text();
    process.prepend("/usr/bin/");
    auto doc = Core::EditorManager::currentDocument();
    QStringList arguments;
    arguments << doc->filePath().toString() << "-soundfile";
    m_cmp_proc->start(process, arguments);
}
} // namespace Internal
} // namespace Faust2QtCreator
