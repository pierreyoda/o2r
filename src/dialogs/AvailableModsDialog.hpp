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

#ifndef AVAILABLEMODSDIALOG_HPP
#define AVAILABLEMODSDIALOG_HPP

#include "ui_AvailableModsDialog.h"

/** Simple list dialog where you can choose one or several mods if they are not
*already chosen and thus different from the default mod.
*
*/
class AvailableModsDialog : public QDialog, private Ui::AvailableModsDialog
{
    Q_OBJECT
    
public:
    /** Default constructor.
    *@param modsList Already chosen mods.
    *@param parent Parent widget.
    */
    explicit AvailableModsDialog(const QStringList &modsList, QWidget *parent = 0);

    /** Get the selected mods.
    */
    const QStringList &selectedMods() const { return mSelectedMods; }
    
protected:
    void changeEvent(QEvent *e);

private:
    QStringList mSelectedMods;

private slots:
    void on_availableModsList_itemDoubleClicked(QListWidgetItem *item);
    void on_availableModsList_itemSelectionChanged();
};

#endif // AVAILABLEMODSDIALOG_HPP
