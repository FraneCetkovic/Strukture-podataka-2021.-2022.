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
    

    /*while(strcmp(buffer,"end\n"))
    {
        printf(">");
        fgets(buffer,128,stdin);
        state=sscanf(buffer," %d",&input);
        if(!state)
        {
            if(strcmp(buffer,"end\n"))
            printf("Invalid input!\n");
        }
        else
        {
            node=CreateNode(input);
            state= InsertNode(root,node);
        }
    }

    PrintPreOrder(root->right);

    printf("kojeg ces brisat?\n");
    scanf("%d",&input);

    node=FindParent(root,input);
    DeleteChild(node,input);

    PrintPreOrder(root->right);
*/

Menu(root);
    return 0;
}