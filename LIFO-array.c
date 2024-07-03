//kolejka talibca
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)
#define MAX_SIZE 100

typedef struct // Struktura przechowuj¹ca informacje o studencie
{
	char imie[50];
	char nazwisko[50];
	int rok_urodzenia;
} Student;

typedef struct // Struktura kolejki
{
	Student data[MAX_SIZE];
	int front;
	int rear;
} Queue;

void initializeQueue(Queue* queue)
{
	queue->front = 0;
	queue->rear = -1;
}

int isEmpty(Queue* queue)
{
	return (queue->rear < queue->front);
}

int isFull(Queue* queue)
{
	return (queue->rear == MAX_SIZE - 1);
}

void enqueue(Queue* queue, const Student* student)
{
	if (isFull(queue))
	{
		printf("Kolejka jest pelna. Nie mozna dodac wiecej elementow.\n");
		return;
	}
	queue->rear++;
	queue->data[queue->rear] = *student;
}

void dequeueAndDisplay(Queue* queue)
{
	if (isEmpty(queue))
	{
		printf("Kolejka jest pusta.\n");
		return;
	}
	printf("Pobrano i wyswietlono element z kolejki: %s %s, Rok urodzenia: %d\n",
		queue->data[queue->front].imie, queue->data[queue->front].nazwisko, queue->data[queue->front].rok_urodzenia);
	queue->front++;
}

void display(Queue* queue)
{
	if (isEmpty(queue))
	{
		printf("Kolejka jest pusta.\n");
		return;
	}
	printf("Zawartosc kolejki:\n");
	for (int i = queue->front; i <= queue->rear; i++)
	{
		printf("Imie: %s, Nazwisko: %s, Rok urodzenia: %d\n",
			queue->data[i].imie, queue->data[i].nazwisko, queue->data[i].rok_urodzenia);
	}
}

int countElements(Queue* queue)
{
	return (queue->rear - queue->front + 1);
}

Student* searchElement(Queue* queue, const char* nazwisko)
{
	for (int i = queue->front; i <= queue->rear; i++)
	{
		if (strcmp(queue->data[i].nazwisko, nazwisko) == 0)
		{
			return &queue->data[i];
		}
	}
	return NULL;
}

void deleteQueue(Queue* queue)
{
	initializeQueue(queue);
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
		printf("\n!kolejka-tablica! Menu:\n");
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
			else {
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