#include <QTranslator>
#include <QLibraryInfo>
#include <QFileDialog>
#include <QDesktopWidget>
#include "MainWindow.hpp"
#include "GameCanvas.hpp"
#include "dialogs/AboutDialog.hpp"
#include "dialogs/EditorLevelPropertiesDialog.hpp"
#include "dialogs/ModsDialog.hpp"
#include "game/GameScreen.hpp"
#include "game/EditorScreen.hpp"
#include "managers/FilespathProvider.hpp"
#include "factories/TiledMapFactory.hpp"
#include "QsLog.h"

const int STATUS_BAR_MSG_TIME = 2000;
const QString LANGUAGE_KEY = "language";
const QString MODS_KEY = "mods";
const char *PROPERTY_CHAR = "char";

QString MainWindow::VERSION("1.0");

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    mSettings("settings.ini", QSettings::IniFormat, this), mDefaultLanguage("en")
{
    setupUi(this);
    mTranslator = new QTranslator(this), mQtTranslator = new QTranslator(this);
    initManagers();
    loadSettings();
    FilespathProvider::refreshAssetsList();
    switchToGameMode(NONE);

    // Init editor bar (make it "unhideable" from context menus and populate it)
    prevSelectedAction = 0;
    editorBar->setContextMenuPolicy(Qt::PreventContextMenu);
    setContextMenuPolicy(Qt::PreventContextMenu);
    populateEditorBar();

    // Init game canvas
    mGameCanvas = new GameCanvas(Ui_MainWindow::centralWidget, QPoint());
    setCentralWidget(mGameCanvas);
    connect(mGameCanvas, SIGNAL(requestResize(int,int)),
            this, SLOT(resizeCanvas(int,int)));

    // Init game screens
    mGameScreen = ScreenPtr(new GameScreen(*mGameCanvas));
    mEditorScreen = ScreenPtr(new EditorScreen(*mGameCanvas));

    // Init dialogs
    mAboutDialog = new AboutDialog(this);
    connect(mAboutDialog, SIGNAL(finished(int)), this,
            SLOT(aboutDialog_finished(int)));
}

MainWindow::~MainWindow()
{
    mGameScreen.clear();
    mEditorScreen.clear();
    prevSelectedAction = 0;
}

void MainWindow::initManagers()
{
    // Initialize FilespathProvider
    FilespathProvider::setModsLocation("mods/");
    FilespathProvider::setMainModFolder("original");
    QStringList nameFilters;
    nameFilters << "*.bmp" << "*.dds" << "*.jpg" << "*.png" << "*.tga" << "*.psd";
    FilespathProvider::setAssetsNameFilters(nameFilters);

    // Set up default tiles
    TilesTypesManager::setType('0', "void.png", TileInfo::TYPE_GROUND);
    TilesTypesManager::setType('1', "block.png", TileInfo::TYPE_BLOCK);
    TilesTypesManager::setType('2', "wall.png", TileInfo::TYPE_WALL);
}

void MainWindow::populateEditorBar()
{
    // Add "Mouse" action (place mouse)
    QIcon mouseIcon(FilespathProvider::assetPathFromAlias("mouse.png"));
    QAction *mouseAction = editorBar->addAction(mouseIcon, tr("Mouse"));
    if (mouseAction == 0)
    {
        QLOG_ERROR() << "Cannot populate the editor toolbar.";
        return;
    }
    mouseAction->setStatusTip(tr("Place the mouse start position"));
    mouseAction->setProperty(PROPERTY_CHAR, EditorScreen::MOUSE_POS_CHAR);
    mouseAction->setCheckable(true);

    // Add all available tiles
    const QMap<QChar, TileInfo> &tilesTypes = TilesTypesManager::getMap();
    QMapIterator<QChar, TileInfo> it(tilesTypes);
    while (it.hasNext())
    {
        it.next();
        const TileInfo &tileInfo = it.value();
        addEditorBarAction(it.key(), tileInfo.type,
                           FilespathProvider::assetPathFromAlias(
                               tileInfo.textureAlias));
    }
}

void MainWindow::addEditorBarAction(const QChar &c, const QString &text,
                                    const QString &iconPath)
{
    QAction *added = editorBar->addAction(QIcon(iconPath),
                                          tr("Tile ID : '%1'").arg(c));
    if (added == 0)
        return;
    if (text == TileInfo::TYPE_WALL)
        added->setStatusTip(tr("Tile type : wall"));
    else if (text == TileInfo::TYPE_BLOCK)
        added->setStatusTip(tr("Tile type : block"));
    else if (text == TileInfo::TYPE_GROUND)
        added->setStatusTip(tr("Tile type : ground"));
    added->setProperty(PROPERTY_CHAR, c);
    added->setCheckable(true);
}

void MainWindow::switchToGameMode(GAME_MODE mode)
{
    if (mode == PLAY)
    {
        toggleEditorActions(false);
        toggleGameActions(true);
    }
    else if (mode == EDIT)
    {
        toggleGameActions(false);
        toggleEditorActions(true);
    }
    else
    {
        toggleGameActions(false);
        toggleEditorActions(false);
    }
}

void MainWindow::toggleGameActions(bool enable)
{
    // Enable or disable all game-related actions
    actionRestartLevel->setEnabled(enable);
    actionChangeCampaignLevel->setEnabled(enable);
    actionEditorCurrentLevel->setEnabled(enable);
}

void MainWindow::toggleEditorActions(bool enable)
{
    // Enable or disable all editor-related actions
    actionEditorSaveLevel->setEnabled(enable);
    actionEditorSaveLevelAs->setEnabled(enable);
    actionEditorLevelProperties->setEnabled(enable);
    // Also show/hide editor bar
    editorBar->setVisible(enable);
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

    // Mods
    const QString mods = mSettings.value(MODS_KEY, "").toString();
    mModsList = mods.split(";", QString::SkipEmptyParts);

    // Log
    QLOG_INFO() << "Settings loaded from" << mSettings.fileName() << ":"
                << "\n\t-language =" << language
                << "\n\t-mods =" << mods;

    // Apply settings
    changeLanguage(language);
    if (!mModsList.isEmpty())
    {
        FilespathProvider::addMods(mModsList, true);
        mModsList = FilespathProvider::modsList(); // all invalid mods have been deleted in addMods()
    }
}

void MainWindow::saveSettings()
{
    const QString mods = mModsList.join(";");
    QLOG_INFO() << "Saving settings to" << mSettings.fileName() << ":"
                << "\n\t-language =" << mCurrentLanguage
                << "\n\t-mods =" << mods;
    mSettings.setValue(LANGUAGE_KEY, mCurrentLanguage);
    mSettings.setValue(MODS_KEY, mods);
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

void MainWindow::adjustSizeToCanvas()
{
    setFixedSize(mGameCanvas->width(), mGameCanvas->height()
                 + Ui_MainWindow::menuBar->height()
                 + Ui_MainWindow::statusBar->height()
                 + (editorBar->isVisible() ? editorBar->height() : 0));
}

int MainWindow::execModalDialog(QDialog &dialog)
{
    mGameCanvas->onPause();
    const int result = dialog.exec();
    mGameCanvas->onResume();
    return result;
}

void MainWindow::on_editorBar_visibilityChanged(bool visible)
{
    adjustSizeToCanvas();
}

void MainWindow::on_editorBar_actionTriggered(QAction *action)
{
    static_cast<EditorScreen*>(mEditorScreen.data())->setPlaceableChar(
                action->property(PROPERTY_CHAR).toChar());
    action->setChecked(true);
    if (prevSelectedAction != 0)
        prevSelectedAction->setChecked(false);
    prevSelectedAction = action;
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

void MainWindow::resizeCanvas(int w, int h)
{
    const QRect screen = QApplication::desktop()->availableGeometry(this);
    if (w >= screen.width() || h >= screen.height())
    {
        QMessageBox::warning(this, tr("Size problem"),
                             tr("Level size is bigger than screen size, level cannot be displayed properly."));
        mGameCanvas->setFixedSize(GameCanvas::DEFAULT_WIDTH,
                                  GameCanvas::DEFAULT_HEIGHT);
        adjustSizeToCanvas();
        return;
    }
    mGameCanvas->setFixedSize(w, h);
    adjustSizeToCanvas();
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
        if (!mGameCanvas->setScreen(mGameScreen))
        {
            QMessageBox::critical(this, tr("Critical error"),
                                  tr("Cannot play level \"%1\".").arg(path));
            switchToGameMode(NONE);
            mGameCanvas->setScreen(ScreenPtr());
            return;
        }
        switchToGameMode(PLAY);
    }
    else
        QMessageBox::critical(this, tr("Critical error"),
                              tr("Cannot load level \"%1\".").arg(path));
}

void MainWindow::on_actionEditorNewLevel_triggered()
{
    // Launch an EditorLevelPropertiesDialog
    EditorLevelPropertiesDialog *newLevelDialog = new EditorLevelPropertiesDialog(
                0, this);
    newLevelDialog->setWindowTitle(tr("New level properties"));
    const int result = execModalDialog(*newLevelDialog);
    if (result == QDialog::Rejected)
        return;
    // Init the new level
    const unsigned int sizeX = newLevelDialog->levelSizeX(),
            sizeY = newLevelDialog->levelSizeY();
    LevelInfo info;
    info.name = newLevelDialog->levelName(),
            info.author = newLevelDialog->levelAuthor();
    info.mousePosX = static_cast<unsigned int>(sizeX / 2),
            info.mousePosY = static_cast<unsigned int>(sizeY / 2);
    TiledMapPtr newLevel(new TiledMap(sizeX, sizeY, info));
    // Launch the editor screen
    if (!newLevel->buildMap())
    {
        QMessageBox::critical(this, tr("Critical error"),
                              tr("Cannot create level \"%1\".").arg(info.name));
        switchToGameMode(NONE);
        mGameCanvas->setScreen(ScreenPtr());
        return;
    }
    mGameCanvas->setLevel(newLevel);
    mGameCanvas->setScreen(mEditorScreen, true);
    switchToGameMode(EDIT);
}

void MainWindow::on_actionEditorExistingLevel_triggered()
{
    // Get the level file path
    QString path = QFileDialog::getOpenFileName(this, tr("Edit an existing level"),
                                                "", tr("Level files (*.txt *.xml)"));
    if (path.isEmpty())
        return; // aborted
    QFileInfo relativePath = QDir(QDir::currentPath()).relativeFilePath(path);
    if (relativePath.isRelative()) // make relative if possible
        path = relativePath.filePath();
    // Load and edit the level
    if (mGameCanvas->loadLevel(path))
    {
        setFocus(); // needed for some reason
        if (!mGameCanvas->setScreen(mEditorScreen))
        {
            QMessageBox::critical(this, tr("Critical error"),
                                  tr("Cannot edit level \"%1\".").arg(path));
            switchToGameMode(NONE);
            mGameCanvas->setScreen(ScreenPtr());
            return;
        }
        switchToGameMode(EDIT);

        // User feedback (status bar message)
        Ui_MainWindow::statusBar->showMessage(tr("Level loaded."), STATUS_BAR_MSG_TIME);
    }
    else
        QMessageBox::critical(this, tr("Loading error"),
                              tr("Cannot load level \"%1\".").arg(path));
}

void MainWindow::on_actionEditorCurrentLevel_triggered()
{
    // Check for current level validity and start editing it if possible
    if (!mGameCanvas->level().isNull() && mGameCanvas->setScreen(mEditorScreen))
        switchToGameMode(EDIT);
    else
    {
        QMessageBox::critical(this, tr("Critical error"),
                              tr("Cannot edit the current level."));
        switchToGameMode(NONE);
    }

}

void MainWindow::on_actionEditorSaveLevel_triggered()
{   
    // Level check
    TiledMapPtr level = mGameCanvas->level();
    if (level.isNull())
    {
        QMessageBox::critical(this, tr("Saving error"),
                              tr("Empty level, cannot save it."));
        return;
    }

    // If no filepath specified : save as...
    const QString filepath = level->info().filePath;
    if (filepath.isEmpty())
    {
        on_actionEditorSaveLevelAs_triggered();
        return;
    }
    // Else, save the level
    else if (!TiledMapFactory::saveLevel(*level, filepath))
        QMessageBox::critical(this, tr("Saving error"),
                              tr("Error while saving the level as \"%1\".").arg(filepath));

    // User feedback (status bar message)
    Ui_MainWindow::statusBar->showMessage(tr("Level saved."), STATUS_BAR_MSG_TIME);
}

void MainWindow::on_actionEditorSaveLevelAs_triggered()
{
    // Level check
    TiledMapPtr level = mGameCanvas->level();
    if (level.isNull())
    {
        QMessageBox::critical(this, tr("Saving error"),
                              tr("Empty level, cannot save it."));
        return;
    }

    // Get the level file path
    const QString currentPath = level->info().filePath;
    QString selectedFilter = tr("Level new format (*.xml)");
    if (!currentPath.isEmpty() && currentPath.section('.', -1) != "xml")
        selectedFilter = tr("Level old format (*.txt)");
    QString path = QFileDialog::getSaveFileName(this, tr("Save level as"),
                                                currentPath,
                                                tr("Level new format (*.xml);;Level old format (*.txt)"),
                                                &selectedFilter);
    if (path.isEmpty())
        return; // aborted

    // Save the level
    if (!TiledMapFactory::saveLevel(*level, path))
        QMessageBox::critical(this, tr("Saving error"),
                              tr("Error while saving the level as \"%1\".").arg(path));

    // User feedback (status bar message)
    Ui_MainWindow::statusBar->showMessage(tr("Level saved."), STATUS_BAR_MSG_TIME);

}

void MainWindow::on_actionEditorLevelProperties_triggered()
{
    // Level check
    TiledMapPtr level = mGameCanvas->level();
    if (level.isNull())
    {
        QMessageBox::critical(this, tr("Critical error"),
                              tr("Empty level, cannot edit its properties."));
        return;
    }

    // Launch an EditorLevelPropertiesDialog
    EditorLevelPropertiesDialog *propertiesDialog = new EditorLevelPropertiesDialog(
                level.data(), this);
    const int oldX = level->sizeX(), oldY = level->sizeY();
    const int result = execModalDialog(*propertiesDialog);
    if (result == QDialog::Rejected)
        return;
    // Apply LevelInfo changes
    level->info().name = propertiesDialog->levelName();
    level->info().author = propertiesDialog->levelAuthor();
    level->info().mouseRandomPos = propertiesDialog->mouseRandomPos();
    // Apply level size changes (warning if needed)
    const int newX = propertiesDialog->levelSizeX(), newY = propertiesDialog->levelSizeY();
    if (newX == oldX && newY == oldY)
        return;
    if (newX < oldX || newY < oldY) // reducing level size : ask for confirmation
    {
        int result = QMessageBox::question(this, tr("Warning"),
                                           tr("Do you really want to reduce the size of the level? The affected tiles will be lost for good."),
                                           QMessageBox::Yes | QMessageBox::No);
        if (result != QMessageBox::Yes)
            return;
    }
    level->resizeX(newX);
    level->resizeY(newY);
    if (!level->buildMap())
    {
        QLOG_ERROR() << "build error";
    }
    mGameCanvas->adjustSizeToLevel();
}

void MainWindow::on_actionEditMods_triggered()
{
    // Launch a ModsDialog for result
    ModsDialog *modsDialog = new ModsDialog(mModsList, this);
    const int result = execModalDialog(*modsDialog);
    if (result == QDialog::Rejected)
        return;
    // Keep changes and print status bar message if changes were made
    const QStringList &newModsList = modsDialog->modsList();
    if (mModsList == newModsList)
        return;
    mModsList = modsDialog->modsList();
    Ui_MainWindow::statusBar->showMessage(tr("Mods list changed."), STATUS_BAR_MSG_TIME);
    modsDialog->deleteLater();
    // Reload textures
    FilespathProvider::addMods(mModsList, true);
    FilespathProvider::refreshAssetsList();
    mGameCanvas->reloadTextures();
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
