#ifndef TRAP_HPP
#define TRAP_HPP

#include "TiledEntity.hpp"

/** A trap immobilizes (holes) or kills (mousetrap) the Mouse.
*/
class Trap : public TiledEntity
{
public:
    /** Default constructor.
    *@param x X position (in tiles units).
    *@param y Y position (in tiles units).
    *@param deadly Is the trap deadly?
    */
    Trap(int x, int y, bool deadly);

    /** Is the trap deadly?
    *@return True if deadly, false otherwise.
    */
    bool deadly() const { return mDeadly; }

private:
    const bool mDeadly;
};

#endif // TRAP_HPP
