#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hello.h"

// #define MAX_ET 11
// #define MAX_MOD 13

char ModulesAnnee[13][8] =  {"Algo", "Sdd", "BD", "SE", "Archi", "TECH", "Reseaux", "Web", "Conce", "UML", "Droit", "Eco", "MoyGen"};

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
int Cle_Etud_cne(char Nom[20])
{
    return ((int) 'z'-Nom[0]);
}

int Cle_Etud(int *ind1, int *ind2, char CNE[20]){
    if(strlen(CNE) != 10){
        printf("\nErr avec le CNE\n");
        return ((int)-1);
    }

    *ind1 = 'Z' - CNE[0];
    *ind2 = '9' - CNE[9] + 1;
    return ((int)1);
}

Note* creerCelNote(){
    Note* NewNote = (Note*)malloc(sizeof(Note));
    if(!NewNote){
        printf("\nErr d'allocation\n");
        exit(-1);
    }
    return NewNote;
    
}


NomEtu * creerCelNom()
{
    NomEtu *ptr;
    ptr = (NomEtu*)malloc(sizeof(NomEtu));
    if(!ptr)
    {
        printf("Pas Assez de memoire");
        exit(-1);
    }

    return((NomEtu*)ptr);
}


Etudiant * creerCelEtud()
{
    Etudiant *ptr;
    ptr = (Etudiant*)malloc(sizeof(Etudiant));
    if(!ptr)
    {
        printf("Pas Assez de memoire");
        exit(-1);
    }
    return((Etudiant*)ptr);
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
        elem->svt = liste;
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
    return((Etudiant*)elem); 
} 

 
void Affichage_ordre_merite(int codeModule, Note *NoteEt[MAX_MOD])
{
    printf("\nCNE\tNOM\tPRENOM\tMODULE\tNOTE\n");
    
    Note* crt = NoteEt[codeModule];
    while (crt)
    {
        printf("%s\t%s\t%s\t%s\t%g", crt->INfos->CNE, crt->INfos->nom->Nom, crt->INfos->nom->Prenom, ModulesAnnee[codeModule], crt->point);
        crt = crt->svt;
    }
}

void Affichage_ordre_alpha(NomEtu *NomSet[26]){
    int i = 0;
    printf("\nCNE\tNom\tPrenom\t\n");
    for(i = 0; i<26; i++){
        NomEtu* crt = NomSet[i];
        while (crt)
        {
            printf("%s\t%s\t%s\n", crt->infoEtu->CNE, crt->Nom, crt->Prenom);
            crt = crt->svt;
        }
    }
}

int Non_valide_module(int codeModule, Note *NoteSet[13]){
    Note *crt = NoteSet[codeModule];
    int Nombre = 0; 
    while (crt)
    {
        if(crt->point < 12)
            Nombre++;
        crt = crt->svt;
    }
    return ((int)Nombre);
}

int Valide_un_module(int codeModule, Note *NoteSet[13]){
    //13 si vous voulez la note generale 
    Note *crt = NoteSet[codeModule];
    int Nombre = 0;
    while (crt)
    {   
        //si la note est sup a 12 on incremente
        //le nombre des etudiants 
        if(crt->point >= 12)
            Nombre ++;
        crt = crt->svt;
    }
    return ((int)Nombre);
}



void statistique_sur_module(int codeModule, Note *NoteSet[13]){
    int Valide = Valide_un_module(codeModule, NoteSet);
    int NValide = Non_valide_module(codeModule, NoteSet);
    if(codeModule != 12){
        printf("\nModule de %s: valide= %d non valide= %d f \n", ModulesAnnee[codeModule], Valide, NValide);
        return;
    }
    printf("\nStatistique sur la moyenne generale\n==> %d valide, et %d Non valide leur annee\n", Valide, NValide);

    return;
    
}

//affichages




void chargementDonnes(NomEtu *nomsets[26],Note *notesEt[13],Etudiant* ets[26][10])
{
    Etudiant *pEtud=NULL;
    Note *pNote=NULL;
    NomEtu *pNom=NULL;
    FILE * f=NULL;
    int stat = 1,indice,clefNom,clef1Etud,clef2Etud;
    f = fopen("Etudiants/Etudiants.txt", "r");
    if(!f)
    {
        printf("Erreur de chargement du fichier Etudiants.txt");
        exit(-1);
    }
    while(stat != EOF)
    {
        pEtud = creerCelEtud();
        pNom  = creerCelNom();
        for ( indice = 0; indice < 13; indice++)
        {
            pEtud->modules[indice] = creerCelNote();
            pEtud->modules[indice]->svt = NULL;
            pEtud->modules[indice]->INfos = pEtud;
        }
        pEtud->nom = pNom;
        pNom->infoEtu = pEtud;
        pEtud->next = pNom->svt = NULL;
        stat = fscanf(f,"%s\t%s\t%s\t%s\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f"
                ,pEtud->CNE,pNom->Nom,pNom->Prenom,pEtud->Date_naiss,pEtud->modules[0]->point
                ,pEtud->modules[1]->point
                ,pEtud->modules[2]->point,pEtud->modules[3]->point,pEtud->modules[4]->point
                ,pEtud->modules[5]->point,pEtud->modules[6]->point,pEtud->modules[7]->point
                ,pEtud->modules[8]->point,pEtud->modules[9]->point,pEtud->modules[10]->point
                ,pEtud->modules[11]->point,pEtud->modules[12]->point
                );
        for ( indice = 0; indice < 13; indice++)
            notesEt[indice]=insertionNote(notesEt[indice],pEtud->modules[indice]);
        clefNom = Cle_Etud_cne(pNom->Nom);
        Cle_Etud(&clef1Etud,&clef2Etud, pEtud->CNE);
        nomsets[clefNom]=insertionNom(nomsets[clefNom],pNom);
        ets[clef1Etud][clef2Etud] = insertionInf(ets[clef1Etud][clef2Etud],pEtud);
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

    // chargementDonnes()
    fclose(fptr);
    printf("\n");

    return 0;
}