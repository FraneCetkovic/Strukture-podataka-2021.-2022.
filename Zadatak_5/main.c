#include "declarations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    double result=0;
    char* filename="";
    int status=0;

    printf("Please enter your postfix filename: ");
    scanf("%s",filename);

    status = CalculatePostfixFromFile(&result,filename);

    if(!status)
    {
        printf("Result: %lf",result);
    }

    return 0;
}