
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ET 11

//take words of a text and store them on a data structure 
typedef struct Cel{
    char Module[20];
    float point;
    struct Cel *svt;
}Note;

typedef struct {
    char CNE[11];
    char Nom[10];
    char Prenom[10];
    char Date_naiss[12];
    Note *modules;
}Etudiant;


int InitEnsemble(Etudiant *MaTable[MAX_ET]){
    for(int i = 0; i < MAX_ET; i++){
        MaTable[i] = NULL;
    }
    return ((int)1);
}

Note* MakeNewNote(float no, char Module[20]){
    Note *NE = (Note*)malloc(sizeof(Note));
    strcpy(NE->Module, Module);
    NE->point = no;
    NE->svt = NULL;
    return ((Note*)NE);
}

Note* InsertionModules(Note *Liste, FILE *nptr){
    float no; 
    char Module[20];
    fscanf(nptr, "%s", Module);
    fscanf(nptr, "%g", no);

    Note *NE = MakeNewNote(no, Module);
    if(!Liste)
        return ((Note*)NE);
    
    Note *crt = Liste;
    while (crt->svt)
        crt = crt->svt;
    
    crt->svt = NE;
    return Liste;
    
    
}


//so basic function for insertion of students 
int TelechargerAuTableau(Etudiant *MaTable[MAX_ET], FILE *fptr){
    char Etud[30];
    for(int i = 0; i< MAX_ET; i++){
        MaTable[i] = (Etudiant*)malloc(sizeof(Etudiant));
        fscanf(fptr, "%s", MaTable[i]->CNE);
        fscanf(fptr, "%s", MaTable[i]->Nom);
        fscanf(fptr, "%s", MaTable[i]->Prenom);
        fscanf(fptr, "%s", MaTable[i]->Date_naiss);

        strcpy(Etud, "Note/");
        strncat(Etud, MaTable[i]->CNE, sizeof(MaTable[i]->CNE));
        strncat(Etud, ".txt", 4);
        FILE * nptr = fopen(Etud, "r");
        MaTable[i]->modules = InsertionModules(MaTable[i]->modules, nptr);
    
    }

    return ((int)1);
}


int AffichageTableau(Etudiant *MaTable[MAX_ET]){
    for(int i = 0; i< MAX_ET; i++){
        printf("%s ", MaTable[i]->CNE);
        printf("%s ", MaTable[i]->Nom);
        printf("%s ", MaTable[i]->Prenom);
        printf("%s ", MaTable[i]->Date_naiss);
        Note *crt = MaTable[i]->modules;
        printf("[");
        while(crt){
            printf("%s: %g", MaTable[i]->modules->Module, MaTable[i]->modules->point);
            crt = crt->svt;
        }
        printf("]");
        printf("\n");
    }
    return ((int)1);
}

// int InsertionPoint()

int main(int argc, char const *argv[])
{
    FILE* fptr; 
    fptr = fopen("Etudiants/Etudiants.txt", "r");
    if(!fptr){
        printf("ERR");
        exit(-1);
    }

    Etudiant *Ensemble[MAX_ET];
    InitEnsemble(Ensemble);
    TelechargerAuTableau(Ensemble, fptr);    
    AffichageTableau(Ensemble);






    fclose(fptr);
    printf("\n");

    return 0;
}
