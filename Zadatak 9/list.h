#pragma once

struct _list;
typedef struct _list* Position;
typedef struct _list
{
    int value;
    Position next;
}list;


int PrintListToFile(Position pos, char* filename);
int AppendList(Position head, Position number);
Position FindLast(Position head);
int InsertAfter(Position position, Position newNumber);
Position CreateListNode(int value);
int DeleteList(Position head);
int DeleteAfter(Position pos);

