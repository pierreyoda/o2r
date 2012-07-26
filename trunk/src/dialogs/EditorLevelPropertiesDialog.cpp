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
#include "EditorLevelPropertiesDialog.hpp"
#include "../map/TiledMap.hpp"

EditorLevelPropertiesDialog::EditorLevelPropertiesDialog(const TiledMap *level,
                                                         QWidget *parent) :
    QDialog(parent), mNewLevelMode(level == 0)
{
    setupUi(this);
    setFixedSize(size());
    // Remove "what's this" icon in title bar
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    spinBox_xSize->setMinimum(TiledMap::SIZE_MIN_LIMIT_X);
    spinBox_xSize->setMaximum(TiledMap::SIZE_MAX_LIMIT_X);
    spinBox_ySize->setMinimum(TiledMap::SIZE_MIN_LIMIT_Y);
    spinBox_ySize->setMaximum(TiledMap::SIZE_MAX_LIMIT_Y);

    // If a level is edited, load its current properties
    if (mNewLevelMode)
        return;
    spinBox_xSize->setValue(level->sizeX());
    spinBox_ySize->setValue(level->sizeY());
    lineEdit_name->setText(level->info().name);
    lineEdit_author->setText(level->info().author);
}

unsigned int EditorLevelPropertiesDialog::levelSizeX() const
{
    return spinBox_xSize->value();
}

unsigned int EditorLevelPropertiesDialog::levelSizeY() const
{
    return spinBox_ySize->value();
}

QString EditorLevelPropertiesDialog::levelName() const
{
    return lineEdit_name->text();
}

QString EditorLevelPropertiesDialog::levelAuthor() const
{
    return lineEdit_author->text();
}

void EditorLevelPropertiesDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    if (e->type() == QEvent::LanguageChange)
        retranslateUi(this);
}

void EditorLevelPropertiesDialog::on_lineEdit_name_textChanged(const QString &text)
{
    if (mNewLevelMode)
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!text.isEmpty());
}

