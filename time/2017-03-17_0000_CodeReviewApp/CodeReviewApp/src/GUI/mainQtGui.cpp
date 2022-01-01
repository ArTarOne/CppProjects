#include <QtWidgets/QApplication>
#include "Application/Application.h"
#include "QtPlus/QtPlus.h"              // consoleOn
#include "GUI/GraphicInterface.h"
#include "GUI/SettingsUsedQt.h"
#include "Console/SettingStdApi.h"


int main(int argc, char *argv[])
{
	QApplication qApplication(argc, argv);

#ifdef _DEBUG
	qtplus::qtConsoleOn(true);
#endif // _DEBUG

    
    SettingStdApi settings;
    GraphicInterface userInterface;

    Application app(argc, argv);
    app.setISettings(&settings);
    app.setIUserInterface(&userInterface);
    app.start();

	qApplication.exec();
}
