#ifndef FAUSTCREATORPLUGIN_HPP
#define FAUSTCREATORPLUGIN_HPP

#include "faustcreator-global.hpp"
#include "faustcreator-options.hpp"
#include "faustcreator-output.hpp"
#include "faustcreator-project.hpp"
#include <extensionsystem/iplugin.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/idocument.h>

#include <QProcess>

namespace Faust {
namespace Internal {

// add options menu: path to faust compiler and other binaries + path to faust libraries
// add faust projects
// add multiple choice menu: choose faust compilation variants (faust2jack, faust2alsa, etc.)
// menu action: compile current .dsp, get output to show in Compile Output
// show errors in Issues footer tab
// show errors in .dsp file, just like in regular c/cxx files

class FaustSettings
{
private:
    QString m_binpath;
};

class FaustPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "FaustCreator.json")

public:
    FaustPlugin();
    ~FaustPlugin() override;

    bool initialize(const QStringList &arguments, QString *errorString) override;
    void extensionsInitialized() override;
    ShutdownFlag aboutToShutdown() override;

public slots:
    void onDocumentOpened(Core::IDocument* doc);
    void onDocumentSaved(Core::IDocument* doc);
    void onDocumentClosed(Core::IDocument* doc);

    void onSvgOutput();
    void onSvgFinished(int excode);
    void onCompilerOutput();
    void onCompilerFinished(int excode);

private:
    void compileSvg(QString path);
    void triggerAction();
    void collectTargets();
    void run();
    QStringList m_targets;
    FaustSettings m_settings;
    Core::IDocument* m_current_doc  = nullptr;
    Core::ActionContainer* m_menu   = nullptr;
    FaustProject* m_project         = nullptr;
    FaustOptionsPage* m_options     = nullptr;
    FaustOutputPane* m_outputs      = nullptr;
    QProcess* m_svg_proc;
    QProcess* m_cmp_proc;
    QProcess* m_run_proc;
};

}
}

#endif
