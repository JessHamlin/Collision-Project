#include "map.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

map::map(int x, int y)
{
  for (int i = 0; i < y; i++)
  {
    vector<char> temp;
    for (int j = 0; j < x; j++)
    {
      temp.push_back(' ');//219 = block
    }
    grid.push_back(temp);
  }
  sizeX = x;
  sizeY = y;
}
map::map()
{
  sizeX = 0;
  sizeY = 0;
}
char map::getVal(int x, int y)
{
  return grid[x][y];
}
void map::setVal(int x, int y, bool v)
{
  if (v == false)
  grid[x][y] = ' ';
  if (v == true)
  grid[x][y] = 219;
}
void map::print()
{
  for (int i = 0; i < sizeY; i++)
  {
    for (int j = 0; j < sizeX; j++)
    {
      cout << getVal(i,j);
    }
    cout << endl;
  }
}
void map::addLine(vector<char> line)
{
  grid.push_back(line);
  sizeY++;
  sizeX = line.size();
}
int main(int argc, char const *argv[])
{
  cout << "Welcome to Game" << endl;
  bool fileNameCheck = false;
  while (fileNameCheck == false)
  {
    cout << "Enter map file name" << endl;
    string fileStr;
    cin >> fileStr;
    ifstream file;
    file.open(fileStr);
    if (file.is_open())
    {
      map m(0,0);
      fileNameCheck = true;
      string fileStrB;
      while (getline(file,fileStr))
      {
        vector<char> temp;
        stringstream ss(fileStr);
        while (getline(ss,fileStrB,' '))
        {
          if (stoi(fileStrB) == 0)
          {
            temp.push_back(' ');
          }
          if (stoi(fileStrB) == 1)
          {
            temp.push_back(219);
          }
        }
        m.addLine(temp);
      }
      m.print();
    }
    else
    {
      cout << "Error opening file" << endl;
    }
  }
}
