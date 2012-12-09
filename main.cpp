#include "mainwindow.h"
#include "cnotifier.h"

#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow* mainWindow =  new MainWindow();
    mainWindow->setOrientation(MainWindow::ScreenOrientationLockPortrait);
    mainWindow->showNormal();

    //    MainWindow mainWindow;
    //    mainWindow.setOrientation(MainWindow::ScreenOrientationLockPortrait);
    //    mainWindow.showNormal();

    return app.exec();
}
