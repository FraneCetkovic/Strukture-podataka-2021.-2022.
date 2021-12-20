#pragma once
#define MAX_STRING 128

struct _tree;
typedef struct _tree* Node;
typedef struct _tree
{
    int value;
    Node left;
    Node right;
}tree;

Node CreateNode(int value);
int InsertNode(Node curr,Node newNode);
int InsertNodes(Node curr);
int PrintPreOrder(Node pos);
int PrintInOrder(Node pos);
int PrintPostOrder(Node pos);
int PrintLevelOrder(Node pos);
Node FindParent(Node curr, int toFind);
int DeleteChild(Node pos, int toDelete);
Node FindLargestLeft(Node pos);
Node FindSmallestRight(Node pos);
int Menu(Node root);
void PrintLine();
void PrintMenu();
int DeleteElement(Node root);