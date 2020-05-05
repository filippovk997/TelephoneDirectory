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

class AddDialog : public QDialog
{
public:
    AddDialog(ListContacts* listContacts,
              QWidget* parent = nullptr);

private:
    QPushButton* addButton;

    ListContacts* lc;
};

#endif // ADDDIALOG_H
