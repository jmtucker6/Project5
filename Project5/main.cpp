#include "Heap.h"
#include <fstream>
#include <iostream>
#include <string>

Node* find(Node*, char);

int main() {
	Heap heap = Heap(10);
	char c;
	Node *chars = NULL;
	Node *ptr = chars;

	std::ifstream in("example.txt");
	while (in.get(c)) {
		std::cout << c;
		if (chars == NULL) {
			Node *temp = new Node;
			temp->content = c;
			temp->priority = 1;
			temp->next = NULL;
			chars = temp;
			ptr = temp;
		}
		else {
			Node *temp = find(chars, c);
			if (temp != NULL) {
				temp->priority++;
			}
			else {
				temp = new Node;
				temp->content = c;
				temp->priority = 1;
				temp->next = NULL;
				ptr->next = temp;
				ptr = temp;
			}
		}
	}

	in.close();

	ptr = chars;
	while (ptr != NULL) {
		heap.insert(ptr);
		ptr = ptr->next;
	}


	return 0;
}

Node* find(Node *head, char c) {
	while (head != NULL) {
		if (head->content == c)
			return head;
		head = head->next;
	}
	return NULL;
}