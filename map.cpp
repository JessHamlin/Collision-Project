#include "map.hpp"
#include <iostream>
#include <vector>
using namespace std;

map::map(int x, int y)
{
  for (int i = 0; i < y; i++)
  {
    vector<char> temp;
    for (int j = 0; j < x; j++)
    {
      temp.push_back(178);
    }
    grid.push_back(temp);
  }
  sizeX = x;
  sizeY = y;
}
char map::getVal(int x, int y)
{
  return grid[x][y];
}
void map::print()
{
  for (int i = 0; i < sizeY; i++)
  {
    for (int j = 0; j < sizeX; j++)
    {
      cout << getVal(i,j) << " ";
    }
    cout << endl;
  }
}
int main()
{
  map m(2,5);
  m.print();
}
