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

    QHBoxLayout* buttonsHBLayout = new QHBoxLayout;

    changeButton = new QPushButton(tr("Изменить"));
    deleteButton = new QPushButton(tr("Удалить"));
    closeButton = new QPushButton(tr("Закрыть"));

    connect(changeButton, &QPushButton::clicked, this, &ItemDialog::itemChangeClicked);

    buttonsHBLayout->addWidget(changeButton);
    buttonsHBLayout->addWidget(deleteButton);
    buttonsHBLayout->addWidget(closeButton);

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
}

void ItemDialog::itemChangeClicked()
{
    nameLineEdit->setReadOnly(false);
    positionComboBox->setDisabled(false);
    departmentComboBox->setDisabled(false);
    roomNumLineEdit->setReadOnly(false);
    phoneLineEdit->setReadOnly(false);

    changeButton->setText(tr("Сохранить"));
    deleteButton->setText(tr("Отменить"));
}
