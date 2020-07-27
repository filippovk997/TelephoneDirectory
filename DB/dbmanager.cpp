#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QSettings>
#include <QFile>

#include "dbmanager.h"

DBManager::DBManager()
{
    createConnection();
    createTable();
}

DBManager::~DBManager()
{

}

bool DBManager::createConnection()
{
    QFile file("settings.ini");
    QString filename = file.fileName();
    QSettings conntectionSettings(filename, QSettings::IniFormat);

    if (!file.exists()) {
        file.open(QIODevice::WriteOnly);
        conntectionSettings.beginGroup("PSQL");
        conntectionSettings.setValue("HOST", "localhost");
        conntectionSettings.setValue("DATABNAME", "TelephoneDirectory");
        conntectionSettings.setValue("PORT", 5433);
        conntectionSettings.setValue("USERNAME", "postgres");
        conntectionSettings.setValue("PASS", "root");
        conntectionSettings.endGroup();
        file.close();
    }

    conntectionSettings.beginGroup("PSQL");
    QString host = conntectionSettings.value("HOST").toString();
    QString databname = conntectionSettings.value("DATABNAME").toString();
    int port = conntectionSettings.value("PORT").toInt();
    QString username = conntectionSettings.value("USERNAME").toString();
    QString pass = conntectionSettings.value("PASS").toString();
    conntectionSettings.endGroup();

    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(host);
    db.setDatabaseName(databname);
    db.setPort(port);
    db.setUserName(username);
    db.setPassword(pass);
    if (!db.open()) {
            return false;
    }

    return true;
}

bool DBManager::createTable()
{
    QSqlQuery query("SELECT * FROM Employee");

    if (query.size() != -1) {
        return false;
    }

    query.exec("CREATE TABLE Employee (name text, "
               "position text,"" department text, "
               "roomNumber integer, phone text)");
    /*
    query.exec("INSERT INTO Employee (name, position, "
               "department, roomNumber, phone) VALUES"
               "('Иванов Иван Иванович', 'Директор', "
               "'NIL1', 26701, '+79279876551')");
    */
    return true;
}

std::vector<Contact> DBManager::getListContacts()
{
    QSqlQuery query("SELECT * FROM Employee");
    QSqlRecord rec = query.record();

    int nameColumn = rec.indexOf("name");
    int positionColumn = rec.indexOf("position");
    int departmentColumn = rec.indexOf("department");
    int roomNumberColumn = rec.indexOf("roomNumber");
    int phoneColumn = rec.indexOf("phone");

    std::vector<Contact> contacts;
    while (query.next()) {
        contacts.push_back(Contact(query.value(nameColumn).toString(),
                                   query.value(positionColumn).toString(),
                                   query.value(departmentColumn).toString(),
                                   query.value(roomNumberColumn).toInt(),
                                   query.value(phoneColumn).toString()));
    }

    return contacts;
}

bool DBManager::updateItem(const Contact& newC, const Contact& oldC)
{
    QSqlQuery insertQuery;
    insertQuery.prepare("UPDATE Employee SET "
                        "name = :name, "
                        "position = :position, "
                        "department = :department, "
                        "roomNumber = :roomNumber, "
                        "phone = :phone "

                        "WHERE name = :findName "
                        "AND position = :findPosition "
                        "AND department = :findDepartment "
                        "AND roomNumber = :findRoomNumber "
                        "AND phone = :findPhone");
    insertQuery.bindValue(":name", newC.m_name);
    insertQuery.bindValue(":position", newC.m_position);
    insertQuery.bindValue(":department", newC.m_department);
    insertQuery.bindValue(":roomNumber", QString::number(newC.m_roomNumber).toInt());
    insertQuery.bindValue(":phone", newC.m_phone);

    insertQuery.bindValue(":findName", oldC.m_name);
    insertQuery.bindValue(":findPosition", oldC.m_position);
    insertQuery.bindValue(":findDepartment", oldC.m_department);
    insertQuery.bindValue(":findRoomNumber", QString::number(oldC.m_roomNumber).toInt());
    insertQuery.bindValue(":findPhone", oldC.m_phone);

    return insertQuery.exec();
}

bool DBManager::insertItem(const Contact &contact)
{
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO Employee (name, position, department, roomNumber, phone) "
                        "VALUES (:name, :position, :department, :roomNumber, :phone)");
    insertQuery.bindValue(":name", contact.m_name);
    insertQuery.bindValue(":position", contact.m_position);
    insertQuery.bindValue(":department", contact.m_department);
    insertQuery.bindValue(":roomNumber", QString::number(contact.m_roomNumber));
    insertQuery.bindValue(":phone", contact.m_phone);
    return insertQuery.exec();
}

bool DBManager::deleteItem(const Contact &contact)
{
    QSqlQuery insertQuery;
    insertQuery.prepare("DELETE FROM Employee "
                        "WHERE name = :findName "
                        "AND position = :findPosition "
                        "AND department = :findDepartment "
                        "AND roomNumber = :findRoomNumber "
                        "AND phone = :findPhone");
    insertQuery.bindValue(":findName", contact.m_name);
    insertQuery.bindValue(":findPosition", contact.m_position);
    insertQuery.bindValue(":findDepartment", contact.m_department);
    insertQuery.bindValue(":findRoomNumber", QString::number(contact.m_roomNumber));
    insertQuery.bindValue(":findPhone", contact.m_phone);

    return insertQuery.exec();
}
