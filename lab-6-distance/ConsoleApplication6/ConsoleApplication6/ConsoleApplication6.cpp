#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <ctime>
#include <locale.h>
#include <queue>
#include <chrono>

using namespace std;

class Timer

{

private:

	using clock_t = std::chrono::high_resolution_clock;

	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:

	Timer() : m_beg(clock_t::now())

	{

	}

	void reset()

	{

		m_beg = clock_t::now();

	}

	double elapsed() const

	{

		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();

	}

};

typedef struct Node {
	int vertex;
	struct	Node* next;
} Node;

void add_Node_to_beginning(Node** head, int data) //функция добавления узла в начало
{
	Node* tmp_node = (Node*)malloc(sizeof(Node)); // создаем новый узел
	tmp_node->vertex = data;
	tmp_node->next = (*head); //присваиваем указателю tmp адрес след. узла
	(*head) = tmp_node; //Присваиваем указателю head адрес tmp
} //после выхода из функции tmp уничтожается

int delete_node(Node** head) { //удаляем узел на который указывает адрес
	Node* prev = NULL;
	int val;
	prev = (*head); //передаем во временную переменную prev адрес
	val = prev->vertex;
	(*head) = (*head)->next; //в head кладем адрес следующего узла
	free(prev); //очищаем временную переменную prev
	return val;
}


Node* findLastHead(Node* head) { //поиск адреса последнего элемента
	if (head == NULL) {
		return NULL;
	}
	while (head->next) {
		head = head->next;
	}
	return head;
}

void add_Node_to_end(Node* head, int data) { //функция добавления нового узла в конец
	Node* last = findLastHead(head); //получаем указатель на последний элемент списка
	Node* tmp_node = (Node*)malloc(sizeof(Node)); // создаем новый узел
	tmp_node->vertex = data;
	tmp_node->next = NULL;
	last->next = tmp_node; //записываем в последний элемент списка указатель на новый узел
}

void createLinkedList(int** mas, Node** head, int n) //создаем связный список
{
	for (int i = 0; i < n; i++)
	{
		add_Node_to_beginning(&head[i], i); //передаем адрес вершины и ее номер 
		for (int j = 0; j < n; j++)
		{
			if (mas[i][j] == 1)
			{
				add_Node_to_end(head[i], j); //добавляем к вершине связные с ней вершины
			}
		}
	}
}


void printLinkedList(const Node* head) {
	printf("\n");
	while (head) {
		printf("%d -->", head->vertex + 1);
		head = head->next;
	}
	printf("\n");
}

void BFS(int** mas, int* visited, int N, int v) //n-кол-во вершин, v- текущая вершина
{
	queue <int> queue;
	queue.push(v);
	visited[v] = 0;
	while (!queue.empty())
	{
		v = queue.front();
		queue.pop();
		for (int i = 0; i < N; i++)
		{
			if (mas[v][i] == 1 && visited[i] == -1)
			{
				queue.push(i);
				visited[i] = visited[v] + 1;
			}
		}
	}
}



void BFS_ForLinkedList(Node** head, int* visited, int v)
{
	Node** tmp_node = head;
	queue <int> queue;
	queue.push(tmp_node[v]->vertex);
	visited[tmp_node[v]->vertex] = 0;
	while (!queue.empty())
	{
		v = queue.front();
		queue.pop();
		while (tmp_node[v])
		{
			if (visited[tmp_node[v]->vertex] == -1)
			{
				queue.push(tmp_node[v]->vertex);
				visited[tmp_node[v]->vertex] = visited[v] + 1;
			}
			tmp_node[v] = tmp_node[v]->next;
		}
	}
}

void DFS(int** mas, int* visited, int N, int v, int distance)
{
	visited[v] = distance;
	for (int i = 0; i < N; i++)
	{
		if (mas[v][i] == 1 && visited[i] == -1)
		{
			DFS(mas, visited, N, i, distance + 1); //если для вершины есть путь вызываем функцию с distance+1
		}
		if (mas[v][i] == 1 && (visited[i] > distance + 1))//если для вершины есть более ближний путь, чем тот, который уже найдет, вызывается это условие
		{
			DFS(mas, visited, N, i, distance + 1);
		}
	}
}


void DFS_ForLinkedList(Node** head, int* visited, int v, int distance)
{
	visited[v] = distance;
	Node* tmp_node = head[v];
	while (tmp_node)
	{
		if (visited[tmp_node->vertex] == -1) {
			DFS_ForLinkedList(head, visited, tmp_node->vertex, distance + 1);
		}
		if (visited[tmp_node->vertex] > distance + 1){
			DFS_ForLinkedList(head, visited, tmp_node->vertex, distance + 1);
		}
		tmp_node = tmp_node->next;
	}
}

void main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	queue <int> queue;
	int** mas, N, num; //N-кол-во вершин, num-вершина для ввода
	time_t start, end;
	printf("Укажите размер матрицы N*N: ");
	scanf("%d", &N);
	Node** head = (Node**)malloc(N * sizeof(Node*));
	for (int i = 0; i < N; i++) {
		head[i] = NULL;
	}
	int* visited = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
	{
		visited[i] = -1;
	}

	mas = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
	{
		mas[i] = (int*)malloc(N * sizeof(int));
	}

	for (int i = 0; i < N; i++)
	{
		mas[i][i] = 0;

		for (int j = i + 1; j < N; j++)
		{

			mas[i][j] = rand() % 2;
			mas[j][i] = mas[i][j];


		}
	}

	printf("\n Вывод матрицы смежности\n ");

	printf("\n ");
	printf("\t");

	for (int i = 0; i < N; i++) {
		printf("%d", i + 1);
	}

	for (int i = 0; i < N; i++) { // вывод матриц смежности

		printf("\n");
		printf("%d\t", i + 1);

		for (int j = 0; j < N; j++) {
			printf("%d", mas[i][j]);
		}


	}

	printf("\n\nВведите вершину для начала обхода графа в глубину : ");
	scanf("%d", &num);
	num--;
	time(&start);
	Timer t;
	BFS(mas, visited, N, num);
	time(&end);
	printf("\nРасстояние от вершины %d до других вершин, найденное с помощью обхода в ширину на матрице смежности:\n", num + 1);

	for (int i = 0; i < N; i++)
	{
		printf("%d - %d\n", i+1, visited[i]);
	}

	printf("\nВремя на проход в ширину на матрице смежности %f\n", t.elapsed());

	for (int i = 0; i < N; i++)
		visited[i] = -1;

	createLinkedList(mas, head, N);
	Timer t1;
	BFS_ForLinkedList(head, visited, num);

	printf("\nРасстояние от вершины %d до других вершин, найденное с помощью обхода в ширину на списке смежности:\n", num + 1);
	for (int i = 0; i < N; i++)
	{
		printf("%d - %d\n", i + 1, visited[i]);
	}

	printf("\nВремя на проход в ширину на списке смежности %f\n", t1.elapsed());

	for (int i = 0; i < N; i++)
		visited[i] = -1;

	int distance = 0;
	Timer t2;
	DFS(mas, visited, N, num, distance);
	printf("\nРасстояние от вершины %d до других вершин, найденное с помощью обхода в глубину на матрице смежности:\n", num + 1);
	for (int i = 0; i < N; i++)
	{
		printf("%d - %d\n", i + 1, visited[i]);
	}

	printf("\nВремя на проход в глубину на матрице смежности %f\n", t2.elapsed());

	for (int i = 0; i < N; i++)
		head[i] = NULL;

	for (int i = 0; i < N; i++)
		visited[i] = -1;

	createLinkedList(mas, head, N);
	Timer t3;
	DFS_ForLinkedList(head, visited, num, distance);

	printf("\nРасстояние от вершины %d до других вершин, найденное с помощью обхода в глубину на списке смежности:\n", num + 1);
	for (int i = 0; i < N; i++)
	{
		printf("%d - %d\n", i + 1, visited[i]);
	}
	printf("\nВремя на проход в глубину на списке смежности %f\n", t3.elapsed());
	_getch();
}
