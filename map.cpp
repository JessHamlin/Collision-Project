#include "map.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

map::map(bool type, int level)
{
  this->type = type;
  ////
  string fileStr;
  ifstream file;
  if (level == 1)
  file.open("lvlA.txt");
  if (level == 2)
  file.open("lvlB.txt");
  if (level == 3)
  file.open("lvlC.txt");
  if (file.is_open())
  {
    string fileStrB;
    while (getline(file,fileStr))
    {
      vector<bool> temp;
      stringstream ss(fileStr);
      while (getline(ss,fileStrB,' '))
      {
        if (stoi(fileStrB) == 0)
        {
          temp.push_back(false);
        }
        if (stoi(fileStrB) == 1)
        {
          temp.push_back(true);
        }
      }
      deleteMe.push_back(temp);
    }
  }
  else
  {
    cout << "Error opening file" << endl;
  }
}
map::~map()
{

}
bool map::getCollisionQuatTree(int x, int y) //TODO
{
  return deleteMe[y][x];
}
bool map::getCollisionHashTable(int x, int y) // TODO
{
  return deleteMe[y][x];
}
void map::printQT(int x, int y)
{
  string str = "";
  for (int i = 0; i < sizeY; i++)
  {
    for (int j = 0; j < sizeX; j++)
    {
      if ((i == y && j == x) || (getCollisionQuatTree(j,i) == true))
      {
        char c = 219;
        str = str + c;
      }
      else
      {
        str = str + ' ';
      }
    }
    str = str + "\n";
  }
  cout << str;
}
void map::printHT(int x, int y)
{
  for (int i = 0; i < sizeY; i++)
  {
    for (int j = 0; j < sizeX; j++)
    {
      if ((i == y && j == x) || (getCollisionHashTable(j,i) == true))
      {
        char c = 219;
        cout << c;
      }
      else
      {
        cout << " ";
      }
    }
    cout << endl;
  }
}
