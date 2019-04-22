#include <vector>
#include <iostream>
#include "map.hpp"
#include "player.hpp"
#include "Windows.h"
using namespace std;

player::player(map* m) //peramaterized constructor
{
  posX = 1;
  posY = 23;
  this->m = m;
  jumpCounter = 0;
}
void player::reset(map* m) // basically the same as the constructor, but with a new map
{
  posX = 1;
  posY = 23;
  this->m = m;
  jumpCounter = 0;
}
int player::getPosX()
{
  return posX;
}
int player::getPosY()
{
  return posY;
}
bool player::update() //This function checks if the player has moved, and returns true if it has
{
  bool updated = false;
  if (GetKeyState(0x41) < 0 || GetKeyState(VK_LEFT) < 0) //has the player moved left?
  {
    if (m->getCollision(posX-1,posY) == false)
      posX = posX - 1;
      updated = true;
  }
  else if (GetKeyState(0x44) < 0 || GetKeyState(VK_RIGHT) < 0) //has the player moved right?
  {
    if (m->getCollision(posX+1,posY) == false)
      posX = posX + 1;
      updated = true;
  }
  if (GetKeyState(VK_SPACE) < 0 || GetKeyState(VK_UP) < 0 || GetKeyState(0x57) < 0) //has the player tried to jump?
  {
    if (m->getCollision(posX,posY-1) == false && m->getCollision(posX,posY+1) == true) //can the player jump?
    {
      posY = posY -1;
      jumpCounter = 4;
      updated = true;
    }
  }
  if (m->getCollision(posX,posY+1) == false && jumpCounter == 0) //is the player falling?
  {
    posY = posY+1;
    updated = true;
  }
  if (jumpCounter > 0) //is the player rising from a jump?
  {
    if (m->getCollision(posX,posY-1) == false)// has the player hit a ceiling?
    {
      posY = posY -1;
      jumpCounter--;
      updated = true;
    }
    else
    {
      jumpCounter = 0;
    }
  }
  return updated;
}
