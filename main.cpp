#include "map.hpp"
#include "player.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Windows.h"
using namespace std;

void menu()
{
  cout << "=====[Welcome to Cube Game]=====" << endl;
  cout << "Controls: WASD Or Arrow Keys To Move" << endl;
  cout << "Press Space Bar To Jump" << endl;
  cout << "Press Enter To Change Maps" << endl;
  cout << "=====[Press Enter To Begin The Game]=====" << endl;
}

int main(int argc, char const *argv[])
{
  menu();
  cin.ignore();
  map m(true,2);
  player p(&m);
  m.printQT(p.getPosX(),p.getPosY());
  bool checker = false;
  while (checker == false)
  {
    Sleep(50);
    if (p.update() == true)
    {
      m.printQT(p.getPosX(),p.getPosY());
    }
    if (GetKeyState(VK_RETURN) < 0)
    {
      checker = true;
    }
  }
  cout << "Goodbye" << endl;
  return 0;
}
