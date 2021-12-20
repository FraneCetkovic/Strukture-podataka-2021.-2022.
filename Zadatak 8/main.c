#include "tree.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main()
{
    Node root=NULL;
    
    root=(Node)malloc(sizeof(tree));
    root->value=INT_MIN;
    root->left=NULL;
    root->right=NULL;

    Menu(root);
    return 0;
}