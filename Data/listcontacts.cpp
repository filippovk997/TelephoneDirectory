#include "listcontacts.h"
#include "../DB/dbmanager.h"

#include <QFile>
#include <QTextStream>

ListContacts::ListContacts()
{

}

void ListContacts::addContact(const Contact &c)
{
    listContacts.push_back(c);
}

void ListContacts::addContact(QString name, QString position, QString department, long roomNum, QString phone)
{
    listContacts.push_back(Contact(name, position, department, roomNum, phone));
}

void ListContacts::deleteContact(const int index)
{
    listContacts.erase(listContacts.begin() + index);
}

void ListContacts::changeContact(const Contact &newC, const int index)
{
    listContacts.at(index) = newC;
}
/*
int ListContacts::findContact(const QString name, const QString department)
{
    for (int i = 0; i < listContacts.size(); ++i) {
        if (listContacts[i].m_name == name && listContacts[i].m_department == department) {
            return i;
        } else {
            return -1;
        }
    }
}
*/
void ListContacts::show()
{
    for (size_t i = 0; i < listContacts.size(); ++i) {
        qDebug() << "{" << listContacts[i].m_name
                 << ", " << listContacts[i].m_position
                 << ", " << listContacts[i].m_department
                 << ", " << listContacts[i].m_roomNumber
                 << ", " << listContacts[i].m_phone
                 << "}" << Qt::endl;
    }
}

void ListContacts::getFromDBData()
{
    DBManager dbm;
    listContacts = dbm.getListContacts();
}

QString ListContacts::toTreeModel() const
{
    QString data {};
    std::vector<QString> used;
    for(const Contact &contact : listContacts) {
        auto iteratorFind = std::find(used.begin(), used.end(),
                                      contact.m_department);
        if (iteratorFind == used.end()) {
            used.push_back(contact.m_department);
            data += contact.m_department +
                    "\t\tФИО\t\t\t\t\t\t\t\tДолжность\t\t"
                    "Номер помещения\tНомер телефона\r\n";
            data += QString("\t%1\t%2\t\t\t%3\t\t%4\t\t\t%5\r\n")
                    .arg(contact.m_department)
                    .arg(contact.m_name)
                    .arg(contact.m_position)
                    .arg(contact.m_roomNumber)
                    .arg(contact.m_phone);
        }
        else {
            for (size_t i = used.size(); i < listContacts.size(); ++i) {
                if (listContacts[i].m_department == contact.m_department) {
                    data += QString("\t%1\t%2\t\t\t%3\t\t%4\t\t\t%5\r\n")
                            .arg(contact.m_department)
                            .arg(contact.m_name)
                            .arg(contact.m_position)
                            .arg(contact.m_roomNumber)
                            .arg(contact.m_phone);
                }
            }
        }
    }

    return data;
}

QStringList ListContacts::getPositions() const
{
    QStringList positions;
    std::vector<QString> used;
    for(const Contact &contact : listContacts) {
        auto iteratorFind = std::find(used.begin(), used.end(),
                                      contact.m_position);
        if (iteratorFind == used.end()) {
            used.push_back(contact.m_position);
            positions << contact.m_position;
        }
    }

    return positions;
}

QStringList ListContacts::getDepartments() const
{
    QStringList departments;
    std::vector<QString> used;
    for(const Contact &contact : listContacts) {
        auto iteratorFind = std::find(used.begin(), used.end(),
                                      contact.m_department);
        if (iteratorFind == used.end()) {
            used.push_back(contact.m_department);
            departments << contact.m_department;
        }
    }

    return departments;
}

