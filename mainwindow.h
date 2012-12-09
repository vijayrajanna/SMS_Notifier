#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "cnotifier.h"
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QMessage>
#include <QMessageManager>
#include <QMessageId>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };

    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    // Note that this will only have an effect on Symbian and Fremantle.
    void setOrientation(ScreenOrientation orientation);
    void showExpanded();

public:
    Ui::MainWindow *ui;

public:
    QMessageManager* MessagingManager ;

public slots:
    void MessageReceived(QMessageId &Id,QMessageManager::NotificationFilterIdSet &matchingFilterIds);
};

#endif // MAINWINDOW_H
