#include "HudManager.hpp"
#include "../GlobalVariables.hpp"
#include "../tools/ImageManager.hpp"

using namespace sf;

const Color HUD_BACKGROUND_COLOR(0, 128, 128);

HudManager::HudManager() : m_gamestart(true)
{
    renderTarget.Create(SCREEN_W, HUD_HEIGHT);
        renderResult.SetImage(renderTarget.GetImage());
        renderResult.SetPosition(0, SCREEN_H-HUD_HEIGHT);
    remainingLifesTarget.Create(SCREEN_W,
                gImageManager.getResource("lifes.png")->GetHeight());
        remainingLifes.SetImage(remainingLifesTarget.GetImage());
}

void HudManager::createHud(const Vector2i &levelSize)
{
    Vector2i screenRealSize(levelSize.x * CASE_SIZE, levelSize.y * CASE_SIZE);
    renderTarget.Create(screenRealSize.x, HUD_HEIGHT);
    renderResult = Sprite(renderTarget.GetImage(), Vector2f(0.f, screenRealSize.y));
    Vector2f refPos(0, 0);

    score.SetPosition(refPos);
        score.SetString("Score: " + gv.nbToText(gv.score));
    nbOfCats.SetPosition(SCREEN_W-130.f, refPos.y);
    // Editor
    Vector2f posBlock(refPos);
    Vector2f posWall(SCREEN_W/2-40.f, refPos.y);
    Vector2f posMouse(SCREEN_W-80.f, refPos.y);
    editorBlock.SetPosition(posBlock);
        editorBlock.SetString("1 : ");
    editorWall.SetPosition(posWall);
        editorWall.SetString("2 : ");
    editorMouse.SetPosition(posMouse);
        editorMouse.SetString("M : ");
    // Editor - Images
    static const float gap = 40.f;
    sEditorBlock.SetImage(*gImageManager.getResource("block.png"));
        sEditorBlock.SetPosition(posBlock.x + gap, posBlock.y + gap/3);
    sEditorWall.SetImage(*gImageManager.getResource("wall.png"));
        sEditorWall.SetPosition(posWall.x + gap, posWall.y + gap/3);
    Image &img = *gImageManager.getResource("mouse.png");
    sEditorMouse.SetImage(img);
        sEditorMouse.SetPosition(posMouse.x + gap + 10.f, posMouse.y + gap/3);
        img.CreateMaskFromColor(Color(128, 128, 0));

    remainingLifes.SetY(refPos.y + HUD_HEIGHT/3);
    updateNbOfRemainingLifes(DEFAULT_NB_OF_LIFES);

}

void HudManager::newGameStarted()
{
    m_gamestart = true;
}

const Sprite &HudManager::drawHud(const unsigned int &catsNb,
    const unsigned int &remainingLifesNb, const bool &inGame)
{
    if (!m_gamestart && (!updateScore() && !updateNbOfCats(catsNb) &&
            !updateNbOfRemainingLifes(remainingLifesNb)))
        return renderResult;
    m_gamestart = false;

    renderTarget.Clear(HUD_BACKGROUND_COLOR);
        if (inGame)
        {
            renderTarget.Draw(score);
            renderTarget.Draw(nbOfCats);
            renderTarget.Draw(remainingLifes);
        }
        else
        {
            renderTarget.Draw(editorBlock);
            renderTarget.Draw(editorWall);
            renderTarget.Draw(editorMouse);
            renderTarget.Draw(sEditorBlock);
            renderTarget.Draw(sEditorWall);
            renderTarget.Draw(sEditorMouse);
        }
    renderTarget.Display();

    return renderResult;
}

bool HudManager::updateScore()
{
    static unsigned int prevScore = 0;
    if (prevScore != gv.score)
    {
        score.SetString("Score: " + gv.nbToText(gv.score));
        prevScore = gv.score;
        return true;
    }
    return false;
}

bool HudManager::updateNbOfCats(const unsigned int &catsNb)
{
    static unsigned int prevCatsNb = 0;
    if (prevCatsNb != catsNb)
    {
        nbOfCats.SetString("Cats: " + gv.nbToText(catsNb));
        prevCatsNb = catsNb;
        return true;
    }
    return false;
}

// TODO (Pierre-Yves#2#): [HUD] Gérer l'affichage CORRECT d'un "grand" nombre de vie (~ > 4) === afficher l'icone de vie avec un texte à côté
bool HudManager::updateNbOfRemainingLifes(const unsigned int &remainingLifesNb)
{
    static unsigned int prevRemainingLifes = 0;
    if (prevRemainingLifes != remainingLifesNb)
    {
        prevRemainingLifes = remainingLifesNb;
        if (remainingLifesNb == 0)
        {
            remainingLifesTarget.Create(1, 1);
            remainingLifesTarget.Clear(Color(0, 0, 0, 0));
            remainingLifesTarget.Display();
            return true;
        }
        Sprite temp(*gImageManager.getResource("lifes.png"));
        const float space = temp.GetImage()->GetWidth() + HUD_SPACE_BETWEEN_LIFES;
        remainingLifesTarget.Create(int(space*remainingLifesNb), int(temp.GetImage()->GetHeight()));
        remainingLifesTarget.Clear(Color(0, 0, 0, 0));
        for (unsigned int i = 0; i <= remainingLifesNb; i++)
        {
            temp.SetX(space * i);
            remainingLifesTarget.Draw(temp);
        }
        remainingLifesTarget.Display();
        remainingLifes.SetX((SCREEN_W/2 - remainingLifes.GetImage()->GetWidth()/2));

        return true;
    }
    return false;
}

void HudManager::drawFps(RenderTarget &target, const float &fpsCount)
{
    static bool init = false, resetpos = true;
    static Clock refreshClock;
    static Text text;
    if (!init || refreshClock.GetElapsedTime() >= 1.f)
    {
        if (!init)
        {
            text.SetString("60");
            text.SetCharacterSize(20);
            init = true;
        }
        float fps = 1.f / fpsCount;
        if (fps < 0)
        {
            fps = 0;
            resetpos = true;
        }
        else if (fps < 100)
            resetpos = true;
        else
            resetpos = true;
        text.SetString(gv.nbToText(static_cast<int>(fps)));
        if (resetpos)
        {
            Vector2f size(text.GetRect().Width, text.GetRect().Height);
            text.SetPosition(SCREEN_W-size.x, SCREEN_H-size.y);
            resetpos = false;
        }
        refreshClock.Reset();
    }
    target.Draw(text);
}

