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

#include "QSfmlCanvas.hpp"

QSfmlCanvas::QSfmlCanvas(QWidget *parent, const QPoint& position,
                         const QSize &size, unsigned int frameTime) :
    QWidget(parent), mInitialized(false)
{
    // Allow direct rendering in the widget
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    // Redirect keyboard events to SFML
    setFocusPolicy(Qt::StrongFocus);

    move(position);
    resize(size);

    mTimer.setInterval(frameTime);
}

QSfmlCanvas::~QSfmlCanvas()
{

}

#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
    #include <X11/Xlib.h>
#endif

void QSfmlCanvas::showEvent(QShowEvent*)
{
    if (!mInitialized)
    {
        // Needed under X11
        #ifdef Q_WS_X11
            XFlush(QX11Info::display());
        #endif

        // Create SFML window with widget ID
        sf::RenderWindow::create(winId());

        // Init in derivated class
        onInit();

        // Set repaint timer
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        mTimer.start();

        mInitialized = true;
    }
}

void QSfmlCanvas::paintEvent(QPaintEvent*)
{
    // Update in derivated class
    onUpdate();

    // Refresh widget
    display();
}

QPaintEngine* QSfmlCanvas::paintEngine() const
{
    return 0;
}
