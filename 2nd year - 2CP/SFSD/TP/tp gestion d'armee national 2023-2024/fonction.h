//
// Created by  Apple on 12/22/23.
//

#ifndef FONCTION_H
#define FONCTION_H

#include "variable_globale.h"

int rendomNumber(int min, int max);
tenrg creerEnrg();

int getIndiceMilitaire(char* region);
int getIndiceForce(char* forceArme);
int getIndiceGrade(char* grade);
const char* getRegionAssocie( int indice);
const char* getForceAssocie( int indice);
const char* getGradeAssocie(int indice);
int getGrade(char *grade);

void Fragmentation(FILE *fichierSource);


//***************************************************************************
//-----------------------les fonctions principals----------------------------

void chargementInitial(FILE *fichier, int nbenrg);
void Chargement_index(Index *index);
void Sauvegarde_Index(Index index);
void Rech_Militaires(int matricule, bool *existe ,int *i, int *j, FILE *fichier);
void insertion(FILE *fichier, tenrg enrg, Index *index1, IndexM *index2, IndexM *index3, IndexM *index4);
void suppersionEnrg(FILE *fichier, int cle, Index *index1);
void SuppersionEnrg(FILE *fichier, Buffer *buf, int i, int j, Index *index1);
void modifRegionMelitaire(int matricule, char *nouveauRegion ,bool *existe);
void affichMilitaireIntervalle(int M1, int M2);

//***************************************************************************
//-----------------------les fonctions facultatifs----------------------------
void rechIntervaleAgeRegion(char *regionMilitaire, int minAge, int maxAge);
void afficherMilitaireParGrade(char *grade);
void creationFichRegionMilitaire(FILE *fichierSource, char *regionMilitaire, FILE *fichierDesination);
void supprimerForceArme(char *forceArme);

//***************************************************************************
//-----------------------  les fonctions des index----------------------------

void Chargement_indexM(FILE *Fi, IndexM *index);
void Sauvegarde_IndexM(FILE *fich, IndexM index);
void rechDicoTableIndex(int key, bool *trouv, int *k, Index index);

void insertionIndex(Ienrg ienrg, int pos, Index *index);
void insertionIndexS(Menrg menrg, IndexM *index);
void suppersionIndex(int pos, Index *index);
void suppressionIndexM(int cle, IndexM *index);


#endif //FONCTION_H
