#include "itemdialog.h"

ItemDialog::ItemDialog(const QModelIndex& index, ListContacts* listContact, QWidget* parent)
    : QDialog(parent)
    , lc(listContact)
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
    saveButton = new QPushButton(tr("Сохранить"));
    cancelButton = new QPushButton(tr("Отменить"));

    buttonsHBLayout->addWidget(changeButton);
    buttonsHBLayout->addWidget(deleteButton);
    buttonsHBLayout->addWidget(saveButton);
    buttonsHBLayout->addWidget(cancelButton);

    saveButton->hide();
    cancelButton->hide();

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
    connect(saveButton, &QPushButton::clicked, this, &ItemDialog::itemSaveChangeClicked);
    connect(cancelButton, &QPushButton::clicked, this, &ItemDialog::cancelClicked);
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

    changeButton->hide();
    deleteButton->hide();

    saveButton->show();
    cancelButton->show();
}

void ItemDialog::itemSaveChangeClicked()
{
    Contact oldValues(nameText, positionText, departmentText, roomNumberText.toInt(), phoneText);
    nameText = nameLineEdit->text();
    positionText = positionComboBox->currentText();
    departmentText = departmentComboBox->currentText();
    roomNumberText = roomNumLineEdit->text();
    phoneText = phoneLineEdit->text();
    Contact newValues(nameText, positionText, departmentText, roomNumberText.toInt(), phoneText);

    if(lc->changeContact(newValues, oldValues)) {
        nameLineEdit->setFocus(Qt::NoFocusReason);
        nameLineEdit->setReadOnly(true);
        positionComboBox->setDisabled(true);
        departmentComboBox->setDisabled(true);
        roomNumLineEdit->setReadOnly(true);
        phoneLineEdit->setReadOnly(true);

        saveButton->hide();
        cancelButton->hide();

        changeButton->show();
        deleteButton->show();
    }
    else {
        cancelClicked();
    }
}

void ItemDialog::cancelClicked()
{
    nameLineEdit->setText(nameText);
    nameLineEdit->setFocus(Qt::NoFocusReason);
    nameLineEdit->setReadOnly(true);

    positionComboBox->setCurrentText(positionText);
    positionComboBox->setDisabled(true);

    departmentComboBox->setCurrentText(departmentText);
    departmentComboBox->setDisabled(true);

    roomNumLineEdit->setText(roomNumberText);
    roomNumLineEdit->setReadOnly(true);

    phoneLineEdit->setText(phoneText);
    phoneLineEdit->setReadOnly(true);

    saveButton->hide();
    cancelButton->hide();

    changeButton->show();
    deleteButton->show();
}
