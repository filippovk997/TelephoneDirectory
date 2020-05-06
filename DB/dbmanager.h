#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>

#include "../Data/listcontacts.h"
class Contact;

class DBManager
{
public:
    DBManager();
    ~DBManager();

    bool createConnection();
    bool createTable();
    std::vector<Contact> getListContacts();

    bool updateItem(const Contact& newC, const Contact& oldC);
    bool insertItem(const Contact& contact);
    bool deleteItem(const Contact& contact);

private:
    QSqlDatabase db;
};

#endif // DBMANAGER_H
