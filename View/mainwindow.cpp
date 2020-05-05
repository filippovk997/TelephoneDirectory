#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    lc = new ListContacts;
    lc->getFromDBData();

    treeContacts();

    QWidget* mainWidget = new QWidget;

    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* buttonsLayout = new QHBoxLayout;

    findMainButton = new QPushButton(tr("Искать"));
    addMainButton = new QPushButton(tr("Добавить"));
    importMainButton = new QPushButton(tr("Импорт"));
    exportMainButton = new QPushButton(tr("Экспорт"));

    findDialog = new FindDialog(lc, this);
    addDialog = new AddDialog(lc, this);

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

    connect(findMainButton, &QAbstractButton::clicked, this, &MainWindow::findWindow);
    connect(addMainButton, &QAbstractButton::clicked, this, &MainWindow::addWindow);
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
    addDialog->show();
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
