#include <iostream>
#include "quadtree.hpp"
using namespace std;

quadtree::quadtree(int x, int y, int lowx, int lowy) //set a values to default
{
  maxX = x;
  maxY = y;
  minX = lowx;
  minY = lowy;
  data = NULL;
  tl = NULL;
  bl = NULL;
  tr = NULL;
  br = NULL;
}
quadtree::~quadtree()
{
  deleteHelper(this);//call delete helper
}
int quadtree::getTotal(quadtree* q) //gets all blocks stored in the quadtree
{
  int counter = 0;
  if (q->tr == NULL && q->tl == NULL && q->bl == NULL && q->br == NULL)
  {
    if (q->data != NULL)
    {
      if (q->data->data == true)
        counter++;
    }
    return counter;
  }
  counter = counter + getTotal(q->tl);//uses recursion to save time coding, could have also been done dynamically perhaps
  counter = counter + getTotal(q->bl);
  counter = counter + getTotal(q->tr);
  counter = counter + getTotal(q->br);
  return counter;
}
void quadtree::deleteHelper(quadtree* q) //similar to getTotal(), but deletes everything instead of counting everything
{
  if (q->tr == NULL && q->tl == NULL && q->bl == NULL && q->br == NULL)
  {
    if (q->data != NULL)
      delete q->data;
    return;
  }
  deleteHelper(q->tl);
  delete q->tl;
  deleteHelper(q->bl);
  delete q->bl;
  deleteHelper(q->tr);
  delete q->tr;
  deleteHelper(q->br);
  delete q->br;
}
void quadtree::insert(int x, int y, bool data, quadtree* q)
{
  if (x > q->maxX || x < q->minX || y > q->maxY || y < q->minY)
  {
    return; //quit if the coordinates are out of bounds
  }
  if (q->tr == NULL && q->tl == NULL && q->bl == NULL && q->br == NULL) //leaf node
  {
    if (q->data == NULL)
    {
      q->data = makeNode(x,y,data);
      return;
    }
    else
    {
      //break the node into 4 nodes
        q->bl = new quadtree(int((q->maxX+q->minX)/2),int((q->maxY+q->minY)/2),q->minX,q->minY);
        q->tl = new quadtree(int((q->maxX+q->minX)/2),q->maxY,q->minX,int((q->maxY+q->minY)/2));
        q->br = new quadtree(q->maxX,int((q->maxY+q->minY)/2),int((q->maxX+q->minX)/2),q->minY);
        q->tr = new quadtree(q->maxX,q->maxY,int((q->maxX+q->minX)/2),int((q->maxY+q->minY)/2));
      //insert the new node and the old node that was stored in data into the four new nodes
      insert(x,y,data,q);
      node* temp = q->data;
      q->data = NULL;
      insert(temp->x,temp->y,temp->data,q);
    }
  }
  else//not a leaf node, search for the right leaf node
  {
    if ((q->maxX+q->minX)/2 >= x) // left subtree
    {
      if ((q->maxY+q->minY)/2 >= y) //bottom subtree
      {
        insert(x,y,data,q->bl);
      }
      else //top subtree
      {
        insert(x,y,data,q->tl);
      }
    }
    else //right subtree
    {
      if ((q->maxY+q->minY)/2 >= y) //bottom subtree
      {
        insert(x,y,data,q->br);
      }
      else //top subtree
      {
        insert(x,y,data,q->tr);
      }
    }
  }
}
bool quadtree::search(int x, int y, quadtree* q, bool d)
{
  if (q->tr == NULL && q->tl == NULL && q->bl == NULL && q->br == NULL)
  {
    if (q->data == NULL)
    {
      return d;//return the default if the leaf node it empty
    }
    if (q->data->x == x && q->data->y == y)
    {
      return q->data->data; //return the data if the coordinates match, or the opposite if the dont
    }
    return !(q->data->data);
  }
  //search for the right node
  if ((q->maxX+q->minX)/2 >= x) // left subtree
  {
    if ((q->maxY+q->minY)/2 >= y) //bottom subtree
    {
      return search(x,y,q->bl, d);
    }
    else //top subtree
    {
      return search(x,y,q->tl, d);
    }
  }
  else //right subtree
  {
    if ((q->maxY+q->minY)/2 >= y) //bottom subtree
    {
      return search(x,y,q->br, d);
    }
    else //top subtree
    {
      return search(x,y,q->tr, d);
    }
  }
}
node* quadtree::makeNode(int x, int y, bool data)//makes a new node
{
  node* n = new node;
  n->x = x;
  n->y = y;
  n->data = data;
  return n;
}
