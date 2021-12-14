#include "functions.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int md(treePos curr)
{
    treePos directory;
    directory= (treePos)malloc(sizeof(tree));
    directory->name=(char*)malloc(MAX_STRING);

    if(!directory)
    {
        perror("Can't allocate memory!");
        return CANT_ALLOCATE;
    }

    if (curr->child != NULL) {
		curr = curr->child;
		while (curr->sibling != NULL)
			curr = curr->sibling;
		curr->sibling = directory;
	}
	else
		curr->child = directory;
 
    fgets(directory->name,MAX_STRING,stdin);

    directory->child=NULL;
    directory->sibling=NULL;

    return 0;
}

int dir(treePos curr)
{
    if(curr->child == NULL)
    {
        printf("Directory is empty");
        return 0;
    }

    curr=curr->child;

    printf("Directories:\n");
    printf("\t%s\n", curr->name);

    while(curr->sibling!=NULL)
    {
        printf("\t%s",curr->sibling->name);
        curr=curr->sibling;
    }

    return 0;
}

stackPos FindLast(stackPos head)
{
    stackPos temp;

    if(head->next==NULL)
    {
        return NULL;
    }

    temp=head->next;

    while(temp->next!=NULL)
    {
        temp=temp->next;
    }

    return temp;    
}

int path(stackPos head, treePos root, treePos curr)
{
    stackPos temp=NULL;
    temp=FindLast(head);

    printf("\n");

    if (head->next == NULL)
	{
		printf("%s>", root->name);
		return EXIT_SUCCESS;
	}

	while (temp->prev != NULL)
	{
		printf("%s>", temp->directory->name);
		temp=temp->prev;
	}

	printf("%s>", curr->name);

	return 0;
}

treePos cd(treePos curr, stackPos head)
{
	treePos file=NULL;
	char* dirName = NULL;
	dirName = (char*)malloc(MAX_STRING);

	scanf(" %s", dirName);

	if (curr->child == NULL)
	{
		perror("No such file or directory\n");
		return curr;
	}

	file = name(curr, dirName);
	if (file == 0)
	{
		printf("Can't find directory\n");
		return curr;
	}

	push(head, curr);

	return file;
}

treePos back(treePos curr, stackPos head)
{
    treePos file=NULL;

    file=pop(head);

    if(!file)
    {
        perror("File doesn't exist\n");
        file=curr;
    }

    return file;
}

treePos name(treePos curr, char* name)
{
	if (curr->child == NULL)
		printf("Directory is empty!\n");

	curr = curr->child;


	while (strcmp(name, curr->name) != 0 && curr->sibling != NULL) {
		curr = curr->sibling;
	}

	if (curr->sibling == NULL) {
		if (strcmp(name, curr->name) != 0)
			return 0;
		else
			return curr;
	}

	else
		return curr;

}

int push(stackPos head, treePos dir)
{
	stackPos new = (stackPos)malloc(sizeof(stack));

	new->next = head->next;
	new->prev = head;
	if (head->next)
		head->next->prev = new;
	head->next = new;
	new->directory = dir;

	return 0;
}

treePos pop(stackPos head) {

	stackPos temp = (stackPos)malloc(sizeof(stack));
	
	treePos temp_tree = NULL;

	if (head->next == NULL)
    {
        printf("No such file or directory\n");
        return 0;
    }
		

	temp = head->next;
	temp_tree = temp->directory;
	head->next = head->next->next;

	if (head->next != NULL)
		head->next->prev = head;
	free(temp);

	return temp_tree;
}

void PrintLine()
{
    printf("============================\n");
}

int Menu(treePos root, stackPos head)
{
    treePos curr=root;
    char buffer[MAX_STRING]="";

    printf("Welcome!\n");
    PrintLine();
    printf("Command list:\n");
    printf("\tmd <filename> - Create directory\n");
    printf("\tcd <filename> - Open directory\n");
    printf("\tcd.. - Close directory\n");
	printf("\tdir - Show all child directories of current directory\n");
    printf("\tmenu - Menu\n");
	printf("\texit - Close program\n");
    PrintLine();



    while(strcmp(buffer,"exit"))
    {
        path(head,root,curr);
        scanf(" %s",buffer);
        
        if (!strcmp(buffer, "md")) 
			md(curr);

		else if (!strcmp(buffer, "cd"))
			curr = cd(curr, head);

		else if (!strcmp(buffer, "cd..")) 
			curr = back(curr, head);

		else if (!strcmp(buffer, "dir"))
			dir(curr);
		

		else if (!strcmp(buffer, "exit")) 
			return 0;

		else if (!strcmp(buffer, "menu")) 
			return 1;
        else
			printf("Command not found\n");
    }

    return 0;
}