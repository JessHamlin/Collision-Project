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

void menu()//This function calls out the menu upon starting the game
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
  menu(); //call out the menu
  string type = "";
  while (type != "1" && type != "2" && type != "3") //loop until the player inputs a valid answer
    cin >> type;
  map m(stoi(type)-1,1); //make a map for level 1
  player p(&m); //make the player
  m.print(p.getPosX(),p.getPosY()); //print the map
  /// Timing stuff
  auto start = std::chrono::high_resolution_clock::now();
    m.getCollision(0,0); //time the time to get a single collision with known coordinates
    Sleep(1); //sleep for 1000 microseconds to make the timer measurable
  auto stop = std::chrono::high_resolution_clock::now();
  auto startB = std::chrono::high_resolution_clock::now();
    int blockCounter = m.getBlockCounter(); //time the time to search all coordinates
    Sleep(1); //sleep for 1000 microseconds to make the timer measurable
  auto stopB = std::chrono::high_resolution_clock::now();
  auto timer = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  auto timerB = std::chrono::duration_cast<std::chrono::microseconds>(stopB - startB);
  int timeA = timer.count()-1000;
  int timeB =  timerB.count()-1000;
  cout << "Time Taken To Detect Collision: " << timeA << " Microseconds" << endl; //subtract the 1000 microseconds that were added
  cout << "Time Taken To Detect All "<< blockCounter <<  " Blocks: " << timeB << " Microseconds" << endl;
  /// End of timing stuff
  bool checker = false;
  while (checker == false) //Main game loop for map 1
  {
    Sleep(50); //sleep 50 milliseconds between every frame
    if (p.update() == true) //only print a frame when the player has moved
    {
      m.print(p.getPosX(),p.getPosY());
      cout << "Time Taken To Detect Collision: " << timeA << " Microseconds" << endl;
      cout << "Time Taken To Detect All "<< blockCounter <<  " Blocks: " << timeB << " Microseconds" << endl;
    }
    if (GetKeyState(0x45) < 0) //check if the next level key has been pressed
    {
      checker = true;
    }
  }
  map mB(stoi(type)-1,2); //make a map for level 2
  p.reset(&mB); //reset the player with the new map
  mB.print(p.getPosX(),p.getPosY());
  /// Timer stuff
  startB = std::chrono::high_resolution_clock::now();
    blockCounter = mB.getBlockCounter(); //recount the blocks
    Sleep(1);
  stopB = std::chrono::high_resolution_clock::now();
  timerB = std::chrono::duration_cast<std::chrono::microseconds>(stopB - startB);
  timeB = timerB.count()-1000;
  cout << "Time Taken To Detect Collision: " << timeA << " Microseconds" << endl;
  cout << "Time Taken To Detect All "<< blockCounter <<  " Blocks: " << timeB << " Microseconds" << endl;
  /// end of timer stuff
  checker = false;
  Sleep(1000); //sleep so you dont accidentally skip a level
  while (checker == false) //level 2 game loop, same as level 1 game loop
  {
    Sleep(50);
    if (p.update() == true)
    {
      mB.print(p.getPosX(),p.getPosY());
      cout << "Time Taken To Detect Collision: " << timeA << " Microseconds" << endl;
      cout << "Time Taken To Detect All "<< blockCounter <<  " Blocks: " << timeB << " Microseconds" << endl;
    }
    if (GetKeyState(0x45) < 0)
    {
      checker = true;
    }
  }
  map mC(stoi(type)-1,3); //make the map for level 3
  p.reset(&mC); //reset the player for level 3
  mC.print(p.getPosX(),p.getPosY()); //print the map
  /// timer stuff
  startB = std::chrono::high_resolution_clock::now();
    blockCounter = mC.getBlockCounter();
    Sleep(1);
  stopB = std::chrono::high_resolution_clock::now();
  timerB = std::chrono::duration_cast<std::chrono::microseconds>(stopB - startB);
  timeB = timerB.count()-1000;
  cout << "Time Taken To Detect Collision: " << timeA << " Microseconds" << endl;
  cout << "Time Taken To Detect All "<< blockCounter <<  " Blocks: " << timeB << " Microseconds" << endl;
  /// end of timer stuff
  checker = false;
  Sleep(1000); //sleep again so the level isnt skipped
  while (checker == false) //game loop for level 3, same as the loop for level 1
  {
    Sleep(50);
    if (p.update() == true)
    {
      mC.print(p.getPosX(),p.getPosY());
      cout << "Time Taken To Detect Collision: " << timeA << " Microseconds" << endl;
      cout << "Time Taken To Detect All "<< blockCounter <<  " Blocks: " << timeB << " Microseconds" << endl;
    }
    if (GetKeyState(0x45) < 0)
    {
      checker = true;
    }
  }
  cout << "Goodbye" << endl; //end the game
  return 0;
}
