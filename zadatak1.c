#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 128
#define MAX_LINE 1024

typedef struct
{
    char ime[MAX_SIZE];
    char prezime[MAX_SIZE];
    double bodovi;
} student;

int countRows(char* filename);
student* AlocirajIProcitaj(int br, char* filename);
double FindMax(int br, student* studenti);
void IspisiStudente(int br, double max, student* ekipa);



int main()
{
    int brRedaka=0,maxBodovi=0;
    char filename[15]="studenti.txt";
    student* studenti=NULL;

    brRedaka=countRows(filename);
    studenti = AlocirajIProcitaj(brRedaka, filename);
    maxBodovi=FindMax(brRedaka,studenti);

    IspisiStudente(brRedaka, maxBodovi, studenti);

    return 0;
}


int countRows(char* filename)
{
    int brojac = 0;
    FILE* datoteka = NULL;
    char buffer[MAX_LINE] = { 0 };

    datoteka = fopen(filename, "r");

if (!datoteka)
{
    printf("Neuspjesno otvaranje datoteke\n");
    return -1;
}

while (!feof(datoteka))
{
    fgets(buffer, MAX_LINE, datoteka);
    brojac++;
}

fclose(datoteka);

return brojac;
}

student* AlocirajIProcitaj(int br, char* filename)
{
    FILE* datoteka = NULL;
    char buffer[MAX_LINE] = { 0 };
    student* studenti = NULL;
    int brojac = 0;

    studenti = (student*)malloc(br * sizeof(student));
    
    if (!studenti)
    {
        printf("Neuspjesna alokacija");
        return NULL;
    }

    datoteka = fopen(filename, "r");

    if (!datoteka)
    {
        printf("Neuspjesno otvaranje datoteke\n");
        return NULL;
    }

    while (!feof(datoteka))
    {
        fscanf(datoteka, " %s %s %lf",
        studenti[brojac].ime,
        studenti[brojac].prezime,
        &studenti[brojac].bodovi);
        brojac++;
    }

    fclose(datoteka);

    return studenti;
}

double FindMax(int br, student* studenti)
{
    double max=0;
    int i=0;
    for(i=0;i<br;i++)
    {
        if(studenti[i].bodovi>max)
            max=studenti[i].bodovi;
    }

    return max;
}

void IspisiStudente(int br, double max, student* ekipa)
{
    int i=0;
    double relativni;

    for(i=0;i<br;i++)
    {
        relativni=ekipa[i].bodovi/max*100;
        if(relativni>100)
            relativni=100;
            
        printf("%s %s\n\t", ekipa[i].ime,ekipa[i].prezime);
            printf("Apsolutni: %lf Relativni:%lf\n",ekipa[i].bodovi,relativni);
    }

    return;
}