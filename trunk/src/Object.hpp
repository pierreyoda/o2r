#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SFML/Graphics.hpp>
#include "tools/ImageManager.hpp"

class Object
{
    public:
        Object(const sf::Vector2i &ipos = sf::Vector2i(0, 0));
        virtual ~Object() { }

        void setPosition(const sf::Vector2i &npos);
        void setImage(sf::Image *img);
        void updatePosition();

        sf::Sprite &refSprite() { return m_sprite; }
        sf::Vector2i pos() const { return m_pos; }
        const sf::Sprite &sprite() const { return m_sprite; }
        static bool outOfScreen(const sf::Vector2i &pos,
                                const sf::Vector2i &screenSize);
        static bool outOfScreen(const unsigned int &x, const unsigned int &y,
                                const sf::Vector2i &screenSize);

    protected:
        sf::Vector2i m_pos;
        sf::Sprite m_sprite;
};

#endif /* OBJECT_HPP */
