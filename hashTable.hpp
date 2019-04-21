using namespace std;

struct HashNode
{
  bool key;
  int x;
  int y;
  HashNode* next;
};

class HashTable
{
private;
  HashNode** table;
  int size;

public:
  HashTable();
  HashTable(int s);
  ~HashTable();
  void insert(int x, int y, bool collision);
  void remove(int x, int y);
  int hashCode(int k)
  bool search(int x, int y);
}
