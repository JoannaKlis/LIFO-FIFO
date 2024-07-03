//stos tablica
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

typedef struct // Struktura stosu
{
	Student data[MAX_SIZE];
	int top;
} Stack;

void initializeStack(Stack* stack)
{
	stack->top = -1;
}

int isFull(Stack* stack)
{
	return (stack->top == MAX_SIZE - 1);
}

int isEmpty(Stack* stack)
{
	return (stack->top == -1);
}

void push(Stack* stack, const Student* student)
{
	if (isFull(stack)) 
	{
		printf("Stos jest pelny. Nie mozna dodac wiecej elementow.\n");
		return;
	}
	stack->top++;
	stack->data[stack->top] = *student;
}

Student pop(Stack* stack) 
{
	Student emptyStudent = { .imie = "", .nazwisko = "", .rok_urodzenia = 0 };
	if (isEmpty(stack)) 
	{
		printf("Stos jest pusty. Brak elementow do zdjecia.\n");
		return emptyStudent;
	}
	Student popped = stack->data[stack->top];
	stack->top--;
	return popped;
}

void display(Stack* stack) 
{
	if (isEmpty(stack)) 
	{
		printf("Stos jest pusty.\n");
		return;
	}
	printf("Zawartoœæ stosu:\n");
	for (int i = stack->top; i >= 0; i--) 
	{
		printf("Imiê: %s, Nazwisko: %s, Rok urodzenia: %d\n",
			stack->data[i].imie, stack->data[i].nazwisko, stack->data[i].rok_urodzenia);
	}
}

int countElements(Stack* stack) 
{
	return stack->top + 1;
}

Student* searchElement(Stack* stack, const char* nazwisko)
{
	for (int i = stack->top; i >= 0; i--) 
	{
		if (strcmp(stack->data[i].nazwisko, nazwisko) == 0)
		{
			return &stack->data[i];
		}
	}
	return NULL;
}

void deleteStack(Stack* stack) 
{
	stack->top = -1;
	printf("Struktura zostala usunieta.\n");
}

int main() 
{
	Stack stack;
	initializeStack(&stack);

	int choice;
	Student student;
	char nazwisko[50];

	while (1)
	{
		printf("\n!stos-tablica! Menu:\n");
		printf("1. Dodaj element na stosie.\n");
		printf("2. Zdejmij element ze stosu.\n");
		printf("3. Wyswietl zawartosc stosu.\n");
		printf("4. Znajdz studenta po nazwisku.\n");
		printf("5. Sprawdz liczbe elementow w strukturze.\n");
		printf("6. Usun cala strukture.\n");
		printf("7. Zakoncz program.\n");
		printf("Wybierz opcje: ");

		if (scanf("%d", &choice) != 1)
		{
			printf("Blad. Podano niepoprawna opcje.\n");
			while (getchar() != '\n'); // Czyœci bufor wejœcia
			continue;
		}

		switch (choice)
		{
		case 1:
			printf("Wpisz dane studenta (imie, nazwisko, rok urodzenia): ");
			scanf("%s %s %d", student.imie, student.nazwisko, &student.rok_urodzenia);
			push(&stack, &student);
			break;
		case 2:
			printf("Zdjeto element ze stosu.\n");
			pop(&stack);
			break;
		case 3:
			display(&stack);
			break;
		case 4:
			printf("Wpisz nazwisko studenta do wyszukania: ");
			scanf("%s", nazwisko);
			Student* foundStudent = searchElement(&stack, nazwisko);
			if (foundStudent != NULL) 
			{
				printf("Znaleziono studenta: %s %s, Rok urodzenia: %d\n", foundStudent->imie,
					foundStudent->nazwisko, foundStudent->rok_urodzenia);
			}
			else 
			{
				printf("Nie znaleziono studenta o podanym nazwisku.\n");
			}
			break;
		case 5:
			printf("Liczba elementow w strukturze: %d\n", countElements(&stack));
			break;
		case 6:
			deleteStack(&stack);
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