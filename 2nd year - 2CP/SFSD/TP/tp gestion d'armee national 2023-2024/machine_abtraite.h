//
// Created by  Apple on 12/22/23.
//

#ifndef MACHINE_ABTRAITE_H
#define MACHINE_ABTRAITE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "variable_globale.h"

//---------------------------les entetes de la machine abstraite-------------------------------------
//****************************le fichier de donnee t7of*****************************************************
bool LireDir(FILE *fichier , int i , Buffer *buff);
void Fermer(FILE *fichier) ;
void EcrireDir(FILE *fichier , int i , Buffer *buff);
void Ouvrire(FILE **fichier , char nom[30] , char mode);
int entete(FILE *fichier, int i);
void aff_entete(FILE *fichier, int i ,int valeur);
Buffer * alloc_bloc(FILE *fichier);


//****************************le fichier d'index tof*****************************************************
void EcrireDirIP(FILE *fichier , int i , BufferIndexP *buffi);
void LireDirIP(FILE *fichier , int i , BufferIndexP *buffer);
BufferIndexP *alloc_bloci();

//****************************le fichier d'index secondaire*****************************************************
void EcrireDirIM(FILE *fichier , int i , BufferIndexM *buffi);
void LireDirIM(FILE *fichier , int i , BufferIndexM *buffi);
BufferIndexM * alloc_blociM();
//*************************************************************************************************

#endif //MACHINE_ABTRAITE_H
