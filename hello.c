
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hello.h"

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


char ModulesAnnee[12][8] =  { "Algo", "Sdd", "BD", "SE", "Archi", "TECH", "Reseaux", "Web", "Conce", "UML", "Droit", "Eco"};


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

int Cle_Etud(int *ind1, int *ind2, char CNE[11]){
    if(sizeof(CNE) != 10){
        printf("\nErr avec le CNE\n");
        return ((int)-1);
    }

    *ind1 = 'Z' - CNE[0];
    *ind2 = '9' - CNE[9] + 1;
    return ((int)1);
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
    return((NomEtu*)elem); 
} 

Note * creerCelNote()
{
    Note *ptr;
    ptr = (Note*)malloc(sizeof(Note));
    if(!ptr)
    {
        printf("Pas Assez de memoire");
        exit(-1);
    }
    return((Note*)ptr);
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



void Affichage_ordre_merite(Note *NoteEt[MAX_MOD])
{
    printf("\nCNE\tNOM\tPRENOM\tMODULE\tNOTE\n");
    
    int i= 0;
    for(i = 0; i<12; i++)
    {
        printf("%c\t%c\t%c\t%c\t%c\n");
    }
}

void chargementDonnes(NomEtu *nomsets[26],Note *notesEt[13],Etudiant* ets[26][10])
{
    Etudiant *pEtud=NULL;
    Note *pNote=NULL;
    NomEtu *pNom=NULL;
    FILE *f=NULL, *fnotes=NULL;
    char nomFichier[100];
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
        stat = fscanf(f,"%s\t%s\t%s\t%s"
                    ,pEtud->CNE,pNom->Nom,pNom->Prenom,pEtud->Date_naiss
                    );
        strcpy(nomFichier,"Note\\");
        strcat(nomFichier,pEtud->CNE);
        strcat(nomFichier,".txt");
        fnotes = fopen(nomFichier,"r");
        if(!fnotes)
        {
            printf("Erreur de chargement du fichier %s.txt",pEtud->CNE,);
            exit(-1);
        }
        for (indice = 0; indice < 13; indice++)
        {
           fscanf(fnotes,"%f",pEtud->modules[indice]->point);
            notesEt[indice]=insertionNote(notesEt[indice],pEtud->modules[indice]); 
        }
            
        fclose(fnotes);

        clefNom = Cle_Etud_cne(pNom->Nom);
        Cle_Etud(&clef1Etud,&clef2Etud,pEtud->CNE);
        nomsets[clefNom]=insertionNom(nomsets[clefNom],pNom);
        ets[clef1Etud][clef2Etud] = insertionInf(ets[clef1Etud][clef2Etud],pEtud);
    }
    fclose(f);
}

void dechargementDonnes(NomEtu *nomsets[26])
{
    NomEtu *pNom=NULL;
    int indice;
    FILE *f=NULL, *fnotes=NULL;
    char nomFichier[100];
    f = fopen("Etudiants/Etudiants.txt", "w");
    if(!f)
    {
        printf("Erreur de chargement du fichier Etudiants.txt");
        exit(-1);
    }
    for(indice=0 ; indice < 26 ; indice++)
    {
        pNom = nomsets[indice];
        while(pNom)
        {
            fprintf(f,"%s\t%s\t%s\t%s\n"
                    ,pNom->infoEtu->CNE,pNom->Nom,pNom->Prenom,pNom->infoEtu->Date_naiss
                    );
            strcpy(nomFichier,"Note\\");
            strcat(nomFichier,pNom->infoEtu->CNE);
            strcat(nomFichier,".txt");
            fnotes = fopen(nomFichier,"w");
            if(!fnotes)
            {
                printf("Erreur de chargement du fichier %s.txt",pNom->infoEtu->CNE);
                exit(-1);
            }
            for (indice = 0; indice < 13; indice++)
                fscanf(fnotes,"%f\n",pNom->infoEtu->modules[indice]->point);
            fclose(fnotes);
            pNom = pNom->svt; 
        }
    }
    fclose(f);
}

void saisieDeDonnes(NomEtu *nomsets[26],Note *notesEt[13],Etudiant* ets[26][10])
{
    Etudiant *pEtud=NULL;
    Note *pNote=NULL;
    NomEtu *pNom=NULL;
    char nomFichier[100];
    int indice,clefNom,clef1Etud,clef2Etud,nbEtud;
    printf("Combien d'etudiants vous voulez ajouter : ");
    scanf("%d",&nbEtud);
    for( indice = 0; indice < nbEtud; indice++)
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

        printf("Entrer le CNE : ");
        scanf("%s",pEtud->CNE);
        printf("Entrer le Nom : ");
        scanf("%s",pNom->Nom);
        printf("Entrer le Prenom : ");
        scanf("%s",pNom->Prenom);
        printf("Entrer la date de naissance (DD-MM-YYYY) : ");
        scanf("%s",pEtud->Date_naiss);
        for (indice = 0; indice < 12; indice++)
        {
            printf("Entrer la note du module %s : ",ModulesAnnee[indice]);
            scanf("%f",pEtud->modules[indice]->point);
            notesEt[indice]=insertionNote(notesEt[indice],pEtud->modules[indice]);
        }
        clefNom = Cle_Etud_cne(pNom->Nom);
        Cle_Etud(&clef1Etud,&clef2Etud,pEtud->CNE);
        nomsets[clefNom]=insertionNom(nomsets[clefNom],pNom);
        ets[clef1Etud][clef2Etud] = insertionInf(ets[clef1Etud][clef2Etud],pEtud);
    }
    
  

}

int main(int argc, char const *argv[])
{
    // FILE* fptr; 
    // fptr = fopen("Etudiants/Etudiants.txt", "r");
    // if(!fptr){
    //     printf("ERR");
    //     exit(-1);
    // }

    // fclose(fptr);
    // printf("\n");

    return 0;
}