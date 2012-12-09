#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug("Calling up logic - start");

    MessagingManager = new QMessageManager();
    MessagingManager->registerNotificationFilter(QMessageFilter::byType(QMessage::Sms));

    connect(MessagingManager,SIGNAL(messageAdded(QMessageId &Id,QMessageManager::NotificationFilterIdSet &matchingFilterIds)), this, SLOT(MessageReceived(QMessageId &Id,QMessageManager::NotificationFilterIdSet &matchingFilterIds)));

    CNotifier* Mynotifier = new CNotifier();

    QString ContactName = Mynotifier->GetContactName();
    ui->pushButton->setText(ContactName);

    QUrl avatar = Mynotifier->GetContactAvatar();
    qDebug("URL = ");
    qDebug(avatar.toString().toAscii());

    QByteArray byteArray = avatar.toString().toUtf8();
    const char* ch = byteArray.constData();
    while(*ch != 'E')
    {
        ch++;
    }

    QString ContactPictureUrl = QString::fromUtf8(ch);
    qDebug("ContactURL = ");
    qDebug(ContactPictureUrl.toAscii());

    QImage* ConatactImage = new QImage(ContactPictureUrl);
    QLabel* ImageLabel = new QLabel(this);

    ImageLabel->setGeometry(QRect(40,50,281,300));
    ImageLabel->setPixmap(QPixmap::fromImage(*ConatactImage));
    ImageLabel->setVisible(true);
    ImageLabel->show();
    qDebug("Calling up logic - End");
}

MainWindow::~MainWindow()
{
    delete ui;
    //if(Mynotifier) delete Mynotifier ;
    //if(ConatactImage) delete ConatactImage ;
    //if(ImageLabel) delete ImageLabel ;
}

void MainWindow::setOrientation(ScreenOrientation orientation)
{
#if defined(Q_OS_SYMBIAN)
    // If the version of Qt on the device is < 4.7.2, that attribute won't work
    if (orientation != ScreenOrientationAuto) {
        const QStringList v = QString::fromAscii(qVersion()).split(QLatin1Char('.'));
        if (v.count() == 3 && (v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt()) < 0x040702) {
            qWarning("Screen orientation locking only supported with Qt 4.7.2 and above");
            return;
        }
    }
#endif // Q_OS_SYMBIAN

    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#endif // QT_VERSION < 0x040702
    };
    setAttribute(attribute, true);
}

void MainWindow::showExpanded()
{
#if defined(Q_OS_SYMBIAN) || defined(Q_WS_SIMULATOR)
    showFullScreen();
#elif defined(Q_WS_MAEMO_5)
    showMaximized();
#else
    show();
#endif
}

void MainWindow::MessageReceived(QMessageId &Id,QMessageManager::NotificationFilterIdSet &matchingFilterIds)
{
qDebug("Message Received");
QMessage ReceivedMessage = MessagingManager->message(Id);
QString user = (ReceivedMessage.from()).addressee();
qDebug(user.toAscii());
}
