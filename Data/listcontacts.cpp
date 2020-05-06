#include <algorithm>
#include <QFile>
#include <QTextStream>

#include "listcontacts.h"

ListContacts::ListContacts()
{
    dbm = new DBManager;
    listContacts = dbm->getListContacts();
}

bool ListContacts::addContact(const Contact &contact)
{
    if (contact.m_name.isEmpty()) {
        return false;
    }
    if (!dbm->insertItem(contact)) {
            qDebug() << "insertItem(): " << false << Qt::endl;
            return false;
    }
    qDebug() << "insertItem(): " << true << Qt::endl;
    listContacts.push_back(contact);

    return true;
}

bool ListContacts::deleteContact(const Contact &contact)
{
    auto iteratorFind = std::find(listContacts.begin(), listContacts.end(), contact);
    if (iteratorFind == listContacts.end()) {
        return false;
    }
    if (!dbm->deleteItem(contact)) {
        qDebug() << "deleteItem(): " << false << Qt::endl;
        return false;
    }
    qDebug() << "deleteItem(): " << true << Qt::endl;
    listContacts.erase(iteratorFind);

    return true;
}

bool ListContacts::changeContact(const Contact &newC, const Contact &oldC)
{
    auto iteratorFind = std::find(listContacts.begin(), listContacts.end(), oldC);
    if (iteratorFind == listContacts.end()) {
        return false;
    }
    if (!dbm->updateItem(newC, oldC)) {
        qDebug() << "updateItem(): " << false << Qt::endl;
        return false;
    }
    qDebug() << "updateItem(): " << true << Qt::endl;
    size_t index = std::distance(listContacts.begin(), iteratorFind);
    listContacts[index] = newC;

    return true;
}

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

QString ListContacts::toTreeModel() const
{
    QString data;
    std::vector<QString> usedDepartment;
    for(size_t i = 0; i < listContacts.size(); ++i) {
        auto iterator = std::find(usedDepartment.begin(),
                                  usedDepartment.end(),
                                  listContacts[i].m_department);
        if (iterator == usedDepartment.end()) {
            usedDepartment.push_back(listContacts[i].m_department);
        }
    }
    for(size_t i = 0; i < usedDepartment.size(); ++i) {
        data += usedDepartment[i] +
                "\t\tФИО\t\t\t\t\t\t\t\tДолжность\t\t"
                "Номер помещения\tНомер телефона\r\n";
        for(size_t j = 0; j < listContacts.size(); ++j) {
            if (listContacts[j].m_department == usedDepartment[i]) {
                data += QString("\t%1\t%2\t\t\t%3\t\t%4\t\t\t%5\r\n")
                        .arg(listContacts[j].m_department)
                        .arg(listContacts[j].m_name)
                        .arg(listContacts[j].m_position)
                        .arg(listContacts[j].m_roomNumber)
                        .arg(listContacts[j].m_phone);
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

