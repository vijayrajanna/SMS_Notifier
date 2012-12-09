#include "cnotifier.h"

CNotifier::CNotifier()
{
    qDebug("Constructing notifier");
    m_ContactManagers = QContactManager::availableManagers();
    m_ContactManagers.removeAll(QString("invalid"));
    m_ContactPhoneNo = new QContactPhoneNumber();
    m_ContactPhoneNo->setNumber("9886889696");

    for(int loc = 0; loc <m_ContactManagers.size() ; loc++)
    {
        m_CurrentContactManager = new QContactManager(m_ContactManagers.at(loc));
        QList<QContactLocalId> ContactIds = m_CurrentContactManager->contactIds();

        qDebug("Manager Found");
        for(int i = 0; i<ContactIds.size(); i++)
        {
            qDebug("Contact ID Found");
            m_CurrentContact =  m_CurrentContactManager->contact(ContactIds.at(i));
            QList<QContactPhoneNumber> PhoneNumbers = m_CurrentContact.details<QContactPhoneNumber>();
            for(int j= 0 ; j < PhoneNumbers.size() ; j++)
            {
                qDebug("Phone No found Found");
                QContactPhoneNumber aNumber = PhoneNumbers.at(j);
                QContactName name = m_CurrentContact.detail<QContactName>();
                qDebug(name.firstName().toAscii());
                qDebug(aNumber.number().toAscii());
                if(!strcmp(m_ContactPhoneNo->number().toAscii(),aNumber.number().toAscii()))
                {
                    QContactName name = m_CurrentContact.detail<QContactName>();
                    return ;
                    qDebug("Srring compare Passed");
                }
                qDebug("Srring compare failed");
            }
        }
    }
}

QString CNotifier::GetContactName()
{
    return (m_CurrentContact.detail<QContactName>()).firstName().toAscii();
}

QUrl CNotifier::GetContactAvatar()
{
    return (m_CurrentContact.detail<QContactAvatar>()).imageUrl();

}
