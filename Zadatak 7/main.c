#include "functions.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int state=1;
    treePos root=NULL;
    stackPos head=NULL;

    root=(treePos)malloc(sizeof(tree));
    root->child=NULL;
    root->sibling=NULL;

    head=(stackPos)malloc(sizeof(stack));
    head->next=NULL;
    head->prev=NULL;

    root->name=(char*)malloc(MAX_STRING);
    root->name="C: ";

    while(state)
    {
        state=Menu(root,head);
    }
    

}

