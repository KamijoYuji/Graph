#include<iostream>
#include<vector>
using namespace std;

#define Mv vector<bool>
#define MMv vector<Mv>
#define Lv vector<int>
#define LLv vector<Lv>

void printGraph(MMv& g) {
	int n = g.size();
	if (!n)
		cout << "EMPTY\n";

	cout << "\t";
	for (int i = 1; i <= n; i++)
		cout << "\t" << "v" << i;
	cout << "\n";

	for (int i = 0; i < n; i++)
	{
		cout << "\t" << "v" << i + 1;
		for (int j = 0; j < n; j++)
			cout << "\t" << g[i][j];
		cout << "\n";
	}
}

void printGraph(LLv& g) {
	int n = g.size();
		if (!n)
			cout << "EMPTY\n";
		
		for (int i = 0; i < n; i++)
		{
			int s = g[i].size();
			cout << "(v" << i+1 << ",(";
			for (int j = 0; j < s; j++)
				cout <<"v" << g[i][j] + 1 << ((j + 1 == s) ? "" : ", ");
			cout << "))" << ((i + 1 == n) ? "" : ", ");
		}
		cout << "\n";
}


void setGraph(MMv& g, int n) { //реализован только для матрицы
	g.clear();

	for (int i = 0; i < n; i++)
	{
		g.push_back(Mv());
		for (int j = 0; j < n; j++) {
			bool a;
			cin >> a;
			g[i].push_back(a);
		}
	}
}

LLv reverse(MMv& g) {
	int n = g.size();
	LLv b;

	for (int i = 0; i < n; i++)
	{
		b.push_back(Lv());
		for (int j = 0; j < n; j++)
			if (g[i][j])
				b[i].push_back(j);
	}
	return b;
}

MMv reverse(LLv& g) {
	int n = g.size();
	MMv b;

	for (int i = 0; i < n; i++)
	{
		b.push_back(Mv(n,0));
		for (int j = 0; j < n; j++)
		{
			int lenG = g[i].size();
			for (int k = 0; k < lenG; k++) {
				if (j == g[i][k]) 
					b[i][j] = 1;
			}
		}
	}
	return b;
}

int main() {
	MMv g;
	setGraph(g, 5);
	LLv r = reverse(g);
	printGraph(r);
	g = reverse(r);
	printGraph(g);
	return 0;
}
