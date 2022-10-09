#include <iostream>
#define MAX(a, b) (a > b ? a : b) // (매크로 함수) 최대값 연산
using namespace std;

/* 다항식 클래스 */
class Polynomial {
public:
	int degree; // 다항식의 차수
	int* coef; // coefficient, 계수 // 상수항 -> 최고차항 순으로 저장

	~Polynomial() { // 소멸자
		if (!coef) delete[] coef;
	}

	Polynomial() { // 기본생성자
		degree = 0; coef = NULL;
	}

	Polynomial(const Polynomial& p) { // 복사생성자
		this->degree = p.degree;
		this->coef = new int[p.degree + 1]; // 상수항 자리까지 할당
		for (int i = 0; i <= p.degree; i++)
			this->coef[i] = p.coef[i];
	}

	void print_polynomial() { // 다항식 출력
		/* 2차항 ~ 최고차항 출력 */
		for (int i = degree; i > 1; i--) {
			if (coef[i] != 0) {
				if (i != degree) cout << " + ";
				cout << coef[i] << "x^" << i;
			}
		}	
		/* 1차항 출력 */
		if (coef[1] != 0) {
			if (degree != 1) cout << " + "; // 1차식이 아니면
			cout << coef[1] << "x";
		}
		/* 상수항 출력 */
		if (coef[0] != 0) {
			if (degree != 0) cout << " + "; // 0차식이 아니면
			cout << coef[0];
		}
		/* 값이 0인 경우 */
		if (degree == 0 && coef[0] == 0)
			cout << 0;
	}
};

/* 다항식 연산 */
class PolyOperation {
public:
	static void add_poly(Polynomial A, Polynomial B, Polynomial *ret) {
		/* ret 초기화 */
		ret->degree = MAX(A.degree, B.degree);
		ret->coef = new int[ret->degree + 1]; // 상수항 자리까지 할당

		/* 덧셈연산 */
		for (int i = 0; i <= ret->degree; i++) {
			if (i > A.degree) { ret->coef[i] = B.coef[i]; continue; }
			if (i > B.degree) { ret->coef[i] = A.coef[i]; continue; }
			ret->coef[i] = A.coef[i] + B.coef[i];
		}
	}
	static void sub_poly(Polynomial A, Polynomial B, Polynomial *ret) {
		/* ret 초기화 */
		ret->degree = MAX(A.degree, B.degree);
		ret->coef = new int[ret->degree + 1]; // 상수항 자리까지 할당

		/* 뺄셈연산 */
		for (int i = 0; i <= ret->degree; i++) {
			if (i > A.degree) { ret->coef[i] = (B.coef[i] * -1); continue; }
			if (i > B.degree) { ret->coef[i] = A.coef[i]; continue; }
			ret->coef[i] = A.coef[i] - B.coef[i];
		}

		/* ret의 degree값 재조정 */
		// 최고차항이 바뀌거나 값이 0인 경우 재조정 필요
		bool isZero = true;
		for (int i = ret->degree; i >= 0; i--) {
			if (ret->coef[i] != 0) {
				ret->degree = i;
				isZero = false;
				break;
			}
		}
		if (isZero) ret->degree = 0; // 값이 0인 경우
	}
	static void mul_poly(Polynomial A, Polynomial B, Polynomial *ret) {
		/* ret 초기화 */
		ret->degree = A.degree + B.degree;
		ret->coef = new int[ret->degree + 1]; // 상수항 자리까지 할당
		for (int i = 0; i <= ret->degree; i++)
			ret->coef[i] = 0;

		/* 곱셈연산 */
		for (int i = 0; i <= A.degree; i++) {
			for (int j = 0; j <= B.degree; j++) {
				ret->coef[i + j] += A.coef[i] * B.coef[j];
			}
		}
	}
	static void div_poly(Polynomial A, Polynomial B, Polynomial *ret1, Polynomial *ret2) {
		/* ret1 (몫) 초기화 */
		ret1->degree = A.degree - B.degree; // 몫의 차수 = A의 차수 - B의 차수
		ret1->coef = new int[ret1->degree + 1]; // 상수항 자리까지 할당
		for (int i = 0; i <= ret1->degree; i++)
			ret1->coef[i] = 0;

		/* ret2 (나머지) 초기화 */
		ret2->degree = A.degree; // 발생 가능한 나머지의 최대 자릿수 할당
		ret2->coef = new int[ret2->degree + 1]; // 상수항 자리까지 할당
		for (int i = 0; i <= ret2->degree; i++)
			ret2->coef[i] = A.coef[i];

		/* 나눗셈연산 */
		for (int i = ret1->degree; i >= 0; i--) { // i = A.degree - B.degree
			ret1->coef[i] = ret2->coef[i + B.degree] / B.coef[B.degree]; // i + B.degree = 다항식 A의 차수부터 1씩 감소 

			/* 빼 줄 다항식(tmp) */
			Polynomial tmp;
			tmp.degree = i + B.degree;
			tmp.coef = new int[tmp.degree + 1];
			for (int j = 0; j <= tmp.degree; j++)
				tmp.coef[j] = 0;

			int count = B.degree;
			for (int j = tmp.degree; i <= j; j--) {
				tmp.coef[j] = (ret1->coef[i]) * (B.coef[count]);
				count--; // 다항식 B의 차수부터 1씩 감소
			}

			/* 빼기 */
			sub_poly(*ret2, tmp, ret2);

			/* ret2 (나머지)의 degree값 재조정 */
			bool isZero = true;
			for (int i = ret2->degree; i >= 0; i--) {
				if (ret2->coef[i] != 0) {
					ret2->degree = i;
					isZero = false;
					break;
				}
			}
			if (isZero) ret2->degree = 0; // 값이 0인 경우
		}
	}
};

class Console {
private:
	static Polynomial A, B;
public:
	static void enter_polynomial() { // 피연산자 입력
		/* 다항식 A 입력 */
		cout << endl << "다항식 A의 차수 입력 >> ";
		cin >> A.degree;

		A.coef = new int[A.degree + 1]; // 상수항 자리까지 할당

		for (int i = A.degree; i > 0; i--) {
			cout << "x^" << i << " 의 계수 입력 >> ";
			cin >> A.coef[i];
		}
		cout << "상수항 입력 >> "; cin >> A.coef[0];

		/* 다항식 B 입력 */
		cout << endl << "다항식 B의 차수 입력 >> ";
		cin >> B.degree;

		B.coef = new int[B.degree + 1]; // 상수항 자리까지 할당

		for (int i = B.degree; i > 0; i--) {
			cout << "x^" << i << " 의 계수 입력 >> ";
			cin >> B.coef[i];
		}
		cout << "상수항 입력 >> "; cin >> B.coef[0];

		/* 입력한 다항식 확인 */
		cout << endl << "\t다항식 A : "; A.print_polynomial();
		cout << endl << "\t다항식 B : "; B.print_polynomial();
	}

	static void print_results() { // 결과값 출력
		Polynomial* ret1 = new Polynomial; Polynomial* ret2 = new Polynomial; Polynomial* ret3 = new Polynomial;
		Polynomial* ret4 = new Polynomial; Polynomial* ret5 = new Polynomial;

		cout << endl;
		PolyOperation::add_poly(A, B, ret1); cout << endl << "\tA + B =  "; ret1->print_polynomial();
		PolyOperation::sub_poly(A, B, ret2); cout << endl << "\tA - B =  "; ret2->print_polynomial();
		PolyOperation::mul_poly(A, B, ret3); cout << endl << "\tA * B =  "; ret3->print_polynomial();
		PolyOperation::div_poly(A, B, ret4, ret5); cout << endl << "\tA / B =  (몫) "; ret4->print_polynomial(); cout << "  (나머지) "; ret5->print_polynomial();
		cout << endl;

		delete ret1; delete ret2; delete ret3; delete ret4; delete ret5;
	}
};

Polynomial Console::A; // static 멤버 변수는 외부에 전역 변수로 선언되어야 함
Polynomial Console::B;

int main() {
	Console::enter_polynomial();
	Console::print_results();
}