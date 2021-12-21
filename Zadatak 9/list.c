#include "tree.h"
#include "error.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int PrintToList(Node pos,Position head)
{
    Position temp=NULL;
    
    if(pos==NULL)
        return EXIT_SUCCESS;
    

    PrintToList(pos->left,head);
    temp=CreateListNode(pos->value);
    AppendList(head,temp);
    PrintToList(pos->right,head);

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
int InsertAfter(Position position, Position newNumber)
{
    newNumber->next = position->next;
    position->next = newNumber;

    return EXIT_SUCCESS;
}

Position CreateListNode(int value)
{
    Position newNumber=NULL;
    
    newNumber=(Position)malloc(sizeof(list));
    newNumber->next=NULL;
    newNumber->value=value;

    return newNumber;
}

int AppendList(Position head, Position number)
{
    Position last = NULL;

    if (!number)
    {
        return DOESNT_EXIST;
    }

    last = FindLast(head);
    InsertAfter(last, number);

    return EXIT_SUCCESS;
}

int PrintListToFile(Position pos, char* filename)
{
    FILE* file=fopen(filename,"a");

    if(!file)
    {
        printf("Error opening file!\n");
        return DOESNT_EXIST;
    }

    while(pos)
    {
        fprintf(file,"%d ",pos->value);
        pos=pos->next;
    }
    fprintf(file,"\n");

    fclose(file);
    return EXIT_SUCCESS;
}

int DeleteAfter(Position pos)
{
    Position Deleted=NULL;

    if(pos->next==NULL)
    {
        return DOESNT_EXIST;
    }

    Deleted=pos->next;
    pos->next=Deleted->next;

    free(Deleted);
    return EXIT_SUCCESS;
}

int DeleteList(Position head)
{
    while(head->next)
    {
        DeleteAfter(head);
    }

    return EXIT_SUCCESS;
}