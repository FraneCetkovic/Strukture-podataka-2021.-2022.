#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE (1024)

struct _Poly;
typedef struct _Poly* Position;

typedef struct _Poly
{
int coefficient;
int exponent;
Position next;
}Poly;



int ReadFromFile(char* filename, Position head1, Position head2);
Position FindPrevious(Position head, Position number);
int MergeAfter(Position pos, Position element);
Position CreateElement(int coefficient, int exponent);
int DeleteAfter(Position pos);
int PrintPoly(Position head);
int AddPoly(Position head1,Position head2,Position result);
int MultiplyPoly(Position head1,Position head2,Position result);

int main()
{
Poly headElement1 = { .coefficient = 0, .exponent = 0, .next = NULL };
Poly headElement2 = { .coefficient = 0, .exponent = 0, .next = NULL };
Poly rez1 = { .coefficient = 0, .exponent = 0, .next = NULL };
Poly rez2 = { .coefficient = 0, .exponent = 0, .next = NULL };

Position head1=&headElement1;
Position head2=&headElement2;
Position result1=&rez1;
Position result2=&rez2;

ReadFromFile("polinomi.txt", head1,head2);

printf("Polinom 1: ");
PrintPoly(head1);
printf("Polinom 2: ");
PrintPoly(head2);

AddPoly(head1,head2,result1);
printf("Zbroj: ");
PrintPoly(result1);

MultiplyPoly(head1,head2,result2);
printf("Umnozak: ");
PrintPoly(result2);

return 0;
}

int ReadFromFile(char* filename, Position head1, Position head2)
{
char* buffer=(char*) malloc(1024);
char* ptr=NULL;
int tempCoefficient = 0;
int tempExponent = 0;
int numberScanned = 0;
int numberFilled=0;
FILE* file = NULL;
Position temp1=NULL;
Position temp2=NULL;
Position head=head1;

file = fopen(filename, "r");
if (!file)
{
perror("Can't open file");
return -1;
}

for(int i=0;i<2;i++)
{
    buffer="";
if(i)
{
    head=head2;
}

fgets(buffer, MAX_LINE, file);
ptr = buffer;

while(strlen(ptr)>0)
    {
        numberFilled = sscanf(ptr, "%d %d %n", &tempCoefficient, &tempExponent, &numberScanned);

        if(numberFilled==2)
        {
            temp1 = CreateElement(tempCoefficient,tempExponent);
            temp2 = FindPrevious(head,temp1);
            MergeAfter(temp2,temp1);
        }
        ptr+=numberScanned;
    }
}
    fclose(file);

    return EXIT_SUCCESS;
}

Position FindPrevious(Position head, Position number)
{
Position temp = head;


if (head->next == NULL)
{
    return temp;
}

while (temp->next && (temp->next->exponent > number->exponent))
{
temp = temp->next;
}

    return temp;
}

int MergeAfter(Position pos, Position element)
{
    int tempCoefficient=0;

    if(!pos->next)
    {
        pos->next=element;
        element->next=NULL;

        return EXIT_SUCCESS;
    }
    if(pos->next->exponent<element->exponent)
    {
        element->next=pos->next;
        pos->next=element;
        
        return EXIT_SUCCESS;
    }

    if(pos->next->exponent==element->exponent)
    {
        tempCoefficient=pos->next->coefficient+element->coefficient;

        if(tempCoefficient)
        {
            pos->next->coefficient=tempCoefficient;
            return EXIT_SUCCESS;
        }

        DeleteAfter(pos);
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

Position CreateElement(int coefficient, int exponent)
{
    Position newElement=NULL;
    newElement=(Position)malloc(sizeof(Poly));

    if(!newElement)
    {
        perror("Can't allocate memory\n");
        return NULL;  
    }

    newElement->coefficient=coefficient;
    newElement->exponent=exponent;
    newElement->next=NULL;

    return newElement;
}

int DeleteAfter(Position pos)
{
    Position temp=NULL;
    if(!(pos->next))
    {
        perror("Element doesn't exist\n");
        return -1;
    }

    temp=pos->next;
    pos->next=pos->next->next;

    if(temp)
    free(temp);

    return EXIT_SUCCESS;
}

int PrintPoly(Position head)
{
    Position temp=NULL;

    if(head->next==NULL)
    {
        printf("0\n");
        return EXIT_SUCCESS;
    }

    for(temp=head->next;temp;temp=temp->next)
    {
        printf("%dx^%d ",temp->coefficient,temp->exponent);
        if(temp->next&&temp->next->coefficient>0) printf("+");
    }
    printf("\n");

    return EXIT_SUCCESS;
}

int AddPoly(Position head1,Position head2,Position result)
{
    Position temp=NULL;
    Position element=NULL;

    for(temp=head1->next;temp;temp=temp->next)
    {
       element=CreateElement(temp->coefficient,temp->exponent);
       MergeAfter(FindPrevious(result,element),element);
    }

    for(temp=head2->next;temp;temp=temp->next)
    {
       element=CreateElement(temp->coefficient,temp->exponent);
       MergeAfter(FindPrevious(result,element),element);
    }

    return EXIT_SUCCESS;
}

int MultiplyPoly(Position head1,Position head2,Position result)
{
    Position temp1=NULL;
    Position temp2=NULL;
    Position element=NULL;

    for(temp1=head1->next;temp1;temp1=temp1->next)
    {
        for(temp2=head2->next;temp2;temp2=temp2->next)
            {
                element=CreateElement(temp1->coefficient*temp2->coefficient,temp1->exponent+temp2->exponent);
                MergeAfter(FindPrevious(result,element),element);
            }
    }

    return EXIT_SUCCESS;
}