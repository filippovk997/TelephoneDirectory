#include "dbmanager.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QSettings>
#include <QFile>

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
        return true;
    }

    query.exec("CREATE TABLE Employee (name text, "
               "position text,"" department text, "
               "roomNumber integer, phone text)");
    /*
    query.exec("INSERT INTO Employee (name, position, "
               "department, roomNumber, phone) VALUES"
               "('Иванов Иван Иванович', 'Директор', "
               "'NIL1', 26701, '+79279876551')");
    query.exec("INSERT INTO Employee (name, position, "
               "department, roomNumber, phone) VALUES"
               "('Алексеев Алексей Алексеевич', 'Техник', "
               "'NIL1', 20101, '+79279876562')");
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

    ListContacts lc;
    while (query.next()) {
        lc.addContact(query.value(nameColumn).toString(),
                      query.value(positionColumn).toString(),
                      query.value(departmentColumn).toString(),
                      query.value(roomNumberColumn).toInt(),
                      query.value(phoneColumn).toString());
    }

    return lc.listContacts;
}
