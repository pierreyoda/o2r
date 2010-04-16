#include "Menu.hpp"

using namespace sf;

Menu::Menu()
{

}

Menu::~Menu()
{

}

void Menu::addButton(const Button &button, bRunFonction fonction,
                     const bool &write)
{
    m_buttons.push_back(menuButton(button, fonction));
    m_writeButtons.push_back(write);
}

void Menu::connectButton(const unsigned int &id, bRunFonction function)
{
    if (id < 0 || id >= m_buttons.size())
        return;
    m_buttons[id].second = function;
}

bool Menu::run(RenderWindow &App, HudManager &hud, bool &resume)
{
    bool writting = false;
    static const Input &Input = App.GetInput();
    while (App.IsOpened())
    {
        Vector2f mousePos(Input.GetMouseX(), Input.GetMouseY());
        Event Event;
        while (App.GetEvent(Event))
        {
            if (Event.Type == Event::Closed)
                App.Close();
            if (Event.Type == Event::KeyPressed)
            {
                if (Event.Key.Code == Key::Escape)
                    return false;
                if (Event.Key.Code == Key::F12)
                    gv.debugMode = !gv.debugMode;
            }
            if (Event.Type == Event::MouseMoved)
            {
                for (unsigned int i = 0; i < m_buttons.size(); i++)
                {
                    if (m_buttons[i].first.isMouseOver(mousePos))
                        m_buttons[i].first.setBorderWidth(12);
                    else
                        m_buttons[i].first.setBorderWidth(8);
                }
            }
            if (Event.Type == Event::MouseButtonReleased)
            {
                for (unsigned int i = 0; i < m_buttons.size(); i++)
                {
                    if (m_buttons[i].first.isMouseOver(mousePos))
                    {
                        if (m_writeButtons[i])
                            writting = true;
                        if (m_buttons[i].second != NULL)
                        {
                            m_buttons[i].second();
                            return false;
                        }
                    }
                }
            }
            if (writting && Event.Type == Event::TextEntered)
                text.onTextEntered(Event.Text.Unicode);
        }

        App.Clear(Color(0, 128, 0));

        for (unsigned int i = 0; i < m_buttons.size(); i++)
        {
            App.Draw(m_buttons[i].first.getBorder());
            App.Draw(m_buttons[i].first.getText());
        }
        if (gv.debugMode)
            hud.drawFps(App, App.GetFrameTime());

        App.Display();
    }
    return false;
}
