#include "Heap.h"


int main() {
	Heap heap(10);
	Node temp;
	temp.content = "abc";
	temp.priority = 10;
	heap.insert(temp);
	temp.content = "bcd";
	temp.priority = 11;
	heap.insert(temp);
	temp.content = "cde";
	temp.priority = 5;
	heap.insert(temp);

	heap.displayArr();

	heap.removeMin();

	heap.displayArr();

	return 0;
}