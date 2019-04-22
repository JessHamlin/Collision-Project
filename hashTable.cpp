#include <iostream>
#include "hashTable.hpp"
#include <math.h>
using namespace std;


HashTable::HashTable()
{
  size = 10;
  table = new HashNode *[10];
  for (int i = 0; i < size; i++) table[i] = 0;
}

HashTable::HashTable(int s)
{
  size = s;
  table = new HashNode *[s];
  for (int i = 0; i < size; i++) table[i] = 0;
}

HashTable::~HashTable()
{
  for (int i = 0; i < size; i++)
  {
    HashNode* tmp = table[i];
    while (tmp != 0)
    {
       HashNode* curr = tmp;
      tmp = tmp->next;
      delete curr;
    }
  }
  delete[] table;
}

int HashTable::hashCode(int k)
{
  return k % 59;
}

void HashTable::insert(int x, int y, bool collision)
{
  int index = hashCode(x);
  HashNode *temp = new HashNode();
  temp->key = collision;
  temp->x = x;
  temp->y = y;

  if(table[index] == 0)
  {
    table[index] = temp;
  }
  else
  {
    HashNode *curr = table[index];
    HashNode *prev = NULL;

    while(curr != NULL)
    {
      if(curr->x == x)
      {
        if(curr->y == y)
        {
          cout << "coordinates (" << x << "," << y  << ") already in hash table" << endl;
          return;
        }
      }
      prev = curr;
      curr = curr->next;
    }

    curr->next = temp;
    return;
  }
}

void HashTable::remove(int x, int y)
{
  int index = hashCode(x);
  HashNode *temp = table[index];
  HashNode *prev = NULL;

  while(temp != NULL)
  {
    if(temp->x == x && temp->y == y)
    {
      break;
    }
    else
    {
      prev = temp;
      temp = temp->next;
    }
  }

  if(temp == NULL)
  {
    return;
  }
  else
  {
    if(prev == NULL)
    {
      table[index] = temp->next;
      delete temp;
      temp = NULL;
    }
    else
    {
      prev->next = temp->next;
      delete temp;
      temp = NULL;
    }
  }
  return;
}

bool HashTable::search(int x, int y)
{
  int index = hashCode(x);
  if(table[index] == NULL)
  {
    cout << "coordinate does not exist in hash table" << endl;
    return false;
  }
  else
  {
    HashNode* curr = table[index];
    while(curr != NULL)
    {
      if(curr->x == x && curr->y == y)
      {
        return curr->key;
      }
      curr = curr->next;
    }
  }
  cout << "coordinate not found" << endl;
  return false;
}
