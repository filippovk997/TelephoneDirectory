#include <QtWidgets>

#include "finddialog.h"

FindDialog::FindDialog(ListContacts* lc, QWidget* parent)
    :QDialog(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;

    QLabel* nameLabel = new QLabel("ФИО:");
    nameLineEdit = new QLineEdit;
    nameLineEdit->setFocus(Qt::OtherFocusReason);

    QLabel* departmentLabel = new QLabel("Подразделение:");
    departmentComboBox = new QComboBox;
    departmentComboBox->addItem(tr(" - "));
    departmentComboBox->addItems(lc->getDepartments());

    QHBoxLayout* buttonsHBLayout = new QHBoxLayout;

    foundButton = new QPushButton(tr("Найти"));

    buttonsHBLayout->addWidget(foundButton);

    layout->addWidget(nameLabel);
    layout->addWidget(nameLineEdit);
    layout->addWidget(departmentLabel);
    layout->addWidget(departmentComboBox);
    layout->addLayout(buttonsHBLayout);

    setLayout(layout);
    setFixedSize(QSize(210, 135));
    setWindowTitle(tr("Найти контакт"));

    connect(foundButton, &QPushButton::clicked, this, &FindDialog::findClicked);
    connect(foundButton, &QPushButton::clicked, this, &FindDialog::accept);
}

void FindDialog::findClicked()
{
    QString name = nameLineEdit->text();
    QString department = departmentComboBox->currentText();
    if (name.isEmpty() || department == " - ") {
        QMessageBox::information(this, tr("Empty field"),
            tr("Please enter a name and select a department."));
        contact = Contact();
        return;
    }
    else {
        contact.m_name = name;
        contact.m_department = department;

        nameLineEdit->clear();
        departmentComboBox->setCurrentText(" - ");
    }
}

Contact FindDialog::getFindContact()
{
    Contact relust = contact;
    contact = Contact();

    return relust;
}

