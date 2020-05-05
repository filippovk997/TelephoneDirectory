#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

#include "../Data/listcontacts.h"

QT_BEGIN_NAMESPACE
class QLineEdit;
class QComboBox;
class QPushButton;
QT_END_NAMESPACE
class Contact;

class FindDialog : public QDialog
{
public:
    FindDialog(ListContacts* lc, QWidget* parent = nullptr);

    Contact getFindContact();

private slots:
    void findClicked();

private:
    QLineEdit* nameLineEdit;
    QComboBox* departmentComboBox;
    QPushButton* foundButton;

    Contact contact;
};

#endif // FINDDIALOG_H
