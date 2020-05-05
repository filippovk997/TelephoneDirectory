#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../TreeModel/treemodel.h"
#include "../Data/listcontacts.h"
#include "itemdialog.h"
#include "finddialog.h"

#include <QMainWindow>
#include <QTreeView>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void treeContacts();
    void itemWindow(const QModelIndex& index);
    void itemChangeWindow(const QModelIndex& index);
    void findWindow();
    void addWindow();

    QTreeView* treeView;
    TreeModel* model;
    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonsLayout;
    QPushButton* findMainButton;
    QPushButton* addMainButton;
    QPushButton* importMainButton;
    QPushButton* exportMainButton;

    ItemDialog* itemDialog;
    FindDialog* findDialog;
    QWidget* findWidget;
    QWidget* addWidget;
    QWidget* itemWidget;
    QWidget* itemChangeWidget;

    ListContacts* lc;
private slots:
    void cancelWindow();
    void openItemDialogDoubleClicked();
    void openItemChangeWindow();
    void openFindWindow();
    void openAddWindow();
    void saveItemChange();
};
#endif // MAINWINDOW_H
