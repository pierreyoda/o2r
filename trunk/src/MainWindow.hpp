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

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

class GameCanvas;

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    
protected:
    void changeEvent(QEvent *e);

private:
    GameCanvas *mGameCanvas;

private slots:
    void on_actionAboutQt_triggered();
};

#endif // MAINWINDOW_HPP
