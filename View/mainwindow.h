#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTreeView>

QT_BEGIN_NAMESPACE
class QFormLayout;
class QHBoxLayout;
class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;
QT_END_NAMESPACE

#include "../TreeModel/treemodel.h"
#include "../Data/listcontacts.h"
#include "itemdialog.h"
#include "finddialog.h"
#include "adddialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    void treeContacts();
    void findWindow();
    void addWindow();

    QTreeView* treeView;
    TreeModel* model;
    QPushButton* findMainButton;
    QPushButton* addMainButton;
    QPushButton* importMainButton;
    QPushButton* exportMainButton;

    ItemDialog* itemDialog;
    FindDialog* findDialog;
    AddDialog* addDialog;

    ListContacts* lc;

private slots:
    void openItemDialogDoubleClicked();

};
#endif // MAINWINDOW_H
