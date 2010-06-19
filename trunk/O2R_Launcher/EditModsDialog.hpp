#ifndef EDITMODSDIALOG_HPP
#define EDITMODSDIALOG_HPP

#include "ui_EditModsDialog.h"
#include <QStringListModel>

class EditModsDialog : public QDialog, private Ui::EditModsDialog {
    Q_OBJECT
public:
    EditModsDialog(const QString &gameMainFolder, QWidget *parent = 0);

    void setList(const QStringList &nlist)
    {
        list = nlist;
        listModel->setStringList(list);
    }

    bool noMods() const { return list.isEmpty(); }
    const QStringList &mods() const { return list; }

public slots:
    int exec();
    void restoreListFromBackup();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_addButton_clicked();
    void on_deleteButton_clicked();


private:
    bool isInList(const QString &string);

    QStringList list, backup;
    QStringListModel *listModel;
    const QString &gameMainFolder;
};

#endif /* EDITMODSDIALOG_HPP */
