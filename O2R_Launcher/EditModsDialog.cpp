#include <QFileDialog>
#include "EditModsDialog.hpp"

EditModsDialog::EditModsDialog(const QString &gameMainFolder, QWidget *parent) :
    QDialog(parent), gameMainFolder(gameMainFolder)
{
    setupUi(this);
    setFixedSize(320, 240);
    listModel = new QStringListModel(list, this);
    listView->setModel(listModel);
}

int EditModsDialog::exec()
{
    backup = list;
    return QDialog::exec();
}

void EditModsDialog::restoreListFromBackup()
{
    list = backup;
    updateView();
}

void EditModsDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    if (e->type() == QEvent::LanguageChange)
        retranslateUi(this);
}

bool EditModsDialog::isInList(const QString &string)
{
    for (int i = 0; i < list.size(); i++)
        if (list[i] == string)
            return true;
    return false;
}

int EditModsDialog::getSelectedStringId()
{
    return listView->currentIndex().row();
}

void EditModsDialog::updateView()
{
    listModel->setStringList(list);
}

void EditModsDialog::selectLine(const unsigned int &row)
{
    /*listView->selectionModel()->select(QModelIndex((int)row, 0, 0, 0),
                                       QItemSelectionModel::ClearAndSelect);*/
}

void EditModsDialog::on_addButton_clicked()
{
    QString folder(QFileDialog::getExistingDirectory(this,
                        tr("Choose a folder mod"),
                        gameMainFolder));
    if (folder.isEmpty() || folder == gameMainFolder)
        return;
    folder.remove(gameMainFolder + "/");
    if (isInList(folder))
        return;
    list << folder;
    updateView();
}

void EditModsDialog::on_deleteButton_clicked()
{
    int pos = getSelectedStringId();
    if (pos < 0 || pos >= list.size())
        return;
    QString toDelete = list[pos];
    QStringList::iterator iter;
    for (iter = list.begin(); iter != list.end(); iter++)
    {
        if (*iter == toDelete)
        {
            list.erase(iter);
            break;
        }
    }
    updateView();
}

void EditModsDialog::on_upButton_clicked()
{
    int pos = getSelectedStringId();
    if (pos <= 0 || pos >= list.size())
        return;
    list.swap(pos, pos-1);
    selectLine(pos-1);
    updateView();
}

void EditModsDialog::on_downButton_clicked()
{
    int pos = getSelectedStringId();
    if (pos < 0 || pos+1 >= list.size())
        return;
    list.swap(pos, pos+1);
    selectLine(pos+1);
    updateView();
}
