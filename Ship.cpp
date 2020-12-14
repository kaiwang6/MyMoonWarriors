#include "Ship.h"

Ship::Ship()
:_active(true)
{}

bool Ship::init()
{
	return true;
}

void Ship::shoot(float dt)
{

}
void Ship::hurt()
{

}
void Ship::destroy()
{

}
Rect Ship::collideRect() 
{
	return Rect(0, 0, 0, 0);
}
void Ship::isActive() 
{

}