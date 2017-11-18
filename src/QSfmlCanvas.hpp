#ifndef QSFMLCANVAS_HPP
#define QSFMLCANVAS_HPP

#include <QWidget>
#include <QTimer>
#include <SFML/Graphics.hpp>

/** A QSfmlCanvas is an abstract class inheriting from both QWidget and sf::RenderWindow
*in order to handle a SFML context inside a Qt window.
*
*/
class QSfmlCanvas : public QWidget, public sf::RenderWindow
{
    Q_OBJECT
public:
    explicit QSfmlCanvas(QWidget *parent, const QPoint &position,
                         const QSize &size, unsigned int frameTime = 0);
    virtual ~QSfmlCanvas();

private :

    virtual void onInit() = 0;
    virtual void onUpdate() = 0;

    virtual QPaintEngine* paintEngine() const;

    virtual void showEvent(QShowEvent*);
    virtual void paintEvent(QPaintEvent*);

    QTimer mTimer;
    bool   mInitialized;
};

#endif // QSFMLCANVAS_HPP
