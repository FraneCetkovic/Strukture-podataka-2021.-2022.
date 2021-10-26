#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person
{
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear;
    Position next;
}Person;

int PrependList(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
int AppendList(Position head, char* name, char* surname, int birthYear);
Position FindPerson(Position first,char* surname);
int DeleteAfter(Position pos);
Position FindPrevious(Position first, char* surname);

int main(int argc, char**argv)
{
    Person head = { .next = NULL, .name = {0},
    .surname = {0}, .birthYear = 0 };
    Position p = &head;
    return 0;
}

int PrependList(Position head, char* name, char* surname, int birthYear)
{
    Position newPerson = NULL;

    newPerson = CreatePerson(name, surname, birthYear);
    if (!newPerson)
    {
      return -1;
    }

    InsertAfter(head, newPerson);

    return EXIT_SUCCESS;
}

int PrintList(Position first)
{
    Position temp = first;

    while (temp)
    {
        printf("Name: %s, surname_ %s, birth year: %d\n", temp->name, temp->surname, temp->birthYear);
        temp = temp->next;
    }

    return EXIT_SUCCESS;
}

Position CreatePerson(char* name, char* surname, int birthYear)
{
    Position newPerson = NULL;

    newPerson = (Position)malloc(sizeof(Person));
    if (!newPerson)
    {
        perror("Can't allocate memory\n");
        return NULL;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->surname, surname);
    newPerson->birthYear = birthYear;
    newPerson->next = NULL;

    return newPerson;
}
int InsertAfter(Position position, Position newPerson)
{
    newPerson->next = position->next;
    position->next = newPerson;

    return EXIT_SUCCESS;
}

Position FindLast(Position head)
{
    Position temp = head;

    while (temp->next)
    {
        temp = temp->next;
    }

    return temp;
}

int AppendList(Position head, char* name, char* surname, int birthYear)
{
    Position newPerson = NULL;
    Position last = NULL;

    newPerson = CreatePerson(name, surname, birthYear);
    if (!newPerson)
    {
        return -1;
    }

    last = FindLast(head);
    InsertAfter(last, newPerson);

    return EXIT_SUCCESS;
}

Position FindPerson(Position first, char* surname)
{
    Position temp = first;

    while (temp)
    {
        if (strcmp(temp->surname, surname) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

int DeleteAfter(Position pos)
{
    Position Deleted=NULL;

    if(pos->next==NULL)
    {
        perror("Element does not exist");
        return -1;
    }

    Position Deleted=pos->next;
    pos->next=Deleted->next;

    free(Deleted);
    return EXIT_SUCCESS;
}

Position FindPrevious(Position first, char* surname)
{
    Position temp=first;
    while(temp->next)
    {
        if(strcmp(temp->next->surname,surname)==0)
        {
            return temp;
        }
    }

    return NULL;
}