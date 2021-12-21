#include "tree.h"
#include "error.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node CreateNode(int value)
{
    Node newNode=NULL;
    newNode=(Node)malloc(sizeof(tree));

    if (!newNode)
    {
        perror("Can't allocate memory!\n");
        return NULL;
    }

    newNode->value=value;
    newNode->left=NULL;
    newNode->right=NULL;

    return newNode;
}

Node InsertNode(Node curr, Node newNode)
{
    if(!curr)
    {
        printf("Tree doesn't exist!\n");
        return NULL;
    }

    if(newNode->value >= curr->value)
    {
        if(!(curr->left))
        {
            curr->left=newNode;
            return curr;
        }
        InsertNode(curr->left,newNode);
        return curr;
    }

    else
    {
         if(!(curr->right))
        {
            curr->right=newNode;
            return curr;
        }
        InsertNode(curr->right,newNode);
        return curr;
    }

    return curr;
}

int PrintInOrder(Node pos)
{
    if(pos==NULL)
        return EXIT_SUCCESS;
    PrintInOrder(pos->left);
    printf("%d ",pos->value);
    PrintInOrder(pos->right);

    return EXIT_SUCCESS;
}

void PrintLine()
{
    printf("============================\n");
}

void PrintMenu()
{
    printf("0 - Exit program\n");
    printf("1 - Insert elements\n");
    printf("2 - Call replace function\n");
    printf("3 - Print tree inorder\n");
    printf("4 - Add random numbers from 11 to 89 (inclusive) to tree\n");
    printf("5 - Print tree to file (inorder)\n");
}
Node InsertNodes(Node root)
{
    char* buffer=NULL;
    int state=0;
    int input=0;
    Node node=NULL;

    buffer=(char*)malloc(MAX_STRING);
    strcpy(buffer,"");

    printf("Please input element values, input 'end' when you're done.\n");
    
    while(strcmp(buffer,"end\n"))
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
            InsertNode(root,node);
            if(input==8)printf("Nos ti posran!\n");
        }
    }

    free(buffer);

    return root;
}

int Menu(Node root, Position head)
{
    int selection=0;
    int state=0;
    int temp=0;

    char* buffer=NULL;
    char* filename=NULL;
    buffer=(char*)malloc(MAX_STRING);
    strcpy(buffer,"");  

    filename=(char*)malloc(MAX_STRING);
    strcpy(filename,"");

    printf("Welcome!\n");
    do
    {
        PrintLine();
        PrintMenu();
        PrintLine();

        fgets(buffer,128,stdin);
        if(!sscanf(buffer," %d",&selection))
            selection=-1;
            
        switch(selection)
        {
            case 0: return EXIT_SUCCESS;
                    break;

            case 1: InsertNodes(root);
                    break;
            
            case 2: printf ("Replacing...\n");
                    replace(root->right);
                    printf("Done!\n");
                    break;

            case 3: printf("\nPrinting inorder:\n");
                    state=PrintInOrder(root->right);
                    printf("\n");
                    break;
            case 4: printf("Please enter amount of random values:\n");
                    fgets(buffer,128,stdin);
                    if(!sscanf(buffer," %d",&temp)||temp<0)
                    {
                        printf("Invalid amount!");
                        break;
                    }
                    printf("Adding random numbers to tree...\n");
                    FillTreeRandom(root,temp);
                    printf("Done!\n");
                    break;

            case 5: if(!strlen(filename))
                    {
                    printf("Please enter filename: ");
                    fgets(filename,128,stdin);
                    filename[strcspn(filename, "\n")] = 0;
                    }
                    
                    printf("Printing to file...\n");
                    PrintToList(root->right,head);
                    PrintListToFile(head->next,filename);
                    DeleteList(head);
                    break;

            default: printf("Unknown command!\n");
                    break;
        }
    }while(selection);
        
    free(buffer);
    free(filename);
    return EXIT_SUCCESS;
}

int replace(Node curr)
{
    int left=0;
    int right=0;
    if(curr==NULL)
        return 0;

    if(!curr->left&&!curr->right);
    else if(!curr->left)right=curr->right->value;
    else if(!curr->right)left=curr->left->value;
    else    
    {
        left=curr->left->value;
        right=curr->right->value;
    }

    curr->value=left+right+replace(curr->left)+replace(curr->right);
    
    return curr->value;
}

int FillTreeRandom(Node root, int amount)
{
    Node temp=NULL;

    if(!root)
    {
        printf("Tree doesn't exist!\n");
        return DOESNT_EXIST;
    }

    srand(time(0));
    for(int i=0;i<amount;i++)
    {
        temp=CreateNode(rand()%79 + 11);
        InsertNode(root,temp);
    }

    return EXIT_SUCCESS;
}

