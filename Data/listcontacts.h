#ifndef LISTCONTACTS_H
#define LISTCONTACTS_H

#include <vector>
#include <QString>
#include <QStringList>
#include <QDebug>

#include "../DB/dbmanager.h"
#include "contact.h"

class DBManager;
class Contact;

class ListContacts : public QObject
{
    Q_OBJECT

public:
    ListContacts();

    bool addContact(const Contact& contact);
    bool deleteContact(const Contact& contact);
    bool changeContact(const Contact& newC, const Contact& oldC);
    void show();

    QString toTreeModel() const;
    QStringList getPositions() const;
    QStringList getDepartments() const;

signals:
    void changeContacts();

private:
    DBManager* dbm;
    std::vector<Contact> listContacts {};
};

#endif // CONTACT_H
