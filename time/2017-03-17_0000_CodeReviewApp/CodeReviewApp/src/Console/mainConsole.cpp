#include "StdPlus/StdPlus.h"
#include "Application/Application.h"
#include "Console/SettingStdApi.h"
#include "Console/ConsoleInterface.h"


int main(int argc, char *argv[])
{    
    SettingStdApi settings;
    ConsoleInterface userInterface;

    Application app(argc, argv);
    app.setISettings(&settings);
    app.setIUserInterface(&userInterface);
    app.start();

    APAUSE;
}
