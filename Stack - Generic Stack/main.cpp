#include <iostream>
using namespace std;

template <class T>
class GenericStack { // 제네릭 스택
public:
	int size; // 스택 크기
	T* data; // 스택 요소(element)
	int top; // 스택 상단 인덱스(stack top)

public:
	GenericStack(int size) { // 생성자
		this->size = size;
		this->data = new T[size];
		this->top = -1; // 스택이 비어 있으면 -1
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

int main() {
	int stackSize;
	cout << "생성 할 스택의 크기 입력 >> ";
	cin >> stackSize;
	cout << "크기 " << stackSize << "의 정수형 스택 생성됨..." << endl;

	GenericStack<int> stack(stackSize); // 정수형 스택 생성
	while (1) {
		int cmd;
		int item;
		cout << endl << "push(1), pop(2), peek(3) >> ";
		cin >> cmd;

		switch (cmd)
		{
		case 1:
			cout << "push 할 정수 입력 >> "; cin >> item;
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
			cout << "다시 입력하세요..." << endl;
			break;
		}
	}
}