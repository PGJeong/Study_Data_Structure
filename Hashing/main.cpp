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
	void search(int studentID, string subject) { // ��ȣ, �����
		int hashVal = hashFunction(studentID, subject);

		for (std::list<Data*>::iterator itr = hashTable[hashVal].begin(); itr != hashTable[hashVal].end(); itr++) {
			if ((*itr)->studentID == studentID && (*itr)->subject == subject) {
				cout << "(" << studentID << ", " << subject << ")�� �˻� ��� : " << (*itr)->score << "��" << endl;
				return;
			}
		}

		cout << "(" << studentID << ", " << subject << ")�� ã�� �� ����..."<< endl;
	}
	void search(string name, string subject) { // ����, �����
		int hashVal = hashFunction(name, subject);

		for (std::list<Data*>::iterator itr = hashTable[hashVal].begin(); itr != hashTable[hashVal].end(); itr++) {
			if ((*itr)->name == name && (*itr)->subject == subject) {
				cout << "(" << name << ", " << subject << ")�� �˻� ��� : " << (*itr)->score << "��" << endl;
				return;
			}
		}

		cout << "(" << name << ", " << subject << ")�� ã�� �� ����..." << endl;
	}
	void add(int studentID, string subject, int score) {
		int hashVal = hashFunction(studentID, subject);

		for (std::list<Data*>::iterator itr = hashTable[hashVal].begin(); itr != hashTable[hashVal].end(); itr++) {
			if ((*itr)->studentID == studentID && (*itr)->subject == subject) {
				cout << "�̹� (�й�, ����)�� ���� ���� ����Ǿ� �ֽ��ϴ�..." << endl;
				return;
			}
		}

		hashTable[hashVal].push_back(new Data(studentID, subject, score));
		cout << "key : (" << studentID << ", " << subject << "), val : " << score << " ����Ϸ�... (Hash Val : " << hashVal << ")" << endl;
	}
	void add(string name, string subject, int score) {
		int hashVal = hashFunction(name, subject);

		for (std::list<Data*>::iterator itr = hashTable[hashVal].begin(); itr != hashTable[hashVal].end(); itr++) {
			if ((*itr)->name == name && (*itr)->subject == subject) {
				cout << "�̹� (����, ����)�� ���� ���� ����Ǿ� �ֽ��ϴ�..." << endl;
				return;
			}
		}

		hashTable[hashVal].push_back(new Data(name, subject, score));
		cout << "key : (" << name << ", " << subject << "), val : " << score << " ����Ϸ�... (Hash Val : " << hashVal << ")" << endl;
	}
	void remove(int studentID, string subject) {
		int hashVal = hashFunction(studentID, subject);

		for (std::list<Data*>::iterator itr = hashTable[hashVal].begin(); itr != hashTable[hashVal].end(); itr++) {
			if ((*itr)->studentID == studentID && (*itr)->subject == subject) {
				hashTable[hashVal].erase(itr);
				cout << "(" << studentID << ", " << subject << ") �����Ϸ�..." << endl;
				return;
			}
		}

		cout << "(" << studentID << ", " << subject << ")�� ã�� �� ����..." << endl;
	}
	void remove(string name, string subject) {
		int hashVal = hashFunction(name, subject);

		for (std::list<Data*>::iterator itr = hashTable[hashVal].begin(); itr != hashTable[hashVal].end(); itr++) {
			if ((*itr)->name == name && (*itr)->subject == subject) {
				hashTable[hashVal].erase(itr);
				cout << "(" << name << ", " << subject << ") �����Ϸ�..." << endl;
				return;
			}
		}

		cout << "(" << name << ", " << subject << ")�� ã�� �� ����..." << endl;
	}
};

int main() {
	// [����] name �� subject�� �ݵ�� �������� �Է��� ��!

	Hash hash;

	/* add(key, value) �Լ� */
	hash.add("Kim", "Math", 26); // Key : (�̸�, �����), Value : ���� 
	hash.add(12, "Science", 60); // Key : (��ȣ, �����), Value : ����

	/* search(key) �Լ� */
	hash.search("Kim", "Math"); // Key : (�̸�, �����)
	hash.search(99, "Science"); // Key : (��ȣ, �����)

	/* remove(key) �Լ� */
	hash.remove("Jeong", "English");
	hash.remove(12, "Science");
}