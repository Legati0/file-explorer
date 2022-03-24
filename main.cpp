#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDir>
#include <QDesktopWidget>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Explorer_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QDir dir = QDir::home();
    if (argc > 1 && QDir(argv[1]).exists())
        dir = QDir(argv[1]);

    MainWindow w(dir);
    auto size = qApp->screens()[0]->size();
    w.resize(size.width() / 2, size.height() / 2);
    w.show();

    return a.exec();
}
