#include <iostream>
using namespace std;

/* 제네릭 스택 */
template <class T>
class GenericStack {
private:
	int size; // 스택 크기
	T* data; // 스택 요소(element)
	int top; // 스택 상단 인덱스(stack top)

public:
	GenericStack(int size) { // 생성자
		this->size = size;
		this->data = new T[size];
		this->top = -1; // 스택이 비어 있으면 -1
	}

	GenericStack(const GenericStack& s) { // 복사생성자 (기존 제네릭 스텍 코드에서 추가)
		size = s.size;
		data = new T[size];
		top = s.top;

		for (int i = 0; i < size; i++) {
			data[i] = s.data[i];
		}
	}

	~GenericStack() { // 소멸자
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
			return false; // push 실패 시 false 반환
		}
		else {
			top++;
			data[top] = item;
			return true;
		}
	}

	bool pop(T& item) {
		if (isEmpty()) {
			return false; // pop 실패 시 false 반환
		}
		else {
			item = data[top];
			top--;
			return true;
		}
	}

	bool peek(T& item) {
		if (isEmpty()) {
			return false; // peek 실패 시 false 반환
		}
		else {
			item = data[top];
			return true;
		}
	}
};

/* 제네릭 스택을 이용한 제네릭 큐 */
template <class T>
class GenericQueue {
private:
	int size; // 큐 크기
	GenericStack<T> *stk1; // Stack 1 (메인)
	GenericStack<T> *stk2; // Stack 2 (보조)

public:
	GenericQueue(int size) { // 생성자
		this->size = size;
		this->stk1 = new GenericStack<T>(size);
		this->stk2 = new GenericStack<T>(size);
	}

	~GenericQueue() { // 소멸자
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
			return false; // enqueue 실패 시 false 반환
		}
		else {
			stk1->push(item);
			return true;
		}
	}

	bool dequeue(T& item) {
		if (isEmpty()) {
			return false; // dequeue 실패 시 false 반환
		}
		else {
			/* [step 1] stk1의 요소를 stk2로 옮겨 요소 순서 반전 */
			while (!stk1->isEmpty()) {
				T tmp;
				stk1->pop(tmp);
				stk2->push(tmp);
			}

			/* [step 2] 요소 순서가 반전된 stk2에서 pop */
			stk2->pop(item);

			/* [step 3] stk2의 요소를 stk1로 옮겨 원상복구 */
			while (!stk2->isEmpty()) {
				T tmp;
				stk2->pop(tmp);
				stk1->push(tmp);
			}

			return true;
		}
	}

	bool peek(T& item) { // dequeue()에서 stap 2부분만 수정
		if (isEmpty()) {
			return false; // peek 실패 시 false 반환
		}
		else {
			/* [step 1] stk1의 요소를 stk2로 옮겨 요소 순서 반전 */
			while (!stk1->isEmpty()) {
				T tmp;
				stk1->pop(tmp);
				stk2->push(tmp);
			}

			/* [step 2] 요소 순서가 반전된 stk2에서 peek */
			stk2->peek(item);

			/* [step 3] stk2의 요소를 stk1로 옮겨 원상복구 */
			while (!stk2->isEmpty()) {
				T tmp;
				stk2->pop(tmp);
				stk1->push(tmp);
			}

			return true;
		}
	}

	void printQueue() {
		GenericStack<T> tmp(*stk1); // 스택 stk1의 복사본 생성

		cout << "[큐의 방향] front→rear = bottom→top" << endl;
		while (!tmp.isEmpty()) {
			int item;
			tmp.pop(item);
			cout << "\t" << item << endl;
		}
	}
};

int main() {
	int queueSize;
	cout << "생성 할 큐의 크기 입력 >> ";
	cin >> queueSize;
	cout << "크기 " << queueSize << "의 정수형 큐 생성됨..." << endl;

	GenericQueue<int> queue(queueSize); // 정수형 큐 생성
	while (1) {
		int cmd;
		int item;
		cout << endl << "enqueue(1), dequeue(2), peek(3), printQueue(4) >> ";
		cin >> cmd;

		switch (cmd)
		{
		case 1:
			cout << "enqueue 할 정수 입력 >> "; cin >> item;
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
			cout << "다시 입력하세요..." << endl;
			break;
		}
	}
}