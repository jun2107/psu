#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <locale.h>
#include <queue>
#include <ctime>
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

void createLinkedList(int** mas, Node** head, int N) //создаем связный список
{
	for (int i = 0; i < N; i++)
	{
		add_Node_to_beginning(&head[i], i); //передаем адрес вершины и ее номер 
		for (int j = 0; j < N; j++)
		{
			if (mas[i][j] == 1)
			{
				add_Node_to_end(head[i], j); //добавляем к вершине связные с ней вершины
			}
		}
	}
}


void printLinkedList(Node* head) {
	printf("\n");
	while (head) {
		printf("%d -->", head->vertex + 1);
		head = head->next;
	}
	printf("\n");
}

void BFS(int** mas, bool* visited, int N, int v) //N - всего вершин, v - вершина, с которой начинаем обход
{
	queue<int> queue;
	queue.push(v);
	visited[v] = true;
	while (!queue.empty())
	{
		v = queue.front();
		queue.pop();
		printf("%d ", v + 1);
		for (int i = 0; i < N; i++)
		{
			if (mas[v][i] == 1 && visited[i] == false)
			{
				queue.push(i);
				visited[i] = true;
			}
		}
	}
}


void BFS_ForLinkedList(Node** head, bool* visited, int v)
{
	Node** tmp_node = head; //передаем адрес, хранящий адреса узлов
	queue <int> queue;
	queue.push(tmp_node[v]->vertex);
	visited[tmp_node[v]->vertex] = true;
	while (!queue.empty())
	{
		v = queue.front();
		queue.pop();
		printf("%d ", v + 1);
		while (tmp_node[v])
		{
			if (visited[tmp_node[v]->vertex] == false)
			{
				queue.push(tmp_node[v]->vertex);
				visited[tmp_node[v]->vertex] = true;
			}
			tmp_node[v] = tmp_node[v]->next; //переход к следующему узлу в списке
		}
	}
}

void BFS_linkedlist_as_queue(int** mas, bool* visited, int v, int N)
{
	Node* head = NULL;
	add_Node_to_beginning(&head, v); //добавляем узел с данной вершиной в начало
	visited[v] = true;
	while (head) //пока есть хоть одно значение
	{
		v = delete_node(&head); //удаляем вершину (по принципу очереди)
		printf("%d ", v + 1);
		for (int i = 0; i < N; i++)
		{
			if (mas[v][i] == 1 && visited[i] == false)
			{
				if (head == NULL)
				{
					add_Node_to_beginning(&head, i); //если нет "головы" добавляем смежную вершину как голову
				}
				else
				{
					add_Node_to_end(head, i); //иначе связываем с ней следующую смежную вершину
				}
				visited[i] = true;
			}
		}
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
	bool* visited = (bool*)malloc(N * sizeof(bool));
	for (int i = 0; i < N; i++)
	{
		visited[i] = false;
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
	printf("\nВывод матрицы смежности\n ");
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
	printf("\nПроход в ширину по матрице смежности : ");
	time(&start);
	Timer t;
	BFS(mas, visited, N, num);
	time(&end);
	printf("\n\nВремя на проход в ширину %f\n", t.elapsed());
	for (int i = 0; i < N; i++)
		visited[i] = false;
	createLinkedList(mas, head, N);
	printf("\nСоздадим список смежности: ");
	for (int i = 0; i < N; i++)
		printLinkedList(head[i]);
	printf("\nПроход в ширину по списку смежности : ");
	Timer t1;
	BFS_ForLinkedList(head, visited, num);
	printf("\n\nВремя на проход по списку смежности %f\n", t1.elapsed());
	for (int i = 0; i < N; i++)
		visited[i] = false;
	printf("\nПроход в ширину по матрице смежности c использованием очереди, построенной на списке смежности: ");
	Timer t2;
	BFS_linkedlist_as_queue(mas, visited, num, N);
	printf("\n\nВремя на проход по матрице смежности с использованием очереди, построенной на списке смежносит %f\n", t2.elapsed());
	printf("\n\n");
	_getch();
}
