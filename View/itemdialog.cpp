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

    QFormLayout* layout = new QFormLayout;

    QLabel* nameLabel = new QLabel("ФИО:");
    nameLineEdit = new QLineEdit(name);

    QLabel* positionLabel = new QLabel("Должность:");
    positionComboBox = new QComboBox;
    positionComboBox->addItem(tr(" - "));
    positionComboBox->addItems(lc->getPositions());
    positionComboBox->setCurrentText(position);

    QLabel* departmentLabel = new QLabel("Подразделение:");
    departmentComboBox = new QComboBox;
    departmentComboBox->addItem(tr(" - "));
    departmentComboBox->addItems(lc->getDepartments());
    departmentComboBox->setCurrentText(department);

    QLabel* roomNumLabel = new QLabel("Номер помещения:");
    roomNumLineEdit = new QLineEdit(roomNumber);

    QLabel* phoneLabel = new QLabel("Номер телефона:");
    phoneLineEdit = new QLineEdit(phone);

    buttonsHBLayout = new QHBoxLayout;

    changeButton = new QPushButton(tr("Изменить"));
    deleteButton = new QPushButton(tr("Удалить"));
    saveButton = new QPushButton(tr("Сохранить"));
    cancelButton = new QPushButton(tr("Отменить"));

    buttonsHBLayout->addWidget(changeButton);
    buttonsHBLayout->addWidget(deleteButton);
    buttonsHBLayout->addWidget(saveButton);
    buttonsHBLayout->addWidget(cancelButton);

    layout->addRow(nameLabel, nameLineEdit);
    layout->addRow(positionLabel, positionComboBox);
    layout->addRow(departmentLabel, departmentComboBox);
    layout->addRow(roomNumLabel, roomNumLineEdit);
    layout->addRow(phoneLabel, phoneLineEdit);
    layout->addRow(buttonsHBLayout);

    setLayout(layout);
    setFixedSize(QSize(350, 175));
    setWindowTitle(name);
    show();

    updateInterface(ViewMode);

    connect(changeButton, &QPushButton::clicked, this, &ItemDialog::itemChangeClicked);
    connect(deleteButton, &QPushButton::clicked, this, &ItemDialog::itemDeleteClicked);
    connect(deleteButton, &QPushButton::clicked, this, &ItemDialog::accept);
    connect(saveButton, &QPushButton::clicked, this, &ItemDialog::itemSaveChangeClicked);
    connect(saveButton, &QPushButton::clicked, this, &ItemDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &ItemDialog::cancelClicked);
}

void ItemDialog::itemChangeClicked()
{   
    nameText = nameLineEdit->text();
    positionText = positionComboBox->currentText();
    departmentText = departmentComboBox->currentText();
    roomNumberText = roomNumLineEdit->text();
    phoneText = phoneLineEdit->text();

    updateInterface(ChangeMode);
}

void ItemDialog::itemDeleteClicked()
{
    nameText = nameLineEdit->text();
    positionText = positionComboBox->currentText();
    departmentText = departmentComboBox->currentText();
    roomNumberText = roomNumLineEdit->text();
    phoneText = phoneLineEdit->text();

    lc->deleteContact(Contact(nameText, positionText, departmentText, roomNumberText.toInt(), phoneText));
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

    if(!lc->changeContact(newValues, oldValues)) {
        QMessageBox::information(this, tr("Неверный ввод"),
                                 tr("Введен неправильный формат данных. "
                                    "Пример: ФИО: 'Иванов Иван Иванович', "
                                    "Должность: 'Директор', "
                                    "Подразделение: 'АБВ1', "
                                    "Номер комнаты: 12345, "
                                    "Номер телефона: '+79123456789'"));
    }

    updateInterface(ViewMode);
}

void ItemDialog::cancelClicked()
{
    nameLineEdit->setText(nameText);
    positionComboBox->setCurrentText(positionText);
    departmentComboBox->setCurrentText(departmentText);
    roomNumLineEdit->setText(roomNumberText);
    phoneLineEdit->setText(phoneText);

    updateInterface(ViewMode);
}

void ItemDialog::updateInterface(ItemDialog::Mode mode)
{
    Mode currentMode = mode;

    switch (currentMode) {

    case ViewMode:

        nameLineEdit->setFocus(Qt::NoFocusReason);
        nameLineEdit->setReadOnly(true);
        positionComboBox->setDisabled(true);
        departmentComboBox->setDisabled(true);
        roomNumLineEdit->setReadOnly(true);
        phoneLineEdit->setReadOnly(true);

        changeButton->show();
        deleteButton->show();

        saveButton->hide();
        cancelButton->hide();
        break;

    case ChangeMode:

        nameLineEdit->setReadOnly(false);
        positionComboBox->setDisabled(false);
        departmentComboBox->setDisabled(false);
        roomNumLineEdit->setReadOnly(false);
        phoneLineEdit->setReadOnly(false);

        saveButton->show();
        cancelButton->show();

        changeButton->hide();
        deleteButton->hide();
        break;
    }
}
