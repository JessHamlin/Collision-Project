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
  if (GetKeyState(0x41) < 0 || GetKeyState(VK_LEFT) < 0)
  {
    if (m->getCollisionQuatTree(posX-1,posY) == false)
      posX = posX - 1;
      return true;
  }
  if (GetKeyState(0x44) < 0 || GetKeyState(VK_RIGHT) < 0)
  {
    if (m->getCollisionQuatTree(posX+1,posY) == false)
      posX = posX + 1;
      return true;
  }
  return false;
}
