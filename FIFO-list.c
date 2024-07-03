//stos lista
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

typedef struct Node // Struktura elementu stosu/kolejki
{
    Student data;
    struct Node* next;
} Node;

typedef enum // Typ wyliczeniowy do menu
{
    DODAJ = 1,
    ZDJECIE,
    WYSWIETL,
    ZNAJDZ,
    LICZBA_ELEMENTOW,
    USUN_STRUKTURE,
    ZAKONCZ
} OpcjeMenu;

typedef struct 
{
    Node* top;
} Stack;

void initializeStack(Stack* stack) 
{
    stack->top = NULL;
}

int isEmpty(Stack* stack) 
{
    return (stack->top == NULL);
}

void push(Stack* stack, const Student* student) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Blad alokacji pamieci!\n");
        return;
    }
    newNode->data = *student;
    newNode->next = stack->top;
    stack->top = newNode;
}

Student pop(Stack* stack) 
{
    Student emptyStudent = { .imie = "", .nazwisko = "", .rok_urodzenia = 0 };
    if (isEmpty(stack)) 
    {
        printf("Stos jest pusty.\n");
        return emptyStudent;
    }
    Node* temp = stack->top;
    Student popped = temp->data;
    stack->top = stack->top->next;
    free(temp);
    return popped;
}

void display(Stack* stack)
{
    if (isEmpty(stack)) 
    {
        printf("Stos jest pusty.\n");
        return;
    }
    Node* current = stack->top;
    printf("Zawartosc stosu:\n");
    while (current != NULL) 
    {
        printf("Imie: %s, Nazwisko: %s, Rok urodzenia: %d\n",
            current->data.imie, current->data.nazwisko, current->data.rok_urodzenia);
        current = current->next;
    }
}

int countElements(Stack* stack)
{
    int count = 0;
    Node* current = stack->top;
    while (current != NULL) 
    {
        count++;
        current = current->next;
    }
    return count;
}

Student* searchElement(Stack* stack, const char* nazwisko)
{
    Node* current = stack->top;
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

void deleteStack(Stack* stack)
{
    Node* current = stack->top;
    Node* temp;
    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }
    stack->top = NULL;
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
        printf("\n!stos-lista! Menu:\n");
        printf("1. Dodaj element na stosie.\n");
        printf("2. Pobierz element.\n");
        printf("3. Wyswietl zawartosc stosu.\n");
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

        switch ((OpcjeMenu)choice) 
        {
        case DODAJ:
            printf("Wpisz dane studenta (imie, nazwisko, rok urodzenia): ");
            scanf("%s %s %d", student.imie, student.nazwisko, &student.rok_urodzenia);
            push(&stack, &student);
            break;
        case ZDJECIE:
            printf("Zdjeto element ze stosu.\n");
            pop(&stack);
            break;
        case WYSWIETL:
            display(&stack);
            break;
        case ZNAJDZ:
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
        case LICZBA_ELEMENTOW:
            printf("Liczba elementow w strukturze: %d\n", countElements(&stack));
            break;
        case USUN_STRUKTURE:
            deleteStack(&stack);
            break;
        case ZAKONCZ:
            printf("Zakonczono program.\n");
            exit(0);
        default:
            printf("Niepoprawny wybor. Sprobuj ponownie.\n");
            break;
        }
    }
    return 0;
}
