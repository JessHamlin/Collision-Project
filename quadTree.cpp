#include <iostream>
#include "quadtree.hpp"
using namespace std;

quadtree::quadtree(int x, int y, int lowx, int lowy)
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

}
void quadtree::deleteHelper(quadtree* q)
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
    return;
  }
  if (q->tr == NULL && q->tl == NULL && q->bl == NULL && q->br == NULL)
  {
    if (q->data == NULL)
    {
      q->data = makeNode(x,y,data);
      return;
    }
    else
    {
      //if ((q->maxX+q->minX)/2 >= x) // left subtree
      //{
        //if ((q->maxY+q->minY)/2 >= y) //bottom subtree
        //{
          q->bl = new quadtree(int((q->maxX+q->minX)/2),int((q->maxY+q->minY)/2),q->minX,q->minY);
        //}
        //else //top subtree
        //{
          q->tl = new quadtree(int((q->maxX+q->minX)/2),q->maxY,q->minX,int((q->maxY+q->minY)/2));
        //}
      //}
      //else //right subtree
      //{
        //if ((q->maxY+q->minY)/2 >= y) //bottom subtree
        //{
          q->br = new quadtree(q->maxX,int((q->maxY+q->minY)/2),int((q->maxX+q->minX)/2),q->minY);
        //}
        //else //top subtree
        //{
          q->tr = new quadtree(q->maxX,q->maxY,int((q->maxX+q->minX)/2),int((q->maxY+q->minY)/2));
        //}
      //}
      insert(x,y,data,q);
      node* temp = q->data;
      q->data = NULL;
      insert(temp->x,temp->y,temp->data,q);
    }
  }
  else
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
      return d;
    }
    if (q->data->x == x && q->data->y == y)
    {
      return q->data->data;
    }
    return !q->data->data;
  }
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
node* quadtree::makeNode(int x, int y, bool data)
{
  node* n = new node;
  n->x = x;
  n->y = y;
  n->data = data;
  return n;
}
