#include <iostream>
#include <list> // (C++ STL) Linked List
#define TABLE_SIZE 97 // Prime No

using namespace std;

class Data {
public:
	int studentID;
	string name;
	string subject;
	int score;

	Data(int studentID, string subject, int score) {
		this->studentID = studentID;
		this->name = '\0';
		this->subject = subject;
		this->score = score;
	}

	Data(string name, string subject, int score) {
		this->studentID = NULL;
		this->name = name;
		this->subject = subject;
		this->score = score;
	}
};

class Hash {
private:
	list<Data*> hashTable[TABLE_SIZE];

	int hashFunction(int studentID, string subject) {
		int subject_val = 0;

		for (int i = 0; i < subject.length(); i++) {
			subject_val += subject[i] - 'a' + 1;
		}

		return (subject_val + studentID) % TABLE_SIZE;
	}
	int hashFunction(string name, string subject) {
		int subject_val = 0;
		int name_val = 0;

		for (int i = 0; i < subject.length(); i++) {
			subject_val += subject[i] - 'a' + 1;
		}

		for (int i = 0; i < name.length(); i++) {
			name_val += name[i] - 'a' + 1;
		}

		return (subject_val + name_val) % TABLE_SIZE;
	}

public:
	void search(int studentID, string subject) { // 번호, 과목명
		int hashVal = hashFunction(studentID, subject);

		for (std::list<Data*>::iterator itr = hashTable[hashVal].begin(); itr != hashTable[hashVal].end(); itr++) {
			if ((*itr)->studentID == studentID && (*itr)->subject == subject) {
				cout << "(" << studentID << ", " << subject << ")의 검색 결과 : " << (*itr)->score << "점" << endl;
				return;
			}
		}

		cout << "(" << studentID << ", " << subject << ")를 찾을 수 없음..."<< endl;
	}
	void search(string name, string subject) { // 성명, 과목명
		int hashVal = hashFunction(name, subject);

		for (std::list<Data*>::iterator itr = hashTable[hashVal].begin(); itr != hashTable[hashVal].end(); itr++) {
			if ((*itr)->name == name && (*itr)->subject == subject) {
				cout << "(" << name << ", " << subject << ")의 검색 결과 : " << (*itr)->score << "점" << endl;
				return;
			}
		}

		cout << "(" << name << ", " << subject << ")를 찾을 수 없음..." << endl;
	}
	void add(int studentID, string subject, int score) {
		int hashVal = hashFunction(studentID, subject);

		for (std::list<Data*>::iterator itr = hashTable[hashVal].begin(); itr != hashTable[hashVal].end(); itr++) {
			if ((*itr)->studentID == studentID && (*itr)->subject == subject) {
				cout << "이미 (학번, 과목)에 대한 값이 저장되어 있습니다..." << endl;
				return;
			}
		}

		hashTable[hashVal].push_back(new Data(studentID, subject, score));
		cout << "key : (" << studentID << ", " << subject << "), val : " << score << " 저장완료... (Hash Val : " << hashVal << ")" << endl;
	}
	void add(string name, string subject, int score) {
		int hashVal = hashFunction(name, subject);

		for (std::list<Data*>::iterator itr = hashTable[hashVal].begin(); itr != hashTable[hashVal].end(); itr++) {
			if ((*itr)->name == name && (*itr)->subject == subject) {
				cout << "이미 (성명, 과목)에 대한 값이 저장되어 있습니다..." << endl;
				return;
			}
		}

		hashTable[hashVal].push_back(new Data(name, subject, score));
		cout << "key : (" << name << ", " << subject << "), val : " << score << " 저장완료... (Hash Val : " << hashVal << ")" << endl;
	}
	void remove(int studentID, string subject) {
		int hashVal = hashFunction(studentID, subject);

		for (std::list<Data*>::iterator itr = hashTable[hashVal].begin(); itr != hashTable[hashVal].end(); itr++) {
			if ((*itr)->studentID == studentID && (*itr)->subject == subject) {
				hashTable[hashVal].erase(itr);
				cout << "(" << studentID << ", " << subject << ") 삭제완료..." << endl;
				return;
			}
		}

		cout << "(" << studentID << ", " << subject << ")를 찾을 수 없음..." << endl;
	}
	void remove(string name, string subject) {
		int hashVal = hashFunction(name, subject);

		for (std::list<Data*>::iterator itr = hashTable[hashVal].begin(); itr != hashTable[hashVal].end(); itr++) {
			if ((*itr)->name == name && (*itr)->subject == subject) {
				hashTable[hashVal].erase(itr);
				cout << "(" << name << ", " << subject << ") 삭제완료..." << endl;
				return;
			}
		}

		cout << "(" << name << ", " << subject << ")를 찾을 수 없음..." << endl;
	}
};

int main() {
	// [주의] name 및 subject는 반드시 영문으로 입력할 것!

	Hash hash;

	/* add(key, value) 함수 */
	hash.add("Kim", "Math", 26); // Key : (이름, 과목명), Value : 점수 
	hash.add(12, "Science", 60); // Key : (번호, 과목명), Value : 점수

	/* search(key) 함수 */
	hash.search("Kim", "Math"); // Key : (이름, 과목명)
	hash.search(99, "Science"); // Key : (번호, 과목명)

	/* remove(key) 함수 */
	hash.remove("Jeong", "English");
	hash.remove(12, "Science");
}