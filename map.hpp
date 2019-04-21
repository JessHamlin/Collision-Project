#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <iostream>
#include "quadTree.hpp"
using namespace std;

class map
{
  public:
    map(int type, int level);
    ~map();
    bool getCollision(int x, int y);
    void print(int x, int y);
  private:
    int sizeX = 60;
    int sizeY = 25;
    int type;
    vector<vector<bool>> vec;
    quadtree q = quadtree(60-1,25-1,0,0);
    bool getCollisionHashTable(int x, int y);
    bool getCollision2DVector(int x, int y);
    bool getCollisionQuatTree(int x, int y);
};

#endif
