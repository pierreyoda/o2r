#include <iostream>
#include <sstream>
#include "Engine.hpp"
#include "constantes.hpp"
#include "LevelFileInterpreter.hpp"
#include "gui/TextBox.hpp"
#include "gui/Button.hpp"

using namespace sf;

// TODO (Pierre-Yves#2#): [RESSOURCES] Ajouter le système de pré-chargements=FAIT (+ thread? + écran de chargement? + fichier texte avec images à charger?=FAIT )
// TODO (Pierre-Yves#3#): [OPTIMISATION] Transformer std::list<Cat> en std::list<Cat> (--> vector inutiles et moins performants).
Engine::Engine(sf::RenderWindow &window, const bool &vsync,
               const unsigned int &fpslimit) : App(window),
    level(), cats(), mouse(level, cats), sScore(), sNbOfCats(), hudBackground(),
    currentLevel(""), gameView(), gameViewZoomFactor(10)
{
    gameView.SetFromRect(FloatRect(0, 0, gv.SCREEN_W, gv.SCREEN_H));
    initializeHud();

    App.UseVerticalSync(vsync);
    App.SetFramerateLimit(fpslimit);
    App.SetIcon(16, 16, gImageManager.getResource(gv.currentTheme + "icon.png")
                ->GetPixelsPtr());
}

Engine::~Engine()
{
    cats.clear();
}

bool Engine::loadLevel(const std::string &filename)
{
    if (filename == "")
        return false;
    if (!LevelFileInterpreter::readLevel(level, filename))
    {
        level.resetLevel();
        return false;
    }
    currentLevel = filename;
    if (gv.sizeChanged)
    {
        initializeHud();
        gv.sizeChanged = false;
    }
    return true;
}

void Engine::initializeGame(const bool &newlvl)
{
    std::cout << "Initializing game." << std::endl;
    gv.score = 0;
    cats.clear();
    if (!newlvl)
        loadLevel("data/1.txt");
    level.randomWalls();
    mouse.setPosition(level.getMouseStartPos());
    for (unsigned int i = 0; i < gv.nbOfCats; i++)
    {
        Cat cat;
        cat.placeCat(level, cats);
        cats.push_back(cat);
    }
}

void Engine::initializeHud()
{
    Vector2f refPos(0, gv.SCREEN_H-HUD_HEIGHT);
    hudBackground = Shape::Rectangle(refPos, Vector2f(gv.SCREEN_W, gv.SCREEN_H),
                                     Color(0, 128, 128));
    // Game
    sScore.SetPosition(refPos);
        sScore.SetText("Score: " + gv.nbToText(gv.score));
    sNbOfCats.SetPosition(gv.SCREEN_W-130.f, refPos.y);
        sNbOfCats.SetText("Cats: " + gv.nbToText(cats.size()));
    // Editor
    Vector2f posBlock(refPos);
    Vector2f posWall(gv.SCREEN_W/2-40.f, refPos.y);
    Vector2f posMouse(gv.SCREEN_W-80.f, refPos.y);
    sEditorBlock.SetPosition(posBlock);
        sEditorBlock.SetText("1 : ");
    sEditorWall.SetPosition(posWall);
        sEditorWall.SetText("2 : ");
    sEditorMouse.SetPosition(posMouse);
        sEditorMouse.SetText("M : ");
    // Editor - Images
    static const float gap = 40.f;
    editorBlock.SetImage(*gImageManager.getResource(gv.currentTheme+"block.png"));
        editorBlock.SetPosition(posBlock.x + gap, posBlock.y + gap/3);
    editorWall.SetImage(*gImageManager.getResource(gv.currentTheme+"wall.png"));
        editorWall.SetPosition(posWall.x + gap, posWall.y + gap/3);
    Image &img = *gImageManager.getResource(gv.currentTheme+"mouse.png");
    editorMouse.SetImage(img);
        editorMouse.SetPosition(posMouse.x + gap + 10.f, posMouse.y + gap/3);
        img.CreateMaskFromColor(Color(128, 128, 0));
}

void Engine::drawHud(const bool &ingame, const bool &ineditor)
{
    if (gv.debugMode)
            GameVariables::drawFps(App);
    if (ingame)
    {
        App.Draw(hudBackground);
        sScore.SetText("Score: " + gv.nbToText(gv.score));
        App.Draw(sScore);
        sNbOfCats.SetText("Cats: " + gv.nbToText(cats.size()));
        App.Draw(sNbOfCats);
    }
    else if (ineditor)
    {
        App.Draw(hudBackground);
        App.Draw(sEditorBlock);
        App.Draw(sEditorWall);
        App.Draw(sEditorMouse);
        App.Draw(editorBlock);
        App.Draw(editorWall);
        App.Draw(editorMouse);
    }
}

// TODO (Pierre-Yves#1#): [GENERAL]Ajouter zoom automatique pour niveaux de tailles non standards...
void Engine::zoom(const bool &in)
{
    if (in)
    {
        ++gameViewZoomFactor;
        gameView.Zoom(1.1);
    }
    else
    {
        --gameViewZoomFactor;
        gameView.Zoom(0.9);
    }
}

void Engine::returnToNormalZoom()
{
    while (gameViewZoomFactor != 10)
    {
        if (gameViewZoomFactor > 10)
            zoom(false);
        else if (gameViewZoomFactor < 10)
            zoom(true);
    }
}

void Engine::run()
{
    const float middleX = App.GetWidth()/2.f, middleY = App.GetHeight()/2.f;
    std::vector<Button> buttons;
    buttons.push_back(Button("Play Game!", Vector2f(middleX-125, middleY-150),
                      Vector2f(middleX+125, middleY-50)));
    buttons.push_back(Button("Create Level", Vector2f(middleX-125, middleY-25),
                        Vector2f(middleX+125, middleY+80)));
    buttons.push_back(Button("Quit", Vector2f(middleX-125, middleY+90),
                        Vector2f(middleX+125, middleY*2-5)));

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
                    App.Close();
                if (Event.Key.Code == Key::F12)
                    gv.debugMode = !gv.debugMode;
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
                    runGame();
                else if (buttons[1].isMouseOver(mousePos))
                    runEditor();
                else if (buttons[2].isMouseOver(mousePos))
                    App.Close();
                App.SetView(App.GetDefaultView());
            }
        }

        App.Clear(Color(0, 128, 0));

        for (unsigned int i = 0; i < buttons.size(); i++)
        {
            App.Draw(buttons[i].getBorder());
            App.Draw(buttons[i].getString());
        }
        drawHud();

        App.Display();
    }
}

void Engine::runGame()
{
    std::cout << "Launching game..." << std::endl;
    if (!loadLevel(currentLevel))
        loadLevel("data/1.txt");
    initializeGame();
    App.SetView(gameView);
    while (App.IsOpened())
    {
        Event Event;
        while (App.GetEvent(Event))
        {
            if (Event.Type == Event::Closed)
                App.Close();
            if (Event.Type == Event::KeyPressed)
            {
                if (Event.Key.Code == Key::Escape)
                {
                    if (menuGame())
                        return;
                    App.SetView(gameView);
                }
                if (Event.Key.Code == Key::F12)
                    gv.debugMode = !gv.debugMode;
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
                if (Event.Key.Code == Key::Add)
                    zoom(true);
                if (Event.Key.Code == Key::Subtract)
                    zoom(false);
                if (Event.Key.Code == Key::Numpad5 ||Event.Key.Code == Key::Return)
                    returnToNormalZoom();
            }
        }

        for (unsigned int i = 0; i < cats.size(); i++)
        {
            if (cats[i].isAlive())
            {
                cats[i].moveCat(level, mouse.pos(), cats, true);
                if (cats[i].cannotMoveNb() > 0)
                    cats[i].setImage(*gImageManager.getResource
                                     (gv.currentTheme+"cat_awaiting.png"));
                else
                    cats[i].setImage(*gImageManager.getResource(gv.currentTheme+"cat.png"));
                if (cats[i].cannotMoveNb() >= gv.catsCannotMoveNbBeforeDead)
                    cats[i].die();
            }
        }

        App.Clear();

        level.render(App);
        for (unsigned int i = 0; i < cats.size(); i++)
            App.Draw(cats[i].sprite());
        App.Draw(mouse.sprite());
        drawHud(true);

        App.Display();
    }
}

bool Engine::menuGame()
{
    const float middleX = App.GetWidth()/2.f, middleY = App.GetHeight()/2.f;
    bool writing = false;
    TextBox textBox(0, currentLevel);
    std::vector<Button> buttons;
    buttons.push_back(Button("Resume", Vector2f(middleX-175, middleY-150),
                             Vector2f(middleX-10, middleY-50)));
    buttons.push_back(Button("Exit", Vector2f(middleX+10, middleY-150),
                             Vector2f(middleX+175, middleY-50)));
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
                    if (loadLevel(textBox.getText()))
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
                    writing = true;
            }
        }

        App.Clear(Color(0, 128, 0));
            for (unsigned int i = 0; i < buttons.size(); i++)
            {
                App.Draw(buttons[i].getBorder());
                App.Draw(buttons[i].getString());
            }
            if (writing)
                App.Draw(textBox.getString());
            drawHud();
        App.Display();
    }
    return true;
}

void Engine::runEditor()
{
    std::cout << "Launching level editor..." << std::endl;
    if (!loadLevel(currentLevel))
        loadLevel("data/1.txt");
    mouse.setPosition(level.getMouseStartPos());
    CASETYPE casetype = BLOCK;
    App.SetView(gameView);
    while (App.IsOpened())
    {
        const Input &Input = App.GetInput();
        Vector2f mousepos = App.ConvertCoords(App.GetInput().GetMouseX(),
                                              App.GetInput().GetMouseY());

        Event Event;
        while (App.GetEvent(Event))
        {
            if (Event.Type == Event::Closed)
                App.Close();
            if (Event.Type == Event::KeyPressed)
            {
                if (Event.Key.Code == Key::Escape)
                {
                    if (menuEditor())
                        return;
                    App.SetView(gameView);
                }
                if (Event.Key.Code == Key::F12)
                    gv.debugMode = !gv.debugMode;
                if (Event.Key.Code == Key::M)
                    placeMouse(mousepos);
                if (Event.Key.Code == Key::Num1 || Event.Key.Code == Key::Numpad1)
                    casetype = BLOCK;
                if (Event.Key.Code == Key::Num2 || Event.Key.Code == Key::Numpad2)
                    casetype = WALL;
                if (Event.Key.Code == Key::Add)
                    gameView.Zoom(1.1f);
                if (Event.Key.Code == Key::Subtract)
                    gameView.Zoom(0.9f);
            }
        }

        if (mousepos.x < gv.SCREEN_W && mousepos.y < gv.SCREEN_H-HUD_HEIGHT)
        {
            if (Input.IsMouseButtonDown(sf::Mouse::Left))
                placeCaseType(mousepos, casetype);
            else if (Input.IsMouseButtonDown(sf::Mouse::Right))
                clearCase(mousepos);
        }

        App.Clear();

        level.render(App);
        App.Draw(mouse.sprite());
        drawHud(false, true);

        App.Display();
    }
}

// TODO (Pierre-Yves#1#): [LEVEL-EDITOR] Ajouter gestion automatique du nombre de chats et de murs aléatoires dans le niveau (menu?)
bool Engine::menuEditor()
{
    bool writing = false, save = false;
    TextBox textBox(0, currentLevel);
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
                    if (save && LevelFileInterpreter::writeLevel(level, textBox.getString().GetText()))
                    {
                        currentLevel = textBox.getString().GetText();
                        writing = save = false;
                        return false;
                    }
                    else
                    {
                        loadLevel(textBox.getString().GetText());
                        mouse.setPosition(level.getMouseStartPos());
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
                App.Draw(buttons[i].getString());
            }
            if (writing)
                App.Draw(textBox.getString());
            drawHud();
        App.Display();
    }
    return true;
}

void Engine::clearCase(const Vector2f &mousepos)
{
    level.setCaseType(pixelToCase(mousepos), NOTHING);
}

void Engine::placeCaseType(const Vector2f &mousepos, const CASETYPE &type)
{
    Vector2i pos = pixelToCase(mousepos);
    if (pos != level.getMouseStartPos())
        level.setCaseType(pos, type);
}

void Engine::placeMouse(const Vector2f &mousepos)
{
    Vector2i pos = pixelToCase(mousepos);
    level.setCaseType(pos, NOTHING);
    level.setMouseStartPos(pos);
    mouse.setPosition(pos);
}

Vector2i Engine::pixelToCase(const Vector2f &pos)
{
    unsigned int x = static_cast<unsigned int>(pos.x/CASE_SIZE);
    unsigned int y = static_cast<unsigned int>(pos.y/CASE_SIZE);
    return Vector2i(x, y);
}
