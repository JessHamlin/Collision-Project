#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <iostream>
using namespace std;

class map
{
  public:
    map(bool type, int level);
    ~map();
    bool getCollisionQuatTree(int x, int y);
    bool getCollisionHashTable(int x, int y);
    void printQT(int x, int y);
    void printHT(int x, int y);
  private:
    int sizeX = 60;
    int sizeY = 25;
    bool type;
    vector<vector<bool>> deleteMe; 
};

#endif
