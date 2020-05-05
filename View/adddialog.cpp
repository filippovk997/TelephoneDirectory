#include <QtWidgets>

#include "adddialog.h"

AddDialog::AddDialog(ListContacts *listContacts, QWidget *parent)
    : QDialog(parent)
    , lc(listContacts)
{
    QFormLayout* layout = new QFormLayout;

    QLabel* nameLabel = new QLabel("ФИО:");
    QLineEdit* nameLineEdit = new QLineEdit;

    QLabel* positionLabel = new QLabel("Должность:");
    QComboBox* positionComboBox = new QComboBox;
    positionComboBox->addItem(tr(" - "));
    positionComboBox->addItems(lc->getPositions());

    QLabel* departmentLabel = new QLabel("Подразделение:");
    QComboBox* departmentComboBox = new QComboBox;
    departmentComboBox->addItem(tr(" - "));
    departmentComboBox->addItems(lc->getDepartments());

    QLabel* roomNumLabel = new QLabel("Номер помещения:");
    QLineEdit* roomNumLineEdit = new QLineEdit;

    QLabel* phoneLabel = new QLabel("Номер телефона:");
    QLineEdit* phoneLineEdit = new QLineEdit;

    QHBoxLayout* buttonsHBLayout = new QHBoxLayout;

    addButton = new QPushButton(tr("Добавить"));

    buttonsHBLayout->addWidget(addButton);

    layout->addRow(nameLabel, nameLineEdit);
    layout->addRow(positionLabel, positionComboBox);
    layout->addRow(departmentLabel, departmentComboBox);
    layout->addRow(roomNumLabel, roomNumLineEdit);
    layout->addRow(phoneLabel, phoneLineEdit);
    layout->addRow(buttonsHBLayout);

    setLayout(layout);
    setFixedSize(QSize(350, 175));
    setWindowTitle("Добавить контакт");
}
