#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "../Data/listcontacts.h"

#include <QSqlDatabase>

class DBManager
{
public:
    DBManager();
    ~DBManager();

    bool createConnection();

    bool createTable();
    std::vector<Contact> getListContacts();

private:
    QSqlDatabase db;
};

#endif // DBMANAGER_H
