#include <QtWidgets>

#include "adddialog.h"

AddDialog::AddDialog(ListContacts *listContacts, QWidget *parent)
    : QDialog(parent)
    , lc(listContacts)
{
    QFormLayout* layout = new QFormLayout;

    QLabel* nameLabel = new QLabel("ФИО:");
    nameLineEdit = new QLineEdit;

    QLabel* positionLabel = new QLabel("Должность:");
    positionComboBox = new QComboBox;
    positionComboBox->addItem(tr(" - "));
    positionComboBox->addItems(lc->getPositions());

    QLabel* departmentLabel = new QLabel("Подразделение:");
    departmentComboBox = new QComboBox;
    departmentComboBox->addItem(tr(" - "));
    departmentComboBox->addItems(lc->getDepartments());

    QLabel* roomNumLabel = new QLabel("Номер помещения:");
    roomNumLineEdit = new QLineEdit;

    QLabel* phoneLabel = new QLabel("Номер телефона:");
    phoneLineEdit = new QLineEdit;

    QHBoxLayout* buttonsHBLayout = new QHBoxLayout;

    addButton = new QPushButton(tr("Добавить"));
    addButton->setMinimumWidth(150);

    buttonsHBLayout->addWidget(addButton);
    buttonsHBLayout->setAlignment(addButton, Qt::AlignCenter);

    layout->addRow(nameLabel, nameLineEdit);
    layout->addRow(positionLabel, positionComboBox);
    layout->addRow(departmentLabel, departmentComboBox);
    layout->addRow(roomNumLabel, roomNumLineEdit);
    layout->addRow(phoneLabel, phoneLineEdit);
    layout->addRow(buttonsHBLayout);

    setLayout(layout);
    setFixedSize(QSize(350, 175));
    setWindowTitle("Добавить контакт");

    connect(addButton, &QPushButton::clicked, this, &AddDialog::addClicked);
    connect(addButton, &QPushButton::clicked, this, &AddDialog::accept);
}

void AddDialog::addClicked()
{
    QString name = nameLineEdit->text();
    QString position = positionComboBox->currentText();
    QString department = departmentComboBox->currentText();
    QString roomNumber = roomNumLineEdit->text();
    QString phone = phoneLineEdit->text();

    if (name.isEmpty() ||
        position == " - " ||
        department == " - " ||
        roomNumber.isEmpty() ||
        phone.isEmpty()) {
        QMessageBox::information(this, tr("Empty field"),
            tr("Please enter text in all fields."));
        contact = Contact();
        return;
    }
    else {
        contact.m_name = name;
        contact.m_position = position;
        contact.m_department = department;
        contact.m_roomNumber = roomNumber.toLong();
        contact.m_phone = phone;

        nameLineEdit->clear();
        positionComboBox->setCurrentText(" - ");
        departmentComboBox->setCurrentText(" - ");
        roomNumLineEdit->clear();
        phoneLineEdit->clear();
    }
}

Contact AddDialog::getAddContact()
{
    Contact result = contact;
    contact = Contact();

    return result;
}

