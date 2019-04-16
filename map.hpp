#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <iostream>
using namespace std;
class map
{
  public:
    map(int x, int y);
    char getVal(int x, int y);
    void print();
  private:
    vector<vector<char>> grid;
    int sizeX;
    int sizeY;
};

#endif
