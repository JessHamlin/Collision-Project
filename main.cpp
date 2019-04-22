#include "map.hpp"
#include "player.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
#include "Windows.h"
#include "hashTable.hpp"
using namespace std;

void menu()
{
  cout << "=====[Welcome to Cube Game]=====" << endl;
  cout << "Guide Your Cube Through All Three Mazes To Win" << endl;
  cout << "See The Time It Takes To Detect Collsion Below The Map" << endl;
  cout << "=====[Controls]=====" << endl;
  cout << "WASD Or Arrow Keys To Move" << endl;
  cout << "Press Space Bar To Jump" << endl;
  cout << "Press E To Change Maps" << endl;
  cout << "=====[Select Collision Type]=====" << endl;
  cout << "1) Two Dimensional Vector Collision" << endl;
  cout << "2) QuadTree Collision" << endl;
  cout << "3) HashTable Collision" << endl;
}

int main(int argc, char const *argv[])
{
  menu();
  string type = "";
  while (type != "1" && type != "2" && type != "3")
    cin >> type;
  map m(stoi(type)-1,1);
  cin.ignore();
  Sleep(5000);
  player p(&m);
  m.print(p.getPosX(),p.getPosY());
  ///
  auto start = std::chrono::high_resolution_clock::now();
    m.getCollision(0,0);
    Sleep(1);
  auto stop = std::chrono::high_resolution_clock::now();
  auto startB = std::chrono::high_resolution_clock::now();
    int blockCounter = m.getBlockCounter();
    Sleep(1);
  auto stopB = std::chrono::high_resolution_clock::now();
  auto timer = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  auto timerB = std::chrono::duration_cast<std::chrono::microseconds>(stopB - startB);
  cout << "Time Taken To Detect Collision: " << timer.count() -1000 << " Microseconds" <<endl;
  cout << "Time Taken To Detect All "<< blockCounter <<  " Blocks: " << timerB.count()-1000 << " Microseconds" << endl;
  bool checker = false;
  while (checker == false)
  {
    Sleep(50);
    if (p.update() == true)
    {
      m.print(p.getPosX(),p.getPosY());
      cout << "Time Taken To Detect Collision: " << timer.count() << " Microseconds" << endl;
      cout << "Time Taken To Detect All "<< blockCounter <<  " Blocks: " << timerB.count() << " Microseconds" << endl;
    }
    if (GetKeyState(0x45) < 0)
    {
      checker = true;
    }
  }
  map mB(stoi(type)-1,2);
  p.reset(&mB);
  mB.print(p.getPosX(),p.getPosY());
  startB = std::chrono::high_resolution_clock::now();
    blockCounter = mB.getBlockCounter();
    Sleep(1);
  stopB = std::chrono::high_resolution_clock::now();
  timerB = std::chrono::duration_cast<std::chrono::microseconds>(stopB - startB);
  cout << "Time Taken To Detect Collision: " << timer.count() << " Microseconds" << endl;
  cout << "Time Taken To Detect All "<< blockCounter <<  " Blocks: " << timerB.count()-1000 << " Microseconds" << endl;
  checker = false;
  Sleep(1000);
  while (checker == false)
  {
    Sleep(50);
    if (p.update() == true)
    {
      mB.print(p.getPosX(),p.getPosY());
      cout << "Time Taken To Detect Collision: " << timer.count() << " Microseconds" << endl;
      cout << "Time Taken To Detect All "<< blockCounter <<  " Blocks: " << timerB.count()-1000 << " Microseconds" << endl;
    }
    if (GetKeyState(0x45) < 0)
    {
      checker = true;
    }
  }
  map mC(stoi(type)-1,3);
  p.reset(&mC);
  mC.print(p.getPosX(),p.getPosY());
  startB = std::chrono::high_resolution_clock::now();
    blockCounter = mC.getBlockCounter();
    Sleep(1);
  stopB = std::chrono::high_resolution_clock::now();
  timerB = std::chrono::duration_cast<std::chrono::microseconds>(stopB - startB);
  cout << "Time Taken To Detect Collision: " << timer.count() << " Microseconds" << endl;
  cout << "Time Taken To Detect All "<< blockCounter <<  " Blocks: " << timerB.count()-1000 << " Microseconds" << endl;
  checker = false;
  Sleep(1000);
  while (checker == false)
  {
    Sleep(50);
    if (p.update() == true)
    {
      mC.print(p.getPosX(),p.getPosY());
      cout << "Time Taken To Detect Collision: " << timer.count() << " Microseconds" << endl;
      cout << "Time Taken To Detect All "<< blockCounter <<  " Blocks: " << timerB.count()-1000 << " Microseconds" << endl;
    }
    if (GetKeyState(0x45) < 0)
    {
      checker = true;
    }
  }
  cout << "Goodbye" << endl;
  return 0;
}
