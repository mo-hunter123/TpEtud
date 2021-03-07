#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Etud.h"



int main(int argc, char const *argv[])
{
    char ModulesAnnee[13][8] =  {"Algo", "Sdd", "BD", "SE", "Archi", "TECH", "Reseaux", "Web", "Conce", "UML", "Droit", "Eco", "MoyGen"};
    int choix1,choix2,indice;
    Etudiant *MaTable[26][10]; 
    NomEtu* NomSets[26];
    Note *NoteEt[MAX_MOD];
    InitEnsembles(MaTable, NomSets, NoteEt);
    chargementDonnes(NomSets, NoteEt, MaTable);
    printf("====== Base d'informations des etudiants ======\n\n");
    while(1){
        printf("============= Ecran Principal =============\n\n");
        printf("\t1 : Afficher par ordre alphabetique\n");
        printf("\t2 : Afficher par ordre de merite\n");
        printf("\t3 : Ajouter des etudiants\n");
        printf("\t\t0 : Quitter\n");
        printf("===========================================\n\n");
        printf(" Donnez votre choix : ");
        scanf("%d",&choix1);
            switch(choix1){
            case 1: system("clear");
                    Affichage_ordre_alpha(NomSets);
                    system("read -n1 -r -p 'Continuer ...'");system("clear");break;
            case 2: system("clear");
                    printf("============= Modules =============\n\n");
                    for (indice = 0; indice < 13; indice++)
                         printf("\t%d : %s\n",indice+1,ModulesAnnee[indice]);
                    printf("===========================================\n\n");
                    printf(" Donnez votre choix : ");
                    scanf("%d",&choix2);
                    system("clear");
                    Affichage_ordre_merite(choix2-1, NoteEt);
                    system("read -n1 -r -p 'Continuer ...'"); 
                    system("clear");break;
            case 3: system("clear");
                    saisieDeDonnes(NomSets,NoteEt,MaTable);
                    system("read -n1 -r -p 'Continuer ...'"); 
                    system("clear");break;
            default: system("clear");
                     printf("\n Dechargement en cours");
                     dechargementDonnes(NomSets);
                     system("clear");
                     exit(-1);
        }
    }
    return 0;
}
