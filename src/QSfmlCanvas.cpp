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
