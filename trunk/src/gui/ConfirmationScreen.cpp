#include "ConfirmationScreen.hpp"
#include "../constantes.hpp"

using namespace sf;

bool ConfirmationScreen::askConfirmation(RenderWindow &App,
                                         const std::string &text)
{
    const Vector2f refPos(SCREEN_W/2, SCREEN_H/3);
    Text message(text);
        message.SetCharacterSize(20);
        message.SetPosition(refPos.x-message.GetRect().Width/2, refPos.y);
    Text confirm("(Y)es / (N)o");
        confirm.SetPosition(refPos.x-confirm.GetRect().Width/2,
            refPos.y+SCREEN_W/2);

    while (App.IsOpened())
    {
        Event Event;
        while (App.GetEvent(Event))
        {
            if (Event.Type == Event::Closed)
                return false;
            if (Event.Type == Event::KeyPressed)
            {
                if (Event.Key.Code == Key::Y)
                    return true;
                if (Event.Key.Code == Key::N)
                    return false;
            }
        }

        App.Clear();
            App.Draw(message);
            App.Draw(confirm);
        App.Display();
    }
    return false;
}
