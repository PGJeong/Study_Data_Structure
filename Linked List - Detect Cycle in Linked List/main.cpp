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

	void remove(int pos) { // pos��ġ�� ��� ����
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

	void clear() { // ��� ��� ����
		Node* temp = head;

		do {
			Node* target = temp;
			temp = temp->link;
			delete target;
			length--;
		} while (temp != NULL);
	}

	element getEntry(int pos) { // pos ��ġ�� ��� ��ȯ
		Node* temp = head;

		for (int i = 0; i < pos; i++) {
			temp = temp->link;
		}

		return temp->data;
	}

	int getLength() { // Linked List�� ���� ��ȯ
		return length;
	}

	bool isEmpty() {
		if (length == 0) return true;
		else return false;
	}

	bool isFull() {
		return false;
	}

	void printList() { // Linked List�� ��� ��� ���
		if (isEmpty()) {
			cout << "Error : The List is Empty!" << endl;
			return;
		}

		Node* temp = head;

		for (int i = 0; i < length; i++) {
			if(temp->link != NULL)
				cout << "[" << i << "]\t" << temp->data << "\t(Link -> " << temp->link->data << ")" << endl;
			else
				cout << "[" << i << "]\t" << temp->data << "\t(Link -> NULL)" << endl;
			temp = temp->link;
		}
	}

	bool hasCycle() { // Linked List�� Cycle�� ���翩�� ����
		Node* fast = head; // 2ĭ�� ������
		Node* slow = head; // 1ĭ�� ������

		// Cycle�� �ִ� ��� 2���� �����ʹ� Cycle �ȿ��� �ݵ�� ������
		// Cycle�� ���� ��� fast�� ���� ����Ʈ�� ���� ����
		// fast�� 2ĭ�� ������ �̵��ϹǷ� fast->link�� NULL�� �ƴϾ�� �Ѵ�

		while (fast != NULL && fast->link != NULL) {
			slow = slow->link;
			fast = fast->link->link;

			if (fast == slow)
				return true;
		}

		return false;
	}

	void modifyLink(int targetNodeIndex, int newLinkNodeIndex) { // 3�� �׸��� ���� �Լ�
		Node* target = head;
		for (int i = 0; i < targetNodeIndex; i++) {
			target = target->link;
		}

		Node* newLink = head;
		for (int i = 0; i < newLinkNodeIndex; i++) {
			newLink = newLink->link;
		}

		target->link = newLink;
	}
};

int main() {
	/* 2�� */

	LinkedList list1;
	for (int i = 1; i <= 5; i++) list1.insertLast(i * 10);

	cout << endl << "- List 1 -" << endl << endl;
	list1.printList();

	/* 3�� */

	LinkedList list2;
	for (int i = 1; i <= 5; i++) list2.insertLast(i * 10);

	cout << endl << "- List 2 -" << endl << endl;
	list2.modifyLink(4, 1);
	list2.printList();

	/* 4�� */

	cout << endl << "List 1 : ";
	if (list1.hasCycle()) cout << "Cycle Found" << endl;
	else cout << "No Cycle" << endl;

	cout << endl << "List 2 : ";
	if (list2.hasCycle()) cout << "Cycle Found" << endl;
	else cout << "No Cycle" << endl;
}