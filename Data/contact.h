#ifndef CONTACT_H
#define CONTACT_H

#include <QString>

class Contact
{
public:
    Contact();
    Contact(QString name, QString position, QString department,
            long roomNum, QString phone);

    bool operator==(const Contact& other);

    bool checkRegExp() const;

    QString m_name;
    QString m_position;
    QString m_department;
    long m_roomNumber;
    QString m_phone;
};

#endif // CONTACT_H
