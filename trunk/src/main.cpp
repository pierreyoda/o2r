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

/** \mainpage Open Rodent's Revenge - Source Documentation
*
* \section Project Summary
*
*Open Rodent's Revenge is the open-source remake of Microsoft's game "Rodent's Revenge" (1991).
*This is the 1.0 version (final), featuring a in-window rendering just like the original game.
*
* \section Licence
*This program is free software: you can redistribute it and/or modify
*it under the terms of the GNU General Public License as published by
*the Free Software Foundation, either version 3 of the License, or
*(at your option) any later version.

*This program is distributed in the hope that it will be useful,
*but WITHOUT ANY WARRANTY; without even the implied warranty of
*MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*GNU General Public License for more details.

*You should have received a copy of the GNU General Public License
*along with this program.  If not, see http://www.gnu.org/licenses/.
*/

#include <QApplication>
#include <QDir>
#include <QTime>
#include "MainWindow.hpp"
#include "QsLog.h"
#include "QsLogDest.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Random number generation
    qsrand(QTime::currentTime().msec());

    // Init the logging mechanism (comes from QsLog's example)
    QsLogging::Logger &logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);
    QsLogging::DestinationPtr fileDestination(
                QsLogging::DestinationFactory::MakeFileDestination("log.txt"));
    QsLogging::DestinationPtr debugDestination(
       QsLogging::DestinationFactory::MakeDebugOutputDestination() );
    logger.addDestination(debugDestination.get());
    logger.addDestination(fileDestination.get());

    QLOG_INFO() << "Open Rodent's Revenge version"
                << MainWindow::VERSION.toLocal8Bit().constData() // avoids quotation marks
                << "started.";
    QLOG_INFO() << "Built with Qt" << QT_VERSION_STR << "running on"
                << qVersion() << ".";

    // MainWindow
    MainWindow window;
    window.show();

    return app.exec();
}
