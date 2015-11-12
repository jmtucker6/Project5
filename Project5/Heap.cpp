#include "Heap.h"



Heap::Heap(int s = 10)
{
	arr = new Node*[s];
	lastPosition = -1;
	size = s;
	numItems = 0;
}


Heap::~Heap()
{
	size = 0;
	delete[] arr;
}

bool Heap::isHeap(Node n) {
	return true;
}

void Heap::insert(Node *n) {
	if (lastPosition == -1) {
		arr[++lastPosition] = n;
		numItems++;
		return;
	}
	if (lastPosition >= size - 1) {
		expandArr();
	}
	numItems++;
	arr[++lastPosition] = n;
	bubbleUp(lastPosition);
	return;
}

void Heap::bubbleUp(int pos) {
	if (pos < 1)
		return;
	if (arr[pos]->priority < arr[getParentIndex(pos)]->priority) {
		Node *temp;
		temp = arr[getParentIndex(pos)];
		arr[getParentIndex(pos)] = arr[pos];
		arr[pos] = temp;
		pos = getParentIndex(pos);
		bubbleUp(pos);
	}
	return;
}

void Heap::bubbleDown(int pos) {
	int min = pos;
	if (getLeftIndex(pos) <= lastPosition && arr[getLeftIndex(pos)]->priority < arr[min]->priority) {
		min = getLeftIndex(pos);
	}
	if (getRightIndex(pos) <= lastPosition && arr[getRightIndex(pos)]->priority < arr[min]->priority) {
		min = getRightIndex(pos);
	}
	if (min != pos) {
		Node *temp = arr[pos];
		arr[pos] = arr[min];
		arr[min] = temp;
		bubbleDown(min);
	}
}

Node Heap::removeMin() {
	Node *temp = arr[lastPosition];
	arr[lastPosition] = arr[0];
	arr[0] = temp;
	Node result = *arr[lastPosition];
	arr[lastPosition]->content = '\0';
	arr[lastPosition]->priority = 0;
	delete arr[lastPosition];
	lastPosition--;
	bubbleDown(0);
	numItems--;
	return result;
}

int Heap::getParentIndex(int pos) {
	int i = (pos - 1) / 2;
	return i;
}

int Heap::getLeftIndex(int pos) {
	return (int) pos * 2 + 1;
}

int Heap::getRightIndex(int pos) {
	return (int) pos * 2 + 2;
}

int Heap::count() {
	return numItems;
}

void Heap::expandArr() {
	Node **temp;
	temp = new Node*[size * 2];
	for (int i = 0; i < size; i++) {
		temp[i] = arr[i];
	}
	delete[] arr;
	arr = temp;
	size *= 2;
}

void Heap::displayArr() {
	for (int i = 0; i < numItems; i++) {
		std::cout << arr[i]->content << " ";
	}
	std::cout << std::endl;
}