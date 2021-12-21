#include "tree.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>

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

int InsertNode(Node curr, Node newNode)
{
    int state=0;
    if(!curr)
    {
        printf("Tree doesn't exist!\n");
        return DOESNT_EXIST;
    }
    if(newNode->value==curr->value)
    {
        free (newNode);
        return EXIT_SUCCESS;
    }

    if(newNode->value < curr->value)
    {
        if(!(curr->left))
        {
            curr->left=newNode;
            return EXIT_SUCCESS;
        }
        state=InsertNode(curr->left,newNode);
        return EXIT_SUCCESS;
    }

    else
    {
         if(!(curr->right))
        {
            curr->right=newNode;
            return EXIT_SUCCESS;
        }
        state=InsertNode(curr->right,newNode);
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

int PrintPreOrder(Node pos)
{
    if(pos==NULL)
        return EXIT_SUCCESS;
    printf("%d ",pos->value);
    PrintPreOrder(pos->left);
    PrintPreOrder(pos->right);

    return EXIT_SUCCESS;
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

int PrintPostOrder(Node pos)
{
    if(pos==NULL)
        return EXIT_SUCCESS;
    PrintPostOrder(pos->left);
    PrintPostOrder(pos->right);
    printf("%d ",pos->value);

    return EXIT_SUCCESS;
}

Node FindParent(Node curr, int toFind)
{
    if(!curr)
    {
        return curr;
    }
    if((curr->left&&curr->left->value==toFind)||(curr->right&&curr->right->value==toFind))
    {
        return curr;
    }

    if(toFind<curr->value)
    {
        return FindParent(curr->left,toFind);
    }

    if(toFind>curr->value)
    {
        return FindParent(curr->right,toFind);
    }

    return NULL;
}

int DeleteChild(Node pos, int toDelete)
{
    Node temp=NULL;
    Node parent=NULL;
    Node toSwap=NULL;
    int swap=0;
    int direction = toDelete - pos->value;

    if(pos->left&&pos->left->value==toDelete)
    {
        temp=pos->left;
    }

    else if(pos->right&&pos->right->value==toDelete)
    {
        temp=pos->right;
    }

    else
    {
        printf("Error - element not found!\n");
        return NOT_FOUND;
    }

    if((!temp->left&&!temp->right))
    {
        free(temp);

        if(direction < 0)
        {
            pos->left=NULL;
        }
        else
        {
            pos->right=NULL;
        }
        
        return EXIT_SUCCESS;
    }

    if(!temp->left)
    {
        pos->right=temp->right;
        free(temp);
        return EXIT_SUCCESS;
    }

    if(!temp->right)
    {
        pos->left=temp->left;
        free(temp);
        return EXIT_SUCCESS;
    }

    toSwap=FindLargestLeft(temp);
    if(!toSwap)
        toSwap=FindSmallestRight(temp);
    
    swap=toSwap->value;
    parent=FindParent(pos,swap);

    DeleteChild(parent,swap);

    temp->value=swap;
    return EXIT_SUCCESS;
}

Node FindLargestLeft(Node pos)
{
    Node temp=pos->left;
    if(!temp)
    {
        return temp;
    }

    while(temp->right)
    {
        temp=temp->right;
    }

    return temp;
}

Node FindSmallestRight(Node pos)
{
    Node temp=pos->right;
    if(!temp)
    {
        return temp;
    }

    while(temp->left)
    {
        temp=temp->left;
    }

    return temp;
}

void PrintLine()
{
    printf("============================\n");
}

void PrintMenu()
{
    printf("0 - Exit program\n");
    printf("1 - Insert elements\n");
    printf("2 - Print tree preorder\n");
    printf("3 - Print tree inorder\n");
    printf("4 - Print tree postorder\n");
    printf("5 - Print tree level order\n");
    printf("6 - Delete element\n");
}

int InsertNodes(Node root)
{
    char* buffer=NULL;
    int state=0;
    int input=0;
    Node node=NULL;

    buffer=(char*)malloc(MAX_STRING);
    strcpy(buffer,"");   

    printf("Please input element values, input 'end' when you're done.\n");
    getchar();
    
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
            state= InsertNode(root,node);
            if(input==8)printf("Nos ti posran!\n");
        }
    }

    free(buffer);

    return EXIT_SUCCESS;
}

int DeleteElement(Node root)
{
    int toDelete=0;
    int state=0;
    Node parent=NULL;
    PrintLine();
    printf("Please input value of element to delete: ");
    scanf(" %d",&toDelete);

    if(!root->right)
    {
        printf("Error - tree is empty!\n");
        return EMPTY;
    }

    if(root->right && root->right->value==toDelete)
    {
        if(!(root->right->left)&&!(root->right->right))
        {
            free(root->right);
            root->right=NULL;
        }
        state = DeleteChild(root,toDelete);
        return state;
    }


    parent=FindParent(root,toDelete);
    if(!parent)
    {
        printf("Element not found!\n");
        return NOT_FOUND;
    }
    DeleteChild(parent,toDelete);

    return EXIT_SUCCESS;
}
int Menu(Node root)
{
    int selection=0;
    int state=0;


    printf("Welcome!\n");
    do
    {
        PrintLine();
        PrintMenu();
        PrintLine();

        scanf(" %d",&selection);

        switch(selection)
        {
            case 0: return EXIT_SUCCESS;

            case 1: state=InsertNodes(root);
                    break;
            case 2: printf("\nPrinting preorder:\n");
            
                    state=PrintPreOrder(root->right);
                    printf("\n");
                    break;
            case 3: printf("\nPrinting inorder:\n");
                    state=PrintInOrder(root->right);
                    printf("\n");
                    break;
            case 4: printf("\nPrinting postorder:\n");
                    state=PrintPostOrder(root->right);
                    printf("\n");
                    break;
            case 5: printf("\nPrinting level order:\n");
                    state=PrintLevelOrder(root->right);
                    printf("\n");
                    break;
            case 6: state=DeleteElement(root);
                    break;
            default: printf("Unknown command!\n");
                    break;
        }
    }while(selection);
        
    return EXIT_SUCCESS;
}

Position CreateList()
{
    Position head=NULL;
    head=(Position)malloc(sizeof(list));
    if(!head)
    {
        perror("No memory!\n");
        return NULL;
    }
    head->node=NULL;
    head->next=NULL;

    return head;
}

int PrintLevelOrder(Node root)
{
    Position head=NULL;
    Position temp=NULL;
    Node curr=NULL;

    head=CreateList();
    if(!head)
    {
        printf("Failed to create list!\n");
        return CANT_ALLOCATE;
    }
    curr=root;

    while(curr)
    {
        printf("%d ",curr->value);
        if(curr->left)
        {
            temp=CreateListNode(curr->left);
            Push_back(head,temp);
        }
        if(curr->right)
        {
            temp=CreateListNode(curr->right);
            Push_back(head,temp);
        }     
        
        curr=Pop(head);
    }

    free(head);
    return EXIT_SUCCESS;
}
int DeleteAfter(Position position)
{
Position temp = position->next;

if (!temp)
{
return EXIT_SUCCESS;
}

position->next = temp->next;
free(temp);

return EXIT_SUCCESS;
}

Position InsertAfter(Position position, Position newNumber)
{
    newNumber->next = position->next;
    position->next = newNumber;

    return newNumber;
}

Position CreateListNode(Node node)
{
    Position newNumber=NULL;
    
    newNumber=(Position)malloc(sizeof(list));
    newNumber->next=NULL;
    newNumber->node=node;

    return newNumber;
}

Node Pop(Position head)
{
    Node temp=NULL;
    if(!head->next)
    {
        return NULL;
    }

    temp=head->next->node;

    DeleteAfter(head);

    return temp;
}

int Push_back(Position head, Position new)
{
    Position temp=head;
    while(temp->next)
        temp=temp->next;
    InsertAfter(temp, new);

return EXIT_SUCCESS;
}