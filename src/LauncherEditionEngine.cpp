#include <iostream>
#include "LauncherEditionEngine.hpp"

using namespace sf;

LauncherEditionEngine::LauncherEditionEngine(RenderWindow &window,
    const bool &vsync,  const unsigned int &fpslimit) : App(window),
    gameView(FloatRect(0, 0, SCREEN_W, SCREEN_H)), game(),
    cats(game.getCatsList()), mouse(game.getMouse())
{
    App.UseVerticalSync(vsync);
    App.SetFramerateLimit(fpslimit);
    App.SetIcon(16, 16, gImageManager.getResource("icon.png")->GetPixelsPtr());
}

LauncherEditionEngine::~LauncherEditionEngine()
{

}

void LauncherEditionEngine::resetView()
{
    const LevelInformations &infos = game.getLevel().getInfos();
    Vector2f screenRealSize(infos.size.x * CASE_SIZE,
                            infos.size.y * CASE_SIZE + HUD_HEIGHT);
    gameView.SetCenter(screenRealSize.x/2, screenRealSize.y/2);
    gameView.SetSize(screenRealSize);
}

void LauncherEditionEngine::runAsGame(const std::string &level,
            const int &nbOfCats, const int &nbOfRW)
{
    std::cout << "Launching game...\n";
    if (!game.loadLevel(level, Vector2i(DLVL_X, DLVL_Y), nbOfCats,
                        nbOfRW))
    {
        std::cerr << "Error : cannot load level '" << level
                        << "'. Game will now exit.\n";
        return;
    }
    resetView();
    hud.createHud(game.getLevel().getInfos().size);
    hud.newGameStarted();
    gv.sizeChanged = false;
    App.SetView(gameView);
    bool astar = true;

    const Input &Input = App.GetInput();
    while (App.IsOpened())
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
            return;

        App.Clear();

        game.renderTower(App);
        for (unsigned int i = 0; i < cats.size(); i++)
            App.Draw(cats[i].sprite());
        App.Draw(mouse.sprite());
        App.Draw(hud.drawHud(cats.size(), mouse.remainingLifes(), true));
        if (gv.debugMode)
        {
            App.SetView(App.GetDefaultView());
                hud.drawFps(App, App.GetFrameTime());
            App.SetView(gameView);
        }
        App.Display();
    }
}

void LauncherEditionEngine::runAsEditor(const std::string &level,
    const sf::Vector2i &sizeIfEmpty,
    const bool &noWarningAtSave)
{
    std::cout << "Launching level editor...\n";
    if (!game.loadLevel(level, sizeIfEmpty))
    {
        std::cerr << "Error : cannot load level '" << level
                        << "'. Game will now exit.\n";
        return;
    }
    resetView();
    hud.createHud(game.getLevel().getInfos().size);
    hud.newGameStarted();
    gv.sizeChanged = false;
    App.SetView(gameView);
    mouse.setPosition(game.getLevel().getInfos().mouseStartPos);
    CASETYPE casetype = BLOCK;

    const Input &Input = App.GetInput();
    while (App.IsOpened())
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
        if (gv.debugMode)
        {
            App.SetView(App.GetDefaultView());
                hud.drawFps(App, App.GetFrameTime());
            App.SetView(gameView);
        }
        App.Display();
    }
}