#include<iostream>
#include<vector>
using namespace std;

#define Mv vector<bool> //элемент матрицы смежности
#define MMv vector<Mv>  //матрица смежности
#define Lv vector<int>  //элемент списка смежности
#define LLv vector<Lv>  //список смежности

/*
* матрица смежности в программе устроена обычным образом:
* i-ые индексы отвечают за вершины графов (i - номер самой вершины в графе), откуда выходит ребро
* j-ые индексы отвечают за вершины графов (j - номер самой вершины в графе), куда ведёт ребро
* ij-ый элемент имеет значение 1, если из i-ая вершина соединена ребром с j-ой вершиной, 0 - если нет
* _____________________________________________________________________________________________________
* список смежности в программе устроен следующим образом:
* i-ые индексы отвечают за вершины графов (i - номер самой вершины в графе), откуда выходит ребро
* j-ые индексы отвечают за вершины графов, куда ведёт ребро, но иным образом (ниже будет сказано)
* ij-ый элемент содержит в себе номер вершины, для которой из i-ой вершины есть ребро
*/

//вывод матрицы смежности (с оформлением)
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

//вывод списка смежности (с оформлением)
void printGraph(LLv& g) {
    int n = g.size();
    if (!n)
        cout << "EMPTY\n";

    for (int i = 0; i < n; i++)
    {
        int s = g[i].size();
        cout << "(v" << i + 1 << ",(";
        for (int j = 0; j < s; j++)
            cout << "v" << g[i][j] + 1 << ((j + 1 == s) ? "" : ", ");
        cout << "))" << ((i + 1 == n) ? "" : ", ");
    }
    cout << "\n";
}

//задание графа в виде матрицы смежности (аругменты: сама матрица, которую нужно задать, и кол-во вершин)
void setGraph(MMv& g, int n) {
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

//создание списка смежности по матрице смежности
LLv reverse(MMv& g) {
    int n = g.size(); //узнаём кол-во вершин в графе
    LLv b; //создаём пустой список смежности b

    for (int i = 0; i < n; i++) //для всех вершин
    {
        b.push_back(Lv()); //кладём в список смежности b элементы списка смежности (вектора вершин, для котого из i-ой вершины есть ребро)
        for (int j = 0; j < n; j++)
            if (g[i][j])
                b[i].push_back(j); //если из i-ой вершины в j-ую есть ребро, то номер j-ой вершины (в матрице это и есть j) кладём в i-ый элемент списка смежности b
    }
    return b;
}

//создание матрицы смежности по списку смежности
MMv reverse(LLv& g) {
    int n = g.size(); //узнаём кол-во вершин в графе
    MMv b; //создаём пустую матрицу смежности b

    for (int i = 0; i < n; i++) //для всех вершин (из)
    {
        b.push_back(Mv(n, 0)); //кладём в матрицу смежности b элементы матрицы смежности (булевы вектора с нулями)
        for (int j = 0; j < n; j++) //для всех вершин (в)
        {
            int lenG = g[i].size(); //узнаём количество вершин, для которых есть ребро из i-ой вершины
            for (int k = 0; k < lenG; k++) { //для всех таких вершин
                if (j == g[i][k])
                    b[i][j] = 1; //если j равен вершине в списке смежности (при том, что вершина эта имеет ребро из вершины i), то в матрице смежности ij-ый элемент будет равен 1
            }
        }
    }
    return b;
}

int main() {
    MMv g; //создаём матрицу смежности g
    cout<<"SET THE MATRIX: ";
    setGraph(g, 5); //заполняем матрицу смежности g вручную (5 вершин)
/*
* нужно ставить в заполнении только 1 и 0
* Названия вершин не будет высвечиваться, писать самостоятельно тоже не стоит их
* Можете заполнить, например, следующий граф:
*   v1 v2 v3 v4 v5
* v1 0  1  0  0  1
* v2 0  0  0  1  0
* v3 0  1  0  0  0
* v4 1  0  1  0  0
* v5 0  0  1  1  0
* Записать в консоль нужно так:
* 0 1 0 0 1
* 0 0 0 1 0
* 0 1 0 0 0
* 1 0 1 0 0
* 0 0 1 1 0
Или так: 0 1 0 0 1 0 0 0 1 0 0 1 0 0 0 1 0 1 0 0 0 0 1 1 0
*/
    LLv r = reverse(g); //создаём список смежности r по матрице смежности g
    cout<<"\nADJACENCY LIST:\n";
    printGraph(r); //выводим спискок смежности
    g = reverse(r); //матрица смежности g будет иметь вид матрицы, построенной по списку смежности r (т.е. g не изменится, нужно для проверки функции reverse)
    cout<<"\nADJACENCY MATRIX:\n";
    printGraph(g); //выводим матрицу смежности
    return 0;
}
