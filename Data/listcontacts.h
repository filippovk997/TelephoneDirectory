#ifndef LISTCONTACTS_H
#define LISTCONTACTS_H

#include "contact.h"

#include <vector>

#include <QString>
#include <QStringList>
#include <QDebug>

class ListContacts
{
public:
    ListContacts();

    void addContact(const Contact& c);
    void addContact(QString name, QString position, QString department, long roomNum, QString phone);
    void deleteContact(const int index);
    void changeContact(const Contact& newC, const int index);
    int findContact(const QString name, const QString department);
    void show();

    void getFromDBData();
    QString toTreeModel() const;
    QStringList getPositions() const;
    QStringList getDepartments() const;

    std::vector<Contact> listContacts {};
};

#endif // CONTACT_H
