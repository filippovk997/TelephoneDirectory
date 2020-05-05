#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include <QDialog>
#include <QtWidgets>

#include "../Data/listcontacts.h"

class ItemDialog : public QDialog
{
public:
    ItemDialog(const QModelIndex& index,
               ListContacts* listContacts,
               QWidget* parent = nullptr);
    enum Mode { ViewMode, ChangeMode };

private slots:
    void itemChangeClicked();
    void itemDeleteClicked();
    void itemSaveChangeClicked();
    void cancelClicked();

private:
    void updateInterface(Mode mode);

    QDialog* itemDialog;
    QLineEdit* nameLineEdit;
    QComboBox* positionComboBox;
    QComboBox* departmentComboBox;
    QLineEdit* roomNumLineEdit;
    QLineEdit* phoneLineEdit;
    QHBoxLayout* buttonsHBLayout;
    QPushButton* changeButton;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    QPushButton* deleteButton;

    ListContacts* lc;

    QString nameText;
    QString positionText;
    QString departmentText;
    QString roomNumberText;
    QString phoneText;
};

#endif // ITEMDIALOG_H
