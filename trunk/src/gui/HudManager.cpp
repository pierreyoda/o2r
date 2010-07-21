#include "HudManager.hpp"
#include "../tools/ImageManager.hpp"
#include "../Level.hpp"

using namespace sf;

const Color HUD_BACKGROUND_COLOR(0, 128, 128);
const unsigned int NB_OF_LIVES_BAD_DISPLAY = 6;

HudManager::HudManager(RenderTarget *otherTarget) : otherTarget(otherTarget),
    m_gamestart(true)
{
    renderTarget.Create(SCREEN_W, HUD_HEIGHT);
        renderResult.SetImage(renderTarget.GetImage());
        renderResult.SetPosition(0, SCREEN_H-HUD_HEIGHT);
    remainingLifesTarget.Create(SCREEN_W,
                gImageManager.getResource("lives.png")->GetHeight());
        remainingLifes.SetImage(remainingLifesTarget.GetImage());
}

HudManager::~HudManager()
{

}

void HudManager::createHud(const Vector2i &levelSize, const bool &useOtherTarget)
{
    const Vector2i screenRealSize(levelSize.x * CASE_SIZE,
        levelSize.y * CASE_SIZE);
    renderTarget.Create(screenRealSize.x, HUD_HEIGHT);
    renderResult = Sprite(renderTarget.GetImage(),
        Vector2f(0.f, screenRealSize.y));
    Vector2f refPos(0, 0);
    if (useOtherTarget && otherTarget != 0)
        refPos.y = screenRealSize.x;

    score.SetPosition(refPos);
        score.SetString("Score: " + gv.nbToText(gv.score));
    nbOfCats.SetPosition(SCREEN_W-130.f, refPos.y);
    // Background (used in compatibility mode)
    background = Shape::Rectangle(refPos.x, screenRealSize.y,
        screenRealSize.x, HUD_HEIGHT, HUD_BACKGROUND_COLOR);
    // Editor
    const Vector2f posBlock(refPos);
    const Vector2f posWall(SCREEN_W/2-40.f, refPos.y);
    const Vector2f posMouse(SCREEN_W-80.f, refPos.y);
    editorBlock.SetPosition(posBlock);
        editorBlock.SetString("1 : ");
    editorWall.SetPosition(posWall);
        editorWall.SetString("2 : ");
    editorMouse.SetPosition(posMouse);
        editorMouse.SetString("M : ");
    // Editor - Images
    static const float gap = 40.f;
    sEditorBlock.SetImage(*Level::charToImage(CHAR_BLOCK));
        sEditorBlock.SetPosition(posBlock.x + gap, posBlock.y + gap/3);
    sEditorWall.SetImage(*Level::charToImage(CHAR_WALL));
        sEditorWall.SetPosition(posWall.x + gap, posWall.y + gap/3);
    Image *img = gImageManager.getResource("mouse.png");
    sEditorMouse.SetImage(*img);
        sEditorMouse.SetPosition(posMouse.x + gap + 10.f, posMouse.y + gap/3);
        img->CreateMaskFromColor(Color(128, 128, 0));

    remainingLifes.SetY(refPos.y + HUD_HEIGHT/3);
    updateNbOfRemainingLifes(DEFAULT_NB_OF_LIVES);
}

void HudManager::newGameStarted()
{
    m_gamestart = true;
}

const Sprite &HudManager::drawHud(const unsigned int &catsNb,
    const unsigned int &remainingLifesNb, const bool &inGame)
{
    if (!m_gamestart && (!updateScore() &&
            !updateNbOfCats(catsNb) &&
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

void HudManager::renderToOtherTarget(const unsigned int &catsNb,
            const unsigned int &remainingLifesNb, const bool &inGame)
{
    if (otherTarget == 0)
        return;

    updateScore();
    updateNbOfCats(catsNb);
    updateNbOfRemainingLifes(remainingLifesNb);
    m_gamestart = false;

    otherTarget->Draw(background);
    if (inGame)
    {
        otherTarget->Draw(score);
        otherTarget->Draw(nbOfCats);
    }
    else
    {
        otherTarget->Draw(editorBlock);
        otherTarget->Draw(editorWall);
        otherTarget->Draw(editorMouse);
        otherTarget->Draw(sEditorBlock);
        otherTarget->Draw(sEditorWall);
        otherTarget->Draw(sEditorMouse);
    }
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

bool HudManager::updateNbOfRemainingLifes(const unsigned int &remainingLifesNb)
{
    RenderTarget *target = &remainingLifesTarget;
    Vector2f refPoint(0.f, 0.f);
    if (gv.compatibilityMode)
    {
        if (m_gamestart)
            return true;
        if (otherTarget != 0)
        {
            refPoint.y = SCREEN_H;
            otherTarget = otherTarget;
        }
    }
    static unsigned int prevRemainingLifes = 0;
    if (gv.compatibilityMode || prevRemainingLifes != remainingLifesNb)
    {
        if (!gv.compatibilityMode)
            prevRemainingLifes = remainingLifesNb;
        if (remainingLifesNb == 0)
        {
            if (!gv.compatibilityMode)
            {
                remainingLifesTarget.Create(1, 1);
                target->Clear(Color(0, 0, 0, 0));
                remainingLifesTarget.Display();
            }
            return true;
        }
        Sprite temp(*gImageManager.getResource("lives.png"));
        static const float space = temp.GetImage()->GetWidth()
            + HUD_SPACE_BETWEEN_LIFES;
        if (remainingLifesNb < NB_OF_LIVES_BAD_DISPLAY)
        {
            if (!gv.compatibilityMode)
            {
                remainingLifesTarget.Create(int(space*remainingLifesNb),
                                            int(temp.GetImage()->GetHeight()));
                target->Clear(Color(0, 0, 0, 0));
            }
            for (unsigned int i = 0; i <= remainingLifesNb; i++)
            {
                temp.SetPosition(refPoint.x + space * i, refPoint.y);
                target->Draw(temp);
            }
            if (!gv.compatibilityMode)
            {
                remainingLifesTarget.Display();
                remainingLifes = Sprite(remainingLifesTarget.GetImage());
            }
            remainingLifes.SetY(refPoint.y + HUD_HEIGHT/3);
            remainingLifes.SetX(refPoint.x + (SCREEN_W/2 -
                                 remainingLifes.GetImage()->GetWidth()/2));
        }
        else
        {
            Text temp2(gv.nbToText(remainingLifesNb));
                temp2.SetCharacterSize(20);
                temp2.SetY(refPoint.y + temp.GetImage()->GetHeight()/2 -
                    temp2.GetRect().Height/2);
            if (!gv.compatibilityMode)
            {
                remainingLifesTarget.Create(temp2.GetRect().Width + space/4+
                    temp.GetImage()->GetWidth(), temp.GetImage()->GetHeight()
                    +space);
                remainingLifesTarget.Clear(Color(0, 0, 0, 0));
            }
            remainingLifesTarget.Draw(temp2);
            temp.SetX(refPoint.x + temp2.GetRect().Width + space/4);
            target->Draw(temp);
            if (!gv.compatibilityMode)
            {
                remainingLifesTarget.Display();
                remainingLifes = Sprite(remainingLifesTarget.GetImage());
                remainingLifes.SetY(HUD_HEIGHT/3);
                remainingLifes.SetX(SCREEN_W/2 - remainingLifesTarget.GetWidth()/2);
            }
        }
        return true;
    }
    return false;
}

void HudManager::drawFps(RenderTarget &target, const float &fpsCount,
                         const Vector2i &screenSize)
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
            text.SetPosition(screenSize.x-size.x, screenSize.y-size.y);
            resetpos = false;
        }
        refreshClock.Reset();
    }
    target.Draw(text);
}

