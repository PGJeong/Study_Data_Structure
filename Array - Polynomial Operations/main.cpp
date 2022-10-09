#include <iostream>
#define MAX(a, b) (a > b ? a : b) // (��ũ�� �Լ�) �ִ밪 ����
using namespace std;

/* ���׽� Ŭ���� */
class Polynomial {
public:
	int degree; // ���׽��� ����
	int* coef; // coefficient, ��� // ����� -> �ְ����� ������ ����

	~Polynomial() { // �Ҹ���
		if (!coef) delete[] coef;
	}

	Polynomial() { // �⺻������
		degree = 0; coef = NULL;
	}

	Polynomial(const Polynomial& p) { // ���������
		this->degree = p.degree;
		this->coef = new int[p.degree + 1]; // ����� �ڸ����� �Ҵ�
		for (int i = 0; i <= p.degree; i++)
			this->coef[i] = p.coef[i];
	}

	void print_polynomial() { // ���׽� ���
		/* 2���� ~ �ְ����� ��� */
		for (int i = degree; i > 1; i--) {
			if (coef[i] != 0) {
				if (i != degree) cout << " + ";
				cout << coef[i] << "x^" << i;
			}
		}	
		/* 1���� ��� */
		if (coef[1] != 0) {
			if (degree != 1) cout << " + "; // 1������ �ƴϸ�
			cout << coef[1] << "x";
		}
		/* ����� ��� */
		if (coef[0] != 0) {
			if (degree != 0) cout << " + "; // 0������ �ƴϸ�
			cout << coef[0];
		}
		/* ���� 0�� ��� */
		if (degree == 0 && coef[0] == 0)
			cout << 0;
	}
};

/* ���׽� ���� */
class PolyOperation {
public:
	static void add_poly(Polynomial A, Polynomial B, Polynomial *ret) {
		/* ret �ʱ�ȭ */
		ret->degree = MAX(A.degree, B.degree);
		ret->coef = new int[ret->degree + 1]; // ����� �ڸ����� �Ҵ�

		/* �������� */
		for (int i = 0; i <= ret->degree; i++) {
			if (i > A.degree) { ret->coef[i] = B.coef[i]; continue; }
			if (i > B.degree) { ret->coef[i] = A.coef[i]; continue; }
			ret->coef[i] = A.coef[i] + B.coef[i];
		}
	}
	static void sub_poly(Polynomial A, Polynomial B, Polynomial *ret) {
		/* ret �ʱ�ȭ */
		ret->degree = MAX(A.degree, B.degree);
		ret->coef = new int[ret->degree + 1]; // ����� �ڸ����� �Ҵ�

		/* �������� */
		for (int i = 0; i <= ret->degree; i++) {
			if (i > A.degree) { ret->coef[i] = (B.coef[i] * -1); continue; }
			if (i > B.degree) { ret->coef[i] = A.coef[i]; continue; }
			ret->coef[i] = A.coef[i] - B.coef[i];
		}

		/* ret�� degree�� ������ */
		// �ְ������� �ٲ�ų� ���� 0�� ��� ������ �ʿ�
		bool isZero = true;
		for (int i = ret->degree; i >= 0; i--) {
			if (ret->coef[i] != 0) {
				ret->degree = i;
				isZero = false;
				break;
			}
		}
		if (isZero) ret->degree = 0; // ���� 0�� ���
	}
	static void mul_poly(Polynomial A, Polynomial B, Polynomial *ret) {
		/* ret �ʱ�ȭ */
		ret->degree = A.degree + B.degree;
		ret->coef = new int[ret->degree + 1]; // ����� �ڸ����� �Ҵ�
		for (int i = 0; i <= ret->degree; i++)
			ret->coef[i] = 0;

		/* �������� */
		for (int i = 0; i <= A.degree; i++) {
			for (int j = 0; j <= B.degree; j++) {
				ret->coef[i + j] += A.coef[i] * B.coef[j];
			}
		}
	}
	static void div_poly(Polynomial A, Polynomial B, Polynomial *ret1, Polynomial *ret2) {
		/* ret1 (��) �ʱ�ȭ */
		ret1->degree = A.degree - B.degree; // ���� ���� = A�� ���� - B�� ����
		ret1->coef = new int[ret1->degree + 1]; // ����� �ڸ����� �Ҵ�
		for (int i = 0; i <= ret1->degree; i++)
			ret1->coef[i] = 0;

		/* ret2 (������) �ʱ�ȭ */
		ret2->degree = A.degree; // �߻� ������ �������� �ִ� �ڸ��� �Ҵ�
		ret2->coef = new int[ret2->degree + 1]; // ����� �ڸ����� �Ҵ�
		for (int i = 0; i <= ret2->degree; i++)
			ret2->coef[i] = A.coef[i];

		/* ���������� */
		for (int i = ret1->degree; i >= 0; i--) { // i = A.degree - B.degree
			ret1->coef[i] = ret2->coef[i + B.degree] / B.coef[B.degree]; // i + B.degree = ���׽� A�� �������� 1�� ���� 

			/* �� �� ���׽�(tmp) */
			Polynomial tmp;
			tmp.degree = i + B.degree;
			tmp.coef = new int[tmp.degree + 1];
			for (int j = 0; j <= tmp.degree; j++)
				tmp.coef[j] = 0;

			int count = B.degree;
			for (int j = tmp.degree; i <= j; j--) {
				tmp.coef[j] = (ret1->coef[i]) * (B.coef[count]);
				count--; // ���׽� B�� �������� 1�� ����
			}

			/* ���� */
			sub_poly(*ret2, tmp, ret2);

			/* ret2 (������)�� degree�� ������ */
			bool isZero = true;
			for (int i = ret2->degree; i >= 0; i--) {
				if (ret2->coef[i] != 0) {
					ret2->degree = i;
					isZero = false;
					break;
				}
			}
			if (isZero) ret2->degree = 0; // ���� 0�� ���
		}
	}
};

class Console {
private:
	static Polynomial A, B;
public:
	static void enter_polynomial() { // �ǿ����� �Է�
		/* ���׽� A �Է� */
		cout << endl << "���׽� A�� ���� �Է� >> ";
		cin >> A.degree;

		A.coef = new int[A.degree + 1]; // ����� �ڸ����� �Ҵ�

		for (int i = A.degree; i > 0; i--) {
			cout << "x^" << i << " �� ��� �Է� >> ";
			cin >> A.coef[i];
		}
		cout << "����� �Է� >> "; cin >> A.coef[0];

		/* ���׽� B �Է� */
		cout << endl << "���׽� B�� ���� �Է� >> ";
		cin >> B.degree;

		B.coef = new int[B.degree + 1]; // ����� �ڸ����� �Ҵ�

		for (int i = B.degree; i > 0; i--) {
			cout << "x^" << i << " �� ��� �Է� >> ";
			cin >> B.coef[i];
		}
		cout << "����� �Է� >> "; cin >> B.coef[0];

		/* �Է��� ���׽� Ȯ�� */
		cout << endl << "\t���׽� A : "; A.print_polynomial();
		cout << endl << "\t���׽� B : "; B.print_polynomial();
	}

	static void print_results() { // ����� ���
		Polynomial* ret1 = new Polynomial; Polynomial* ret2 = new Polynomial; Polynomial* ret3 = new Polynomial;
		Polynomial* ret4 = new Polynomial; Polynomial* ret5 = new Polynomial;

		cout << endl;
		PolyOperation::add_poly(A, B, ret1); cout << endl << "\tA + B =  "; ret1->print_polynomial();
		PolyOperation::sub_poly(A, B, ret2); cout << endl << "\tA - B =  "; ret2->print_polynomial();
		PolyOperation::mul_poly(A, B, ret3); cout << endl << "\tA * B =  "; ret3->print_polynomial();
		PolyOperation::div_poly(A, B, ret4, ret5); cout << endl << "\tA / B =  (��) "; ret4->print_polynomial(); cout << "  (������) "; ret5->print_polynomial();
		cout << endl;

		delete ret1; delete ret2; delete ret3; delete ret4; delete ret5;
	}
};

Polynomial Console::A; // static ��� ������ �ܺο� ���� ������ ����Ǿ�� ��
Polynomial Console::B;

int main() {
	Console::enter_polynomial();
	Console::print_results();
}