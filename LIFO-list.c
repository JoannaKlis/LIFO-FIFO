//kolejka lista
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

typedef struct // Struktura przechowuj¹ca informacje o studencie
{
	char imie[50];
	char nazwisko[50];
	int rok_urodzenia;
} Student;

typedef struct Node // Struktura elementu kolejki
{
	Student data;
	struct Node* next;
} Node;

typedef struct 
{
	Node* front;
	Node* rear;
} Queue;

void initializeQueue(Queue* queue) 
{
	queue->front = NULL;
	queue->rear = NULL;
}

int isEmpty(Queue* queue) 
{
	return (queue->front == NULL);
}

void enqueue(Queue* queue, const Student* student) 
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) 
	{
		printf("Blad alokacji pamieci.\n");
		return;
	}
	newNode->data = *student;
	newNode->next = NULL;
	if (isEmpty(queue)) 
	{
		queue->front = newNode;
		queue->rear = newNode;
	}
	else 
	{
		queue->rear->next = newNode;
		queue->rear = newNode;
	}
}

void dequeueAndDisplay(Queue* queue) 
{
	if (isEmpty(queue))
	{
		printf("Kolejka jest pusta.\n");
		return;
	}
	Node* temp = queue->front;
	printf("Pobrano i wyœwietlono element z kolejki: %s %s, Rok urodzenia: %d\n",
		temp->data.imie, temp->data.nazwisko, temp->data.rok_urodzenia);

	queue->front = queue->front->next;
	free(temp);
}

void display(Queue* queue) 
{
	if (isEmpty(queue)) 
	{
		printf("Kolejka jest pusta.\n");
		return;
	}
	Node* current = queue->front;
	printf("Zawartosc kolejki:\n");
	while (current != NULL) {
		printf("Imie: %s, Nazwisko: %s, Rok urodzenia: %d\n",
			current->data.imie, current->data.nazwisko, current->data.rok_urodzenia);
		current = current->next;
	}
}

int countElements(Queue* queue) 
{
	int count = 0;
	Node* current = queue->front;
	while (current != NULL) 
	{
		count++;
		current = current->next;
	}
	return count;
}

Student* searchElement(Queue* queue, const char* nazwisko)
{
	Node* current = queue->front;
	while (current != NULL)
	{
		if (strcmp(current->data.nazwisko, nazwisko) == 0)
		{
			return &current->data;
		}
		current = current->next;
	}
	return NULL;
}

void deleteQueue(Queue* queue) 
{
	Node* current = queue->front;
	Node* temp;
	while (current != NULL) 
	{
		temp = current;
		current = current->next;
		free(temp);
	}
	queue->front = NULL;
	queue->rear = NULL;
	printf("Struktura zostala usunieta.\n");
}

int main() 
{
	Queue queue;
	initializeQueue(&queue);

	int choice;
	Student student;
	char nazwisko[50];

	while (1)
	{
		printf("\n!kolejka-lista! Menu:\n");
		printf("1. Dodaj element do kolejki.\n");
		printf("2. Pobierz i wyswietl element z kolejki.\n");
		printf("3. Wyswietl zawartosc kolejki.\n");
		printf("4. Znajdz studenta po nazwisku.\n");
		printf("5. Sprawdz liczbe elementow w strukturze.\n");
		printf("6. Usun cala strukture.\n");
		printf("7. Zakoncz program.\n");
		printf("Wybierz opcje: ");
		
		if (scanf("%d", &choice) != 1)
		{
			printf("Blad. Podano niepoprawna opcje.\n");
			while (getchar() != '\n');
			continue;
		}

		switch (choice) 
		{
		case 1:
			printf("Wpisz dane studenta (imie, nazwisko, rok urodzenia): ");
			scanf("%s %s %d", student.imie, student.nazwisko, &student.rok_urodzenia);
			enqueue(&queue, &student);
			break;
		case 2:
			dequeueAndDisplay(&queue);
			break;
		case 3:
			display(&queue);
			break;
		case 4:
			printf("Wpisz nazwisko studenta do wyszukania: ");
			scanf("%s", nazwisko);
			Student* foundStudent = searchElement(&queue, nazwisko);
			if (foundStudent != NULL) {
				printf("Znaleziono studenta: %s %s, Rok urodzenia: %d\n",
					foundStudent->imie, foundStudent->nazwisko, foundStudent->rok_urodzenia);
			}
			else 
			{
				printf("Nie znaleziono studenta o podanym nazwisku.\n");
			}
			break;
		case 5:
			printf("Liczba elementow w strukturze: %d\n", countElements(&queue));
			break;
		case 6:
			deleteQueue(&queue);
			break;
		case 7:
			printf("Zakonczono program.\n");
			exit(0);
		default:
			printf("Niepoprawny wybor. Sprobuj ponownie.\n");
			break;
		}
	}
	return 0;
}
