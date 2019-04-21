#include <vector>
#include <iostream>
#include "map.hpp"
#include "player.hpp"
#include "Windows.h"
using namespace std;

player::player(map* m)
{
  posX = 1;
  posY = 23;
  this->m = m;
  jumpCounter = 0;
}
void player::reset(map* m)
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
bool player::update()
{
  bool updated = false;
  if (GetKeyState(0x41) < 0 || GetKeyState(VK_LEFT) < 0)
  {
    if (m->getCollision(posX-1,posY) == false)
      posX = posX - 1;
      updated = true;
  }
  else if (GetKeyState(0x44) < 0 || GetKeyState(VK_RIGHT) < 0)
  {
    if (m->getCollision(posX+1,posY) == false)
      posX = posX + 1;
      updated = true;
  }
  if (GetKeyState(VK_SPACE) < 0 || GetKeyState(VK_UP) < 0 || GetKeyState(0x57) < 0)
  {
    if (m->getCollision(posX,posY-1) == false && m->getCollision(posX,posY+1) == true)
    {
      posY = posY -1;
      jumpCounter = 4;
      updated = true;
    }
  }
  if (m->getCollision(posX,posY+1) == false && jumpCounter == 0)
  {
    posY = posY+1;
    updated = true;
  }
  if (jumpCounter > 0)
  {
    if (m->getCollision(posX,posY-1) == false)
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
