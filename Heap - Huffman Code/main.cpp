#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int frequency[128]; // 빈도수 저장 배열 (ASCII Code 범위 : 0~127)

char code[128][50]; // 각 문자에 해당하는 코드 저장
char character[128]; // code[]와 대응되는 문자 배열
int index = 0;

/* 교재(p.351)소스 - START */
#define MAX_ELEMENT 200

typedef struct TreeNode {
	int weight; // 빈도수
	char ch;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

typedef struct {
	TreeNode* ptree;
	char ch;
	int key;
} element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

// 생성 함수
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}
// 초기화 함수
void init(HeapType* h)
{
	h->heap_size = 0;
}
// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
// 삽입 함수
void insert_min_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // 새로운 노드를 삽입
}
// 삭제 함수
element delete_min_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드중 더 작은 자식노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key < h->heap[child].key) break;
		// 한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// 이진 트리 생성 함수
TreeNode* make_tree(TreeNode* left,
	TreeNode* right)
{
	TreeNode* node =
		(TreeNode*)malloc(sizeof(TreeNode));
	node->left = left;
	node->right = right;
	return node;
}
// 이진 트리 제거 함수
void destroy_tree(TreeNode* root)
{
	if (root == NULL) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

int is_leaf(TreeNode* root)
{
	return !(root->left) && !(root->right);
}
void print_array(int codes[], int n)
{
	for (int i = 0; i < n; i++) {
		if (codes[i] == 0)
			code[index][i] = '0';
		if (codes[i] == 1)
			code[index][i] = '1';
	}
	code[index][n] = '\0';
}

void print_codes(TreeNode* root, int codes[], int top)
{
	// 1을 저장하고 순환호출한다. 
	if (root->left) {
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
	}

	// 0을 저장하고 순환호출한다. 
	if (root->right) {
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}

	// 단말노드이면 코드를 출력한다. 
	if (is_leaf(root)) {
		character[index] = root->ch;
		print_array(codes, top);
		index++;
	}
}

// 허프만 코드 생성 함수
TreeNode* huffman_tree(int freq[], int n)
{
	int i;
	TreeNode* node, * x;
	HeapType* heap;
	element e, e1, e2;
	int codes[100];
	int top = 0;

	heap = create();
	init(heap);
	for (i = 0; i < n; i++) {
		node = make_tree(NULL, NULL);
		e.ch = node->ch = (char)i;
		e.key = node->weight = freq[i];
		e.ptree = node;
		insert_min_heap(heap, e);
	}
	for (i = 1; i < n; i++) {
		// 최소값을 가지는 두개의 노드를 삭제
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		// 두개의 노드를 합친다.
		x = make_tree(e1.ptree, e2.ptree);
		e.key = x->weight = e1.key + e2.key;
		e.ptree = x;
		insert_min_heap(heap, e);
	}
	e = delete_min_heap(heap); // 최종 트리
	print_codes(e.ptree, codes, top);
	free(heap);
	return e.ptree;
}
/* 교재(p.351)소스 - END */

TreeNode* encode(string source, string save) {
	string line;
	string output = "";
	int length = 0;

	cout << "--- ENCODE ---" << endl;
	cout << "[ " << source << " >> " << save << " ]" << endl << endl;

	/* 파일 읽기 */
	ifstream in(source);
	if (in.fail()) {
		cout << "File Open Error!" << endl;
		return NULL;
	}

	while (!in.eof()) {
		getline(in, line);
		// line.length() : 문장의 길이
		// line[i] : 문장의 i번째 문자

		// 이곳에서 각 문자의 빈도수를 저장할 것
		for (int i = 0; i < line.length(); i++) {
			cout << line[i];
			frequency[line[i]]++; // 빈도수 저장
			length++;
		}
		cout << endl;
	}
	cout << endl << "File read complete... (No. of Characters : " << length << ")" << endl << endl;
	in.close();

	/* 허프만 코드 생성 */
	TreeNode* root = huffman_tree(frequency, 128);

	/* 허프만 코드 변환 */
	in.open(source);
	if (in.fail()) {
		cout << "File Open Error!" << endl;
		return NULL;
	}

	while (!in.eof()) {
		getline(in, line);
		for (int i = 0; i < line.length(); i++) {
			for (int j = 0; j < 128; j++) {
				if (line[i] == character[j])
					output += code[j];
			}
		}
	}
	in.close();

	cout << output << endl;
	cout << endl << "Decode complete..." << endl << endl;

	/* 파일 쓰기 */
	ofstream out(save);

	if (out.fail()) {
		cout << "File Open Error!" << endl;
		return NULL;
	}

	out << output; // output는 encode() 함수의 실행 결과이다. 
	out.close();

	return root;
}

void decode(string source, TreeNode* root) {
	TreeNode* temp = root;
	string line;

	cout << "--- DECODE ---" << endl;
	cout << "[ " << source << " ]" << endl << endl;

	/* 파일 읽기 */
	ifstream in(source);
	if (in.fail()) {
		cout << "File Open Error!" << endl;
		return;
	}

	while (!in.eof()) {
		getline(in, line);
		// line.length() : 문장의 길이
		// line[i] : 문장의 i번째 문자

		for (int i = 0; i < line.length(); i++) {
			if (line[i] == '0') {
				temp = temp->right;
				if ((temp->left == NULL) && (temp->right == NULL)) {
					cout << temp->ch;
					temp = root;
				}
			}
			if (line[i] == '1') {
				temp = temp->left;
				if ((temp->left == NULL) && (temp->right == NULL)) {
					cout << temp->ch;
					temp = root;
				}
			}
		}
		cout << endl;
	}
	cout << endl << "Encode complete..." << endl;
	in.close();
}

int main() {
	TreeNode* root = encode("ds.txt", "ds_zipped.txt");
	decode("ds_zipped.txt", root);
	destroy_tree(root);
}