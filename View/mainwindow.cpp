#include <memory>

#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // get data
    lc = new ListContacts;
    lc->getFromDBData();

    treeContacts();
//    findWindow();
//    addWindow();

    QWidget* mainWidget = new QWidget;

    mainLayout = new QVBoxLayout;
    buttonsLayout = new QHBoxLayout;

    findMainButton = new QPushButton(tr("Искать"));
    addMainButton = new QPushButton(tr("Добавить"));
    importMainButton = new QPushButton(tr("Импорт"));
    exportMainButton = new QPushButton(tr("Экспорт"));

    findDialog = new FindDialog(lc, this);

    connect(findMainButton, &QAbstractButton::clicked, this, &MainWindow::findWindow);
    connect(addMainButton, &QAbstractButton::clicked, this, &MainWindow::addWindow);

    buttonsLayout->addWidget(findMainButton);
    buttonsLayout->addWidget(addMainButton);
    buttonsLayout->addWidget(importMainButton);
    buttonsLayout->addWidget(exportMainButton);

    mainLayout->addWidget(treeView);
    mainLayout->addLayout(buttonsLayout);

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
    setMinimumSize(600, 500);
    setWindowTitle("Телефонный справочник организации");
}

MainWindow::~MainWindow()
{
}

void MainWindow::treeContacts()
{
    model = new TreeModel(lc->toTreeModel());
    treeView = new QTreeView;
    treeView->setModel(model);

    connect(treeView, &QAbstractItemView::doubleClicked, this, &MainWindow::openItemDialogDoubleClicked);

    treeView->setColumnWidth(1, 150);
    treeView->expandAll();
}

void MainWindow::itemChangeWindow(const QModelIndex &index)
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

    itemChangeWidget = new QWidget;
    QFormLayout* layout = new QFormLayout;

    QLabel* nameLabel = new QLabel("ФИО:");
    QLineEdit* nameLineEdit = new QLineEdit(name);

    QLabel* positionLabel = new QLabel("Должность:");
    QComboBox* positionComboBox = new QComboBox;
    positionComboBox->addItem(tr(" - "));
    positionComboBox->addItems(lc->getPositions());
    positionComboBox->setCurrentText(position);

    QLabel* departmentLabel = new QLabel("Подразделение:");
    QComboBox* departmentComboBox = new QComboBox;
    departmentComboBox->addItem(tr(" - "));
    departmentComboBox->addItems(lc->getDepartments());
    departmentComboBox->setCurrentText(department);

    QLabel* roomNumLabel = new QLabel("Номер помещения:");
    QLineEdit* roomNumLineEdit = new QLineEdit(roomNumber);

    QLabel* phoneLabel = new QLabel("Номер телефона:");
    QLineEdit* phoneLineEdit = new QLineEdit(phone);

    nameLineEdit->setReadOnly(false);
    positionComboBox->setDisabled(false);
    departmentComboBox->setDisabled(false);
    roomNumLineEdit->setReadOnly(false);
    phoneLineEdit->setReadOnly(false);

    QHBoxLayout* buttonsHBLayout = new QHBoxLayout;

    QPushButton* saveButton = new QPushButton(tr("Сохранить"));
    QPushButton* cancelButton = new QPushButton(tr("Отменить"));

    connect(saveButton, &QAbstractButton::clicked, this, &MainWindow::saveItemChange);
//    connect(cancelButton, &QAbstractButton::clicked, this, &MainWindow::cancelWindow);

    buttonsHBLayout->addWidget(saveButton);
    buttonsHBLayout->addWidget(cancelButton);

    layout->addRow(nameLabel, nameLineEdit);
    layout->addRow(positionLabel, positionComboBox);
    layout->addRow(departmentLabel, departmentComboBox);
    layout->addRow(roomNumLabel, roomNumLineEdit);
    layout->addRow(phoneLabel, phoneLineEdit);
    layout->addRow(buttonsHBLayout);

    itemChangeWidget->setLayout(layout);
    itemChangeWidget->setFixedSize(QSize(350, 175));
    itemChangeWidget->setWindowTitle(name);
    itemChangeWidget->show();
}

void MainWindow::findWindow()
{
    findDialog->show();
    if (findDialog->exec() == 1) {
        Contact findContact = findDialog->getFindContact();
        QModelIndex findIndex = model->findItem(findContact.m_name,
                                                findContact.m_department, 1, 0);
        if (findIndex == QModelIndex()) {
            QMessageBox::information(this, tr("Контакт не найден"),
                tr("Извините , работник %1 из подразделения %2 не найден.")
                   .arg(findContact.m_name)
                   .arg(findContact.m_department));
            return;
        }
        else {
            findDialog->close();
            itemDialog = new ItemDialog(findIndex, lc, this);
        }
    }
}

void MainWindow::addWindow()
{
    addWidget = new QWidget;
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

    QPushButton* addButton = new QPushButton(tr("Добавить"));
    QPushButton* closeButton = new QPushButton(tr("Закрыть"));

    buttonsHBLayout->addWidget(addButton);
    buttonsHBLayout->addWidget(closeButton);

    layout->addRow(nameLabel, nameLineEdit);
    layout->addRow(positionLabel, positionComboBox);
    layout->addRow(departmentLabel, departmentComboBox);
    layout->addRow(roomNumLabel, roomNumLineEdit);
    layout->addRow(phoneLabel, phoneLineEdit);
    layout->addRow(buttonsHBLayout);

    addWidget->setLayout(layout);
    addWidget->setWindowTitle("Добавить контакт");
    addWidget->show();
}

void MainWindow::cancelWindow()
{

}

void MainWindow::openItemDialogDoubleClicked()
{
    QModelIndex index = treeView->currentIndex();
    int hierarchyLevel = 1;
    QModelIndex seekRoot = index;
    while (seekRoot.parent() != QModelIndex()) {
        seekRoot = seekRoot.parent();
        hierarchyLevel++;
    }
    if (hierarchyLevel == 1) {
        return;
    }

    itemDialog = new ItemDialog(index, lc, this);
}

void MainWindow::openItemChangeWindow()
{
//    itemWidget->close();
    itemChangeWindow(treeView->currentIndex());
}

void MainWindow::openFindWindow()
{

}

void MainWindow::openAddWindow()
{

}

void MainWindow::saveItemChange()
{

}

