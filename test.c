
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ET 11
#define MAX_MOD 13

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


#define ModulesAnnee[][] = 
    {
        "Algo", 
        "Sdd", 
        "BD", 
        "SE", 
        "Archi", 
        "TECH", 
        "Reseaux", 
        "Web", 
        "Conce", 
        "UML", 
        "Droit", 
        "Eco"
    };


typedef struct Cel{
    float point;
    Etudiant *INfos;
    struct Cel *svt;
}Note;

//Note *notesEt[13]; 13: nombre des modules 

typedef struct Inf{
    char CNE[11];
    char Date_naiss[12];
    Note *modules[13];
    NomEtu *nom;
    struct Inf *next;
}Etudiant;

//Etudiant* ets[26][10] 26: nombre des lettres, 10 cas pour le dernier caractere de cne

typedef struct NP{
    char Nom[20];
    char Prenom[20];
    Etudiant *infoEtu;
    struct NP *next;
}NomEtu;

//NomEtu* nomsets[26] 26: nombre des cas pour la premiere lettre d'un nom 

int InitEnsembles(Etudiant *MaTable[26][10], NomEtu* NomSets[26], Note *NoteEt[MAX_MOD])
{
    int i, j;
    //initialisation pour la base des etudiants 
    //et base des Noms 
    for(i = 0; i<26; i++)
    {
        NomSets[i] = NULL;
        for(j = 0; j<10; j++)
        {
            MaTable[i][j] = NULL;
        }
    }
    //initialisation de base des Notes 
    for(i = 0; i<MAX_MOD; i++)
    {
        NoteEt[i] = NULL;
    }

    return ((int)1);
}


//NomEtu *nomsets[26]
int Cle_Etud_cne(char Nom[20]
{
    return ((int) 'z'-Nom[0]);
}

int Cle_Etud(int *ind1, int *ind2, char CNE[20]){
    if(sizeof(CNE) != 10){
        printf("\nErr avec le CNE\n");
        return ((int)-1);
    }

    *ind1 = 'Z' - CNE[0];
    *ind2 = '9' - CNE[9] + 1;
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


// int InsertionPoint()
// insertion note 
Note * insertionNote(Note *liste, Note *elem)
{
    Note *crt=NULL;
    if(!liste) return((Note*)elem);
    if (elem->point > liste->point)
    {
        elem->svt = liste;
        return((Note *)elem); 
    }
    crt = liste;
    while(crt->svt)
    {
        if(elem->point > crt->svt->point)
        {
            elem->svt = crt->svt;
            crt->svt = elem;
            return((Note*)liste);
        }
        crt = crt->svt;
    } 
    crt->svt = elem;
    return((Note*)liste);
}

// insertion nom 
NomEtu * insertionNom(NomEtu *liste, NomEtu *elem)
{
    NomEtu *crt=NULL;
    if(!liste) return((NomEtu*)elem);
    if (strcmp(elem->Nom,liste->Nom) > 0)
    {
        elem->next = liste;
        return((NomEtu*)elem); 
    }
    crt = liste;
    while(crt->svt)
    {
        if(strcmp(elem->Nom,liste->Nom) > 0)
        {
            elem->svt = crt->svt;
            crt->svt = elem;
            return((NomEtu*)liste);
        }
        crt = crt->svt;
    } 
    crt->svt = elem;
    return((NomEtu*)liste);
} 
// int InsertionPoint()
// insertion note 
Note * insertionNote(Note *liste, Note *elem)
{
    Note *crt=NULL;
    if(!liste) return((Note*)elem);
    if (elem->point > liste->point)
    {
        elem->svt = liste;
        return((Note *)elem); 
    }
    crt = liste;
    while(crt->svt)
    {
        if(elem->point > crt->svt->point)
        {
            elem->svt = crt->svt;
            crt->svt = elem;
            return((Note*)liste);
        }
        crt = crt->svt;
    } 
    crt->svt = elem;
    return((Note*)liste);
}

// insertion nom 
NomEtu * insertionNom(NomEtu *liste, NomEtu *elem)
{
    NomEtu *crt=NULL;
    if(!liste) return((NomEtu*)elem);
    if (strcmp(elem->Nom,liste->Nom) > 0)
    {
        elem->next = liste;
        return((NomEtu*)elem); 
    }
    crt = liste;
    while(crt->svt)
    {
        if(strcmp(elem->Nom,liste->Nom) > 0)
        {
            elem->svt = crt->svt;
            crt->svt = elem;
            return((NomEtu*)liste);
        }
        crt = crt->svt;
    } 
    crt->svt = elem;
    return((NomEtu*)liste);
} 

// insertion nom 
Etudiant * insertionInf(Etudiant *liste, Etudiant *elem)
{
    elem->next = liste;
    return((NomEtu*)elem); 
} 
 

void Affichage_ordre_merite(Note *NoteEt[MAX_MOD])
{
    printf("\nCNE\tNOM\tPRENOM\tMODULE\tNOTE\n");
    
    int i= 0;
    for(i = 0; i<12; i++)
    {
        printf("%c\t%c\t%c\t%c\t%c\n", NoteEt->)
    }
}


int main(int argc, char const *argv[])
{
    FILE* fptr; 
    fptr = fopen("Etudiants/Etudiants.txt", "r");
    if(!fptr){
        printf("ERR");
        exit(-1);
    }

    fclose(fptr);
    printf("\n");

    return 0;
}
