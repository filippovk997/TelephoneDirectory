#include <QRegExp>
#include <QDebug>
#include <QMessageBox>

#include "contact.h"

Contact::Contact()
    : m_name(QString())
    , m_position(QString())
    , m_department(QString())
    , m_roomNumber(0l)
    , m_phone(QString())
{ }

Contact::Contact(QString name, QString position, QString department,
                 long roomNum, QString phone)
                 : m_name(name)
                 , m_position(position)
                 , m_department(department)
                 , m_roomNumber(roomNum)
                 , m_phone(phone)
{ }

bool Contact::operator==(const Contact &other)
{
    return (m_name       == other.m_name &&
            m_position   == other.m_position &&
            m_department == other.m_department &&
            m_roomNumber == other.m_roomNumber &&
            m_phone      == other.m_phone);
}

bool Contact::checkRegExp() const
{
    QRegExp nameRegExp("^[А-Я][а-я]{,20}\\s[А-Я][а-я]{,20}\\s[А-Я][а-я]{,20}$");
    QRegExp positionRegExp("^[A-Я][а-я]{,20}$");
    QRegExp departmentRegExp("^[А-Я]{3}[1-9]$");
    QRegExp roomNumberRegExp("^\\d{5}$");
    QRegExp phoneRegExp("^\\+79\\d{9}$");

    if (!nameRegExp.exactMatch(m_name)) {
        return false;
    }
    if (!positionRegExp.exactMatch(m_position)) {
        return false;
    }
    if (!departmentRegExp.exactMatch(m_department)) {
        return false;
    }
    if (!roomNumberRegExp.exactMatch(QString::number(m_roomNumber))) {
        return false;
    }
    if (!phoneRegExp.exactMatch(m_phone)) {
        return false;
    }

    return true;
}
