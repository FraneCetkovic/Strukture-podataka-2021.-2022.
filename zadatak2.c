#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)
#define MAX_LINE (1024)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person
{
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear;
    Position next;
}Person;

int PrependList(Position head, Position newPerson);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
int AppendList(Position head, Position newPerson);
Position FindPerson(Position first,char* surname);
int DeleteAfter(Position pos);
Position FindPrevious(Position first, char* surname);
int InsertBefore(Position position, Position newPerson, Position first);
int InsertSorted(Position head, Position newPerson);
int WriteToFile (char * filename, Position first);
int ReadFromFile(char* filename, Position head);
void Menu(Position head);
Position ReadPerson();



int main(int argc, char**argv)
{
    Person head = { .next = NULL, .name = {0},
    .surname = {0}, .birthYear = 0 };
    Position p = &head;

    printf("Welcome\n");
    Menu(p);

    return 0;
}

int PrependList(Position head, Position newPerson)
{
    printf("Adding person to start of list\n");

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

    printf("\nPrinting list: \n");
    while (temp)
    {
        printf("%s %s %d\n", temp->name, temp->surname, temp->birthYear);
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

int AppendList(Position head, Position newPerson)
{
    Position last = NULL;

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

    Deleted=pos->next;
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
        temp=temp->next;
    }

    return NULL;
}

int InsertBefore(Position position, Position newPerson, Position first)
{
    Position previous= NULL;
    previous=FindPrevious(first, position->surname);

    if(previous)
    {
        newPerson->next=previous->next;
        previous->next=newPerson;
        return EXIT_SUCCESS;
    }

    return -1;
}

int InsertSorted(Position head , Position newPerson)
{
    Position temp=head;

    if(head->next == NULL)
    {
        head->next=newPerson;
        newPerson->next=NULL;

        return EXIT_SUCCESS;
    }

    while( (temp-> next) && (strcmp(newPerson->surname , temp->next->surname) > 0) )
    {
        temp=temp->next;
    }

    newPerson->next=temp->next;
    temp->next=newPerson;

    return EXIT_SUCCESS;
}

int WriteToFile(char * filename, Position first)
{
    FILE * file=NULL;
    Position temp=first;

    file=fopen(filename, "w");

    if(!file)
    {
        perror("Error : Cannot open file");
        return -1;
    }

    while(temp)
    {
        fprintf(file , "%s %s %d\n", temp->name, temp->surname, temp->birthYear);
        temp=temp->next;
    }

    fclose(file);
    return EXIT_SUCCESS;
}

int ReadFromFile(char* filename, Position head)
{
    FILE * file=NULL;
    Position temp = head;
    Position newPerson=NULL;

    char name[MAX_SIZE]="",surname[MAX_SIZE]="";
    char line[MAX_LINE]="";
    int birthYear=0;

    file=fopen(filename, "r");

    if(!file)
    {
        perror("Error : Cannot open file \n}");
        return -1;
    }

    while(!feof(file))
    {
        fgets(line,1024,file);

        if(sscanf(line,"%s %s %d", name,surname,&birthYear)==3)
        {
            newPerson=CreatePerson(name,surname,birthYear);
            InsertSorted(head,newPerson);
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}

void Menu(Position head)
{
    int choice=0;
    char filename[MAX_SIZE]="", surname[MAX_SIZE]="";
    Position temp=NULL;
    

    
    do
    {
        printf("\nChoose action : \n 0 : Exit program\n 1 : Read from file\n 2 : Write to file\n 3 : Print list\n 4 : Prepend list \n 5 : Append list \n 6 : Insert after certain surname\n 7 : Insert before certain surname\n 8 : Insert person alphabetically sorted\n 9 : Delete person\n");
        scanf(" %d",&choice);

        switch (choice)
        {
            case 0 : 
                printf("Exiting\n");
                return;
            case 1 : 
                printf("\nPlease input filename: ");
                scanf("%s",filename);
                ReadFromFile(filename,head);
                break;

            case 2 : 
                printf("\nPlease input filename: ");
                scanf("%s",filename);
                WriteToFile(filename,head->next);
                break;

            case 3 : 
                PrintList(head->next);
                break;

            case 4:
                temp=ReadPerson();
                if(temp)
                    PrependList(head, temp );
                break;

            case 5:
                temp=ReadPerson();
                if(temp)
                AppendList(head, temp );
                break;

            case 6:
                printf("Please enter surname after which to insert new person: ");
                scanf("%s", surname);
                temp=ReadPerson();
                if(temp)
                    InsertAfter(FindPerson(head->next,surname), temp);
                break;

            case 7:
                printf("Please enter surname before which to insert new person: ");
                scanf("%s", surname);
                temp=ReadPerson();
                if(temp)
                    InsertBefore(FindPerson(head->next,surname),temp,head->next);
                break;
            
            case 8:
                temp=ReadPerson();
                if(temp)
                    InsertSorted(head,temp);
                break;
            
            case 9:
                printf("Enter surname of person to delete: ");
                scanf("%s",surname);

                temp = FindPrevious(head->next,surname);
                DeleteAfter(temp);
                break;
            
            default:
                printf("Unknown action\n");
        }
    } while(choice);

    return;
}

Position ReadPerson()
{
    char name[MAX_SIZE]="", surname[MAX_SIZE]="";
    char line[MAX_LINE]="";
    Position newPerson=NULL;

    int birthYear=0;

    printf("Please enter name, surname and birth year:");
    
    scanf(" ");
    fgets(line,1024,stdin);

    printf("LINE : %s",line);

    if(sscanf(line,"%s %s %d", name , surname , &birthYear)==3)
    {
        newPerson=CreatePerson(name,surname,birthYear);
    }

    else
    {
        perror("Error : Invalid input");
        return NULL;
    }

    return newPerson;
}



































































