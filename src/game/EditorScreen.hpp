#ifndef EDITORSCREEN_HPP
#define EDITORSCREEN_HPP

#include "Screen.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

/** The editor screen.
*/
class EditorScreen : public Screen
{
public:
    EditorScreen(const sf::Window &window);

    void render(sf::RenderTarget &target,
                sf::RenderStates states = sf::RenderStates::Default);

    void update(const sf::Time &dt);

    void handleEvent(const sf::Event &event);

    /** Start editing an existing level.
    *@param level Level to edit.
    */
    bool start(TiledMapPtr level);

    /** Set the current character ID to place (mouse position or tile).
    */
    void setPlaceableChar(const QChar &c);

    static const QChar MOUSE_POS_CHAR;

private:
    void relocateMousePosIndicator();

    QChar mPlaceableChar;
    bool mPlaceableCharUpdated;
    sf::Vector2i mLastPlacedPos;
    sf::Sprite mMousePosIndicator;
};

#endif // EDITORSCREEN_HPP
