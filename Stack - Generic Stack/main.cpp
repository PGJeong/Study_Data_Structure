#include <iostream>
using namespace std;

template <class T>
class GenericStack { // ���׸� ����
public:
	int size; // ���� ũ��
	T* data; // ���� ���(element)
	int top; // ���� ��� �ε���(stack top)

public:
	GenericStack(int size) { // ������
		this->size = size;
		this->data = new T[size];
		this->top = -1; // ������ ��� ������ -1
	}

	~GenericStack() { // �Ҹ���
		delete[] data;
	}

	bool isFull() {
		if (top == (size - 1)) return true;
		else return false;
	}

	bool isEmpty() {
		if (top == -1) return true;
		else return false;
	}

	bool push(T item) {
		if (isFull()) {
			return false; // push ���� �� false ��ȯ
		}
		else {
			top++;
			data[top] = item;
			return true;
		}
	}

	bool pop(T& item) {
		if (isEmpty()) {
			return false; // pop ���� �� false ��ȯ
		}
		else {
			item = data[top];
			top--;
			return true;
		}
	}

	bool peek(T& item) {
		if (isEmpty()) {
			return false; // peek ���� �� false ��ȯ
		}
		else {
			item = data[top];
			return true;
		}
	}
};

int main() {
	int stackSize;
	cout << "���� �� ������ ũ�� �Է� >> ";
	cin >> stackSize;
	cout << "ũ�� " << stackSize << "�� ������ ���� ������..." << endl;

	GenericStack<int> stack(stackSize); // ������ ���� ����
	while (1) {
		int cmd;
		int item;
		cout << endl << "push(1), pop(2), peek(3) >> ";
		cin >> cmd;

		switch (cmd)
		{
		case 1:
			cout << "push �� ���� �Է� >> "; cin >> item;
			if (stack.push(item)) cout << item << " pushed..." << endl;
			else cout << "stack full..." << endl;
			break;

		case 2:
			if (stack.pop(item)) cout << item << " popped..." << endl;
			else cout << "stack empty..." << endl;
			break;

		case 3:
			if (stack.peek(item)) cout << item << " is the top element..." << endl;
			else cout << "stack empty..." << endl;
			break;

		default:
			cout << "�ٽ� �Է��ϼ���..." << endl;
			break;
		}
	}
}