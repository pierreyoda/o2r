/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Thu 24. Jun 12:33:28 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionAbout;
    QAction *actionAboutQt;
    QAction *actionFrench;
    QAction *actionEnglish;
    QAction *actionLocation;
    QWidget *mainWidget;
    QWidget *layoutWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QLineEdit *browseEdit;
    QToolButton *browseButton;
    QSpacerItem *horizontalSpacer_4;
    QGridLayout *gridLayout_2;
    QPushButton *editorButton;
    QPushButton *gameButton;
    QGroupBox *groupBox;
    QLabel *label_3;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *defineCatsNumberBox;
    QSpinBox *numberOfCatsSpinBox;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *defineRWNumberBox;
    QSpinBox *numberOfRWSpinBox;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *defineLivesNumberBox;
    QSpinBox *numberOfLivesSpinBox;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox_2;
    QCheckBox *emptyLevelBox;
    QSpinBox *levelXSpinBox;
    QSpinBox *levelYSpinBox;
    QLabel *label_4;
    QLabel *label_5;
    QCheckBox *noWarningAtSaveBox;
    QLabel *label_6;
    QPushButton *resetButton;
    QGroupBox *groupBox_3;
    QLineEdit *browseLesEdit;
    QToolButton *browseLesButton;
    QLabel *label;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *debugModeBox;
    QCheckBox *enableVSyncBox;
    QCheckBox *adjustWindowSizeBox;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *defineFpsLimitBox;
    QSpinBox *fpsLimitSpinBox;
    QPushButton *editModsButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuLanguage;
    QMenu *menuGame;
    QMenu *menu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(570, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAboutQt = new QAction(MainWindow);
        actionAboutQt->setObjectName(QString::fromUtf8("actionAboutQt"));
        actionFrench = new QAction(MainWindow);
        actionFrench->setObjectName(QString::fromUtf8("actionFrench"));
        actionFrench->setCheckable(true);
        actionEnglish = new QAction(MainWindow);
        actionEnglish->setObjectName(QString::fromUtf8("actionEnglish"));
        actionEnglish->setCheckable(true);
        actionLocation = new QAction(MainWindow);
        actionLocation->setObjectName(QString::fromUtf8("actionLocation"));
        mainWidget = new QWidget(MainWindow);
        mainWidget->setObjectName(QString::fromUtf8("mainWidget"));
        layoutWidget = new QWidget(mainWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 571, 521));
        mainLayout = new QVBoxLayout(layoutWidget);
        mainLayout->setSpacing(6);
        mainLayout->setContentsMargins(11, 11, 11, 11);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalSpacer = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Fixed);

        horizontalLayout->addItem(verticalSpacer);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        browseEdit = new QLineEdit(layoutWidget);
        browseEdit->setObjectName(QString::fromUtf8("browseEdit"));

        horizontalLayout->addWidget(browseEdit);

        browseButton = new QToolButton(layoutWidget);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));

        horizontalLayout->addWidget(browseButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        mainLayout->addLayout(horizontalLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        editorButton = new QPushButton(layoutWidget);
        editorButton->setObjectName(QString::fromUtf8("editorButton"));

        gridLayout_2->addWidget(editorButton, 0, 2, 1, 1);

        gameButton = new QPushButton(layoutWidget);
        gameButton->setObjectName(QString::fromUtf8("gameButton"));

        gridLayout_2->addWidget(gameButton, 0, 0, 1, 1);

        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 20, 121, 16));
        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 40, 171, 81));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        defineCatsNumberBox = new QCheckBox(layoutWidget1);
        defineCatsNumberBox->setObjectName(QString::fromUtf8("defineCatsNumberBox"));

        horizontalLayout_2->addWidget(defineCatsNumberBox);

        numberOfCatsSpinBox = new QSpinBox(layoutWidget1);
        numberOfCatsSpinBox->setObjectName(QString::fromUtf8("numberOfCatsSpinBox"));
        numberOfCatsSpinBox->setSuffix(QString::fromUtf8(""));
        numberOfCatsSpinBox->setMaximum(999);

        horizontalLayout_2->addWidget(numberOfCatsSpinBox);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        defineRWNumberBox = new QCheckBox(layoutWidget1);
        defineRWNumberBox->setObjectName(QString::fromUtf8("defineRWNumberBox"));

        horizontalLayout_3->addWidget(defineRWNumberBox);

        numberOfRWSpinBox = new QSpinBox(layoutWidget1);
        numberOfRWSpinBox->setObjectName(QString::fromUtf8("numberOfRWSpinBox"));
        numberOfRWSpinBox->setSuffix(QString::fromUtf8(""));
        numberOfRWSpinBox->setMaximum(999);

        horizontalLayout_3->addWidget(numberOfRWSpinBox);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        defineLivesNumberBox = new QCheckBox(layoutWidget1);
        defineLivesNumberBox->setObjectName(QString::fromUtf8("defineLivesNumberBox"));

        horizontalLayout_4->addWidget(defineLivesNumberBox);

        numberOfLivesSpinBox = new QSpinBox(layoutWidget1);
        numberOfLivesSpinBox->setObjectName(QString::fromUtf8("numberOfLivesSpinBox"));
        numberOfLivesSpinBox->setSuffix(QString::fromUtf8(""));
        numberOfLivesSpinBox->setMaximum(999);

        horizontalLayout_4->addWidget(numberOfLivesSpinBox);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 130, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_2, 1, 1, 1, 1);

        groupBox_2 = new QGroupBox(layoutWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        emptyLevelBox = new QCheckBox(groupBox_2);
        emptyLevelBox->setObjectName(QString::fromUtf8("emptyLevelBox"));
        emptyLevelBox->setGeometry(QRect(10, 50, 111, 21));
        levelXSpinBox = new QSpinBox(groupBox_2);
        levelXSpinBox->setObjectName(QString::fromUtf8("levelXSpinBox"));
        levelXSpinBox->setGeometry(QRect(10, 90, 42, 22));
        levelXSpinBox->setMinimum(5);
        levelXSpinBox->setMaximum(999);
        levelYSpinBox = new QSpinBox(groupBox_2);
        levelYSpinBox->setObjectName(QString::fromUtf8("levelYSpinBox"));
        levelYSpinBox->setGeometry(QRect(60, 90, 42, 22));
        levelYSpinBox->setMinimum(5);
        levelYSpinBox->setMaximum(999);
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 70, 46, 13));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(60, 70, 46, 13));
        noWarningAtSaveBox = new QCheckBox(groupBox_2);
        noWarningAtSaveBox->setObjectName(QString::fromUtf8("noWarningAtSaveBox"));
        noWarningAtSaveBox->setGeometry(QRect(10, 0, 261, 51));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/warning"), QSize(), QIcon::Normal, QIcon::Off);
        noWarningAtSaveBox->setIcon(icon1);
        noWarningAtSaveBox->setIconSize(QSize(16, 13));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(0, 110, 151, 31));
        resetButton = new QPushButton(groupBox_2);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(110, 90, 71, 23));

        gridLayout_2->addWidget(groupBox_2, 1, 2, 1, 1);


        mainLayout->addLayout(gridLayout_2);

        groupBox_3 = new QGroupBox(layoutWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        browseLesEdit = new QLineEdit(groupBox_3);
        browseLesEdit->setObjectName(QString::fromUtf8("browseLesEdit"));
        browseLesEdit->setGeometry(QRect(10, 40, 378, 20));
        browseLesButton = new QToolButton(groupBox_3);
        browseLesButton->setObjectName(QString::fromUtf8("browseLesButton"));
        browseLesButton->setGeometry(QRect(400, 40, 25, 20));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 111, 16));
        layoutWidget2 = new QWidget(groupBox_3);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 60, 181, 93));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        debugModeBox = new QCheckBox(layoutWidget2);
        debugModeBox->setObjectName(QString::fromUtf8("debugModeBox"));

        verticalLayout_2->addWidget(debugModeBox);

        enableVSyncBox = new QCheckBox(layoutWidget2);
        enableVSyncBox->setObjectName(QString::fromUtf8("enableVSyncBox"));

        verticalLayout_2->addWidget(enableVSyncBox);

        adjustWindowSizeBox = new QCheckBox(layoutWidget2);
        adjustWindowSizeBox->setObjectName(QString::fromUtf8("adjustWindowSizeBox"));

        verticalLayout_2->addWidget(adjustWindowSizeBox);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        defineFpsLimitBox = new QCheckBox(layoutWidget2);
        defineFpsLimitBox->setObjectName(QString::fromUtf8("defineFpsLimitBox"));

        horizontalLayout_5->addWidget(defineFpsLimitBox);

        fpsLimitSpinBox = new QSpinBox(layoutWidget2);
        fpsLimitSpinBox->setObjectName(QString::fromUtf8("fpsLimitSpinBox"));
        fpsLimitSpinBox->setSuffix(QString::fromUtf8(""));
        fpsLimitSpinBox->setMinimum(0);
        fpsLimitSpinBox->setMaximum(99999);

        horizontalLayout_5->addWidget(fpsLimitSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_5);

        editModsButton = new QPushButton(groupBox_3);
        editModsButton->setObjectName(QString::fromUtf8("editModsButton"));
        editModsButton->setGeometry(QRect(200, 70, 131, 31));

        mainLayout->addWidget(groupBox_3);

        MainWindow->setCentralWidget(mainWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 570, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuLanguage = new QMenu(menuFile);
        menuLanguage->setObjectName(QString::fromUtf8("menuLanguage"));
        menuGame = new QMenu(menuFile);
        menuGame->setObjectName(QString::fromUtf8("menuGame"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menu->menuAction());
        menuFile->addAction(menuGame->menuAction());
        menuFile->addAction(menuLanguage->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuLanguage->addAction(actionEnglish);
        menuLanguage->addAction(actionFrench);
        menuGame->addAction(actionLocation);
        menu->addAction(actionAbout);
        menu->addAction(actionAboutQt);

        retranslateUi(MainWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Open Rodent's Revenge - Official Launcher", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionAboutQt->setText(QApplication::translate("MainWindow", "About Qt", 0, QApplication::UnicodeUTF8));
        actionFrench->setText(QApplication::translate("MainWindow", "Fran\303\247ais", 0, QApplication::UnicodeUTF8));
        actionEnglish->setText(QApplication::translate("MainWindow", "English", 0, QApplication::UnicodeUTF8));
        actionLocation->setText(QApplication::translate("MainWindow", "Location", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Level file :", 0, QApplication::UnicodeUTF8));
        browseButton->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        editorButton->setText(QApplication::translate("MainWindow", "Editor", 0, QApplication::UnicodeUTF8));
        gameButton->setText(QApplication::translate("MainWindow", "Game", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Game Settings", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Set number of...", 0, QApplication::UnicodeUTF8));
        defineCatsNumberBox->setText(QApplication::translate("MainWindow", "cats :", 0, QApplication::UnicodeUTF8));
        numberOfCatsSpinBox->setPrefix(QString());
        defineRWNumberBox->setText(QApplication::translate("MainWindow", "random walls :", 0, QApplication::UnicodeUTF8));
        numberOfRWSpinBox->setPrefix(QString());
        defineLivesNumberBox->setText(QApplication::translate("MainWindow", "lives (player)", 0, QApplication::UnicodeUTF8));
        numberOfLivesSpinBox->setPrefix(QString());
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Editor Settings", 0, QApplication::UnicodeUTF8));
        emptyLevelBox->setText(QApplication::translate("MainWindow", "Empty level", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        levelXSpinBox->setToolTip(QApplication::translate("MainWindow", "Horizontal size (width)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        levelYSpinBox->setToolTip(QApplication::translate("MainWindow", "Vertical size (height)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("MainWindow", "X size", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Y size", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        noWarningAtSaveBox->setToolTip(QApplication::translate("MainWindow", "WARNING : can be dangerous, caution when it is enabled", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        noWarningAtSaveBox->setText(QApplication::translate("MainWindow", "No warning at save", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "+ See game settings", 0, QApplication::UnicodeUTF8));
        resetButton->setText(QApplication::translate("MainWindow", "Reset", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Global Settings", 0, QApplication::UnicodeUTF8));
        browseLesButton->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "LES file (*.xml)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        debugModeBox->setToolTip(QApplication::translate("MainWindow", "FPS number will be print (F12 to toggle in game)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        debugModeBox->setText(QApplication::translate("MainWindow", "Debug mode", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        enableVSyncBox->setToolTip(QApplication::translate("MainWindow", "Wait for vertical synchronisation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        enableVSyncBox->setText(QApplication::translate("MainWindow", "Enable V.Sync.", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        adjustWindowSizeBox->setToolTip(QApplication::translate("MainWindow", "The window will expand to adjust to the level size (limited by screen's resolution)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        adjustWindowSizeBox->setText(QApplication::translate("MainWindow", "Adjust window size", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        defineFpsLimitBox->setToolTip(QApplication::translate("MainWindow", "This will limit the FPS (0 = no limit)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        defineFpsLimitBox->setText(QApplication::translate("MainWindow", "Set FPS  limit :", 0, QApplication::UnicodeUTF8));
        fpsLimitSpinBox->setPrefix(QString());
        editModsButton->setText(QApplication::translate("MainWindow", "Edit mods to use", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "Launcher", 0, QApplication::UnicodeUTF8));
        menuLanguage->setTitle(QApplication::translate("MainWindow", "Language", 0, QApplication::UnicodeUTF8));
        menuGame->setTitle(QApplication::translate("MainWindow", "Game", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "?", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
