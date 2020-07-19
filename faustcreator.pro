DEFINES += FAUSTCREATOR_LIBRARY
QT += svg
# Faust2QtCreator files

PROJECT_SOURCE_DIR = source

SOURCES += \
        $$PROJECT_SOURCE_DIR/faustcreator.cpp \
        $$PROJECT_SOURCE_DIR/faustcreator-options.cpp \
        $$PROJECT_SOURCE_DIR/faustcreator-output.cpp \
        $$PROJECT_SOURCE_DIR/faustcreator-project.cpp \
        $$PROJECT_SOURCE_DIR/faustcreator-build.cpp

HEADERS += \
        $$PROJECT_SOURCE_DIR/faustcreator.hpp \
        $$PROJECT_SOURCE_DIR/faustcreator-global.hpp \
        $$PROJECT_SOURCE_DIR/faustcreator-constants.hpp \
        $$PROJECT_SOURCE_DIR/faustcreator-options.hpp \
        $$PROJECT_SOURCE_DIR/faustcreator-output.hpp \
        $$PROJECT_SOURCE_DIR/faustcreator-project.hpp \
        $$PROJECT_SOURCE_DIR/faustcreator-build.hpp

DISTFILES += \
        .github/workflow/build_qmake.yml \
        .github/workflow/README.md

# Qt Creator linking

## Either set the IDE_SOURCE_TREE when running qmake,
## or set the QTC_SOURCE environment variable, to override the default setting
isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = $$(QTC_SOURCE)
isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = "/home/wpn214/Repositories/grame/qt-creator-4.12.1"

## Either set the IDE_BUILD_TREE when running qmake,
## or set the QTC_BUILD environment variable, to override the default setting
isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = $$(QTC_BUILD)
isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = "/home/wpn214/Repositories/grame/build-qtcreator-Qt_5_14_1_in_PATH_System-Debug"

## uncomment to build plugin into user config directory
## <localappdata>/plugins/<ideversion>
##    where <localappdata> is e.g.
##    "%LOCALAPPDATA%QtProjectqtcreator" on Windows Vista and later
##    "$XDG_DATA_HOME/data/QtProject/qtcreator" or "~/.local/share/data/QtProject/qtcreator" on Linux
##    "~/Library/Application Support/QtProject/Qt Creator" on OS X
# USE_USER_DESTDIR = yes

###### If the plugin can be depended upon by other plugins, this code needs to be outsourced to
###### <dirname>_dependencies.pri, where <dirname> is the name of the directory containing the
###### plugin's sources.

QTC_PLUGIN_NAME = FaustCreator
QTC_LIB_DEPENDS += \
    # nothing here at this time

QTC_PLUGIN_DEPENDS += \
    coreplugin \
    texteditor \
    projectexplorer \

QTC_PLUGIN_RECOMMENDS += \
    # optional plugin dependencies. nothing here at this time

###### End _dependencies.pri contents ######

include($$IDE_SOURCE_TREE/src/qtcreatorplugin.pri)
