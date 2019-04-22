#include "map.hpp"
#include "quadTree.hpp"
#include "hashTable.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

map::map(int type, int level)
{
  this->type = type; //0 = vector, 1 = quadtree, 2 = hashtable
  string fileStr;
  ifstream file;
  if (level == 1)
    file.open("lvlA.txt");
  if (level == 2)
    file.open("lvlB.txt");
  if (level == 3)
    file.open("lvlC.txt");
  ////vector method
  if (file.is_open() && type == 0)
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
      vec.push_back(temp);
    }
  }
  //quadtree method
  if (file.is_open() && type == 1)
  {
    int x = 0;
    int y = 0;
    string fileStrB;
    while (getline(file,fileStr))
    {
      stringstream ss(fileStr);
      while (getline(ss,fileStrB,' '))
      {
        if (stoi(fileStrB) == 1)
        {
          q.insert(x,y,true,&q);
        }
        x++;
      }
      x = 0;
      y++;
    }
    cout << x << " " << y << endl;
  }
  //Hashtable method
  if (file.is_open() && type == 2)
  {
    int x = 0;
    int y = 0;
    string fileStrB;
    while (getline(file, fileStr))
    {
      stringstream ss(fileStr);
      while (getline(ss,fileStrB,' '))
      {
        if (stoi(fileStrB) == 1)
        {
          h.insert(x,y,true);
        }
        x++;
      }
      x = 0;
      y++;
    }
  }
}
map::~map()
{
  if (type ==1)
    q.~quadtree();
  if (type ==2)
    h.~HashTable();
}
bool map::getCollision(int x, int y)
{
  if (type == 0) //2d vector
    return getCollision2DVector(x,y);
  else if (type == 1) //quadtree
    return getCollisionQuatTree(x,y);
  else //hashtable
    return getCollisionHashTable(x,y);
}
bool map::getCollision2DVector(int x, int y)
{
  return vec[y][x];
}
bool map::getCollisionQuatTree(int x, int y)
{
  return q.search(x,y,&q,false);
}
bool map::getCollisionHashTable(int x, int y) // TODO
{
    return h.search(x,y);
}
void map::print(int x, int y)
{
  string str = "";
  for (int i = 0; i < sizeY; i++)
  {
    for (int j = 0; j < sizeX; j++)
    {
      if ((i == y && j == x) || (getCollision(j,i) == true))
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
int map::getBlockCounter()
{
  int counter = 0;
  if (type == 0)
  {
    for (int i = 0; i < sizeY; i++)
    {
      for (int j = 0; j < sizeX; j++)
      {
        if (vec[i][j] == true)
        {
          counter ++;
        }
      }
    }
  }
  else if (type == 1)
  {
    counter = q.getTotal(&q);
  }
  else
  {
    for (int i = 0; i < sizeY; i++)
    {
      for (int j = 0; j < sizeX; j++)
      {
        if (h.search(j,i) == true)
        {
          counter ++;
        }
      }
    }
  }
  return counter;
}
