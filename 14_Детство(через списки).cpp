#include <fstream>
#include <iostream>
using namespace std;

struct el {
	int s;
	el* next;
};

void del(el** G, int x, int y) {
	if (G[x]->s == y) {
		el* p = G[x];
		G[x] = G[x]->next;
		delete p;
		return;
	}

	for (el* p = G[x];p != nullptr;p = p->next) {
		if (p->next->s == y) {
			el * d = p->next;
			p->next = p->next->next;
			delete d;
			return;
		}
	}
}

void eiler(el** G, int n, int start) {
	el* S = nullptr;
	el* C = nullptr;

	el* p0 = new el;
	p0->s = start;
	p0->next = S;
	S = p0;

	while (S != nullptr) {
		int x = S->s;
		if (G[x] == nullptr) {
			el* p = S;
			S = S->next;
			p->next = C;
			C = p;
		}
		else {
			int y = G[x]->s;
			el* p = new el;
			p->s = y;
			p->next = S;
			S = p;

			del(G, x, y);
			del(G, y, x);
		}
	}

	cout << "Путь:" << endl;
	for (el* p = C;p != nullptr;p = p->next) {
		cout << p->s << " ";
	}
	cout << endl;
}

int main(){
	setlocale(LC_ALL, "ru");
	ifstream fin("in_envelope.txt");
	/*
	in_cycle.txt
	in_envelope.txt
	in_star.txt
	in_way.txt
	in_error.txt
	*/
	if (!fin) return -1;

	int n;
	fin >> n;
	el** G = new el * [n];
	for (int i = 0;i < n;i++)G[i] = nullptr;

	while (!fin.eof()) {
		int a, b;
		fin >> a >> b;

		el* pa = new el;
		pa->s = b;
		pa->next = G[a];
		G[a] = pa;

		el* pb = new el;
		pb->s = a;
		pb->next = G[b];
		G[b] = pb;
	}

	int q = 0, start;
	for (int i = 0;i < n;i++) {
		int k = 0;
		for (el* p = G[i];p != nullptr;p = p->next)k++;
		if (k % 2 == 1) {
			q++;
			start = i;
		}
	}

	if (q == 0) {
		cout << "Можно нарисовать эту фигуру, начиная и заканчивая рисование в одной и той же точке." << endl;
		eiler(G, n, 0);
	}
	else if (q == 2) {
		cout << "Можно нарисовать эту фигуру, начиная и заканчивая рисование в различных точках." << endl;
		eiler(G, n, start);
	}
	else {
		cout << "Нельзя нарисовать эту фигуру(без наложения линий), не отрывая карандаша от бумаги." << endl;
		return 0;
	}
}