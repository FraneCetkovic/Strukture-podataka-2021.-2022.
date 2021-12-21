#include "tree.h"
#include "error.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main()
{
    Node root=NULL;
    Node node=NULL;
    Node temp=NULL;
    Position head=NULL;
    
    root=(Node)malloc(sizeof(tree));
    root->value=INT_MAX;
    root->left=NULL;
    root->right=NULL;

    head=(Position)malloc(sizeof(list));
    head->value=0;
    head->next=NULL;


    Menu(root,head);
    return 0;
}