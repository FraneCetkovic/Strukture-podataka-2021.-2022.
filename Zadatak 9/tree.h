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
Node InsertNode(Node curr,Node newNode);
Node InsertNodes(Node curr);
int PrintInOrder(Node pos);
int replace(Node root);
int FillTreeRandom(Node root, int amount);


void PrintLine();
void PrintMenu();
