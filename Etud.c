#include "Etud.h"

char ModulesAnnee[13][8] =  {"Algo", "Sdd", "BD", "SE", "Archi", "TECH", "Reseaux", "Web", "Conce", "UML", "Droit", "Eco", "MoyGen"};

/******************************************************
>_Nom:          InitEnsembles.
>_Entree:       Notre base toute entière.
>_Sortie:       Base initialisée.
>_Description:  La fonction permet d’initialiser 
                les différents pointeurs de notre base.
******************************************************/
int InitEnsembles   (Etudiant *MaTable[26][10]
                    ,NomEtu* NomSets[26]
                    ,Note *NoteEt[MAX_MOD]
                    )
{
    int i, j;
    //initialisation pour 
    //la base des étudiants et la base des Noms 
    for(i = 0; i<26; i++)
    {
        NomSets[i] = NULL;
        for(j = 0; j<10; j++)
            MaTable[i][j] = NULL; 
    }
    //initialisation de base des Notes 
    for(i = 0; i<MAX_MOD; i++)
        NoteEt[i] = NULL;
    return ((int)1);
}
/*****************************************************/


/******************************************************
>_Nom:          chargementDonnes.
>_Entree:       Notre base toute entière.
>_Sortie:       Base remplie.
>_Description:  La fonction permet de charger 
                les données depuis les fichiers 
                vers notre structure.
******************************************************/
void chargementDonnes     (NomEtu *nomsets[26]
,Note *notesEt[13]
,Etudiant* ets[26][10]
)
{
    // pointeurs sur les structures
    Etudiant *pEtud=NULL;
    Note *pNote=NULL;
    NomEtu *pNom=NULL;
    // pointeurs sur le fichier des information et celui des notes
    FILE *fnotes=NULL, *f=NULL;
    // tableau pour stocker le chemin du fichier des notes
    char nomFichier[100];
    int indice, clefNom, clef1Etud, clef2Etud;
    // ouvrir le fichier Etudiants.txt en mode lecture
    f = fopen("Etudiants/Etudiants.txt", "r");
    if(!f)
    {
        printf("Erreur de chargement du fichier Etudiants.txt");
        exit(-1);
    }
    // tant qu'on a pas atteint la fin du fichier
    fgetc(f);
    while(!feof(f))
    {
        // créer des nouveaux cellules
        pEtud = creerCelEtud();
        pNom  = creerCelNom();
        // créer des cellules pour chaque module et celle de la moyenne
        for ( indice = 0; indice < 13; indice++)
        {
            pEtud->modules[indice] = creerCelNote();
            pEtud->modules[indice]->svt = NULL;
            // éditer le lien avec l'étudiant correspondant
            pEtud->modules[indice]->INfos = pEtud;
        }
        // lien de Etudiant vers Nom
        pEtud->nom = pNom;
        // lien de Nom vers Etudiant
        pNom->infoEtu = pEtud;
        pEtud->next = NULL;
        pNom->svt = NULL;
        // lire la ligne depuis le fichier 
        fscanf(f,"%s\t%s\t%s\t%s",pEtud->CNE,pNom->Nom,pNom->Prenom,pEtud->Date_naiss);
        // constituer le chemin du fichier des notes
        strcpy(nomFichier,"Note/");
        strcat(nomFichier,pEtud->CNE);
        strcat(nomFichier,".txt");
        printf("%s\n",nomFichier);
        // ouverture du fichier des notes
        fnotes = fopen(nomFichier,"r");
        if(!fnotes)
        {
            printf("Erreur de chargement du fichier %s.txt",pEtud->CNE);
            exit(-1);
        }
        // lecture des notes
        for (indice = 0; indice < 13; indice++)
        {
            fscanf(fnotes,"%f",&pEtud->modules[indice]->point);
            // insertion de la note dans la bonne place
            notesEt[indice]=insertionNote(notesEt[indice],pEtud->modules[indice]); 
        }
        // fermeture du fichier des notes    
        fclose(fnotes);
        // génération des clefs pour insertion
        clefNom = Cle_Etud_cne(pNom->Nom);
        Cle_Etud(&clef1Etud,&clef2Etud,pEtud->CNE);
        // insertion des cellules dans la bonne place 
        nomsets[clefNom]=insertionNom(nomsets[clefNom],pNom);
        ets[clef1Etud][clef2Etud] = insertionInf(ets[clef1Etud][clef2Etud],pEtud);
    }
    fclose(f);
}
/*****************************************************/

/******************************************************
>_Nom:          creerCelNote,creerCelNom,creerCelEtud.
>_Entree:       Aucune.
>_Sortie:       Pointeurs sur les cellules.
>_Description:  La fonction permet de réserver un espace mémoire de cellules.
******************************************************/
Note * creerCelNote()
{
    //création de la cellule d'une note 
    Note *ptr;
    //réservation d'espace 
    ptr = (Note*)malloc(sizeof(Note));
    if(!ptr) //erreur d'allocation 
    {
        printf("Pas Assez de mémoire");
        exit(-1);
    }
    return((Note*)ptr);
}
/*****************************************************/
NomEtu * creerCelNom()
{
    //création de la cellule d'un nom
    NomEtu *ptr;
    //réservation d'espace 
    ptr = (NomEtu*)malloc(sizeof(NomEtu));
    if(!ptr) //erreur d'allocation 
    {
        printf("Pas Assez de mémoire");
        exit(-1);
    }
    return((NomEtu*)ptr);
}
/*****************************************************/
Etudiant * creerCelEtud()
{
    int indice;
    //création de la cellule d'un nom
    Etudiant *ptr;
    //réservation d'espace 
    ptr = (Etudiant*)malloc(sizeof(Etudiant));
    if(!ptr)//erreur d'allocation
    {
        printf("Pas Assez de mémoire");
        exit(-1);
    }
    return((Etudiant*)ptr);
}
/*****************************************************/

/******************************************************
>_Nom:          insertionNote.
>_Entree:       La liste et la cellule à insérer.
>_Sortie:       La nouvelle liste.
>_Description:  La fonction permet d'insérer 
                une cellule de note à la bonne place 
                dans une liste.
******************************************************/
Note * insertionNote(Note *liste, Note *elem)
{
    //le courant 
    Note *crt = NULL;
    //si la liste est vide on retourne l'élément à insérer 
    if(!liste) 
        return((Note*)elem);
    
    //insertion d'élément si la valeur 
    if (elem->point > liste->point)
    {
        elem->svt = liste; //insertion si elem > la tête
        return((Note *)elem); 
    }
    //on parcours la liste  
    crt = liste;
    //tant que la liste contient des éléments 
    while(crt->svt)
    {
        //on insère par ordre 
        if(elem->point > crt->svt->point)
        {
            elem->svt = crt->svt;
            crt->svt = elem;
            return((Note*)liste);
        }
        //on avance le pointeur 
        crt = crt->svt;
    } 
    //si on atteint la fin 
    crt->svt = elem;
    return((Note*)liste);
}

/*****************************************************/

/******************************************************
>_Nom:          insertionNom.
>_Entree:       La liste et la cellule à insérer.
>_Sortie:       La nouvelle liste.
>_Description:  La fonction permet d'insérer une cellule 
                de nom à la bonne place dans une liste.
******************************************************/
NomEtu * insertionNom(NomEtu *liste, NomEtu *elem)
{

    NomEtu *crt = NULL;
    //si la liste est vide 
    if(!liste) 
        return((NomEtu*)elem);
    
    //si le nom est < la tête 
    if (strcmp(elem->Nom,liste->Nom) < 0)
    {
        elem->svt = liste;
        return((NomEtu*)elem); 
    }
    //on parcours la liste des noms 
    crt = liste;
    //tant qu'on a des étudiants 
    while(crt->svt)
    {
        //on insère si on a la condition 
        if(strcmp(elem->Nom,crt->svt->Nom) < 0)
        {
            elem->svt = crt->svt;
            crt->svt = elem;
            return((NomEtu*)liste);
        }
        crt = crt->svt;
    } 
    //insertion à la fin si elle est nécessaire 
    crt->svt = elem;
    return((NomEtu*)liste);
}


/*****************************************************/

/******************************************************
>_Nom:          insertionInf.
>_Entree:       La liste et la cellule à insérer.
>_Sortie:       La nouvelle liste.
>_Description:  La fonction permet d'insérer une cellule 
                Etudiant au début d’une liste.
******************************************************/
Etudiant * insertionInf(Etudiant *liste, Etudiant *elem)
{
    //Insertion au début
    elem->next = liste;
    return((Etudiant*)elem); 
}
/*****************************************************/

/******************************************************
>_Nom:          Cle_Etud_cne.
>_Entree:       Un Nom.
>_Sortie:       Sa clé correspondante.
>_Description:  La fonction permet de générer la clé 
                pour accéder à la liste où 
                se trouve le nom.
******************************************************/
int Cle_Etud_cne(char Nom[20])
{   
    //retourner l'indice de premier caractère 
    return ((int) (Nom[0] - 'A'));
}
/*****************************************************/

/******************************************************
>_Nom:          Cle_Etud.
>_Entree:       Un CNE.
>_Sortie:       Sa clé correspondante.
>_Description:  La fonction permet de générer la clé 
                pour accéder à la liste où 
                se trouve le CNE.
******************************************************/
int Cle_Etud(int *ind1, int *ind2, char CNE[11])
{
    *ind1 = CNE[0] - 'A'; //avoir le premier indice 
    *ind2 = (CNE[9] + 1) - '0'; //avoir le 2eme indice 
    return ((int)1);
}

/*****************************************************/


/******************************************************
>_Nom:          saisieDeDonnes.
>_Entree:       Les informations relatives à un étudiant.
>_Sortie:       Ajout des informations dans la base.
>_Description:  La fonction permet à l’utilisateur 
                d’entrer manuellement des informations 
                d’un nouvel étudiant dans 
                la base d’information.
******************************************************/
void saisieDeDonnes (NomEtu *nomsets[26]
                    ,Note *notesEt[13]
                    ,Etudiant* ets[26][10]
                    )
{
    // pointeurs sur les cellules
    Etudiant *pEtud=NULL;
    Note *pNote=NULL;
    NomEtu *pNom=NULL;
    // somme qui sera utilisé pour le calcule de la moyenne
    float somme=0.0;
    char nomFichier[100];
    int indice,indice2,clefNom,clef1Etud,clef2Etud,nbEtud;
    printf("Combien d'etudiants vous voulez ajouter : ");
    scanf("%d",&nbEtud);
    for( indice2 = 0; indice2 < nbEtud; indice2++)
    {
        // création des cellules
        pEtud = creerCelEtud();
        pNom  = creerCelNom();
        for ( indice = 0; indice < 13; indice++)
        {
            pEtud->modules[indice] = creerCelNote();
            pEtud->modules[indice]->svt = NULL;
            pEtud->modules[indice]->INfos = pEtud;
        }
        // edition des liens
        pEtud->nom = pNom;
        pNom->infoEtu = pEtud;
        pEtud->next = NULL;
        pNom->svt = NULL;
        // remplissage des données
        printf("\nInformation de l'etudiant %d :\n",indice2);

        printf("Entrer le CNE : ");
        scanf("%s",pEtud->CNE);
        printf("Entrer le Nom : ");
        scanf("%s",pNom->Nom);
        printf("Entrer le Prenom : ");
        scanf("%s",pNom->Prenom);
        printf("Entrer la date de naissance (DD-MM-YYYY) : ");
        scanf("%s",pEtud->Date_naiss);
        // remplissage des notes
        for (indice = 0; indice < 12; indice++)
        {
            printf("Entrer la note du module %s : ",ModulesAnnee[indice]);
            scanf("%f",&pEtud->modules[indice]->point);
            somme += pEtud->modules[indice]->point;
            notesEt[indice]=insertionNote(notesEt[indice],pEtud->modules[indice]);
        }
        // calcule de la moyenne et son insertion
        pEtud->modules[12]->point = somme/(float)12;
        clefNom = Cle_Etud_cne(pNom->Nom);
        Cle_Etud(&clef1Etud,&clef2Etud,pEtud->CNE);
        nomsets[clefNom]=insertionNom(nomsets[clefNom],pNom);
        ets[clef1Etud][clef2Etud] = insertionInf(ets[clef1Etud][clef2Etud],pEtud);
    }
}
/*****************************************************/
/******************************************************
>_Nom:          Affichage_ordre_merite.
>_Entree:       code module à traiter et la base 
                des notes.
>_Sortie:       affichage des résultats par ordre 
                de mérite.
>_Description:  La fonction permet d’afficher 
                les résultats liant à un module 
                par ordre de mérite.
******************************************************/
void Affichage_ordre_merite(int codeModule, Note *NoteEt[MAX_MOD])
{
    printf("+================+==============+=============+==================+==================+\n");
    printf("|      CNE       |     Nom      |   Prenom    |      Module      |       Note       |\n");
    printf("+================+==============+=============+==================+==================+\n");
    
    //on parcours la liste des notes
    Note* crt = NoteEt[codeModule];
    while (crt)
    {
        printf("| %1s     | %-11.25s  | %-11.25s |   %11s    |     %10g   |\n", crt->INfos->CNE, crt->INfos->nom->Nom, crt->INfos->nom->Prenom, ModulesAnnee[codeModule], crt->point);
        crt = crt->svt;
    }
    printf("+================+==============+=============+==================+==================+\n");
}


/*****************************************************/

/******************************************************
>_Nom:          ffichage_ordre_alpha.
>_Entree:       base des noms.
>_Sortie:       affichage des étudiants 
                par ordre alphabétique.
>_Description:  La fonction permet d’afficher 
                les informations sur les étudiants 
                par ordre alphabétique.
******************************************************/
void Affichage_ordre_alpha(NomEtu *NomSet[26])
{
    int i = 0;

    printf("+=================+==============+=================+\n");
    printf("|      CNE        |     Nom      |      Prenom     |\n");
    printf("+=================+==============+=================+\n");

    //parcours la base des Noms 
    NomEtu* crt;
    for(i = 0; i<26; i++)
    {
        crt = NomSet[i]; //la liste à afficher 
        while (crt)
        {
         printf("| %11s  | %-11.25s  | %11s   |\n", crt->infoEtu->CNE,                                     crt->Nom, crt->Prenom);
            crt = crt->svt;
        }
    }//fin de for 
    printf("+=================+==============+=================+\n");

}
/*****************************************************/


/******************************************************

>_Nom:          Non_valide_module.
>_Entree:       code de module et la base des notes.
>_Sortie:       nombre d' étudiants qui ont raté 
                leur module.
>_Description:  La fonction permet de calculer 
                le nombre d'étudiants qui n’ont 
                pas validé leur module.
******************************************************/
int Non_valide_module(int codeModule, Note *NoteSet[13])
{
    //on parcours la liste de module 
    Note *crt = NoteSet[codeModule];
    int Nombre = 0; 
    while (crt)
    {
        //on calcule le nombre des gens qui ont rater leur module 
        if(crt->point < 12)
            Nombre++;
        crt = crt->svt;//on passe au suivant 
    }
    return ((int)Nombre);
}//fin de la fonction 
/*****************************************************/


/******************************************************
>_Nom:          Valide_module.
>_Entree:       code de module et la base des notes.
>_Sortie:       Nombre d' étudiants qui ont validé 
                leur module.
>_Description:  a fonction permet de calculer le nombre 
                d'étudiants qui ont bien validé 
                leur module.
******************************************************/
int Valide_un_module(int codeModule, Note *NoteSet[13])
{
    //13 si vous voulez la note générale 
    Note *crt = NoteSet[codeModule];
    int Nombre = 0;
    while (crt)
    {   
        //si la note est sup a 12 on incrémente
        //le nombre des étudiants 
        if(crt->point >= 12)
            Nombre ++;
        crt = crt->svt;
    }
    return ((int)Nombre);
}
/*****************************************************/

/******************************************************
>_Nom:          Valide_module.
>_Entree:       code de module et la base des notes.
>_Sortie:       nombre d' étudiants qui ont validé 
                leur module.
>_Description:  La fonction permet de calculer 
                le nombre d'étudiants qui ont bien 
                validé leur module.
******************************************************/
void dechargementDonnes(NomEtu *nomsets[26])
{
    /*
    le déchargement se fait en enregistrant la base de données 
    en ordre croissant dans le fichier Etudiant.txt donc
    on aura besoin seulement de l'accès depuis la base des noms
    et grâce à la liaison entres les cellules on peut trouver
    les autres informations facilement  
    */
   // pointeur de parcours
    NomEtu *pNom=NULL;
    int indice,indice2;
    // pointeurs sur les fichiers
    FILE *f=NULL, *fnotes=NULL;
    // chaine pour stocker le chemin du fichier
    char nomFichier[100];
    // ouvrir Etudiants.txt en mode edition
    f = fopen("Etudiants/Etudiants.txt", "w");
    if(!f)
    {
        printf("Erreur de chargement du fichier Etudiants.txt");
        exit(-1);
    }
    // parcours de la base des noms 
    for(indice2=0 ; indice2 < 26 ; indice2++)
    {
        // parcours de la liste de chaque lettre
        pNom = nomsets[indice2];
        // tant qu'il y a des cellules
        while(pNom)
        {
            // écrire les infos relatives à l'étudiant
            fprintf(f,"\n%s\t%s\t%s\t%s",pNom->infoEtu->CNE,pNom->Nom,pNom->Prenom,pNom->infoEtu->Date_naiss);
            // constituer le nom du fichier des notes
            strcpy(nomFichier,"Note/");
            strcat(nomFichier,pNom->infoEtu->CNE);
            strcat(nomFichier,".txt");
            // ouvrir le fichier des notes en mode édition 
            fnotes = fopen(nomFichier,"w");
            if(!fnotes)
            {
                printf("Erreur de chargement du fichier %s.txt",pNom->infoEtu->CNE);
                exit(-1);
            }
            // écriture des notes
            for (indice = 0; indice < 13; indice++)
                fprintf(fnotes,"%g\n",pNom->infoEtu->modules[indice]->point);
            fclose(fnotes);
            // passage à la cellule suivante
            pNom = pNom->svt; 
        }
    }
    // fermeture du fichier 
    fclose(f);
}

/*****************************************************/