#include <QFileDialog>
#include "EditModsDialog.hpp"

EditModsDialog::EditModsDialog(const QString &gameMainFolder, QWidget *parent) :
    QDialog(parent), gameMainFolder(gameMainFolder)
{
    setupUi(this);
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
    listModel->setStringList(list);
}

void EditModsDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

bool EditModsDialog::isInList(const QString &string)
{
    for (int i = 0; i < list.size(); i++)
        if (list[i] == string)
            return true;
    return false;
}

void EditModsDialog::on_addButton_clicked()
{
    QString folder(QFileDialog::getExistingDirectory(this,
                        tr("Choose a folder mod"),
                        gameMainFolder));
    if (folder.isEmpty())
        return;
//    folder = QDir(folder).relativeFilePath(folder);
//    folder = QDir(gameMainFolder).filePath(folder);
    if (isInList(folder))
        return;
    list << folder;
    listModel->setStringList(list);
}

void EditModsDialog::on_deleteButton_clicked()
{
    QModelIndex index = listView->currentIndex();
    int pos = index.column();
    if (pos < 0 || pos >= list.size())
        return;
    QStringList::iterator iter;
    for (iter = list.begin(); iter != list.end(); iter++)
    {
        if (*iter == list[pos])
        {
            list.erase(iter);
            break;
        }
    }
    listModel->setStringList(list);
}
