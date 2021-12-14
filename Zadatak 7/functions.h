#pragma once

#define MAX_STRING 128

struct _tree;
typedef struct _tree* treePos;
typedef struct _tree
{
    char *name;
    treePos child;
    treePos sibling;

}tree;

struct _stack;
typedef struct _stack* stackPos;
typedef struct _stack
{
    treePos directory;
    stackPos next;
    stackPos prev;
}stack;

int md(treePos);
int dir(treePos);
treePos cd(treePos, stackPos);
int path(stackPos,treePos,treePos);
stackPos FindLast(stackPos);
treePos back(treePos,stackPos);
treePos name(treePos,char*);
int push(stackPos,treePos);
treePos pop(stackPos);
void PrintLine();
int Menu(treePos,stackPos);

