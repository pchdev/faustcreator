#ifndef FAUSTCREATOR_CONSTANTS_HPP
#define FAUSTCREATOR_CONSTANTS_HPP

namespace Faust {
namespace Constants {

const char C_FAUST_MIME_TYPE[]          = "text/x-faust";
const char C_FAUST_DISPLAY_NAME[]       = "Faust";
const char C_FAUST_LANGUAGE_ID[]        = "Faust";
const char C_FAUST_ACTION_RUN_ID[]      = "FaustEditor.Run";
const char C_FAUST_MENU_ID[]            = "FaustEditor.Menu";
const char C_FAUST_OPTIONS_PAGE_ID[]    = "FaustEditor.OptionsPage";
const char C_FAUST_PROJECT_ID[]         = "FaustEditor.Project";
const char C_FAUST_CATEGORY[]           = "F.Faust";

const char C_FAUST_MINIMAL_DSP_FILE[] =
        "import(\"stdfaust.lib\")\n\n"
        "process = +;";
}
}

#endif
