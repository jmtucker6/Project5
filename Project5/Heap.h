#include <string>
#include <iostream>

struct Node {
	char content;
	std::string label;
	int priority;
	Node *next;
	Node *left;
	Node *right;
};
class Heap
{
public:
	Heap(int);
	~Heap();
	bool isHeap(Node);
	Node* removeMin();
	void insert(Node*);
	void bubbleUp(int);
	void bubbleDown(int);
	int count();
	int getParentIndex(int);
	int getLeftIndex(int);
	int getRightIndex(int);
	void expandArr();
	void displayArr();
private:
	Node **arr;
	int size;
	int lastPosition;
	int numItems;
};

