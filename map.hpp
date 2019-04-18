#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <iostream>
using namespace std;
class map
{
  public:
    map();
    map(int x, int y);
    char getVal(int x, int y);
    void print();
    void setVal(int x, int y, bool v);
    void addLine(vector<char> line);
  private:
    vector<vector<char>> grid;
    int sizeX;
    int sizeY;
};

#endif
