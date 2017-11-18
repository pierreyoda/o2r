#include "AvailableModsDialog.hpp"
#include <QDirIterator>
#include "../managers/FilespathProvider.hpp"
#include "QsLog.h"

AvailableModsDialog::AvailableModsDialog(const QStringList &modsList,
                                         QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // Search for available mods
    QDirIterator it(FilespathProvider::modsLocation(),
                    QDir::Dirs | QDir::NoDotAndDotDot,
                    QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        it.next();
        const QFileInfo info = it.fileInfo();
        if (!info.isDir())
            continue;
        const QString modName = info.fileName();
        if (info.filePath() != FilespathProvider::mainModPath()
                && !modsList.contains(modName))
            availableModsList->addItem(modName);
    }
}

void AvailableModsDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    if (e->type() == QEvent::LanguageChange)
        retranslateUi(this);
}

void AvailableModsDialog::on_availableModsList_itemDoubleClicked(
        QListWidgetItem *item)
{
    mSelectedMods.clear();
    mSelectedMods.append(item->text());
    done(QDialog::Accepted);
}

void AvailableModsDialog::on_availableModsList_itemSelectionChanged()
{
    mSelectedMods.clear();
    QList<QListWidgetItem*> selectedItems = availableModsList->selectedItems();
    QListIterator<QListWidgetItem*> it(selectedItems);
    while (it.hasNext())
        mSelectedMods.append(it.next()->text());
    buttonOk->setEnabled(!mSelectedMods.isEmpty());
}
