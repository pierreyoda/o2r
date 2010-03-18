#include "ErrorScreens.hpp"
#include "../constantes.hpp"

using namespace sf;

void ErrorScreens::missingResources(sf::RenderWindow &App)
{
    Vector2f refPos(gv.SCREEN_W/2, gv.SCREEN_H/3);
    String error("Error : \nOne or more resources are missing.");
        error.SetSize(20.f);
        error.SetColor(Color::Red);
        error.SetPosition(refPos.x-error.GetRect().GetWidth()/2, refPos.y);
    String presskey("Press a key to exit");
        presskey.SetPosition(refPos.x-presskey.GetRect().GetWidth()/2,
                             refPos.y+gv.SCREEN_W/2);

    while (App.IsOpened())
    {
        Event Event;
        while (App.GetEvent(Event))
        {
            if (Event.Type == Event::Closed)
                App.Close();
            if (Event.Type == Event::KeyPressed)
                App.Close();
        }

        App.Clear();
            App.Draw(error);
            App.Draw(presskey);
        App.Display();
    }
}
