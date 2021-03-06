typedef struct Cel{
    float point;
    struct Inf *INfos;
    struct Cel *svt;
}Note;

//Note *notesEt[13]; 13: nombre des modules 

typedef struct Inf{
    char CNE[11];
    char Date_naiss[12];
    Note *modules[13];
    struct NP *nom;
    struct Inf *next;
}Etudiant;

//Etudiant* ets[26][10] 26: nombre des lettres, 10 cas pour le dernier caractere de cne

typedef struct NP{
    char Nom[20];
    char Prenom[20];
    Etudiant *infoEtu;
    struct NP *svt;
}NomEtu;

//NomEtu* nomsets[26] 26: nombre des cas pour la premiere lettre d'un nom 