#ifndef FAUSTCREATOR_PROJECT_HPP
#define FAUSTCREATOR_PROJECT_HPP

#include <projectexplorer/project.h>

namespace Faust {
namespace Internal {

class FaustProject : public ProjectExplorer::Project
{
    Q_OBJECT

public:
    explicit FaustProject(const Utils::FilePath& filename);
    bool needsConfiguration() const final override { return true; }

private:
    RestoreResult fromMap(const QVariantMap& map, QString* errorMessage) override;
};
}
}
#endif
