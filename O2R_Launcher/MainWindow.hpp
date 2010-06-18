#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QSettings>
#include <QTranslator>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, private Ui::MainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *e);

private slots:
    void on_actionAboutQt_triggered()
    {
        qApp->aboutQt();
    }
    void on_actionLocation_triggered();
    void on_actionEnglish_triggered(const bool &state);
    void on_actionFrench_triggered(const bool &state);
    void on_emptyLevelBox_toggled(const bool &state);
    void on_browseButton_clicked();
    void on_browseLesButton_clicked();
    void on_browseEdit_textChanged(const QString &text);

private:
    void loadSettings();
        void loadSingleOption(const QString &boxName, QCheckBox *box);
        void loadOptionSet(const QString &boxName, const QString &spinBoxName,
                           QCheckBox *box, QSpinBox *spinBox,
                           const QString &spinBoxName2 = "",
                           QSpinBox *spinBox2 = 0, const int &min = -9999);
    void saveSettings();
    void setTranslation(const QString &newLanguage);

    const QString defaultLanguage;
    QTranslator translator;
    QSettings settings;
    QString language, currentBrowseFolder, gameMainFolder;
};

#endif /* MAINWINDOW_HPP */