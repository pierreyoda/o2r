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

#include "ModsDialog.hpp"
#include <QDirIterator>
#include <QListWidget>
#include "../managers/FilespathProvider.hpp"
#include "AvailableModsDialog.hpp"

ModsDialog::ModsDialog(const QStringList &modsList, QWidget *parent) :
    QDialog(parent), mModsList(modsList)
{
    setupUi(this);
    setFixedSize(size());
    // Remove "what's this" icon in title bar
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    // Fill the mods list
    modsListWidget->addItems(modsList);

    connect(this, SIGNAL(finished(int)), this, SLOT(buildResult(int)));
}

void ModsDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    if (e->type() == QEvent::LanguageChange)
        retranslateUi(this);
}

void ModsDialog::buildModsList()
{
    mModsList.clear();
    for (int i = 0; i < modsListWidget->count(); i++)
    {
        const QListWidgetItem *item = modsListWidget->item(i);
        if (item == 0)
            continue;
        mModsList.append(item->text());
    }
}

void ModsDialog::buildResult(int result)
{
    // If dialog rejected : avoid useless computation
    if (result != Accepted)
        return;
    // Build mods list
    buildModsList();
}

void ModsDialog::on_buttonAdd_clicked()
{
    // Launch an AvailableModsDialog for result
    buildModsList();
    AvailableModsDialog *availableModsDialog = new AvailableModsDialog(mModsList,
                                                                       this);
    const int result = availableModsDialog->exec();
    if (result != QDialog::Accepted)
        return;
    const QStringList &modsToAdd = availableModsDialog->selectedMods();
    mModsList += modsToAdd;
    modsListWidget->addItems(modsToAdd);
}

void ModsDialog::on_buttonDelete_clicked()
{
    QListWidgetItem *itemToDelete = modsListWidget->takeItem(
                modsListWidget->currentRow());
    if (itemToDelete == 0)
        return;
    delete itemToDelete;
}

void ModsDialog::on_buttonUp_clicked()
{
    // Change item pos
    int currentRow = modsListWidget->currentRow();
    if (currentRow <= 0)
        return;
    QListWidgetItem *currentItem = modsListWidget->takeItem(currentRow);
    if (currentItem == 0)
        return;
    modsListWidget->insertItem(currentRow - 1, currentItem);
    modsListWidget->setCurrentRow(currentRow - 1);
}

void ModsDialog::on_buttonDown_clicked()
{
    // Change item pos
    int currentRow = modsListWidget->currentRow();
    if (currentRow >= modsListWidget->count() - 1)
        return;
    QListWidgetItem *currentItem = modsListWidget->takeItem(currentRow);
    if (currentItem == 0)
        return;
    modsListWidget->insertItem(currentRow + 1, currentItem);
    modsListWidget->setCurrentRow(currentRow + 1);
}

void ModsDialog::on_modsListWidget_itemSelectionChanged()
{
    const bool validSelection = (modsListWidget->currentItem() != 0);
    buttonUp->setEnabled(validSelection);
    buttonDown->setEnabled(validSelection);
    buttonDelete->setEnabled(validSelection);
}
