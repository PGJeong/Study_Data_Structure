#include <iostream>
using namespace std;

typedef int element;

class Node {
private:
	element data;
	Node* link;
	Node() { data = NULL; link = NULL; }

	friend class LinkedList;
};

class LinkedList {
private:
	Node* head;
	Node* tail;
	int length;

public:	
	LinkedList() {
		head = NULL;
		tail = NULL;
		length = 0;
	}

	Node* getHead() {
		return head;
	}

	void insertFirst(element data) {
		if (!isEmpty()) {
			cout << "Error : Element already exists in the List!" << endl;
			return;
		}

		head = new Node;
		head->data = data;
		tail = head;
		length++;
	}

	void insertLast(element data) {
		if (isEmpty()) {
			insertFirst(data);
			return;
		}

		Node* temp = new Node;
		temp->data = data;
		tail->link = temp;
		tail = temp;
		length++;
	}

	void insert(int pos, element data) {
		if (pos - 1 > length) {
			cout << "Error : The value entered is greater than the length!" << endl;
			return;
		}

		if (pos == 0) {
			insertFirst(data);
			return;
		}

		if (pos - 1 == length) {
			insertLast(data);
			return;
		}

		Node* prev = head;
		Node* temp = new Node;

		for (int i = 1; i < pos; i++) {
			prev = prev->link;
		}

		temp->data = data;
		temp->link = prev->link;
		prev->link = temp;
		length++;
	}

	void removeFirst() {
		if (isEmpty()) {
			cout << "Error : The List is Empty!" << endl;
			return;
		}

		Node* target = head;

		head = head->link;
		delete target;
		length--;
	}

	void remove(int pos) { // pos위치의 요소 제거
		if (isEmpty()) {
			cout << "Error : The List is Empty!" << endl;
			return;
		}

		if (pos == 0) {
			removeFirst();
			return;
		}

		if (pos > length) {
			cout << "Error : The value entered is greater than the length!" << endl;
			return;
		}

		Node* prev = head;
		Node* target;

		for (int i = 1; i < pos; i++) {
			prev = prev->link;
		}

		target = prev->link;
		prev->link = target->link;
		delete target;
		length--;
	}

	void clear() { // 모든 요소 제거
		Node* temp = head;

		do {
			Node* target = temp;
			temp = temp->link;
			delete target;
			length--;
		} while (temp != NULL);
	}

	element getEntry(int pos) { // pos 위치의 요소 반환
		Node* temp = head;

		for (int i = 0; i < pos; i++) {
			temp = temp->link;
		}

		return temp->data;
	}

	int getLength() { // Linked List의 길이 반환
		return length;
	}

	bool isEmpty() {
		if (length == 0) return true;
		else return false;
	}

	bool isFull() {
		return false;
	}

	void printList() { // Linked List의 모든 요소 출력
		if (isEmpty()) {
			cout << "Error : The List is Empty!" << endl;
			return;
		}

		Node* temp = head;

		for (int i = 0; i < length; i++) {
			cout << "[" << i << "]\t" << temp->data << endl;
			temp = temp->link;
		}
	}
};

int main() {
	
}