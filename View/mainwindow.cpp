#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    lc = new ListContacts;

    contactsTree();

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
    connect(importMainButton, &QAbstractButton::clicked, this, &MainWindow::importFromXml);
    connect(exportMainButton, &QAbstractButton::clicked, this, &MainWindow::exportToXml);
}

void MainWindow::contactsTree()
{
    model = new TreeModel(lc->toTreeModel());
    treeView = new QTreeView;
    treeView->setModel(model);

    connect(treeView, &QAbstractItemView::doubleClicked, this, &MainWindow::openItemDialogDoubleClicked);

    treeView->setColumnWidth(1, 150);
    treeView->expandAll();
}

void MainWindow::updateTree()
{
    model->updateData(lc->toTreeModel());
    treeView->reset();
    treeView->expandAll();
}

void MainWindow::findWindow()
{
    findDialog->show();
    if (findDialog->exec() == 1) {
        Contact findContact = findDialog->getFindContact();
        if (findContact == Contact()) {
            return;
        }
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
    if (addDialog->exec() == 1) {
        Contact addContact = addDialog->getAddContact();
        if (addContact == Contact()) {
            return;
        }
        lc->addContact(addContact);
        updateTree();
    }
}

void MainWindow::exportToXml()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Export contacts to file xml"), "",
        tr("xml (*.xml);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else {
        lc->toXml(fileName);
    }

//        QFile file(fileName);
//        if (!file.open(QIODevice::WriteOnly)) {
//            QMessageBox::information(this, tr("Unable to export to xml"),
//                file.errorString());
//            return;
//        }

}

void MainWindow::importFromXml()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Import contacts from file xml"), "",
        tr("xml (*.xml);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else {
        lc->fromXml(fileName);
        updateTree();
    }

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
    connect(itemDialog, &ItemDialog::accepted, this, &MainWindow::updateTree);
}
