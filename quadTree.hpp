#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <vector>
#include <iostream>
using namespace std;

struct node
{
  bool data;
  int x,y;
  node(bool data, int x, int y)
  {
    this->data = data;
    this->x = x;
    this->y = y;
  }
  node()
  {
    x = 0;
    y = 0;
    data = false;
  }
};

class quadtree
{
  public:
    quadtree(int x, int y, int lowx, int lowy);
    ~quadtree();
    void insert(int x, int y, bool data, quadtree* q);
    bool search(int x, int y, quadtree* q, bool d);
  private:
    node* makeNode(int x, int y, bool data);
    void deleteHelper(quadtree* q);
    node *data;
    int maxX;
    int maxY;
    int minX;
    int minY;
    quadtree* tr;
    quadtree* tl;
    quadtree* br;
    quadtree* bl;
};

#endif
