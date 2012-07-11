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
