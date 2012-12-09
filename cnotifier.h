#ifndef CNOTIFIER_H
#define CNOTIFIER_H
#include <QContact>
#include <QContactId>
#include <QContactManager>
#include <QContactPhoneNumber>
#include <QContactName>
#include <QWidget>
#include <QContactAvatar>
#include <QUrl>

#include "QStringList"

QTM_USE_NAMESPACE

class CNotifier
{
    public:
    CNotifier();
    ~CNotifier();
    QString GetContactName();
    QUrl GetContactAvatar();

    private:

    QStringList             m_ContactManagers ;
    QContact                m_CurrentContact ;
    QContactManager*        m_CurrentContactManager;
    QContactPhoneNumber*    m_ContactPhoneNo ;

};

#endif // CNOTIFIER_H
