/*
    Open Rodent's Revenge is the open-source remake of Microsoft's game "Rodent's Revenge" (1991).
    Copyright (C) 2010-2012  Pierre-Yves Diallo (Pierreyoda).
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see http://www.gnu.org/licenses/.
*/

#include <QTranslator>
#include <QLibraryInfo>
#include <QFileDialog>
#include "MainWindow.hpp"
#include "GameCanvas.hpp"
#include "dialogs/AboutDialog.hpp"
#include "game/GameScreen.hpp"
#include "QsLog.h"

const QString LANGUAGE_KEY = "language";

QString MainWindow::VERSION("1.0");

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    mSettings("settings.ini", QSettings::IniFormat, this), mDefaultLanguage("en")
{
    setupUi(this);
    setFixedSize(size());
    mTranslator = new QTranslator(this), mQtTranslator = new QTranslator(this);
    loadSettings();

    // Init game canvas
    mGameCanvas = new GameCanvas(Ui_MainWindow::centralWidget, QPoint());
    Ui_MainWindow::centralWidget->setMinimumSize(GameCanvas::DEFAULT_WIDTH,
                                                 GameCanvas::DEFAULT_HEIGHT);

    // Init game screens
    mGameScreen = ScreenPtr(new GameScreen());

    // Init dialogs
    mAboutDialog = new AboutDialog(this);
    connect(mAboutDialog, SIGNAL(finished(int)), this,
            SLOT(aboutDialog_finished(int)));
}

MainWindow::~MainWindow()
{
    mGameScreen.clear();
}

void MainWindow::loadSettings()
{
    // Language
    QString language = mSettings.value(LANGUAGE_KEY, mDefaultLanguage).toString();
    if (language == "en")
        actionLanguageEnglish->setChecked(true);
    else if (language == "fr")
        actionLanguageFrench->setChecked(true);
    else
    {
        language = mDefaultLanguage;
        actionLanguageEnglish->setChecked(true);
    }
    changeLanguage(language);

    // Log
    QLOG_INFO() << "Settings loaded from" << mSettings.fileName() << ":"
                << "\n\t-language =" << language;
}

void MainWindow::saveSettings()
{
    QLOG_INFO() << "Saving settings to" << mSettings.fileName() << ":"
                << "\n\t-language =" << mCurrentLanguage;;
    mSettings.setValue(LANGUAGE_KEY, mCurrentLanguage);
}


void MainWindow::changeLanguage(const QString &id)
{
    if (id == mCurrentLanguage)
        return;
    if (id == mDefaultLanguage) // use default language
    {
        QApplication::removeTranslator(mTranslator);
        QApplication::removeTranslator(mQtTranslator);
    }
    else
    {
        mTranslator->load(QString(":translation_%1.qm").arg(id));
        mQtTranslator->load(QString(":translation_qt_%1.qm").arg(id));
        QApplication::installTranslator(mTranslator);
        QApplication::installTranslator(mQtTranslator);
    }
    mCurrentLanguage = id;
    QLOG_INFO() << "Language set to" << id << ".";
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    if (e->type() == QEvent::LanguageChange)
    {
        retranslateUi(this);
        mGameCanvas->onRetranslate();
    }
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    saveSettings();
    QLOG_INFO() << "Closing Open Rodent's Revenge.";
    QMainWindow::closeEvent(e);
}

void MainWindow::on_actionPlayLevel_triggered()
{
    // Get the level file path
    QString path = QFileDialog::getOpenFileName(this, tr("Play a level"),
                                                "", tr("Level files (*.txt *.xml)"));
    if (path.isEmpty())
        return; // aborted
    QFileInfo relativePath = QDir(QDir::currentPath()).relativeFilePath(path);
    if (relativePath.isRelative()) // make relative if possible
        path = relativePath.filePath();
    // Load and play the level
    if (mGameCanvas->loadLevel(path))
    {
        setFocus(); // needed for some reason
        if (!mGameScreen->start(mGameCanvas->loadedLevel()))
        {
            QMessageBox::critical(this, tr("Critical error"),
                                  tr("Cannot play level \"%1\"").arg(path));
            return;
        }
        mGameCanvas->setScreen(mGameScreen);
    }
    else
        QMessageBox::critical(this, tr("Critical error"),
                              tr("Cannot load level \"%1\"").arg(path));
}

void MainWindow::on_actionLanguageEnglish_triggered(bool state)
{
    if (state)
    {
        changeLanguage("en");
        actionLanguageFrench->setChecked(false);
    }
    else
        actionLanguageEnglish->setChecked(true); // reject uncheck
}

void MainWindow::on_actionLanguageFrench_triggered(bool state)
{
    if (state)
    {
        changeLanguage("fr");
        actionLanguageEnglish->setChecked(false);
    }
    else
        actionLanguageFrench->setChecked(true); // reject uncheck
}

void MainWindow::on_actionAbout_triggered()
{
    mGameCanvas->onPause();
    mAboutDialog->show();
}

void MainWindow::aboutDialog_finished(int)
{
    mGameCanvas->onResume();
}

void MainWindow::on_actionAboutQt_triggered()
{
    // Create text (comes from Qt sources)
    QString translatedTextAboutQtCaption;
    translatedTextAboutQtCaption = QMessageBox::tr(
        "<h3>About Qt</h3>"
        "<p>This program uses Qt version %1.</p>"
        ).arg(QLatin1String(QT_VERSION_STR));
    QString translatedTextAboutQtText;
    translatedTextAboutQtText = QMessageBox::tr(
        "<p>Qt is a C++ toolkit for cross-platform application "
        "development.</p>"
        "<p>Qt provides single-source portability across MS&nbsp;Windows, "
        "Mac&nbsp;OS&nbsp;X, Linux, and all major commercial Unix variants. "
        "Qt is also available for embedded devices as Qt for Embedded Linux "
        "and Qt for Windows CE.</p>"
        "<p>Qt is available under three different licensing options designed "
        "to accommodate the needs of our various users.</p>"
        "<p>Qt licensed under our commercial license agreement is appropriate "
        "for development of proprietary/commercial software where you do not "
        "want to share any source code with third parties or otherwise cannot "
        "comply with the terms of the GNU LGPL version 2.1 or GNU GPL version "
        "3.0.</p>"
        "<p>Qt licensed under the GNU LGPL version 2.1 is appropriate for the "
        "development of Qt applications (proprietary or open source) provided "
        "you can comply with the terms and conditions of the GNU LGPL version "
        "2.1.</p>"
        "<p>Qt licensed under the GNU General Public License version 3.0 is "
        "appropriate for the development of Qt applications where you wish to "
        "use such applications in combination with software subject to the "
        "terms of the GNU GPL version 3.0 or where you are otherwise willing "
        "to comply with the terms of the GNU GPL version 3.0.</p>"
        "<p>Please see <a href=\"http://qt.nokia.com/products/licensing\">qt.nokia.com/products/licensing</a> "
        "for an overview of Qt licensing.</p>"
        "<p>Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).</p>"
        "<p>Qt is a Nokia product. See <a href=\"http://qt.nokia.com/\">qt.nokia.com</a> "
        "for more information.</p>"
        );
    // Init and launch the MessageBox
    QMessageBox *aboutQtBox = new QMessageBox(this);
    aboutQtBox->setWindowTitle(tr("About Qt"));
    aboutQtBox->setText(translatedTextAboutQtCaption);
    aboutQtBox->setInformativeText(translatedTextAboutQtText);
    // Launch the MessageBox
    mGameCanvas->onPause();
    aboutQtBox->open(this, SLOT(aboutQtMessageBox_finished(int)));
}

void MainWindow::aboutQtMessageBox_finished(int)
{
    mGameCanvas->onResume();
}
