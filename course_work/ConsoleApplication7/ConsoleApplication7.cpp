#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <set>
#include <map>
#include <vector>
#include <fstream>
using namespace std;

set<set<int> > independentSets;

int** edges;
vector<int> vertices;

void printAllIndependentSets()
{
    fstream inOut;
    inOut.open("file.txt", ios::out);
    printf("\n");
    cout << "Все независимые множества вершин в графе: ";
    inOut << "Все независимые множества вершин в графе: " << endl;
    for (auto iter : independentSets) {
        printf("\n");
        cout << "{ ";
        inOut << "{ ";
        for (auto iter2 : iter) {
            cout << iter2 + 1 << " ";
            inOut << iter2 + 1 << " ";
        }
        cout << "}";
        inOut << "} " << endl;
    }
    inOut.close();
    cout << endl;
    independentSets.clear();
}


bool isSafeForIndependentSet(int vertex, set<int> tempSolutionSet)
{
    for (auto iter : tempSolutionSet) {
        if (edges[iter][vertex] == 1) {
            return false;
        }
    }
    return true;

}


void findAllIndependentSets(int currV, int setSize, set<int> tempSolutionSet)
{
    for (int i = currV; i <= setSize; i++) {
        if (isSafeForIndependentSet(vertices[i - 1], tempSolutionSet))
        {
            tempSolutionSet.insert(vertices[i - 1]);
            findAllIndependentSets(i + 1, setSize, tempSolutionSet);
            tempSolutionSet.erase(vertices[i - 1]);
        }
    }
    independentSets.insert(tempSolutionSet);
}


void MakeaArray(int k)
{
    setlocale(LC_ALL, "RUS");
    int V;
    if (k == 1) {
        V = rand() % 9;
    }
    else {
        while (true)
        {
            printf("\nУкажите размер матрицы V*V (не более 9): ");
            scanf_s("%d", &V);
            if ((V<10) && (V>0)) {
                break;
            }
            else {
                printf("Error enter again!!!");
            }
        }

    }

    for (int i = 0; i < V; i++)
        vertices.push_back(i);

    edges = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++)
    {
        edges[i] = (int*)malloc(V * sizeof(int));
    }
    for (int i = 0; i < V; i++)
    {
        edges[i][i] = 0;
        for (int j = i + 1; j < V; j++)
        {
            edges[i][j] = rand() % 2;
            edges[j][i] = edges[i][j];
        }
    }
    for (int i = 0; i < V; i++) { // вывод матриц смежности

        printf("\n");

        for (int j = 0; j < V; j++) {
            printf("%d", edges[i][j]);
        }
    }

    set<int> tempSolutionSet;

    findAllIndependentSets(1, V, tempSolutionSet);

    printAllIndependentSets();

    _getch();
}

int Menu(void)
{
	system("CLS");
	int c = 0;
	setlocale(LC_ALL, "Rus");
	while (c < '0' || c > '2')
	{
		printf(
			"::====================================================::\n"
			"|| 1 : Задать размер матрицы автоматически            ||\n"
            "|| 2 : Задать размер матрицы вручную.                 ||\n"
			"|| 0 : Выход                                          ||\n"
			"::====================================================::\n"
			"> ");
		c = _getch();
		system("cls");
	}
	return c;
}

void main(void)
{
	int Select;
	while ((Select = Menu()) != '0' && Select != 27)
		switch (Select)
		{
		case '1':
			MakeaArray(1);
			break;
        case '2':
            MakeaArray(2);
            break;
		}
}