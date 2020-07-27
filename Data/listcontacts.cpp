#include <algorithm>
#include <QtXml>
#include <QMessageBox>

#include "listcontacts.h"

ListContacts::ListContacts()
{
    dbm = new DBManager;
    listContacts = dbm->getListContacts();
}

bool ListContacts::addContact(const Contact &contact)
{
    if (!contact.checkRegExp()) {
        return false;
    }

    if (!dbm->insertItem(contact)) {
            return false;
    }
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
        return false;
    }
    listContacts.erase(iteratorFind);

    return true;
}

bool ListContacts::changeContact(const Contact &newC, const Contact &oldC)
{
    if (!newC.checkRegExp()) {
        return false;
    }

    auto iteratorFind = std::find(listContacts.begin(), listContacts.end(), oldC);
    if (iteratorFind == listContacts.end()) {
        return false;
    }
    if (!dbm->updateItem(newC, oldC)) {
        return false;
    }
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

void ListContacts::toXml(const QString& fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("TelephoneDirectory");
    for (const Contact& contact : listContacts) {
        stream.writeStartElement("Contact");
        stream.writeTextElement("name", contact.m_name);
        stream.writeTextElement("position", contact.m_position);
        stream.writeTextElement("department", contact.m_department);
        stream.writeTextElement("roomnumber", QString::number(contact.m_roomNumber));
        stream.writeTextElement("phone", contact.m_phone);
        stream.writeEndElement(); // Contact
    }
    stream.writeEndElement(); // TelephoneDirectory
    stream.writeEndDocument();

    file.close();
}

void ListContacts::fromXml(const QString& fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    bool addError = false;
    std::vector<Contact> addListContacts;
    QXmlStreamReader xml(&file);

    if (xml.readNextStartElement()) {
        if (xml.name() == "TelephoneDirectory") {
            while (xml.readNextStartElement()) {
                if (xml.name() == "Contact") {
                    Contact contact;
                    while (xml.readNextStartElement()) {
                        if (xml.name() == "name") {
                            contact.m_name = xml.readElementText();
                        }
                        else if (xml.name() == "position") {
                            contact.m_position = xml.readElementText();
                        }
                        else if (xml.name() == "department") {
                            contact.m_department = xml.readElementText();
                        }
                        else if (xml.name() == "roomnumber") {
                            contact.m_roomNumber = xml.readElementText().toLong();
                        }
                        else if (xml.name() == "phone") {
                            contact.m_phone = xml.readElementText();
                        }
                        else {
                            addError = true;
                        }
                    }
                    if (!addError)
                        addListContacts.push_back(contact);
                }
                else {
                    addError = true;
                }
            }
        }
        else {
            return;
        }
    }
    if (!addError) {
        listContacts = addListContacts;
    }

    file.close();
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

