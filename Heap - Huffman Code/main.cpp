#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int frequency[128]; // �󵵼� ���� �迭 (ASCII Code ���� : 0~127)

char code[128][50]; // �� ���ڿ� �ش��ϴ� �ڵ� ����
char character[128]; // code[]�� �����Ǵ� ���� �迭
int index = 0;

/* ����(p.351)�ҽ� - START */
#define MAX_ELEMENT 200

typedef struct TreeNode {
	int weight; // �󵵼�
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

// ���� �Լ�
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}
// �ʱ�ȭ �Լ�
void init(HeapType* h)
{
	h->heap_size = 0;
}
// ���� ����� ������ heap_size�� ���� h�� item�� �����Ѵ�.
// ���� �Լ�
void insert_min_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	//  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // ���ο� ��带 ����
}
// ���� �Լ�
element delete_min_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ���� �� ���� �ڽĳ�带 ã�´�.
		if ((child < h->heap_size) &&
			(h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key < h->heap[child].key) break;
		// �� �ܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// ���� Ʈ�� ���� �Լ�
TreeNode* make_tree(TreeNode* left,
	TreeNode* right)
{
	TreeNode* node =
		(TreeNode*)malloc(sizeof(TreeNode));
	node->left = left;
	node->right = right;
	return node;
}
// ���� Ʈ�� ���� �Լ�
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
	// 1�� �����ϰ� ��ȯȣ���Ѵ�. 
	if (root->left) {
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
	}

	// 0�� �����ϰ� ��ȯȣ���Ѵ�. 
	if (root->right) {
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}

	// �ܸ�����̸� �ڵ带 ����Ѵ�. 
	if (is_leaf(root)) {
		character[index] = root->ch;
		print_array(codes, top);
		index++;
	}
}

// ������ �ڵ� ���� �Լ�
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
		// �ּҰ��� ������ �ΰ��� ��带 ����
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		// �ΰ��� ��带 ��ģ��.
		x = make_tree(e1.ptree, e2.ptree);
		e.key = x->weight = e1.key + e2.key;
		e.ptree = x;
		insert_min_heap(heap, e);
	}
	e = delete_min_heap(heap); // ���� Ʈ��
	print_codes(e.ptree, codes, top);
	free(heap);
	return e.ptree;
}
/* ����(p.351)�ҽ� - END */

TreeNode* encode(string source, string save) {
	string line;
	string output = "";
	int length = 0;

	cout << "--- ENCODE ---" << endl;
	cout << "[ " << source << " >> " << save << " ]" << endl << endl;

	/* ���� �б� */
	ifstream in(source);
	if (in.fail()) {
		cout << "File Open Error!" << endl;
		return NULL;
	}

	while (!in.eof()) {
		getline(in, line);
		// line.length() : ������ ����
		// line[i] : ������ i��° ����

		// �̰����� �� ������ �󵵼��� ������ ��
		for (int i = 0; i < line.length(); i++) {
			cout << line[i];
			frequency[line[i]]++; // �󵵼� ����
			length++;
		}
		cout << endl;
	}
	cout << endl << "File read complete... (No. of Characters : " << length << ")" << endl << endl;
	in.close();

	/* ������ �ڵ� ���� */
	TreeNode* root = huffman_tree(frequency, 128);

	/* ������ �ڵ� ��ȯ */
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

	/* ���� ���� */
	ofstream out(save);

	if (out.fail()) {
		cout << "File Open Error!" << endl;
		return NULL;
	}

	out << output; // output�� encode() �Լ��� ���� ����̴�. 
	out.close();

	return root;
}

void decode(string source, TreeNode* root) {
	TreeNode* temp = root;
	string line;

	cout << "--- DECODE ---" << endl;
	cout << "[ " << source << " ]" << endl << endl;

	/* ���� �б� */
	ifstream in(source);
	if (in.fail()) {
		cout << "File Open Error!" << endl;
		return;
	}

	while (!in.eof()) {
		getline(in, line);
		// line.length() : ������ ����
		// line[i] : ������ i��° ����

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