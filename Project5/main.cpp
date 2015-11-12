#include "Heap.h"
#include "Table.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

Node* find(Node*, char);
std::string preorder(Node *);
std::string inorder(Node *);
std::string removeSpaces(std::string);
void generateEncodingTable(Node*, Table*, std::string);

int main(int argc, char* argv[]) {
	Heap heap = Heap(10);
	char c;
	Node *chars = NULL;
	Node *ptr = chars;
	/////////////////////////////// Read and Create Linked List (for Frequencies) ////////////////////////////////
	std::ifstream in(argv[1]);
	while (in.get(c)) {
		std::cout << c;
		if (chars == NULL) {
			Node *temp = new Node;
			temp->content = c;
			temp->label = "L:";
			temp->label += static_cast<std::ostringstream*>(&(std::ostringstream() << (int) c)) -> str(); // Get ASCII Value
			temp->priority = 1;
			temp->next = NULL;
			temp->right = NULL;
			temp->left = NULL;
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
				temp->label = "L:";
				temp->label += static_cast<std::ostringstream*>(&(std::ostringstream() << (int)c))->str(); // Get ASCII Value
				temp->priority = 1;
				temp->next = NULL;
				temp->right = NULL;
				temp->left = NULL;
				ptr->next = temp;
				ptr = temp;
			}
		}
	}

	in.close();
	/////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////// Create Initial Heap //////////////////////////////////////
	ptr = chars;
	while (ptr != NULL) {
		heap.insert(ptr);
		ptr = ptr->next;
	}
	int totalChars = heap.count();

	/////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////// Create Huffman Code Tree /////////////////////////////////
	int counter = 0;
	Node *parent = NULL;
	while (heap.count() > 1) {
		Node *n1 = heap.removeMin();
		Node *n2 = heap.removeMin();
		parent = new Node;
		parent->label = "I:" + static_cast<std::ostringstream*>(&(std::ostringstream() << counter++))->str();
		parent->content = '*';
		parent->left = n1;
		parent->right = n2;
		parent->next = NULL;
		parent->priority = n1->priority + n2->priority;
		heap.insert(parent);
	}
	Node *codeTree = parent;
	/////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////// Get Traversals ////////////////////////////////////////////

	std::ofstream outTree("tree.txt");
	outTree << removeSpaces(preorder(codeTree)) << std::endl;
	outTree << removeSpaces(inorder(codeTree)) << std::endl;
	outTree.close();

	/////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////// Create Encoding Table ////////////////////////////////////

	Table *codeTable = new Table[totalChars];
	std::string code = "";
	generateEncodingTable(codeTree, codeTable, code);

	////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////// Write Code ////////////////////////////////////////////////
	std::ofstream outCode("code.txt");
	in.open(argv[1]);
	c = '\0';
	while (in.get(c)) {
		for (int i = 0; i < totalChars; i++)
		{
			if (c == codeTable[i].content) {
				outCode << codeTable[i].encoding;
				break;
			}
		}
	}
	in.close();
	outCode.close();
	////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////// Output Lengths ////////////////////////////////////////
	std::ofstream outLength("length.txt");
	for (int i = 0; i < totalChars; i++)
	{
		outLength << codeTable[i].content << " " << " " << codeTable[i].encoding << " " << codeTable[i].encoding.length() << std::endl;
	}
	outLength.close();
	////////////////////////////////////////////////////////////////////////////////////////
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

std::string preorder(Node *parent) {
	if (parent == NULL)
		return "";
	return parent->label + " " + preorder(parent->left) + " " + preorder(parent->right) + " ";
}

std::string inorder(Node *parent) {
	if (parent == NULL)
		return "";
	return inorder(parent->left) + " " + parent->label + " " + inorder(parent->right) + " ";
}

std::string removeSpaces(std::string s) {
	std::string result = "";
	for (int i = 0; i < s.length() - 1; i++)
		if (s[i] != ' ' || (s[i] == ' ' && s[i + 1] != ' ' && i != 0))
			result += s[i];
	if (s[s.length() - 1] != ' ')
		result += s[s.length() - 1];
	return result;
}

void generateEncodingTable(Node *parent, Table *table, std::string code) {
	static int index = 0;
	std::string myCode = code;
	if (parent == NULL)
		return;
	if (parent->left == NULL && parent->right == NULL) {
		table[index].content = parent->content;
		table[index].encoding = myCode;
		index++;
		return;
	}
	generateEncodingTable(parent->left, table, myCode+"0");
	generateEncodingTable(parent->right, table, myCode+"1");
}