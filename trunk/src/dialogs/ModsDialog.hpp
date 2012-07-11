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

#ifndef MODSDIALOG_HPP
#define MODSDIALOG_HPP

#include "ui_ModsDialog.h"
#include <QStringListModel>


/** Add/remove mods, and change their load order.
*
*/
class ModsDialog : public QDialog, private Ui::ModsDialog
{
    Q_OBJECT
    
public:
    explicit ModsDialog(const QStringList &modsList, QWidget *parent = 0);

    const QStringList &modsList() const { return mModsList; }
    
protected:
    void changeEvent(QEvent *e);

private:
    void buildModsList();

    QStringList mModsList;

private slots:
    void buildResult(int result);
    void on_buttonAdd_clicked();
    void on_buttonDelete_clicked();
    void on_buttonUp_clicked();
    void on_buttonDown_clicked();
    void on_modsListWidget_itemSelectionChanged();
};

#endif // MODSDIALOG_HPP
