#include "Trap.hpp"

Trap::Trap(int x, int y, bool deadly) :
    TiledEntity(x, y, deadly? "mousetrap.png" : "hole.png"), mDeadly(deadly)
{
}
