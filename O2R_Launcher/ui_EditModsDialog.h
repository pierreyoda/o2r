/********************************************************************************
** Form generated from reading UI file 'EditModsDialog.ui'
**
** Created: Sat 19. Jun 17:17:43 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITMODSDIALOG_H
#define UI_EDITMODSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_EditModsDialog
{
public:
    QDialogButtonBox *buttonBox;
    QListView *listView;
    QToolButton *addButton;
    QToolButton *deleteButton;

    void setupUi(QDialog *EditModsDialog)
    {
        if (EditModsDialog->objectName().isEmpty())
            EditModsDialog->setObjectName(QString::fromUtf8("EditModsDialog"));
        EditModsDialog->resize(320, 240);
        buttonBox = new QDialogButtonBox(EditModsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 200, 301, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        listView = new QListView(EditModsDialog);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(20, 10, 241, 171));
        addButton = new QToolButton(EditModsDialog);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setGeometry(QRect(270, 10, 41, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        addButton->setIcon(icon);
        addButton->setIconSize(QSize(32, 32));
        deleteButton = new QToolButton(EditModsDialog);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setGeometry(QRect(270, 50, 41, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        deleteButton->setIcon(icon1);
        deleteButton->setIconSize(QSize(32, 32));

        retranslateUi(EditModsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), EditModsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), EditModsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(EditModsDialog);
    } // setupUi

    void retranslateUi(QDialog *EditModsDialog)
    {
        EditModsDialog->setWindowTitle(QApplication::translate("EditModsDialog", "Edit mods", 0, QApplication::UnicodeUTF8));
        addButton->setText(QString());
        deleteButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class EditModsDialog: public Ui_EditModsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITMODSDIALOG_H
