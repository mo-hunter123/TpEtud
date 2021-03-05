
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ET 11
#define MAX_MOD 9

//take words of a text and store them on a data structure 

//0 => Algo
//1 => Sdd
//2 => BD
//3 => SE
//4 => Archi
//5 => Tech
//6 => Reseaux
//7 => Web
//8 => Conce
//9 => UML
//10 => Droit
//11 => Eco


typedef struct Cel{
    float point;
    Etudiant *INfos;
    struct Cel *svt;
}Note;

//Note *notesEt[13];

typedef struct Inf{
    char CNE[11];
    char Date_naiss[12];
    Note *modules[13];
    NomEtu *nom;
    struct Inf *next;
}Etudiant;

//Etudiant* ets[26][10]

typedef struct NP{
    char Nom[20];
    char Prenom[20];
    Etudiant *infoEtu;
    struct NP *next;
}NomEtu;

//NomEtu* nomsets[26]

int InitEnsemble(Etudiant *MaTable[MAX_ET]){
    for(int i = 0; i < MAX_ET; i++)
    {
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

Note *AddEnd(Note* Liste, Note *NE){
    NE->svt = Liste; 
    return NE;
}

Note* InsertionModules(Note *Liste, FILE *nptr)
{
    float no; 
    char Module[20];
    Note *NE = NULL;
    for(int j = 0; j<MAX_MOD; j++)
    {
        fscanf(nptr, "%s", Module);
        fscanf(nptr, "%g", &no);
        NE = MakeNewNote(no, Module);
        Liste = AddEnd(Liste, NE);
    }
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
        printf("\n[");
        while(crt){
            printf("%s: %g   ", crt->Module, crt->point);
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
