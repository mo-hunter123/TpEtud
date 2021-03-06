#define MAX_ET 11
#define MAX_MOD 13


//Note *notesEt[13]; 13: nombre des modules 

typedef struct Cel{
    float point; //point de module
    struct Inf *INfos; //informations d'etudiant 
    struct Cel *svt; //la note suivante dans le module
}Note; //nom de la structure 


//Etudiant* EtudInfo[26][10] 26: nombre des lettres, 10 cas pour le dernier caractere de cne

typedef struct Inf{
    char CNE[11]; //Cne de l'etudiant 
    char Date_naiss[12]; //sa date de naissance 
    Note *modules[13]; //ses modules 
    struct NP *nom; //son nom complet sur la base de donnees des noms 
    struct Inf *next; //l'etudiant suivant 
}Etudiant; //nom de la structure 

//NomEtu* nomsets[26] 26: nombre des cas pour la premiere lettre d'un nom 

typedef struct NP{
    char Nom[20]; //nom de l'etudiant 
    char Prenom[20]; //son prenom 
    Etudiant *infoEtu; //les informations de l'etudiant
    struct NP *svt; //l'etudiant suivant 
}NomEtu; //nom de la structure 


int InitEnsembles(Etudiant *MaTable[26][10], NomEtu* NomSets[26], Note *NoteEt[MAX_MOD]);
int Cle_Etud_cne(char Nom[20]);
int Cle_Etud(int *ind1, int *ind2, char CNE[20]);
Note * creerCelNote();
NomEtu * creerCelNom();
Etudiant * creerCelEtud();
Note * insertionNote(Note *liste, Note *elem);
NomEtu * insertionNom(NomEtu *liste, NomEtu *elem);
Etudiant * insertionInf(Etudiant *liste, Etudiant *elem);
void Affichage_ordre_merite(int codeModule, Note *NoteEt[MAX_MOD]);
void Affichage_ordre_alpha(NomEtu *NomSet[26]);
int Non_valide_module(int codeModule, Note *NoteSet[13]);
int Valide_un_module(int codeModule, Note *NoteSet[13]);
void statistique_sur_module(int codeModule, Note *NoteSet[13]);
void chargementDonnes(NomEtu *nomsets[26],Note *notesEt[13],Etudiant* ets[26][10], FILE *f);
void dechargementDonnes(NomEtu *nomsets[26]);
void saisieDeDonnes(NomEtu *nomsets[26],Note *notesEt[13],Etudiant* ets[26][10]);