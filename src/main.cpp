/*
*	File:			main.cpp
*	Created:		GAlbert 21.01.24
*	Description:	File for the strategy pattern applied to recognise different commands given to the shell
*/

#include <QApplication>
#include <QtWidgets>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "mmk-gui_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    QMainWindow w;
    w.setWindowTitle("Monkey ModelKits");
    w.resize(600, 500);
    w.show();
    return a.exec();
}
