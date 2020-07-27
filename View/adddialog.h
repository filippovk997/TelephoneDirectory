#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

#include "../Data/listcontacts.h"

QT_BEGIN_NAMESPACE
class QFormLayout;
class QHBoxLayout;
class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;
QT_END_NAMESPACE
class Contact;

class AddDialog : public QDialog
{
public:
    AddDialog(ListContacts* listContacts,
              QWidget* parent = nullptr);

    Contact getAddContact();
private slots:
    void addClicked();

private:
    QLineEdit* nameLineEdit;
    QComboBox* positionComboBox;
    QComboBox* departmentComboBox;
    QLineEdit* roomNumLineEdit;
    QLineEdit* phoneLineEdit;
    QPushButton* addButton;

    Contact contact;
    ListContacts* lc;
};

#endif // ADDDIALOG_H
