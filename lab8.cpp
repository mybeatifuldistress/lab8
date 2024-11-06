#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <locale>
#include <iostream> 
#include <queue>

using namespace std;
queue <int> Q;

int k;
int size1, h;
int** arr1;
int* vis;

void print_vis();

void add_to_list_queue(int s);
void del_from_list();
struct Node* add_elem(int s);

struct Node* head = nullptr, * last = nullptr;

struct Node
{
	int n;			//Номер вершины (0..N-1)
	Node* next;
};

Node* LA;			//Массив структур - списков смежности [N]

Node* make_LA() {
	Node* la = new Node[size1];
	Node* p;

	for (int i = 0; i < size1; i++) {
		la[i].n = i;
		la[i].next = nullptr;
		p = &la[i];

		for (int j = 0; j < size1; j++) {
			if (arr1[i][j] == 1) {
				p->next = new Node;
				p = p->next;
				p->n = j;
				p->next = nullptr;
			}
		}
	}
	return la;
}

void print_LA() {
	Node* p;
	for (int i = 0; i < size1; i++) {
		p = &LA[i];
		while (p != nullptr) {
			cout << p->n << " > ";
			p = p->next;
		}
		cout << endl;
	}
}

void first_list(int l) {
	Node* p;
	p = &LA[l];

	vis[l] = 1;
	cout << l << ' ';
	Q.push(l);

	while (!Q.empty()) {
		l = Q.front();
		Q.pop();
		if (vis[l] == 1) {
			p = &LA[l];
		}
		while (p->next != nullptr) {
			if (vis[p->next->n] == 1) {
				p = p->next;
			}
			else {
				vis[p->next->n] = 1;
				p = p->next;

				l = p->n;
				Q.push(l);
				cout << l << ' ';
			}
		}
	}
}

void create_matrix() {
	for (int i = 0; i < size1; i++) {
		for (int j = i; j < size1; j++) {
			if (i == j) {
				arr1[i][j] = 0;
			}
			else {
				arr1[i][j] = rand() % 2;
				arr1[j][i] = arr1[i][j];
			}
		}
	}
}

void print_matrix() {
	cout << "     " << endl;
	for (int i = 0; i < size1; i++) {
		cout << i << ' ';
	}
	cout << endl;
	cout << "-----------------------------------------------------------\n";

	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size1; j++) {
			cout << arr1[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void print_vis() {
	cout << "\nМассив vis:\n";
	for (int i = 0; i < size1; i++) {
		cout << vis[i];
	}
	cout << "\n\n";
}

void BFS1(int s) {
	vis[s] = 1;
	cout << s << ' ';
	Q.push(s);
	while (!Q.empty()) {
		s = Q.front();
		Q.pop();
		for (int i = 0; i < size1; i++) {
			if ((arr1[s][i] == 1) && (vis[i] == 0)) {
				cout << i << ' ';
				vis[i] = 1;
				Q.push(i);
			}
		}
	}
}

void BFS2(int s) {
	vis[s] = 1;
	cout << s << ' ';
	add_to_list_queue(s);
	while (head != 0) {
		s = last->n;
		del_from_list();
		for (int i = 0; i < size1; i++) {
			if ((arr1[s][i] == 1) && (vis[i] == 0)) {
				cout << i << ' ';
				vis[i] = 1;
				add_to_list_queue(i);
			}
		}
	}
}

void clean_vis() {
	for (int i = 0; i < size1; i++) {
		vis[i] = 0;
	}
}

void add_to_list_queue(int s) {
	Node* p = nullptr;
	p = add_elem(s);
	if (head == nullptr) {
		head = p;
		last = p;
	}
	else {
		p->next = head;
		head = p;
	}
}

struct Node* add_elem(int s) {
	Node* p = nullptr;

	p = new Node;
	if (p == nullptr) {
		cout << "Ошибка при распределении памяти\n";
		exit(1);
	}

	p->n = s;

	p->next = nullptr;
	return p;
}

void del_from_list() {
	Node* struc = head;
	if (struc->next == nullptr) {
		delete struc;
		head = nullptr;
		last = nullptr;
		return;
	}
	while (struc) {
		if (struc->next == last) {
			delete struc->next;
			struc->next = nullptr;
			last = struc;
			break;
		}
		struc = struc->next;
	}
}

int main() {

	srand(time(nullptr));
	setlocale(LC_ALL, "");

	cout << "Задание 1\n";
	cout << "Введите размер матрицы смежности M1: ";
	cin >> size1;
	cout << endl;

	vis = new int[size1];

	arr1 = new int* [size1];
	for (int i = 0; i < size1; i++) {
		arr1[i] = new int[size1];
	}

	cout << "Матрица M1:\n";
	create_matrix();
	print_matrix();

	clean_vis();
	cout << "=======================================================================\n\n";
	cout << "Задание 2\n";
	cout << "Введите вершину от (0 до " << size1 - 1 << ") для начала обхода: ";
	cin >> h;

	int l = h;

	k = h;
	cout << endl;
	cout << "был в вершинах: ";

	clock_t start, end;
	double time;

	start = clock();
	BFS1(h);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << endl;
	cout << "Время работы стандартной queue: " << time << endl;

	clean_vis();

	cout << endl;

	cout << "=======================================================================\n\n";
	cout << "Задание 3\n";
	cout << "Список смежности S1:\n";
	LA = make_LA();
	print_LA();
	cout << endl;

	cout << "был в вершинах: ";
	first_list(l);
	cout << endl;

	cout << "=======================================================================\n\n";
	cout << "Задание 4\n";

	clean_vis();
	cout << "был в вершинах: ";

	int s = h;

	start = clock();
	BFS2(s);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << endl;
	cout << "Время работы нашей queue: " << time << endl;

	for (int i = 0; i < size1; ++i) delete[] arr1[i];
	delete[] arr1;
	delete[] vis;
	delete[] LA;

	return 0;
}