//
// Created by  Apple on 12/24/23.
//

#include <stdio.h>
#include "affichage.h"
#include "variable_globale.h"
#include "fonction.h"
#include "machine_abtraite.h"


/**
 * Prints the index table for primary records in central memory.
 *
 * @param index The index table for primary records.
 */
void affichIndexPrimaire(Index index) {
    for (int i = 0; i < index.nb; ++i) {
        printf(" %d/ le matricule %d dans  %d %d \n", i, index.tab[i].cle, index.tab[i].adress.nbBloc,
               index.tab[i].adress.nbEnrg);
    }
}

/**
 * Prints the index table for military records in central memory.
 *
 * @param index The index table for military records.
 */
void affichIndexMilitaire(IndexM index) {
    for (int i = 0; i < index.nb; ++i) {
        printf(" %d/ le matricule %d de  %s\n", i, index.tab[i].cle, getRegionAssocie(index.tab[i].indice));
    }
}

/**
 * Prints the index table for force records in central memory.
 *
 * @param index The index table for force records.
 */
void affichIndexForce(IndexM index){
    for (int i = 0; i < index.nb; ++i) {
        printf(" %d/ le matricule %d de %s \n",i,index.tab[i].cle, getForceAssocie(index.tab[i].indice));
    }
}

/**
 * Prints the index table for grade records in central memory.
 *
 * @param index The index table for grade records.
 */
void affichIndexGrade(IndexM index){
    for (int i = 0; i < index.nb; ++i) {
        printf(" %d/ le matricule %d de %s \n",i,index.tab[i].cle, getGradeAssocie(index.tab[i].indice));
    }
}


















/**
 * Prints the content of a file.
 * 
 * @param nomFichier The name of the file to be printed.
 */
void printfFichier(char *nomFichier) {
    FILE *f ;
    int s = 1024;
    Ouvrire(&f, nomFichier, 'A');
    for (int i = 1; i <= entete(f, 1); ++i) {
        if (i == entete(f, 1)) {
            s = entete(f, 2);
        }else {
            s = 1024;
        }
        LireDir(f, i, &buffer);
        for (int j = 0; j < s; ++j) {
            printf("buffer de %d %d est %d %s\n", i, j, buffer.tab[j].Matricule, buffer.tab[j].Region_militaire);
        }
    }
    Fermer(f);
}


/**
 * Prints the primary index of a file.
 * 
 * @param nomFichier The name of the file.
 */
void printIndexPrimaire(char *nomFichier) {
    FILE *f;
    int s = 1024;
    int in = 0;
    BufferIndexP bufer;
    Ouvrire(&f, nomFichier, 'A');
    for (int i = 1; i <= entete(f, 1); ++i) {
        LireDirIP(f, i, &bufer);
        if (i == entete(f, 1)) {
            s = entete(f, 2);
        } else {
            s = 1024;
        }
        for (int j = 0; j < s; ++j) {
            printf(" %d/ le matricule %d dans  %d %d \n", in, bufer.tab[j].cle, bufer.tab[j].adress.nbBloc,
                   bufer.tab[j].adress.nbEnrg);
            in++;
        }
    }
    Fermer(f);
}

/**
 * Prints the military index of a file.
 * 
 * @param nomFichier The name of the file.
 */
void printMilitaireIndex(char *nomFichier) {
    FILE *f;
    int s = 1024;
    int in = 0;
    BufferIndexM bufer;
    Ouvrire(&f, nomFichier, 'A');
    for (int i = 1; i <= entete(f, 1); ++i) {
        LireDirIM(f, i, &bufer);
        if (i == entete(f, 1)) {
            s = entete(f, 2);
        } else {
            s = 1024;
        }
        for (int j = 0; j < s; ++j) {
            printf(" %d/ le matricule %d de  %s\n", in, bufer.tab[j].cle, getRegionAssocie(bufer.tab[j].indice));
            in++;
        }
    }
    Fermer(f);
}

/**
 * Prints the force index of a file.
 * 
 * @param nomFichier The name of the file.
 */
void printForceIndex(char *nomFichier) {
    FILE *f;
    int s = 1024;
    int in = 0;
    BufferIndexM bufer;
    Ouvrire(&f, nomFichier, 'A');
    for (int i = 1; i <= entete(f, 1); ++i) {
        LireDirIM(f, i, &bufer);
        if (i == entete(f, 1)) {
            s = entete(f, 2);
        } else {
            s = 1024;
        }
        for (int j = 0; j < s; ++j) {
            printf(" %d/ le matricule %d de  %s\n", in, bufer.tab[j].cle, getForceAssocie(bufer.tab[j].indice));
            in++;
        }
    }
    Fermer(f);
}

/**
 * Prints the grade index of a file.
 * 
 * @param nomFichier The name of the file.
 */
void printGradeIndex(char *nomFichier) {
    FILE *f;
    int s = 1024;
    int in = 0;
    BufferIndexM bufer;
    Ouvrire(&f, nomFichier, 'A');
    for (int i = 1; i <= entete(f, 1); ++i) {
        LireDirIM(f, i, &bufer);
        if (i == entete(f, 1)) {
            s = entete(f, 2);
        } else {
            s = 1024;
        }
        for (int j = 0; j < s; ++j) {
            printf(" %d/ le matricule %d de  %s\n", in, bufer.tab[j].cle, getGradeAssocie(bufer.tab[j].indice));
            in++;
        }
    }
    Fermer(f);
}
