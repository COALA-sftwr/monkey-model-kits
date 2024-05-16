/*
*	File:			main.cpp
*	Created:		GAlbert 21.01.24
*	Description:	File for the strategy pattern applied to recognise different commands given to the shell
*/

#include <QtWidgets>
#include <QLocale>
#include <MonkeyWindow.hpp>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    MonkeyWindow mwindow;
    // QMainWindow mwindow;

    for (const QString &locale : uiLanguages) {
        const QString baseName = "mmk-gui_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    // window.show();
    mwindow.setWindowTitle("Monkey ModelKits");
    mwindow.show();
    return app.exec();
}
