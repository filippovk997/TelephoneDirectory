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
