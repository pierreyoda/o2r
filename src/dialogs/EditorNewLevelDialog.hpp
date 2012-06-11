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

#ifndef EDITORNEWLEVELDIALOG_HPP
#define EDITORNEWLEVELDIALOG_HPP

#include "ui_EditorNewLevelDialog.h"

/** The editor new level dialog.
*User can change the name, the author name and the size.
*/
class EditorNewLevelDialog : public QDialog, private Ui::EditorNewLevelDialog
{
    Q_OBJECT
    
public:
    explicit EditorNewLevelDialog(QWidget *parent = 0);

    unsigned int levelSizeX() const;
    unsigned int levelSizeY() const;

    QString levelName() const;
    QString levelAuthor() const;
    
protected:
    void changeEvent(QEvent *e);

private slots:
    void on_lineEdit_name_textChanged(const QString &text);
};

#endif // EDITORNEWLEVELDIALOG_HPP
