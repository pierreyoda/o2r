#include "core.hpp"

using namespace sf;

Core Core::core;

/*****************************
*   constructeur
*****************************/
Core::Core() : graph(Size)
{


}


/*****************************
*   on lance le jeu
*****************************/
void Core::run()
{
    VideoMode video(Width, Height, 32);
    WindowSettings setting(24, 8, 0);
    RenderWindow App(video, "A*", Style::Close, setting);
    Event Event;
    App.SetFramerateLimit(FPS);
    while(!graph.Connexe())
        graph.Resize(Size);
    while (App.IsOpened())
    {
        if(graph.Win())
        {
            graph.Resize(Size);
            while(!graph.Connexe())
                graph.Resize(Size);
        }

        //Parse events
        while (App.GetEvent(Event))
        {
            if(Event.Type == sf::Event::Closed)
                App.Close();
            else if(Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Return)
            {
                graph.Resize(Size);
                while(!graph.Connexe())
                    graph.Resize(Size);
            }
        }


        //Move player &  monster
        graph.Move(App);

        // Clear the window
        App.Clear();
        //Draw
        graph.Draw(App);
        App.Display();
    }
}
