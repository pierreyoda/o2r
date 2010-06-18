#include <QFileDialog>
#include <QLibraryInfo>
#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
defaultLanguage("en"), settings("settings.ini", QSettings::IniFormat, this),
    language(defaultLanguage)
{
    setupUi(this);
    mainWidget->setLayout(mainLayout);
    setFixedSize(480, 420);
    browseEdit->setText(tr("Choose a level file"));
    loadSettings();

    connect(defineCatsNumberBox, SIGNAL(toggled(bool)), numberOfCatsSpinBox,
            SLOT(setEnabled(bool)));
    connect(defineRWNumberBox, SIGNAL(toggled(bool)), numberOfRWSpinBox,
            SLOT(setEnabled(bool)));
    connect(defineLivesNumberBox, SIGNAL(toggled(bool)), numberOfLivesSpinBox,
            SLOT(setEnabled(bool)));
    connect(defineFpsLimitBox, SIGNAL(toggled(bool)), fpsLimitSpinBox,
            SLOT(setEnabled(bool)));
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
    currentBrowseFolder = settings.value("currentBrowseFolder", "").toString();
    gameMainFolder = settings.value("gameMainFolder", currentBrowseFolder)
                     .toString();
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
    // Debug mode
    loadSingleOption("debugMode", debugModeBox);
    // Vertical Synchronisation
    loadSingleOption("enableVSync", enableVSyncBox);
    // FPS limit
    loadOptionSet("defineFpsLimit", "fpsLimit", defineFpsLimitBox,
                  fpsLimitSpinBox);

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
    if (spinBoxName2.isEmpty() || spinBox == 0)
        return;
    spinBox2->setValue(settings.value(spinBoxName, minimum).toInt());
    spinBox2->setEnabled(state);
}

void MainWindow::saveSettings()
{
    settings.beginGroup("Settings");
    settings.setValue("language", language);
    settings.setValue("gameMainFolder", gameMainFolder);
    settings.setValue("levelFile", browseEdit->text());
    settings.setValue("lesFile", browseLesEdit->text());
    settings.setValue("currentBrowseFolder", currentBrowseFolder);
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
    settings.setValue("defineFpsLimit", defineFpsLimitBox->isChecked());
    settings.setValue("fpsLimit", fpsLimitSpinBox->value());
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
}

void MainWindow::on_browseButton_clicked()
{
    QString filename(QFileDialog::getOpenFileName(this, tr("Choose a level file"),
                             currentBrowseFolder, tr("Level file")
                             + " (*.txt *.lvl *.o2r);;" + tr("All files")
                             + " (*.*);;"));
    if (filename.isEmpty())
        return;
    browseEdit->setText(filename);
    currentBrowseFolder = QFileInfo(filename).absolutePath();
}

void MainWindow::on_browseEdit_textChanged(const QString &text)
{
    const bool ok = (!text.isEmpty() && QFile::exists(text));
    gameButton->setEnabled(ok);
    editorButton->setEnabled(ok);
}

void MainWindow::on_browseLesButton_clicked()
{
    QString filename(QFileDialog::getOpenFileName(this, tr("Choose a LES file"),
                             currentBrowseFolder, tr("LES file")
                             + " (*.xml);;" + tr("All files") + " (*.*);;"));
    if (filename.isEmpty())
        return;
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
