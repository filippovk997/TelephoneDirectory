#include "itemdialog.h"

ItemDialog::ItemDialog(const QModelIndex& index, ListContacts* lc, QWidget* parent)
    : QDialog(parent)
{
    QModelIndex nameRowIndex = index.sibling(index.row(), 1);
    QModelIndex positionRowIndex = index.sibling(index.row(), 2);
    QModelIndex departmentRowIndex = index.sibling(index.row(), 0);
    QModelIndex roomNumberRowIndex = index.sibling(index.row(), 3);
    QModelIndex phoneRowIndex = index.sibling(index.row(), 4);

    QString name = nameRowIndex.data(Qt::DisplayRole).toString();
    QString position = positionRowIndex.data(Qt::DisplayRole).toString();
    QString department = departmentRowIndex.data(Qt::DisplayRole).toString();
    QString roomNumber = roomNumberRowIndex.data(Qt::DisplayRole).toString();
    QString phone = phoneRowIndex.data(Qt::DisplayRole).toString();

    itemDialog = new QDialog;
    QFormLayout* layout = new QFormLayout;

    QLabel* nameLabel = new QLabel("ФИО:");
    nameLineEdit = new QLineEdit(name);
    nameLineEdit->setReadOnly(true);

    QLabel* positionLabel = new QLabel("Должность:");
    positionComboBox = new QComboBox;
    positionComboBox->addItem(tr(" - "));
    positionComboBox->addItems(lc->getPositions());
    positionComboBox->setCurrentText(position);
    positionComboBox->setDisabled(true);

    QLabel* departmentLabel = new QLabel("Подразделение:");
    departmentComboBox = new QComboBox;
    departmentComboBox->addItem(tr(" - "));
    departmentComboBox->addItems(lc->getDepartments());
    departmentComboBox->setCurrentText(department);
    departmentComboBox->setDisabled(true);

    QLabel* roomNumLabel = new QLabel("Номер помещения:");
    roomNumLineEdit = new QLineEdit(roomNumber);
    roomNumLineEdit->setReadOnly(true);

    QLabel* phoneLabel = new QLabel("Номер телефона:");
    phoneLineEdit = new QLineEdit(phone);
    phoneLineEdit->setReadOnly(true);

    buttonsHBLayout = new QHBoxLayout;

    changeButton = new QPushButton(tr("Изменить"));
    deleteButton = new QPushButton(tr("Удалить"));


    buttonsHBLayout->addWidget(changeButton);
    buttonsHBLayout->addWidget(deleteButton);

    layout->addRow(nameLabel, nameLineEdit);
    layout->addRow(positionLabel, positionComboBox);
    layout->addRow(departmentLabel, departmentComboBox);
    layout->addRow(roomNumLabel, roomNumLineEdit);
    layout->addRow(phoneLabel, phoneLineEdit);
    layout->addRow(buttonsHBLayout);

    itemDialog->setLayout(layout);
    itemDialog->setFixedSize(QSize(350, 175));
    itemDialog->setWindowTitle(name);
    itemDialog->show();

    connect(changeButton, &QPushButton::clicked, this, &ItemDialog::itemChangeClicked);
}

void ItemDialog::itemChangeClicked()
{   
    nameText = nameLineEdit->text();
    positionText = positionComboBox->currentText();
    departmentText = departmentComboBox->currentText();
    roomNumberText = roomNumLineEdit->text();
    phoneText = phoneLineEdit->text();

    nameLineEdit->setReadOnly(false);
    positionComboBox->setDisabled(false);
    departmentComboBox->setDisabled(false);
    roomNumLineEdit->setReadOnly(false);
    phoneLineEdit->setReadOnly(false);

    buttonsHBLayout->removeWidget(changeButton);
    buttonsHBLayout->removeWidget(deleteButton);

    saveButton = new QPushButton(tr("Сохранить"));
    cancelButton = new QPushButton(tr("Отменить"));

    buttonsHBLayout->addWidget(saveButton);
    buttonsHBLayout->addWidget(cancelButton);

    connect(cancelButton, &QPushButton::clicked, this, &ItemDialog::cancelClicked);
}

void ItemDialog::cancelClicked()
{
    nameLineEdit->setText(nameText);
    nameLineEdit->setReadOnly(false);

    positionComboBox->setCurrentText(positionText);
    positionComboBox->setDisabled(false);

    departmentComboBox->setCurrentText(departmentText);
    departmentComboBox->setDisabled(false);

    roomNumLineEdit->setText(roomNumberText);
    roomNumLineEdit->setReadOnly(false);

    phoneLineEdit->setText(phoneText);
    phoneLineEdit->setReadOnly(false);

    buttonsHBLayout->removeWidget(saveButton);
    buttonsHBLayout->removeWidget(cancelButton);

    buttonsHBLayout->addWidget(changeButton);
    buttonsHBLayout->addWidget(deleteButton);
}
