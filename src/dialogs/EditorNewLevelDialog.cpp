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

#include <QPushButton>
#include "EditorNewLevelDialog.hpp"
#include "../map/TiledMap.hpp"

EditorNewLevelDialog::EditorNewLevelDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setFixedSize(size());
    // Remove "what's this" icon in title bar
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    spinBox_xSize->setMinimum(TiledMap::SIZE_MIN_LIMIT_X);
    spinBox_xSize->setMaximum(TiledMap::SIZE_MAX_LIMIT_X);
    spinBox_ySize->setMinimum(TiledMap::SIZE_MIN_LIMIT_Y);
    spinBox_ySize->setMaximum(TiledMap::SIZE_MAX_LIMIT_Y);
}

unsigned int EditorNewLevelDialog::levelSizeX() const
{
    return spinBox_xSize->value();
}

unsigned int EditorNewLevelDialog::levelSizeY() const
{
    return spinBox_ySize->value();
}

QString EditorNewLevelDialog::levelName() const
{
    return lineEdit_name->text();
}

QString EditorNewLevelDialog::levelAuthor() const
{
    return lineEdit_author->text();
}

void EditorNewLevelDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    if (e->type() == QEvent::LanguageChange)
        retranslateUi(this);
}

void EditorNewLevelDialog::on_lineEdit_name_textChanged(const QString &text)
{
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!text.isEmpty());
}

