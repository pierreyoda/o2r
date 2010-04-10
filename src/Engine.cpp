#include <iostream>
#include <sstream>
#include "Engine.hpp"
#include "GlobalVariables.hpp"
#include "LevelFileInterpreter.hpp"
#include "gui/TextBox.hpp"
#include "gui/Button.hpp"
#include "tools/FilesLoader.hpp"

using namespace sf;

// TODO (Pierre-Yves#2#): Créer campagne
// TODO (Pierre-Yves#4#): [GENERAL]Ajouter zoom automatique pour niveaux de tailles non standards...
Engine::Engine(sf::RenderWindow &window, const bool &vsync,
    const unsigned int &fpslimit) : App(window), game(), cats(game.getCatsList()),
    mouse(game.getMouse()), gameView(FloatRect(0, 0, gv.SCREEN_W, gv.SCREEN_H)),
     running(true)
{
    //gameView.Rotate(180);
    App.UseVerticalSync(vsync);
    App.SetFramerateLimit(fpslimit);
    App.SetIcon(16, 16, gImageManager.getResource("icon.png")->GetPixelsPtr());
    createMenus();
}

Engine::~Engine()
{

}

void Engine::createMenus()
{
    const float middleX = App.GetWidth()/2.f, middleY = App.GetHeight()/2.f;
    const float refX = middleX-125;
    mainMenu.addButton(Button("Play Game!", Vector2f(refX, middleY-160)));
    mainMenu.addButton(Button("Create Level", Vector2f(refX, middleY-40)));
    mainMenu.addButton(Button("Quit", Vector2f(refX, middleY+80)));
    mainMenu.connectButton(0, boost::bind(&Engine::runGame, this));
    mainMenu.connectButton(1, boost::bind(&Engine::runEditor, this));
    mainMenu.connectButton(2, boost::bind(&Engine::exit, this));
}

bool Engine::loadLevel(const std::string &filename)
{
    Vector2i oldSize(gv.SCREEN_W, gv.SCREEN_H-HUD_HEIGHT);
    bool ok = game.loadLevel(filename);
    if (ok && gv.sizeChanged)
    {
        //hud.createHud();
        resizeGameView(oldSize);
        gv.sizeChanged = false;
    }
    return ok;
}

bool Engine::loadTower(const std::string &filename)
{
    bool ok = game.loadTower(filename);
    /*if (ok && gv.sizeChanged)
    {
        hud.createHud();
        resizeGameView(oldSize);
        gv.sizeChanged = false;
    }*/
    return ok;
}

void Engine::resizeGameView(const Vector2i &prevSize)
{
    sf::Vector2i factor(prevSize.x / gv.SCREEN_W, prevSize.y / gv.SCREEN_H);
    //gameView.
}

void Engine::initializeGame(const bool &newlvl)
{
    game.initializeGame(newlvl);
    hud.newGameStarted();
}

void Engine::drawFps()
{
    if (gv.debugMode)
        hud.drawFps(App, App.GetFrameTime());
}

void Engine::run()
{
    if (!running)
        return;
    mainMenu.run(App, hud);
}

void Engine::runGame()
{
    bool astar = true;
    std::cout << "Launching game...\n";
    if (!loadLevel(game.getCurrentLevelName()))
        loadLevel("data/1.txt");
    initializeGame();
    App.SetView(gameView);
    while (App.IsOpened() && running)
    {
        Event Event;
        while (App.GetEvent(Event))
        {
            if (Event.Type == Event::Closed)
                App.Close();
            if (Event.Type == Event::KeyPressed)
            {
                if (!USE_WINDOWGUI && Event.Key.Code == Key::Escape)
                {
                    if (menuGame())
                        return;
                    App.SetView(gameView);
                }
                if (Event.Key.Code == Key::F12)
                    gv.debugMode = !gv.debugMode;
                if (Event.Key.Code == Key::A)
                    astar = !astar;
                if (!game.getMouse().dead() &&  Event.Key.Code == Key::S)
                    game.getMouse().die();
                if (cats.size() >= 1 && Event.Key.Code == Key::D)
                    cats.begin()->die();
                if (cats.size() >= 1 && cats.begin()->isAlive() && Event.Key.Code == Key::K)
                    Cat::killCat(cats.begin()->pos(), cats);
                if (Event.Key.Code == Key::Up)
                    mouse.move(UP);
                else if (Event.Key.Code == Key::Down)
                    mouse.move(DOWN);
                if (Event.Key.Code == Key::Left)
                    mouse.move(LEFT);
                else if (Event.Key.Code == Key::Right)
                    mouse.move(RIGHT);
            }
        }

        game.updateCats(astar);
        if (mouse.dead())
            return;

        App.Clear();

        game.renderTower(App);
        //App.Draw(game.getLevel().getRenderResult());
        for (unsigned int i = 0; i < cats.size(); i++)
            App.Draw(cats[i].sprite());
        App.Draw(mouse.sprite());
        App.Draw(hud.drawHud(cats.size(), mouse.remainingLifes(), true));
            drawFps();
        //App.SetView(gameView);

        App.Display();
    }
}

bool Engine::menuGame()
{
    const float middleX = App.GetWidth()/2.f, middleY = App.GetHeight()/2.f;
    bool writing = false, level = true;
    TextBox textBox(0, game.getCurrentLevelName());
    std::vector<Button> buttons;
    buttons.push_back(Button("Resume", Vector2f(middleX-175, middleY-150),
                             Vector2f(185, 150)));
    buttons.push_back(Button("Exit", Vector2f(middleX+10, middleY-150),
                             Vector2f(185, middleY-150)));
    buttons.push_back(Button("Open Level", Vector2f(middleX-175, middleY+75),
                             Vector2f(300, 100)));
    buttons.push_back(Button("Open Tower", Vector2f(middleX-175, middleY-25),
                            Vector2f(300, 100)));

    App.SetView(App.GetDefaultView());
    static const Input &Input = App.GetInput();
    while (App.IsOpened())
    {
        Vector2f mousePos(Input.GetMouseX(), Input.GetMouseY());
        Event Event;
        while (App.GetEvent(Event))
        {
            if (Event.Type == Event::Closed)
            {
                App.Close();
                return true;
            }
            if (Event.Type == Event::KeyPressed)
            {
                if (Event.Key.Code == Key::Escape)
                    return false;
                if (Event.Key.Code == Key::Delete)
                    textBox.clearText();
                if (writing && Event.Key.Code == Key::Return)
                {
                    const std::string filename(textBox.getString());
                    if (FilesLoader::fileExists(filename));
                    else if (level && loadLevel(filename))
                    {
                        writing = false;
                        initializeGame(true);
                        return false;
                    }
                    else if (loadTower(filename))
                    {
                        writing = false;
                        initializeGame(true);
                        return false;
                    }
                }
            }
            if (writing && Event.Type == Event::TextEntered)
                textBox.onTextEntered(Event.Text.Unicode);
            if (Event.Type == Event::MouseMoved)
            {
                for (unsigned int i = 0; i < buttons.size(); i++)
                {
                    if (buttons[i].isMouseOver(mousePos))
                        buttons[i].setBorderWidth(12);
                    else
                        buttons[i].setBorderWidth(8);
                }
            }
            if (Event.Type == Event::MouseButtonReleased)
            {
                if (buttons[0].isMouseOver(mousePos))
                    return false;
                else if (buttons[1].isMouseOver(mousePos))
                    return true;
                else if (buttons[2].isMouseOver(mousePos))
                    writing = level = true;
                else if (buttons[3].isMouseOver(mousePos))
                {
                    writing = true;
                    level = false;
                }
            }
        }

        App.Clear(Color(0, 128, 0));
            for (unsigned int i = 0; i < buttons.size(); i++)
            {
                App.Draw(buttons[i].getBorder());
                App.Draw(buttons[i].getText());
            }
            if (writing)
                App.Draw(textBox.getText());
            drawFps();

        App.Display();
    }
    return true;
}

void Engine::runEditor()
{
    std::cout << "Launching level editor...\n";
    if (!loadLevel(game.getCurrentLevelName()))
        loadLevel("data/1.txt");
    hud.newGameStarted();
    mouse.setPosition(game.getLevel().getMouseStartPos());
    CASETYPE casetype = BLOCK;
    App.SetView(gameView);
    const Input &Input = App.GetInput();
    while (App.IsOpened() && running)
    {
        Vector2f mousepos = App.ConvertCoords(App.GetInput().GetMouseX(),
                                              App.GetInput().GetMouseY());

        Event Event;
        while (App.GetEvent(Event))
        {
            if (Event.Type == Event::Closed)
                App.Close();
            if (Event.Type == Event::KeyPressed)
            {
                if (!USE_WINDOWGUI && Event.Key.Code == Key::Escape)
                {
                    if (menuEditor())
                        return;
                    App.SetView(gameView);
                }
                if (Event.Key.Code == Key::F12)
                    gv.debugMode = !gv.debugMode;
                if (Event.Key.Code == Key::M)
                    game.placeMouse(mousepos);
                if (Event.Key.Code == Key::Num1 || Event.Key.Code == Key::Numpad1)
                    casetype = BLOCK;
                if (Event.Key.Code == Key::Num2 || Event.Key.Code == Key::Numpad2)
                    casetype = WALL;
            }
        }

        if (mousepos.x < gv.SCREEN_W && mousepos.y < gv.SCREEN_H-HUD_HEIGHT)
        {
            if (Input.IsMouseButtonDown(sf::Mouse::Left))
                game.placeCaseType(mousepos, casetype);
            else if (Input.IsMouseButtonDown(sf::Mouse::Right))
                game.clearCase(mousepos);
        }

        App.Clear();

        App.Draw(game.getLevel().getRenderResult());
        App.Draw(mouse.sprite());
        App.Draw(hud.drawHud(cats.size(), mouse.remainingLifes(), false));
            drawFps();

        App.Display();
    }
}

bool Engine::menuEditor()
{
    bool writing = false, save = false;
    TextBox textBox(0, game.getCurrentLevelName());
    std::vector<Button> buttons;
        const float middleX = App.GetWidth()/2.f, middleY = App.GetHeight()/2.f;
    buttons.push_back(Button("Resume", Vector2f(middleX-175, middleY-150),
                             Vector2f(middleX-10, middleY-50)));
    buttons.push_back(Button("Exit", Vector2f(middleX+10, middleY-150),
                             Vector2f(middleX+175, middleY-50)));
    buttons.push_back(Button("Save Level", Vector2f(middleX-175, middleY-25),
                             Vector2f(middleX+175, middleY+65)));
    buttons.push_back(Button("Open Level", Vector2f(middleX-175, middleY+75),
                             Vector2f(middleX+175, middleY+175)));

    App.SetView(App.GetDefaultView());
    static const Input &Input = App.GetInput();
    while (App.IsOpened())
    {
        Vector2f mousePos(Input.GetMouseX(), Input.GetMouseY());
        Event Event;
        while (App.GetEvent(Event))
        {
            if (Event.Type == Event::Closed)
            {
                App.Close();
                return true;
            }
            if (Event.Type == Event::KeyPressed)
            {
                if (Event.Key.Code == Key::Escape)
                    return false;
                if (Event.Key.Code == Key::Delete)
                    textBox.clearText();
                if (writing && Event.Key.Code == Key::Return)
                {
                    const std::string filename = textBox.getString();
                    if (save && LevelFileInterpreter::writeLevel(game.getLevel(),
                            filename))
                    {
                        game.setCurrentLevelName(filename);
                        writing = save = false;
                        return false;
                    }
                    else
                    {
                        loadLevel(filename);
                        writing = false;
                        return false;
                    }
                }
            }
            else if (writing && Event.Type == Event::TextEntered)
            {
                textBox.onTextEntered(Event.Text.Unicode);
            }
            if (Event.Type == Event::MouseMoved)
            {
                for (unsigned int i = 0; i < buttons.size(); i++)
                {
                    if (buttons[i].isMouseOver(mousePos))
                        buttons[i].setBorderWidth(12);
                    else
                        buttons[i].setBorderWidth(8);
                }
            }
            if (Event.Type == Event::MouseButtonReleased)
            {
                if (buttons[0].isMouseOver(mousePos))
                    return false;
                else if (buttons[1].isMouseOver(mousePos))
                    return true;
                else if (buttons[2].isMouseOver(mousePos))
                    writing = save = true;
                else if (buttons[3].isMouseOver(mousePos))
                    writing = true;
            }
        }

        App.Clear(Color(0, 128, 0));
            for (unsigned int i = 0; i < buttons.size(); i++)
            {
                App.Draw(buttons[i].getBorder());
                App.Draw(buttons[i].getText());
            }
            if (writing)
                App.Draw(textBox.getText());
            drawFps();
        App.Display();
    }
    return true;
}
