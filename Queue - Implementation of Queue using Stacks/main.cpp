#include <iostream>
using namespace std;

/* ���׸� ���� */
template <class T>
class GenericStack {
private:
	int size; // ���� ũ��
	T* data; // ���� ���(element)
	int top; // ���� ��� �ε���(stack top)

public:
	GenericStack(int size) { // ������
		this->size = size;
		this->data = new T[size];
		this->top = -1; // ������ ��� ������ -1
	}

	GenericStack(const GenericStack& s) { // ��������� (���� ���׸� ���� �ڵ忡�� �߰�)
		size = s.size;
		data = new T[size];
		top = s.top;

		for (int i = 0; i < size; i++) {
			data[i] = s.data[i];
		}
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

/* ���׸� ������ �̿��� ���׸� ť */
template <class T>
class GenericQueue {
private:
	int size; // ť ũ��
	GenericStack<T> *stk1; // Stack 1 (����)
	GenericStack<T> *stk2; // Stack 2 (����)

public:
	GenericQueue(int size) { // ������
		this->size = size;
		this->stk1 = new GenericStack<T>(size);
		this->stk2 = new GenericStack<T>(size);
	}

	~GenericQueue() { // �Ҹ���
		delete stk1;
		delete stk2;
	}

	bool isFull() {
		if (stk1->isFull()) return true;
		else return false;
	}

	bool isEmpty() {
		if (stk1->isEmpty()) return true;
		else return false;
	}

	bool enqueue(T item) {
		if (isFull()) {
			return false; // enqueue ���� �� false ��ȯ
		}
		else {
			stk1->push(item);
			return true;
		}
	}

	bool dequeue(T& item) {
		if (isEmpty()) {
			return false; // dequeue ���� �� false ��ȯ
		}
		else {
			/* [step 1] stk1�� ��Ҹ� stk2�� �Ű� ��� ���� ���� */
			while (!stk1->isEmpty()) {
				T tmp;
				stk1->pop(tmp);
				stk2->push(tmp);
			}

			/* [step 2] ��� ������ ������ stk2���� pop */
			stk2->pop(item);

			/* [step 3] stk2�� ��Ҹ� stk1�� �Ű� ���󺹱� */
			while (!stk2->isEmpty()) {
				T tmp;
				stk2->pop(tmp);
				stk1->push(tmp);
			}

			return true;
		}
	}

	bool peek(T& item) { // dequeue()���� stap 2�κи� ����
		if (isEmpty()) {
			return false; // peek ���� �� false ��ȯ
		}
		else {
			/* [step 1] stk1�� ��Ҹ� stk2�� �Ű� ��� ���� ���� */
			while (!stk1->isEmpty()) {
				T tmp;
				stk1->pop(tmp);
				stk2->push(tmp);
			}

			/* [step 2] ��� ������ ������ stk2���� peek */
			stk2->peek(item);

			/* [step 3] stk2�� ��Ҹ� stk1�� �Ű� ���󺹱� */
			while (!stk2->isEmpty()) {
				T tmp;
				stk2->pop(tmp);
				stk1->push(tmp);
			}

			return true;
		}
	}

	void printQueue() {
		GenericStack<T> tmp(*stk1); // ���� stk1�� ���纻 ����

		cout << "[ť�� ����] front��rear = bottom��top" << endl;
		while (!tmp.isEmpty()) {
			int item;
			tmp.pop(item);
			cout << "\t" << item << endl;
		}
	}
};

int main() {
	int queueSize;
	cout << "���� �� ť�� ũ�� �Է� >> ";
	cin >> queueSize;
	cout << "ũ�� " << queueSize << "�� ������ ť ������..." << endl;

	GenericQueue<int> queue(queueSize); // ������ ť ����
	while (1) {
		int cmd;
		int item;
		cout << endl << "enqueue(1), dequeue(2), peek(3), printQueue(4) >> ";
		cin >> cmd;

		switch (cmd)
		{
		case 1:
			cout << "enqueue �� ���� �Է� >> "; cin >> item;
			if (queue.enqueue(item)) cout << item << " enqueued..." << endl;
			else cout << "queue full..." << endl;
			break;

		case 2:
			if (queue.dequeue(item)) cout << item << " dequeued..." << endl;
			else cout << "queue empty..." << endl;
			break;

		case 3:
			if (queue.peek(item)) cout << item << " is the first element..." << endl;
			else cout << "queue empty..." << endl;
			break;

		case 4:
			if (queue.isEmpty()) cout << "queue empty..." << endl;
			else queue.printQueue();
			break;

		default:
			cout << "�ٽ� �Է��ϼ���..." << endl;
			break;
		}
	}
}