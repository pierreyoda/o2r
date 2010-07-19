#include <iostream>
#include "Engine.hpp"
#include "GlobalVariables.hpp"
#include "gui/TextBox.hpp"
#include "gui/Button.hpp"
#include "tools/FilesLoader.hpp"
#include "tools/Logger.hpp"

using namespace sf;

// TODO (Pierre-Yves#6#): Cr�er campagne
Engine::Engine(sf::RenderWindow &window, const bool &vsync,
    const unsigned int &fpslimit) : App(window), game(), cats(game.getCatsList()),
    mouse(game.getMouse()), hud(&App),
    gameView(FloatRect(0, 0, SCREEN_W, SCREEN_H)), running(true), resume(false),
    quitToMainMenu(false)
{
    App.UseVerticalSync(vsync);
    App.SetFramerateLimit(fpslimit);
    App.SetIcon(16, 16, gImageManager.getResource("icon.png")->GetPixelsPtr());
    createMenus();
    hud.createHud(game.getLevel().getInfos().size);
}

Engine::~Engine()
{

}

void Engine::createMenus()
{
    const float middleX = App.GetWidth()/2.f, middleY = App.GetHeight()/2.f;
    mainMenu.addButton(Button("Play Game!", middleY-160),
                          boost::bind(&Engine::runGame, this));
    mainMenu.addButton(Button("Create Level", middleY-40),
                          boost::bind(&Engine::runEditor, this));
    mainMenu.addButton(Button("Quit", middleY+80),
                          boost::bind(&Engine::exit, this));

    Button resume("Resume", Vector2f(middleX-150, middleY-150), BUTTON_HALF_SIZE);
    Button exit("Exit", Vector2f(middleX+10, middleY-150), BUTTON_HALF_SIZE);

    gameMenu.addButton(resume, boost::bind(&Engine::resume, this));
    gameMenu.addButton(exit, boost::bind(&Engine::toMainMenu, this));
    gameMenu.addButton(Button("Open Tower", middleY-25, BUTTON_WIDE_SIZE),
                        boost::bind(&Engine::buttonLoadTower, this), true);
    gameMenu.addButton(Button("Open Level", middleY+90, BUTTON_WIDE_SIZE),
                        boost::bind(&Engine::buttonLoadLevel, this), true);

    editorMenu.addButton(resume, boost::bind(&Engine::resume, this));
    editorMenu.addButton(exit, boost::bind(&Engine::toMainMenu, this));
    editorMenu.addButton(Button("Save Level", middleY-25, BUTTON_WIDE_SIZE),
                        boost::bind(&Engine::buttonSave, this), true);
    editorMenu.addButton(Button("Open Level", middleY+90, BUTTON_WIDE_SIZE),
                        boost::bind(&Engine::buttonLoad, this), true);
}

bool Engine::loadLevel(const std::string &filename)
{
    bool ok = game.loadLevel(filename);
    if (ok && gv.sizeChanged)
    {
        resetView();
        hud.createHud(game.getLevel().getInfos().size);
        hud.newGameStarted();
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

void Engine::initializeGame(const bool &newlvl)
{
    game.initializeGame(newlvl);
    hud.newGameStarted();
}

void Engine::drawHud(const bool &inGame)
{
    if (!gv.compatibilityMode)
        App.Draw(hud.drawHud(cats.size(), mouse.remainingLifes(), inGame));
    else
        hud.renderToOtherTarget(cats.size(), mouse.remainingLifes(), inGame);
}

void Engine::drawFps()
{
    if (gv.debugMode)
        hud.drawFps(App, App.GetFrameTime());
}

void Engine::resetView()
{
    const LevelInformations &infos = game.getLevel().getInfos();
    Vector2f screenRealSize(infos.size.x * CASE_SIZE,
                            infos.size.y * CASE_SIZE + HUD_HEIGHT);
    gameView.SetCenter(screenRealSize.x/2, screenRealSize.y/2);
    gameView.SetSize(screenRealSize);
}

void Engine::run()
{
    if (!running)
        return;
    App.SetView(App.GetDefaultView());
    mainMenu.run(App, hud, resume);
}

void Engine::runGame()
{
    bool astar = true;
    gLog << "Launching game...\n";
    if (!loadLevel(game.getCurrentLevelName()))
        loadLevel("data/1.txt");
    game.testTower();
    initializeGame();
    App.SetView(gameView);
    const Input &Input = App.GetInput();
    while (App.IsOpened() && running)
    {
        const float dt = App.GetFrameTime();
        if (Input.IsKeyDown(Key::Add))
            gameView.Zoom(1.f - dt);
        else if (Input.IsKeyDown(Key::Subtract))
            gameView.Zoom(1.f + dt);

        Event Event;
        while (App.GetEvent(Event))
        {
            if (Event.Type == Event::Closed)
                App.Close();
            if (Event.Type == Event::KeyPressed)
            {
                if (!USE_WINDOWGUI && Event.Key.Code == Key::Escape)
                {
                    if (menuGame() || quitToMainMenu)
                    {
                        quitToMainMenu = false;
                        run();
                    }
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
                if (Event.Key.Code == Key::Z)
                    resetView();
                else if (Event.Key.Code == Key::E)
                {
                    gameView.Reset(FloatRect(0, 0, SCREEN_W, SCREEN_H));
                    gameView.SetCenter(mouse.pos().x * CASE_SIZE, mouse.pos().y * CASE_SIZE);
                }
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
            run();

        App.Clear();

        game.renderTower(App);
        static l_cats::const_iterator iter;
        for (iter = cats.begin(); iter != cats.end(); iter++)
            App.Draw(iter->sprite());
        App.Draw(mouse.sprite());
        drawHud(true);
        App.SetView(App.GetDefaultView());
            drawFps();
        App.SetView(gameView);

        App.Display();
    }
}

bool Engine::menuGame()
{
    if (!running)
        return true;
    App.SetView(App.GetDefaultView());
    return gameMenu.run(App, hud, resume, game.getCurrentLevelName());
}

void Engine::buttonLoadLevel()
{
    const std::string file = gameMenu.currentString();
    if (file.empty())
        return;
    if (loadLevel(file))
        closeMenu();
}

void Engine::buttonLoadTower()
{
    const std::string file = gameMenu.currentString();
    if (file.empty())
        return;
    if (loadTower(file))
        closeMenu();
}

void Engine::runEditor()
{
    gLog << "Launching level editor...\n";
    if (!loadLevel(game.getCurrentLevelName()))
        loadLevel("data/1.txt");
    hud.newGameStarted();
    mouse.setPosition(game.getLevel().getInfos().mouseStartPos);
    CASETYPE casetype = BLOCK;
    App.SetView(gameView);
    const Input &Input = App.GetInput();
    while (App.IsOpened() && running)
    {
        Vector2f mousepos = App.ConvertCoords(App.GetInput().GetMouseX(),
                                              App.GetInput().GetMouseY());

        const float dt = App.GetFrameTime();
        if (Input.IsKeyDown(Key::Add))
            gameView.Zoom(1.f - dt);
        else if (Input.IsKeyDown(Key::Subtract))
            gameView.Zoom(1.f + dt);

        Event Event;
        while (App.GetEvent(Event))
        {
            if (Event.Type == Event::Closed)
                App.Close();
            if (Event.Type == Event::KeyPressed)
            {
                if (!USE_WINDOWGUI && Event.Key.Code == Key::Escape)
                {
                    if (menuEditor() || quitToMainMenu)
                    {
                        quitToMainMenu = false;
                        run();
                    }
                    App.SetView(gameView);
                }
                if (Event.Key.Code == Key::F12)
                    gv.debugMode = !gv.debugMode;
                if (Event.Key.Code == Key::M)
                    game.placeMouse(mousepos);
                if (Event.Key.Code == Key::Z)
                    resetView();
                if (Event.Key.Code == Key::Num1 || Event.Key.Code == Key::Numpad1)
                    casetype = BLOCK;
                if (Event.Key.Code == Key::Num2 || Event.Key.Code == Key::Numpad2)
                    casetype = WALL;
            }
        }

        if (mousepos.x > 0 && mousepos.y > 0)
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
        App.SetView(App.GetDefaultView());
            drawFps();
        App.SetView(gameView);

        App.Display();
    }
}

bool Engine::menuEditor()
{
    if (!running)
        return true;
    App.SetView(App.GetDefaultView());
    return editorMenu.run(App, hud, resume, game.getCurrentLevelName());
}

void Engine::buttonSave()
{
    const std::string file = editorMenu.currentString();
    if (file.empty())
        return;
    if (game.saveLevel(file))
        closeMenu();
}

void Engine::buttonLoad()
{
    const std::string file = editorMenu.currentString();
    if (file.empty())
        return;
    if (loadLevel(file))
        closeMenu();
}
