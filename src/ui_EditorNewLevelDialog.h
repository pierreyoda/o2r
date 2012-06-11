/********************************************************************************
** Form generated from reading UI file 'EditorNewLevelDialog.ui'
**
** Created: Mon 11. Jun 17:19:51 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITORNEWLEVELDIALOG_H
#define UI_EDITORNEWLEVELDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_EditorNewLevelDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *lineEdit_name;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_4;
    QLineEdit *lineEdit_author;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBox_xSize;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QSpinBox *spinBox_ySize;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *EditorNewLevelDialog)
    {
        if (EditorNewLevelDialog->objectName().isEmpty())
            EditorNewLevelDialog->setObjectName(QString::fromUtf8("EditorNewLevelDialog"));
        EditorNewLevelDialog->setWindowModality(Qt::NonModal);
        EditorNewLevelDialog->resize(394, 106);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(EditorNewLevelDialog->sizePolicy().hasHeightForWidth());
        EditorNewLevelDialog->setSizePolicy(sizePolicy);
        EditorNewLevelDialog->setSizeGripEnabled(false);
        EditorNewLevelDialog->setModal(true);
        verticalLayout = new QVBoxLayout(EditorNewLevelDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(EditorNewLevelDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        lineEdit_name = new QLineEdit(EditorNewLevelDialog);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
        lineEdit_name->setMaxLength(50);

        horizontalLayout_2->addWidget(lineEdit_name);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_4 = new QLabel(EditorNewLevelDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        lineEdit_author = new QLineEdit(EditorNewLevelDialog);
        lineEdit_author->setObjectName(QString::fromUtf8("lineEdit_author"));
        lineEdit_author->setMaxLength(50);

        horizontalLayout_2->addWidget(lineEdit_author);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(EditorNewLevelDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        spinBox_xSize = new QSpinBox(EditorNewLevelDialog);
        spinBox_xSize->setObjectName(QString::fromUtf8("spinBox_xSize"));
        spinBox_xSize->setMinimum(5);
        spinBox_xSize->setValue(23);

        horizontalLayout->addWidget(spinBox_xSize);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(EditorNewLevelDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        spinBox_ySize = new QSpinBox(EditorNewLevelDialog);
        spinBox_ySize->setObjectName(QString::fromUtf8("spinBox_ySize"));
        spinBox_ySize->setMinimum(5);
        spinBox_ySize->setValue(23);

        horizontalLayout->addWidget(spinBox_ySize);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(EditorNewLevelDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setEnabled(true);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(EditorNewLevelDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), EditorNewLevelDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), EditorNewLevelDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(EditorNewLevelDialog);
    } // setupUi

    void retranslateUi(QDialog *EditorNewLevelDialog)
    {
        EditorNewLevelDialog->setWindowTitle(QApplication::translate("EditorNewLevelDialog", "New level", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("EditorNewLevelDialog", "Name :", 0, QApplication::UnicodeUTF8));
        lineEdit_name->setText(QApplication::translate("EditorNewLevelDialog", "New level", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("EditorNewLevelDialog", "Author", 0, QApplication::UnicodeUTF8));
        lineEdit_author->setText(QString());
        label->setText(QApplication::translate("EditorNewLevelDialog", "X size :", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("EditorNewLevelDialog", "Y size :", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EditorNewLevelDialog: public Ui_EditorNewLevelDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITORNEWLEVELDIALOG_H
