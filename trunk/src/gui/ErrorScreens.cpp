#include <string>
#include "ErrorScreens.hpp"
#include "../GlobalVariables.hpp"

using namespace sf;

void ErrorScreens::missingResources(sf::RenderWindow &App)
{
    Vector2f refPos(gv.SCREEN_W/2, gv.SCREEN_H/3);
    Text error("Error : \nOne or more resources are missing.\nCheck if folder : '"
               + baseModule + "' is present.");
        error.SetCharacterSize(20);
        error.SetColor(Color::Red);
        error.SetPosition(refPos.x-error.GetRect().Width/2, refPos.y);
    Text presskey("Press a key to exit.");
        presskey.SetPosition(refPos.x-presskey.GetRect().Width/2,
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
