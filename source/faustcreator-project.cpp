#include "faustcreator-project.hpp"
#include "faustcreator-constants.hpp"

using namespace Faust::Internal;

FaustProject::FaustProject(const Utils::FilePath& filename) :
    ProjectExplorer::Project(Constants::C_FAUST_MIME_TYPE, filename)
{
    setId(Constants::C_FAUST_PROJECT_ID);
    setDisplayName(Constants::C_FAUST_DISPLAY_NAME);
    setProjectLanguage(Constants::C_FAUST_LANGUAGE_ID, true);
    setNeedsBuildConfigurations(true);
    setNeedsDeployConfigurations(true);
}

ProjectExplorer::Project::RestoreResult
FaustProject::fromMap(const QVariantMap& map, QString* errorMessage)
{
    Project::RestoreResult res = Project::fromMap(map, errorMessage);
    if (res == RestoreResult::Ok) {
        if (!activeTarget())
            addTargetForDefaultKit();
    }
    return res;
}
