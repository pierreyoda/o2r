#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

class QTranslator;
class AboutDialog;

#include <QSettings>
#include <QMessageBox>
#include "GameCanvas.hpp"
#include "ui_MainWindow.h"

class GameScreen;

/** Possible game modes.
*/
enum GAME_MODE {
    PLAY,
    EDIT,
    NONE
};

/** The main window.
*
*/
class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    static QString VERSION;
    
protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *e);

private:
    void initManagers();
    void populateEditorBar();
    void addEditorBarAction(const QChar &c, const QString &text,
                            const QString &iconPath);
    void switchToGameMode(GAME_MODE mode);
    void toggleGameActions(bool enable);
    void toggleEditorActions(bool enable);
    void loadSettings();
    void saveSettings();
    void changeLanguage(const QString &id);
    void adjustSizeToCanvas();

    int execModalDialog(QDialog &dialog);

    // Game
    GameCanvas *mGameCanvas;
    ScreenPtr mGameScreen, mEditorScreen;
    // Editor bar
    QAction *prevSelectedAction;
    // Options
    QStringList mModsList;
    // Dialogs
    AboutDialog *mAboutDialog;
    // MainWindow stuff
    QSettings mSettings;
    QTranslator *mTranslator, *mQtTranslator;
    QString mCurrentLanguage;
    const QString mDefaultLanguage;

private slots:
    // Canvas slots
    void resizeCanvas(int w, int h);
    // Game slots
    void on_actionPlayLevel_triggered();
    // Editor slots
    void on_actionEditorNewLevel_triggered();
    void on_actionEditorExistingLevel_triggered();
    void on_actionEditorCurrentLevel_triggered();
    void on_actionEditorSaveLevel_triggered();
    void on_actionEditorSaveLevelAs_triggered();
    void on_actionEditorLevelProperties_triggered();
    // Editor toolbar slots
    void on_editorBar_visibilityChanged(bool visible);
    void on_editorBar_actionTriggered(QAction *action);
    // Options slots
    void on_actionEditMods_triggered();
    // Language change slots
    void on_actionLanguageEnglish_triggered(bool state);
    void on_actionLanguageFrench_triggered(bool state);
    // AboutDialog slots
    void on_actionAbout_triggered();
    void aboutDialog_finished(int);
    // "About Qt" slots
    void on_actionAboutQt_triggered();
    void aboutQtMessageBox_finished(int);
};

#endif // MAINWINDOW_HPP
