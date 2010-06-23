#include <QProcess>
#include <QFileDialog>
#include <QLibraryInfo>
#include <QMessageBox>
#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    defaultLanguage("en"), settings("settings.ini", QSettings::IniFormat, this),
    language(defaultLanguage)
{
    setupUi(this);
    mainWidget->setLayout(mainLayout);
    setFixedSize(480, 420);
    browseEdit->setText(tr("Choose a level file"));
    editModsDialog = new EditModsDialog(gameMainFolder, this);
    aboutDialog = new AboutDialog(this);
    loadSettings();

    connect(defineCatsNumberBox, SIGNAL(toggled(bool)), numberOfCatsSpinBox,
            SLOT(setEnabled(bool)));
    connect(defineRWNumberBox, SIGNAL(toggled(bool)), numberOfRWSpinBox,
            SLOT(setEnabled(bool)));
    connect(defineLivesNumberBox, SIGNAL(toggled(bool)), numberOfLivesSpinBox,
            SLOT(setEnabled(bool)));
    connect(defineFpsLimitBox, SIGNAL(toggled(bool)), fpsLimitSpinBox,
            SLOT(setEnabled(bool)));
    connect(editModsDialog, SIGNAL(rejected()), editModsDialog,
            SLOT(restoreListFromBackup()));
}

void MainWindow::launch_O2R(const bool &game)
{
    QProcess *process = new QProcess(this);
    QString program = gameMainFolder + "/OpenRodentsRevenge.exe";
    QStringList arguments;
    arguments << "-LE" << "-vsync=" + QString::number(enableVSyncBox
                                                      ->isChecked())
            << "-adjustWindowSize=" + QString::number(adjustWindowSizeBox
                                                      ->isChecked())
            << "-d=" + QString::number(debugModeBox->isChecked());
    if (defineFpsLimitBox->isChecked())
        arguments << "-limitfps=" + QString::number(fpsLimitSpinBox->value());
    arguments << "-game=" + QString::number(game)
            << "-level=" + browseEdit->text() << "-les=" + browseLesEdit->text();
    QString mods = editModsDialog->mods().join(";");
    if (!mods.isEmpty())
        arguments << "-mods=" + mods;
    if (game)
    {
        if (defineCatsNumberBox->isChecked())
            arguments << "-nbOfCats=" + QString::number(numberOfCatsSpinBox
                                                        ->value());
        if (defineRWNumberBox->isChecked())
            arguments << "-nbOfRW=" + QString::number(numberOfRWSpinBox
                                                      ->value());
        if (defineLivesNumberBox->isChecked())
            arguments << "-nbOfLives=" + QString::number(numberOfLivesSpinBox
                                                        ->value());
    }
    else
    {
        if (emptyLevelBox->isChecked())
        {
            arguments << "-emptyLevel" << "-levelX="
                    + QString::number(levelXSpinBox->value())
                << "-levelY=" + QString::number(levelYSpinBox->value());
        }
    }
    if (!process->startDetached(program, arguments, gameMainFolder))
    {
        QMessageBox::critical(this, tr("Game launching error"),
              tr("Failed to launch the game, please check the game location")
              + "<br />" + tr("Cannot found : ") + program);
    }
}

void MainWindow::loadSettings()
{
    settings.beginGroup("Settings");
    // Language
    QString lang = settings.value("language", defaultLanguage).toString();
    if (lang == "fr")
        actionFrench->setChecked(true);
    else if (lang == "en")
        actionEnglish->setChecked(true);
    else
    {
        lang = defaultLanguage;
        actionEnglish->setChecked(true);
    }
    setTranslation(lang);

    // Folders
    gameMainFolder = settings.value("gameMainFolder", "").toString();
    currentBrowseFolder = gameMainFolder;
    // Browse level file text
    browseEdit->setText(settings.value("levelFile", tr("Choose a level file"))
                        .toString());
    // Browse LES file
    browseLesEdit->setText(settings.value("lesFile", "").toString());
    // Nb of cats group
    loadOptionSet("manualNbOfCats", "nbOfCats", defineCatsNumberBox,
                  numberOfCatsSpinBox);
    // Nb of random walls group
    loadOptionSet("manualNbOfRandomWalls", "nbOfRandomWalls", defineRWNumberBox,
                  numberOfRWSpinBox);
    // Nb of player's life
    loadOptionSet("manualNbOfLives", "nbOfLives", defineLivesNumberBox,
                  numberOfLivesSpinBox);
    // Warning at save?
    loadSingleOption("noWarningAtSave", noWarningAtSave);
    // Level size
    loadOptionSet("emptyLevel", "levelX", emptyLevelBox, levelXSpinBox,
                  "levelY", levelYSpinBox, 23);
    resetButton->setEnabled(emptyLevelBox->isChecked());
    // Debug mode
    loadSingleOption("debugMode", debugModeBox);
    // Vertical Synchronisation
    loadSingleOption("enableVSync", enableVSyncBox);
    // Adjust window sier
    loadSingleOption("adjustWindowSize", adjustWindowSizeBox);
    // FPS limit
    loadOptionSet("defineFpsLimit", "fpsLimit", defineFpsLimitBox,
                  fpsLimitSpinBox);
    // Mods list
    QString mods = settings.value("mods", "").toString();
    if (!mods.isEmpty())
        editModsDialog->setList(mods.split(";"));

    settings.endGroup();
}

void MainWindow::loadSingleOption(const QString &boxName, QCheckBox *box)
{
    box->setChecked(settings.value(boxName).toBool());
}

void MainWindow::loadOptionSet(const QString &boxName, const QString &spinBoxName,
                               QCheckBox *box, QSpinBox *spinBox,
                               const QString &spinBoxName2, QSpinBox *spinBox2,
                               const int &min)
{
    int minimum = min;
    if (min == -9999)
        minimum = spinBox->minimum();
    const bool state = settings.value(boxName, false).toBool();
    spinBox->setValue(settings.value(spinBoxName, minimum).toInt());
    spinBox->setEnabled(state);
    box->setChecked(state);
    if (spinBoxName2.isEmpty() || spinBox2 == 0)
        return;
    if (min == -9999)
        minimum = spinBox2->minimum();
    spinBox2->setValue(settings.value(spinBoxName2, minimum).toInt());
    spinBox2->setEnabled(state);
}

void MainWindow::saveSettings()
{
    settings.beginGroup("Settings");
    settings.setValue("language", language);
    settings.setValue("gameMainFolder", gameMainFolder);
    settings.setValue("levelFile", browseEdit->text());
    settings.setValue("lesFile", browseLesEdit->text());
    settings.setValue("manualNbOfCats", defineCatsNumberBox->isChecked());
    settings.setValue("nbOfCats", numberOfCatsSpinBox->value());
    settings.setValue("manualNbOfRandomWalls", defineRWNumberBox->isChecked());
    settings.setValue("nbOfRandomWalls", numberOfRWSpinBox->value());
    settings.setValue("manualNbOfLives", defineLivesNumberBox->isChecked());
    settings.setValue("nbOfLives", numberOfLivesSpinBox->value());
    settings.setValue("noWarningAtSave", noWarningAtSave->isChecked());
    settings.setValue("emptyLevel", emptyLevelBox->isChecked());
    settings.setValue("levelX", levelXSpinBox->value());
    settings.setValue("levelY", levelYSpinBox->value());
    settings.setValue("debugMode", debugModeBox->isChecked());
    settings.setValue("enableVSync", enableVSyncBox->isChecked());
    settings.setValue("adjustWindowSize", adjustWindowSizeBox->isChecked());
    settings.setValue("defineFpsLimit", defineFpsLimitBox->isChecked());
    settings.setValue("fpsLimit", fpsLimitSpinBox->value());
    settings.setValue("mods", editModsDialog->mods().join(";"));
    settings.endGroup();
}

void MainWindow::setTranslation(const QString &newlanguage)
{
    if (newlanguage == language)
        return;
    if (newlanguage == defaultLanguage)
        translator.load("");
    else
        translator.load(":translate_" + newlanguage);
    language = newlanguage;
    QString locale = QLocale::system().name();
    QTranslator generalTranslator;
    generalTranslator.load(QString("qt_") + locale, QLibraryInfo::location(
            QLibraryInfo::TranslationsPath));

    QCoreApplication::installTranslator(&generalTranslator);
    QCoreApplication::installTranslator(&translator);
}

void MainWindow::on_editModsButton_clicked()
{
    editModsDialog->exec();
}

void MainWindow::on_resetButton_clicked()
{
    levelXSpinBox->setValue(23), levelYSpinBox->setValue(23);
}

void MainWindow::on_actionLocation_triggered()
{
    QString folder(QFileDialog::getExistingDirectory(this,
                        tr("Choose the game main folder"),
                        currentBrowseFolder));
    if (folder.isEmpty())
        return;
    currentBrowseFolder = gameMainFolder = folder;
}

void MainWindow::on_actionEnglish_triggered(const bool &state)
{
    if (state)
    {
        actionFrench->setChecked(false);
        setTranslation("en");
    }
    else
        actionEnglish->setChecked(true);
}

void MainWindow::on_actionFrench_triggered(const bool &state)
{
    if (state)
    {
        actionEnglish->setChecked(false);
        setTranslation("fr");
    }
    else
        actionFrench->setChecked(true);
}

void MainWindow::on_emptyLevelBox_toggled(const bool &state)
{
    levelXSpinBox->setEnabled(state), levelYSpinBox->setEnabled(state);
    resetButton->setEnabled(state);
    on_browseEdit_textChanged(browseEdit->text());
}

void MainWindow::on_browseButton_clicked()
{
    QString filename(QFileDialog::getOpenFileName(this, tr("Choose a level file"),
                             currentBrowseFolder, tr("Level file")
                             + " (*.txt *.lvl *.o2r);;" + tr("All files")
                             + " (*.*);;"));
    if (filename.isEmpty())
        return;
    filename.remove(gameMainFolder + "/");
    browseEdit->setText(filename);
    currentBrowseFolder = QFileInfo(filename).absolutePath();
}

void MainWindow::on_browseEdit_textChanged(const QString &text)
{
    bool ok = (!text.isEmpty() && QFile::exists(QDir(gameMainFolder)
                                                      .absoluteFilePath(text)));
    gameButton->setEnabled(ok);
    if (!ok)
        ok = emptyLevelBox->isChecked();
    editorButton->setEnabled(ok);
}

void MainWindow::on_browseLesButton_clicked()
{
    QString filename(QFileDialog::getOpenFileName(this, tr("Choose a LES file"),
                             currentBrowseFolder, tr("LES file")
                             + " (*.xml);;" + tr("All files") + " (*.*);;"));
    if (filename.isEmpty())
        return;
    filename.remove(gameMainFolder + "/");
    browseLesEdit->setText(filename);
    currentBrowseFolder = QFileInfo(filename).absolutePath();
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    if (e->type() == QEvent::LanguageChange)
        retranslateUi(this);
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    saveSettings();
    QMainWindow::closeEvent(e);
}
