#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include <QDialog>
#include <QtWidgets>

#include "../Data/listcontacts.h"

class ItemDialog : public QDialog
{
public:
    ItemDialog(const QModelIndex& index,
               ListContacts* lc,
               QWidget* parent = nullptr);

    ItemDialog* createItemDialog(const QModelIndex& index,
                                 ListContacts* lc,
                                 QWidget* parent = nullptr);

private slots:
    void itemChangeClicked();

private:
    QDialog* itemDialog;
    QLineEdit* nameLineEdit;
    QComboBox* positionComboBox;
    QComboBox* departmentComboBox;
    QLineEdit* roomNumLineEdit;
    QLineEdit* phoneLineEdit;
    QPushButton* changeButton;
    QPushButton* deleteButton;
    QPushButton* closeButton;
};

#endif // ITEMDIALOG_H
