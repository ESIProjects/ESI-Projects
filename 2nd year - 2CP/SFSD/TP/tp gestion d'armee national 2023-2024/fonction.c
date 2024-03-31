//
// Created by  Apple on 12/22/23.
//

#include "machine_abtraite.h"
#include "variable_globale.h"
#include "fonction.h"
#include "affichage.h"
#include <string.h>

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>



/**
 * Calculates the age based on the birth date and returns the actual age.
 *
 * @param birthDate The birth date of the person.
 * @return The calculated age.
 */
int calculateAge(date birthDate) {
    currentDate.day = 31;
    currentDate.month = 12;
    currentDate.year = 2023;

    int age = currentDate.year - birthDate.year;

    if (currentDate.month < birthDate.month ||
        (currentDate.month == birthDate.month && currentDate.day < birthDate.day)) {
        age--;
    }

    return age;
}

//************************************************************************

/**
 * Returns the index of a military region based on its name.
 *
 * @param region The name of the military region.
 * @return The index of the military region, or -1 if not found.
 */
int getIndiceMilitaire(char* region){
    int indice;
    for (int i = 0; i < 6; ++i) {
        if(strcmp(region,militaryRegions[i])==0){
            indice = i;
        }
    }
    return indice;
}

//************************************************************************

/**
 * Returns the index of the given forceArme in the armedForces array.
 *
 * @param forceArme The forceArme to search for.
 * @return The index of the forceArme in the armedForces array, or -1 if not found.
 */
int getIndiceForce(char* forceArme){
    int indice ;
    for (int i = 0; i < 8; ++i) {
        if(strcmp(forceArme,armedForces[i])==0){
            indice = i;
        }
    }
    return indice;
}
//************************************************************************

/**
 * Returns the index of a military grade in the array `militaryGrades`.
 * 
 * @param grade The military grade to search for.
 * @return The index of the military grade in the array `militaryGrades`.
 */
int getIndiceGrade(char* grade){
    int indice;
    for (int i = 0; i < 19; ++i) {
        if(strcmp(grade, militaryGrades[i])==0){
            if( i>= 0 && i <= 3 ){
                indice = 0;
            }else if (i>= 4 && i <= 7 ){
                indice = 1;
            }else if (i>= 8 && i<= 12){
                indice = 2;
            }else if(i>= 13 && i<= 15){
                indice = 3;
            }else{
                indice = 4;
            }
            break;
        }
    }
    return indice;
}

//************************************************************************


/**
 * @brief Gets the index of a grade in the Grades array.
 * 
 * This function takes a grade as input and searches for its index in the Grades array.
 * The Grades array is assumed to contain 5 grades.
 * 
 * @param grade The grade to search for.
 * @return The index of the grade in the Grades array. If the grade is not found, -1 is returned.
 */
int getGrade(char *grade){
    int indice = -1;
    for (int i = 0; i < 5; ++i) {
        if(strcmp(grade,Grades[i])==0){
            indice = i;
        }
    }
    return indice;
}

/**
 * Returns the military region associated with the given index.
 *
 * @param indice The index of the military region.
 * @return The military region associated with the given index.
 */
const char* getRegionAssocie(int indice) {
    return militaryRegions[indice];
}


/**
 * Retrieves the associated armed force based on the given index.
 *
 * @param indice The index of the armed force.
 * @return The associated armed force as a string.
 */
const char* getForceAssocie(int indice) {
    return armedForces[indice];
}
/**
 * Retrieves the grade associated with the given index.
 *
 * @param indice The index of the grade to retrieve.
 * @return The grade associated with the given index.
 */
const char* getGradeAssocie(int indice){
    return Grades[indice];
}



















/**
 * Determines if a given year is a leap year.
 *
 * @param year The year to check.
 * @return True if the year is a leap year, false otherwise.
 */
bool isLeapYear(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

/**
 * Generates a random number between the given minimum and maximum values.
 *
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 * @return The randomly generated number.
 */
int rendomNumber(int min, int max) {
//    srand((unsigned int)time(NULL));
       int a,b,c;
         a=rand() %100000 + 100000;
         b = rand() % 30 +1;
         c = (a*b) % (max - min+1)+min;
    return c;
}

/**
 * Gets the number of days in a given month of a given year.
 *
 * @param month The month (1-12).
 * @param year The year.
 * @return The number of days in the specified month and year.
 */
int getDaysInMonth(int month, int year) {
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        return 31;
    }
}
//****************************************************************

/**
 * Generates a random date.
 *
 * @return The randomly generated date.
 */
date rendomDate() {
    date rendomDate;
    rendomDate.year = rendomNumber(1942, 2005);
    rendomDate.month = rendomNumber(1, 12);
    rendomDate.day = rendomNumber(1, getDaysInMonth(rendomDate.month, rendomDate.year));
    return rendomDate;
}
//****************************************************************
//rendomWilaya return un pointeur vers le debut de string (chaine de caractere)
/**
 * Generates a random wilaya (province) from the list of Algerian wilayas.
 *
 * @return A pointer to a string representing the randomly generated wilaya.
 */
const char *rendomWilaya() {
    int i;
    i = rendomNumber(1, 58);
    //TODO 3 : COMPLITER LES RENDOM GENRATION
    return algerianWilayas[i - 1];
}
//****************************************************************

/**
 * Generates a random blood type.
 *
 * This function generates a random number between 1 and 8 and uses it to select a blood type from the `bloodTypes` array.
 *
 * @return A pointer to the randomly selected blood type.
 */
const char *rendomGroupeSanguin() {
    int i;
    i = rendomNumber(1, 8);
    return bloodTypes[i - 1];
}
//****************************************************************

/**
 * Generates a random military grade.
 *
 * @return A pointer to a string representing the random military grade.
 */
const char *rendomGrade() {
    int i;
    i = rendomNumber(1, 19);
    return militaryGrades[i - 1];
}
//****************************************************************

/**
 * Generates a random force from the armedForces array.
 *
 * @return A pointer to a string representing the random force.
 */
const char *rendomForceArmee() {
    int i;
    i = rendomNumber(1, 8);
    return armedForces[i - 1];
}
//****************************************************************

/**
 * Generates a random military region.
 *
 * This function generates a random number between 1 and 6 and uses it to select a military region from the array `militaryRegions`.
 *
 * @return A pointer to a string representing the randomly selected military region.
 */
const char *rendomRegionMilitaire() {
    int i;
    i = rendomNumber(1, 6);
    return militaryRegions[i - 1];
}
//****************************************************************
/**
 * @brief Generates a random name and surname.
 *
 * This function generates a random name and surname by assigning random alphabets to the given arrays.
 * The length of the name and surname is determined by a random number between 4 and 30.
 * The generated name and surname are null-terminated strings.
 *
 * @param nom The array to store the generated name.
 * @param prenom The array to store the generated surname.
 */
void getNomPrenom(char nom[], char prenom[]) {
    int taille, i;

    // Get the length of the name and surname
    taille = rendomNumber(4, 30);

    // Generate random alphabets for name and surname
    for (i = 0; i < taille; i++) {
        nom[i] = 'A' + rand() % 26;
        prenom[i] = 'A' + rand() % 26;
    }

    // Null-terminate the generated name and surname
    nom[taille] = '\0';
    prenom[taille] = '\0';
}

//****************************************************************
/**
 * Creates a new Enrgegistrement with random values.
 *
 * @return The newly created enregistrement.
 */
tenrg creerEnrg() {
    tenrg enrg;

    strcpy(enrg.Wilaya_Naissance, rendomWilaya());
    enrg.Date_Naissance = rendomDate();
    strcpy(enrg.Region_militaire, rendomRegionMilitaire());
    getNomPrenom(enrg.Nom, enrg.Prenom);
    enrg.Matricule = rendomNumber(111111, 999999);
    strcpy(enrg.Grade, rendomGrade());
    strcpy(enrg.Groupe_sanguin, rendomGroupeSanguin());
    strcpy(enrg.Force_armee, rendomForceArmee());

    return enrg;
}
//****************************************************************

void initIndex(Index *index) {
    int i = 0;
    for (; i < 100000; i++) {
        index->nb = 0;
        index->tab[i].cle = '\0';
        index->tab[i].adress.nbBloc = '\0';
        index->tab[i].adress.nbEnrg = '\0';
    }
}
//****************************************************************
/**
 * Searches for a key in the given index table using binary search.
 *
 * @param key The key to search for.
 * @param trouv Pointer to a boolean variable indicating if the key is found.
 * @param k Pointer to an integer variable to store the index of the key.
 * @param index The index table to search in.
 */
void rechDicoTableIndex(int key, bool *trouv, int *k, Index index) {
    *trouv = false;
    int inf, sup, m = 0, j2 = 0;
    inf = 0;
    sup = index.nb - 1;
    while ((inf <= sup) && (!*trouv)) {
        int mid = (sup + inf) / 2;

        if (index.tab[mid].cle == key) {
            *trouv = true;
            j2 = mid;
        } else if (index.tab[mid].cle > key) {
            sup = mid - 1;
        } else {
            inf = mid + 1;
        }
        if (!*trouv || inf > sup) {
            j2 = inf;
        }
    }
    *k = j2;
}

//**************************************************************

/**
 * Sequential search in the Secondary index array and returns the position and found.
 * 
 * @param cle The key to search for in the Secondary index array.
 * @param trouv A pointer to a boolean variable that will be set to true if the key is found, otherwise false.
 * @param pos A pointer to an integer variable that will hold the position of the key in the Secondary index array.
 * @param index The Secondary index array in which to perform the search.
 */
void rechTableIndexM(int cle, bool *trouv, int *pos, IndexM index) {
    *trouv = false;
    for (int i = 0; i < index.nb; i++) {
        if (index.tab[i].cle == cle) {
            *trouv = true;
            *pos = i;
            break;
        }
    }
}
//**************************************************************
/**
 * Inserts an Ienrg object at the specified position in the Index.
 *
 * @param ienrg The Ienrg object to be inserted.
 * @param pos The position at which the object should be inserted.
 * @param index The Index object in which the insertion should be performed.
 */
void insertionIndex(Ienrg ienrg, int pos, Index *index) {
    //TODO : WHAT ABOUT THE FIRST INSERTION
    int m = index->nb - 1;
    for (; pos <= m; m--) {
        index->tab[m + 1] = index->tab[m];
    }
    index->tab[pos] = ienrg;
    index->nb += 1;
}

//**************************************************************

/**
 * Inserts a record into the secondary index.
 *
 * This function inserts a record into the secondary index by assigning the given
 * index value and key to the next available position in the index table.
 *
 * @param menrg The record to be inserted into the secondary index.
 * @param index The secondary index structure.
 */
void insertionIndexS(Menrg menrg, IndexM *index){
    int m = index->nb;
    int i = 0;
    i = menrg.indice;
    index->tab[m].indice = i;
    index->tab[m].cle = menrg.cle;
    index->nb += 1;
}

//**************************************************************

/**
 * Searches for a military personnel based on their matricule in a given file.
 * 
 * @param matricule The matricule of the military personnel to search for.
 * @param i Pointer to store the block number where the military personnel is found.
 * @param j Pointer to store the record number where the military personnel is found.
 * @param fichier The file to search in.
 */
void Rech_Militaires(int matricule, bool *existe , int *i, int *j, FILE *fichier) {
    *i = 0;
    *j = 0;
    int pos = 0;
    bool trouv  = false;
    rechDicoTableIndex(matricule, &trouv, &pos, indexP);
    *existe = trouv ;
    if (trouv) {
        *i = indexP.tab[pos].adress.nbBloc;
        *j = indexP.tab[pos].adress.nbEnrg;
        LireDir(fichier, *i, &buffer);
    }
}
//***************************************************************************
/** Sauvegarde de l'index dans un fichier TOF nomm? "Matricule_Index.idx" **/

void Sauvegarde_Index(Index index) {
    FILE *F;
    int i, j, k;
    i = 1;
    j = 0;
    Ouvrire(&F, "MATRICULE_INDEX.idx", 'N');
    bufferIndexP= *alloc_bloci();
    for (k = 0; k < index.nb; k++) {

        if (j < 1024) {
            bufferIndexP.tab[j] = index.tab[k];
            j++;
        } else {
            EcrireDirIP(F, i, &bufferIndexP);
            bufferIndexP = *alloc_bloci();
            bufferIndexP.tab[0] = index.tab[k];
            j = 1;
            i++;
        }
    }
    EcrireDirIP(F, i, &bufferIndexP);
    aff_entete(F, 1, i);
    aff_entete(F, 2, j);
    Fermer(F);
}
/**
 * @brief Removes an element from the index array at the specified position.
 *
 * This function removes an element from the index array at the specified position.
 * It shifts all the elements after the specified position to the left by one position.
 *
 * @param cle The key of the element to be removed.
 * @param pos The position of the element to be removed.
 * @param index Pointer to the Index structure.
 */
void suppersionIndex(int pos, Index *index) {
    int m = index->nb - 1;
    for (; pos <= m; pos++) {
        index->tab[pos] = index->tab[pos + 1];
    }
    index->nb -= 1;
}
void suppressionIndexM(int cle, IndexM *index){
    bool trouv = false;
    int pos = 0;
    // Find the position of the Menrg with the given cle
    rechTableIndexM(cle, &trouv, &pos, *index);
    if (trouv) {
        // Shift all elements after pos to the left
        if(pos != index->nb - 1){
            index->tab[pos] = index->tab[index->nb - 1];
        }
        // Decrease the number of elements in the index
        index->nb--;
    }
}
void Sauvegarde_IndexM(FILE *fich, IndexM index) {
    int i, j, k;
    i = 1;
    j = 0;
    bufferIndexM = *alloc_blociM();
    for (k = 0; k < index.nb; k++) {
        if (j < 1024) {
            bufferIndexM.tab[j] = index.tab[k];
            j++;
        } else {
            EcrireDirIM(fich, i, &bufferIndexM);
            bufferIndexM = *alloc_blociM();
            bufferIndexM.tab[0] = index.tab[k];
            j = 1;
            i++;
        }
    }
    EcrireDirIM(fich, i, &bufferIndexM);
    aff_entete(fich, 1, i);
    aff_entete(fich, 2, j);
    entete(fich,1);
    Fermer(fich);
}

/** Chargement de l'index en MC ? partir du fichier TOF "Matricule_Index.idx" **/

void Chargement_index(Index *index) {
    FILE *Fi;
    Ouvrire(&Fi, "MATRICULE_INDEX.idx", 'A');
    int i, j, k, nbi, nb;
    k = 0;
    nbi = 0;
    int d;
    for (i = 1; i <= entete(Fi, 1); i++) {
        LireDirIP(Fi, i, &bufferIndexP);
        if (i == entete(Fi, 1)) { nb = entete(Fi, 2); }
        else { nb = 1024; }
        j = 0;
        for (; j < nb; j++) {
            index->tab[k] = bufferIndexP.tab[j];
            nbi++;
            k++;
        }
    }
    index->nb = nbi;
    Fermer(Fi);
}
void Chargement_indexM(FILE *Fi, IndexM *index) {
    int i, j, k, nbi, nb;
    k = 0;
    nbi = 0;
    int d;
    for (i = 1; i <= entete(Fi, 1); i++) {
        LireDirIM(Fi, i, &bufferIndexM);
        if (i == entete(Fi, 1)) { nb = entete(Fi, 2); }
        else { nb = 1024; }
        j = 0;
        for (; j < nb; j++) {
            index->tab[k] = bufferIndexM.tab[j];
            nbi++;
            k++;
        }

    }
    index->nb = nbi;
}
//****************************************************************
/**
 * Loads the initial data into the file.
 *
 * @param fichier The file to load the data into.
 * @param nbenrg The number of records to load.
 */
void chargementInitial(FILE *fichier, int nbenrg) {

    srand(time(NULL));
    tenrg enrg;
    int i, j, k, nb;
    Ienrg ienrg;
    Menrg menrg,merng1,merng2;
    Adress adress;
    bool trouve = false;
    nb = 1;//on utilise i pour le parcour des elements
    i = 1;
    j = 0;
    FILE *Fi;
    char * ptr,*ptr1,*ptr3;
    initIndex(&indexP);
    while (nb <= nbenrg) {
        enrg = creerEnrg();
        rechDicoTableIndex(enrg.Matricule, &trouve, &k, indexP);
        if (trouve == false) {
            if (j < 1024) {
                buffer.tab[j] = enrg;
                adress.nbBloc = i;
                adress.nbEnrg = j;

                ienrg.adress = adress;
                ienrg.cle = enrg.Matricule;

                menrg.cle = ienrg.cle;
                ptr = strdup(enrg.Region_militaire);
                menrg.indice = getIndiceMilitaire(ptr);

                merng1.cle = ienrg.cle;
                ptr1 = strdup(enrg.Force_armee);
                merng1.indice = getIndiceForce(ptr1);

                merng2.cle = ienrg.cle;
                ptr3  = strdup(enrg.Grade);
                merng2.indice = getIndiceGrade(ptr3);

                insertionIndex(ienrg, k, &indexP);
                insertionIndexS(menrg, &indexM);
                insertionIndexS(merng1,&indexF);
                insertionIndexS(merng2,&indexG);
                ++j;
            } else {
                EcrireDir(fichier, i, &buffer);
                buffer = *alloc_bloc(fichier);
                buffer.tab[0] = enrg;
                j = 1;
                ++i;
                adress.nbBloc = i;
                adress.nbEnrg = 0;

                ienrg.adress = adress;
                ienrg.cle = enrg.Matricule;

                menrg.cle = ienrg.cle;
                ptr = strdup(enrg.Region_militaire);
                menrg.indice = getIndiceMilitaire(ptr);

                merng1.cle = ienrg.cle;
                ptr1 = strdup(enrg.Force_armee);
                merng1.indice = getIndiceForce(ptr1);

                merng2.cle = ienrg.cle;
                ptr3  = strdup(enrg.Grade);
                merng2.indice = getIndiceGrade(ptr3);

                insertionIndex(ienrg, k, &indexP);
                insertionIndexS(menrg, &indexM);
                insertionIndexS(merng1,&indexF);
                insertionIndexS(merng2,&indexG);
            }
            ++nb;//on incremente le nombre des enregistrement ecrites
        }

    }
    EcrireDir(fichier, i, &buffer);
    aff_entete(fichier, 1, i);
    aff_entete(fichier, 2, j);
    Fermer(fichier);
    Sauvegarde_Index(indexP);
}

//****************************************************************

/**
 * Inserts a record into the file.
 *
 * @param fichier The file to insert the record into.
 * @param enrg The record to be inserted.
 */
void insertion(FILE *fichier, tenrg enrg, Index *index1, IndexM *index2, IndexM *index3, IndexM *index4) {
    Menrg menrg1,menrg2;
    int k, N, nb;
    N = 0;
    nb = 0;
    bool trouv = false;
    rechDicoTableIndex(enrg.Matricule, &trouv, &k, *index1);
    if (trouv == false) {
        Ienrg ienrg;
        Menrg menrg;
        N = entete(fichier, 1);
        if (N != 0) {
            LireDir(fichier, N, &buffer);
            nb = entete(fichier, 2);
        } else {
            N = 1;
            aff_entete(fichier, 1, 1);
            nb = 0;
            aff_entete(fichier, 2, nb);
        }
        if (nb < 1024) {
            nb += 1;
            buffer.tab[nb - 1] = enrg;
            EcrireDir(fichier, N, &buffer);
        } else {
            nb = 1;
            buffer = *alloc_bloc(fichier);
            buffer.tab[nb - 1] = enrg;
            EcrireDir(fichier, N + 1, &buffer);
            aff_entete(fichier, 1, N + 1);
        }
        aff_entete(fichier, 2, nb);
        ienrg.cle = enrg.Matricule;
        ienrg.adress.nbBloc = entete(fichier, 1);
        ienrg.adress.nbEnrg = entete(fichier, 2)-1;

        menrg.indice = getIndiceMilitaire(enrg.Region_militaire);
        menrg.cle = enrg.Matricule;

        menrg1.indice = getIndiceForce(enrg.Force_armee);
        menrg1.cle = enrg.Matricule;

        menrg2.indice = getIndiceGrade(enrg.Grade);
        menrg2.cle = enrg.Matricule;

        insertionIndex(ienrg, k, index1);
        insertionIndexS(menrg, index2);
        insertionIndexS(menrg1,index3);
        insertionIndexS(menrg2,index4);
        printf("\ninsertion avec succes.");
    } else {
        printf("\nl'enregistrement que vous voulez inserer existe deja.\n");
    }
}

//****************************************************************

/**
 * @brief Deletes a record based on its key from a file.
 *
 * @param cle The key of the record to be deleted.
 */
void suppersionEnrg(FILE *fichier, int cle, Index *index1) {
    bool trouv = false,trouv1 = false;
    int k =0,k1 = 0;
    int N = 2;
    int i = 1;
    int j = 0;
    int nb =0;
    Buffer buf = *alloc_bloc(fichier);
    //N : le nombre des bloques
    //i,j : les indices
    //nb : le nombre des enrg dans le dernier bloque
    //k : l'indice d'enrg qu'on va supprimer
    rechDicoTableIndex(cle, &trouv, &k, *index1);
    if (trouv) {
        N = entete(fichier, 1);
        i = index1->tab[k].adress.nbBloc;
        j = index1->tab[k].adress.nbEnrg;
        nb = entete(fichier, 2);
        if (i != N) {
            LireDir(fichier, i, &buf);
            LireDir(fichier, N, &buf1);
            buf.tab[j] = buf1.tab[nb - 1];
            rechDicoTableIndex(buf.tab[j].Matricule,&trouv1,&k1,*index1);
            if(trouv1){
                index1->tab[k1].adress.nbBloc = i;
                index1->tab[k1].adress.nbEnrg = j;
            }
            EcrireDir(fichier, i, &buf);
            --nb;
            if (nb > 0) {
                EcrireDir(fichier, N, &buf1);
                aff_entete(fichier, 2, nb);
            } else {
                aff_entete(fichier, 1, N - 1);
                aff_entete(fichier, 2, 1024);
            }
        } else {
            LireDir(fichier, N, &buf);
            buf.tab[j] = buf.tab[nb - 1];
            rechDicoTableIndex(buf.tab[j].Matricule,&trouv1,&k1,*index1);
            if(trouv1){
                index1->tab[k1].adress.nbEnrg = j;
            }
            --nb;
            if (nb > 0) {
                EcrireDir(fichier, N, &buf);
                aff_entete(fichier, 2, nb);
            } else {
                aff_entete(fichier, 1, N - 1);
                aff_entete(fichier, 2, 1024);
            }
        }
        suppersionIndex(k, index1);
        suppressionIndexM(cle, &indexM);
        suppressionIndexM(cle, &indexF);
        suppressionIndexM(cle,&indexG);
    }else{
        printf("l'enregistrement que vous voulez supprimer n'existe pas");
    }
}

//****************************************************************

/**
 * @brief Removes a record from the file and updates the index.
 *
 * This function removes a record from the file specified by the 'fichier' parameter.
 * It takes the buffer 'buf' and the indices 'i' and 'j' as input to determine the record to be removed.
 * The 'index1' parameter is a pointer to the index structure that needs to be updated.
 *
 * @param fichier The file pointer to the file from which the record needs to be removed.
 * @param buf The buffer containing the records.
 * @param i The index of the block in the file.
 * @param j The index of the record in the block.
 * @param index1 A pointer to the index structure that needs to be updated.
 */
void SuppersionEnrg(FILE *fichier, Buffer *buf, int i, int j, Index *index1) {
    bool trouv1 = false;
    int k1 = 0;
    int N = 2;
    int nb =0;
    //N : le number of blocks
    //i,j : the indices
    //nb : the number of records in the last block

    N = entete(fichier, 1);
    nb = entete(fichier, 2);
    if (i != N) {
        LireDir(fichier, N, &buf1);
        buf->tab[j] = buf1.tab[nb - 1];
        rechDicoTableIndex(buf->tab[j].Matricule,&trouv1,&k1,*index1);
        if(trouv1){
            index1->tab[k1].adress.nbBloc = i;
            index1->tab[k1].adress.nbEnrg = j;
        }
        EcrireDir(fichier, i, buf);
        --nb;
        if (nb > 0) {
            EcrireDir(fichier, N, &buf1);
            aff_entete(fichier, 2, nb);
        } else {
            aff_entete(fichier, 1, N - 1);
            aff_entete(fichier, 2, 1024);
        }
    } else {
        buf->tab[j] = buf->tab[nb - 1];
        rechDicoTableIndex(buf->tab[j].Matricule,&trouv1,&k1,*index1);
        if(trouv1){
            index1->tab[k1].adress.nbEnrg = j;
        }
        --nb;
        if (nb > 0) {
            EcrireDir(fichier, N, buf);
            aff_entete(fichier, 2, nb);
        } else {
            aff_entete(fichier, 1, N - 1);
            aff_entete(fichier, 2, 1024);
        }
    }
//    suppersionIndex(k1, index1);
//    suppressionIndexM(buf->tab[j].Matricule, &indexM);
//    suppressionIndexM(buf->tab[j].Matricule,&indexG);
}

//****************************************************************

/**
 * Modifies the military region of a record in the file.
 *
 * This function takes a file pointer, a record, and a new military region as parameters.
 * It searches for the record in the file using its Matricule, and if found, updates its military region.
 * The function uses a directory-based indexing system to locate the record in the file.
 *
 * @param matricule The record to be modified.
 * @param nouveauRegion The new military region to be assigned to the record.
 */
void modifRegionMelitaire(int matricule, char *nouveauRegion, bool *existe) {
    int i, j, k;
    int clean;
    bool trouv;
    FILE *fichier, *fichier2 ;
    Ouvrire(&fichier, "PERSONNEL-ANP_DZ.dat", 'A');
    Ouvrire(&fichier2, "MILITAIRE_INDEX.idx", 'A');
    rechDicoTableIndex(matricule, &trouv, &k, indexP);
    *existe = trouv;
    if (trouv) {
        i = indexP.tab[k].adress.nbBloc;
        j = indexP.tab[k].adress.nbEnrg;
        LireDir(fichier, i, &buffer);
        LireDirIM(fichier2, i, &bufferIndexM);
        for (clean = 0; clean < 30; clean++) {
            buffer.tab[i].Region_militaire[clean] = '\0';
        }
        strcpy(buffer.tab[j].Region_militaire, nouveauRegion);
        bufferIndexM.tab[j].indice = getIndiceMilitaire(nouveauRegion);
        EcrireDir(fichier, i, &buffer);
        EcrireDirIM(fichier2, i, &bufferIndexM);
    } else {
        printf("l'enregistrement que vous voulez changes sa region Milittaire n'existe pas");
    }
    Fermer(fichier);
    Fermer(fichier2);
}

//****************************************************************

/**
 * @brief Displays military personnel within a given range of matricule numbers.
 *
 * This function reads data from a file and displays the military personnel
 * whose matricule numbers fall within the specified range [M1, M2].
 *
 * @param M1 The lower bound of the matricule range.
 * @param M2 The upper bound of the matricule range.
 */
void affichMilitaireIntervalle(int M1, int M2) {
    int inf, sup;
    bool trouv1, trouv2;
    FILE *fichier;
    Ouvrire(&fichier, "PERSONNEL-ANP_DZ.dat", 'A');
    rechDicoTableIndex(M1, &trouv1, &inf, indexP);
    rechDicoTableIndex(M2, &trouv2, &sup, indexP);
    if (!trouv2) {
        --sup;
    }
    int i = inf;
    int j;
    printf("\n%d nombre des element :\n", sup - inf + 1);
    printf(" les militaire entre le matricule %d et %d sont : \n", M1, M2);
    Buffer *bufer = alloc_bloc(fichier);
    LireDir(fichier, indexP.tab[i].adress.nbBloc, bufer);
    j = indexP.tab[i].adress.nbEnrg; //j : l'indice de l'enregistrement
    printf("%d/ %d %s %s %d %d/%d/%d %s %s %s %s %s\n", 0, indexP.tab[i].cle, bufer->tab[j].Nom, bufer->tab[j].Prenom,
           bufer->tab[j].Matricule, bufer->tab[j].Date_Naissance.day, bufer->tab[j].Date_Naissance.month,
           bufer->tab[j].Date_Naissance.year, bufer->tab[j].Wilaya_Naissance, bufer->tab[j].Region_militaire,
           bufer->tab[j].Grade, bufer->tab[j].Groupe_sanguin, bufer->tab[j].Force_armee);
//    LireDir(fichier,2,bufer);
    for (i = inf + 1; i <= sup; i++) {
        if (indexP.tab[i].adress.nbBloc != indexP.tab[i - 1].adress.nbBloc) {
            free(bufer);
            bufer = alloc_bloc(fichier);
            LireDir(fichier, indexP.tab[i].adress.nbBloc, bufer);
        }
        j = indexP.tab[i].adress.nbEnrg; //j : l'indice de l'enregistrement
        printf("%d/ %d %s %s %d %d/%d/%d %s %s %s %s %s\n", i - inf, indexP.tab[i].cle, bufer->tab[j].Nom,
               bufer->tab[j].Prenom, bufer->tab[j].Matricule, bufer->tab[j].Date_Naissance.day,
               bufer->tab[j].Date_Naissance.month, bufer->tab[j].Date_Naissance.year, bufer->tab[j].Wilaya_Naissance,
               bufer->tab[j].Region_militaire, bufer->tab[j].Grade, bufer->tab[j].Groupe_sanguin,
               bufer->tab[j].Force_armee);
//        free(bufer);
    }
    Fermer(fichier);
}

//****************************************************************

/**
 * Searches for military personnel within a specified age range in a given military region.
 *
 * @param regionMilitaire The name of the military region.
 * @param minAge The minimum age of the military personnel to search for.
 * @param maxAge The maximum age of the military personnel to search for.
 */
void rechIntervaleAgeRegion(char *regionMilitaire, int minAge, int maxAge) {

    int indice = getIndiceMilitaire(regionMilitaire);
    int i, j, nb, age;
    int s,sCopy;
    FILE *fichier;
    int beforI;
    int k = 0; // Initialize 'k' to 0
    Ouvrire(&fichier,"PERSONNEL-ANP_DZ.dat",'A');
    nb = indexP.nb;
    //POSITION OF THE FIRST RECORD OF THE REGION
    while(indice != indexM.tab[k].indice){
        k++;
    }
    //IF THE FILE IS NOT EMPTY
    if (k != indexM.nb) {
        _Bool trouv;
        //FIND THE ADRESS OF THE FIRST RECORD OF THE REGION IN THE PRIMARY INDEX
        rechDicoTableIndex(indexM.tab[k].cle, &trouv, &s, indexP);
        if(trouv){
            i = indexP.tab[s].adress.nbBloc;
            j = indexP.tab[s].adress.nbEnrg;
            beforI = i;
            buffer = *alloc_bloc(fichier);
            LireDir(fichier, i, &buffer);
            //CHECK IF THE FIRST RECORD IS IN THE AGE INTERVAL AND PRINT IT THEN
            age = calculateAge(buffer.tab[j].Date_Naissance);
            if ((age >= minAge) && (age <= maxAge)) {
                printf("%d/ %d %s  %s  %d  %d/%d/%d    %s  %s  %s  %s \n", 0, buffer.tab[j].Matricule, buffer.tab[j].Nom,
                       buffer.tab[j].Prenom, buffer.tab[j].Matricule, buffer.tab[j].Date_Naissance.day,
                       buffer.tab[j].Date_Naissance.month, buffer.tab[j].Date_Naissance.year,
                       buffer.tab[j].Wilaya_Naissance, buffer.tab[j].Grade, buffer.tab[j].Region_militaire,
                       buffer.tab[j].Force_armee);
            }
        }
        int z = 1;
        k++;
        // DO THE SAME FOR THE REST OF THE RECORDS IN THE REGION
        while (k < nb) {
            //IF THE REGION IS THE SAME AS THE  PARAMETER REGION
            if(indexM.tab[k].indice == indice) {
                int cle =0;
                cle =indexM.tab[k].cle;
                //FIN THE ADRESS OF THE RECORD IN THE PRIMARY INDEX

                rechDicoTableIndex(cle, &trouv, &sCopy, indexP);
                if(trouv){
                    s = sCopy;
                    j = indexP.tab[s].adress.nbEnrg;
                    i = indexP.tab[s].adress.nbBloc;
                    //WE READ A NEW BUFFER JUST IF THE RECORD ADDRESS IS IN A NEW BLOCK
                    if (i != beforI) {
                        buffer = *alloc_bloc(fichier); // Refresh the buffer for each record
                        LireDir(fichier, i, &buffer);
                    }
                    //CHECK IF THE RECORD IS IN THE AGE INTERVAL AND PRINT IT THEN
                    age = calculateAge(buffer.tab[j].Date_Naissance);
                    if ((age >= minAge) && (age <= maxAge)) {
                        printf("%d/ %d %s  %s  %d  %d/%d/%d    %s  %s  %s  %s \n", z, buffer.tab[j].Matricule,
                               buffer.tab[j].Nom, buffer.tab[j].Prenom, buffer.tab[j].Matricule,
                               buffer.tab[j].Date_Naissance.day, buffer.tab[j].Date_Naissance.month,
                               buffer.tab[j].Date_Naissance.year, buffer.tab[j].Wilaya_Naissance, buffer.tab[j].Grade,
                               buffer.tab[j].Region_militaire, buffer.tab[j].Force_armee);
                        z++;
                    }
                    //UPDATE THE BREVIOUS BLOCK
                    beforI =i;
                }
            };
            k++;
        }
    } else {
        printf("il n'y a pas de militaire dans cette region \n");
    }
    Fermer(fichier);
}

//****************************************************************

/**
 * @brief Creates a new file containing records from a specific region in a source file.
 * 
 * This function reads records from the source file and writes them to the destination file
 * if they belong to the specified region. The region is determined by the regionMilitaire parameter.
 * 
 * @param fichierSource The source file to read records from.
 * @param regionMilitaire The region to filter records by.
 * @param fichierDesination The destination file to write filtered records to.
 */
void creationFichRegionMilitaire(FILE *fichierSource, char *regionMilitaire, FILE *fichierDesination) {
    int indice = getIndiceMilitaire(regionMilitaire);
    int i, j,i1,j1, nb, age;
    Buffer buf1,buf;
    int s,sCopy;
    FILE *fichier;
    int beforI;
    int k = 0;// Initialize 'k' to 0
    i1 = 0;
    j1 = 0;
    nb = indexP.nb;
    _Bool trouv = false;
    //POSITION OF THE FIRST RECORD OF THE REGION
    while(indice != indexM.tab[k].indice){
        k++;
    }
    //IF THE FILE IS NOT EMPTY
    rechDicoTableIndex(indexM.tab[k].cle, &trouv, &s, indexP);
    if (k != indexM.nb && trouv) {
        //FIND THE ADRESS OF THE FIRST RECORD OF THE REGION IN THE PRIMARY INDEX
        i = indexP.tab[s].adress.nbBloc;
        j = indexP.tab[s].adress.nbEnrg;
        beforI = i;
        buf = *alloc_bloc(fichierSource);
        LireDir(fichierSource, i, &buf);
        buf1 = *alloc_bloc(fichierDesination);
        buf1.tab[0] = buf.tab[j];

        i1 = 1;j1 = 1;
        int z = 1;
        k++;
        // DO THE SAME FOR THE REST OF THE RECORDS IN THE REGION
        while (k < nb) {
            int cle =0;
            cle =indexM.tab[k].cle;
            //FIN THE ADRESS OF THE RECORD IN THE PRIMARY INDEX
            rechDicoTableIndex(cle, &trouv, &sCopy, indexP);
            //IF THE REGION IS THE SAME AS THE  PARAMETER REGION
            if(indexM.tab[k].indice == indice && trouv) {
                s = sCopy;
                j = indexP.tab[s].adress.nbEnrg;
                i = indexP.tab[s].adress.nbBloc;
                //WE READ A NEW BUFFER JUST IF THE RECORD ADDRESS IS IN A NEW BLOCK
                if (i != beforI) {
                    buf = *alloc_bloc(fichierSource); // Refresh the buffer for each record
                    LireDir(fichierSource, i, &buf);
                }
                //CHECK IF THE RECORD IS IN THE AGE INTERVAL AND PRINT IT THEN
                if (j1 < 1024) {
                    buf1.tab[j1] = buf.tab[j];
                    j1++;
                } else {
                    EcrireDir(fichierDesination, i1, &buf1);
                    buf1 = *alloc_bloc(fichierDesination);
                    buf1.tab[0] = buf.tab[j];
                    j1 = 1;
                    i1++;
                }
                //UPDATE THE BREVIOUS BLOCK
                beforI =i;
            };
            k++;
        }
        EcrireDir(fichierDesination, i1, &buf1);
    }
    aff_entete(fichierDesination, 1, i1);
    aff_entete(fichierDesination, 2, j1);
}
//****************************************************************


/**
 * @brief Fragmentation function divides the personnel data from the source file into separate region files.
 * 
 * This function takes a source file pointer as input and creates separate region files for each region of the military.
 * The region files are named as "1RM-Blida", "2RM-Oran", "3RM-Bechar", "4RM-Ouargla", "5RM-Constantine", and "6RM-Tamanrasset".
 * The function uses the Ouvrire, creationFichRegionMilitaire, and Fermer functions to open, create, and close the region files respectively.
 * 
 * @param fichierSource Pointer to the source file containing personnel data.
 */
void Fragmentation(FILE *fichierSource) {
    FILE *f1, *f2, *f3, *f4, *f5, *f6;
    Ouvrire(&f1, "PERSONNEL-ANP_DZ.dat(1RM-Blida)", 'N');
    creationFichRegionMilitaire(fichierSource, "1RM-Blida", f1);
    Fermer(f1);
    Ouvrire(&f2, "PERSONNEL-ANP_DZ.dat(2RM-Oran)", 'N');
    creationFichRegionMilitaire(fichierSource, "2RM-Oran",  f2);
    Fermer(f2);
    Ouvrire(&f3, "PERSONNEL-ANP_DZ.dat(3RM-Bechar)", 'N');
    creationFichRegionMilitaire(fichierSource, "3RM-Bechar",  f3);
    Fermer(f3);
    Ouvrire(&f4, "PERSONNEL-ANP_DZ.dat(4RM-Ouargla)", 'N');
    creationFichRegionMilitaire(fichierSource, "4RM-Ouargla",  f4);
    Fermer(f4);
    Ouvrire(&f5, "PERSONNEL-ANP_DZ.dat(5RM-Constantine)", 'N');
    creationFichRegionMilitaire(fichierSource, "5RM-Constantine",  f5);
    Fermer(f5);
    Ouvrire(&f6, "PERSONNEL-ANP_DZ.dat(6RM-Tamanrasset)", 'N');
    creationFichRegionMilitaire(fichierSource, "6RM-Tamanrasset",  f6);
    Fermer(f6);
}

//****************************************************************

/**
 * @brief Removes a specific forceArme from the main file and updates the indexes.
 * 
 * This function removes a specific forceArme from the main file "PERSONNEL-ANP_DZ.dat" and updates the primary index and secondary index accordingly.
 * It first finds the address of the first record of the forceArme in the secondary index, then locates the corresponding record in the primary index.
 * It deletes the record from the main file and updates the indexes. It repeats this process for the rest of the records in the forceArme.
 * Finally, it saves the updated indexes.
 * 
 * @param forceArme The forceArme to be removed.
 */
void supprimerForceArme( char *forceArme) {
    int indice = getIndiceForce(forceArme);
        FILE *F;
    FILE *fich;
    FILE *Fi;
    FILE *fichierSource;
    Ouvrire(&fichierSource, "PERSONNEL-ANP_DZ.dat", 'A');
//    Ouvrire(&fic, "PERSONNEL-ANP_DZ.idx", 'A');
    Chargement_index(&indexP);
    Ouvrire(&fich,"FORCE_ARME_INDEX.idx",'A');
    Chargement_indexM(fich,&indexF);
    int i, j, nb;
    Buffer buf;
    int s, sCopy;
    int beforI;
    int k = 0;
    nb = indexP.nb;
    //POSITION OF THE FIRST RECORD OF THE FORCE ARME
    while(indice != indexF.tab[k].indice){
        k++;
    }
    //IF THE FILE IS NOT EMPTY
    if (k != indexF.nb) {
        _Bool trouv = false;
        //FIND THE ADRESS OF THE FIRST RECORD OF THE FORCE ARME IN THE PRIMARY INDEX
        rechDicoTableIndex(indexF.tab[k].cle, &trouv, &s, indexP);
        i = indexP.tab[s].adress.nbBloc;
        j = indexP.tab[s].adress.nbEnrg;
        beforI = i;
        buf = *alloc_bloc(fichierSource);
        LireDir(fichierSource, i, &buf);
        SuppersionEnrg(fichierSource,&buf,i,j,&indexP);
        suppersionIndex(s, &indexP);
        k++;
        // DO THE SAME FOR THE REST OF THE RECORDS IN THE FORCE ARME
        while (k < nb) {
            int cle =0;
            cle =indexF.tab[k].cle;
            //FIND THE ADRESS OF THE RECORD IN THE PRIMARY INDEX
            rechDicoTableIndex(cle, &trouv, &sCopy, indexP);
            if(indexF.tab[k].indice == indice && trouv) {
                s = sCopy;
                j = indexP.tab[s].adress.nbEnrg;
                i = indexP.tab[s].adress.nbBloc;
                //WE READ A NEW BUFFER JUST IF THE RECORD ADDRESS IS IN A NEW BLOCK
                if (i != beforI) {
                    buf = *alloc_bloc(fichierSource); // Refresh the buffer for each record
                    LireDir(fichierSource, i, &buf);
                }
                //DELETE THE RECORD FROM THE MAIN FILE AND UPDATE THE INDEXES
                SuppersionEnrg(fichierSource, &buf, i, j, &indexP);
                suppersionIndex(s, &indexP);
                //UPDATE THE PREVIOUS BLOCK
                beforI = i;
            };
            trouv =false;
            k++;
        }
    }
    int count = indexF.nb;
    for (int l = 0; l < count; ++l) {
        if(indexF.tab[l].indice == indice){
            suppressionIndexM(indexF.tab[l].cle,&indexF);
        }
    }

    //SAVE THE UPDATED INDEXES
    Sauvegarde_Index(indexP);
    Fermer(fichierSource);
    Sauvegarde_IndexM(fich,indexF);
    Fermer(fich);
}

//****************************************************************

/**
 * @brief Displays the military personnel with a specific rank.
 * 
 * This function displays the information of military personnel with a specified rank.
 * It uses a binary file containing the data of military personnel and two indexes:
 * a primary index and a secondary index to quickly access the records.
 * 
 * @param grade The specified rank.
 */
void afficherMilitaireParGrade(char *grade) {
    int indice = getGrade(grade);
    FILE *fichierSource;
    Ouvrire(&fichierSource, "PERSONNEL-ANP_DZ.dat", 'A');
    int i, j, nb;
    Buffer buf;
    int s, sCopy;
    int beforI;
    int k = 0;
    int z;
    nb = indexP.nb;
    //POSITION OF THE FIRST RECORD OF THE GRADE
    while(indice != indexG.tab[k].indice){
        k++;
    }
    //IF THE FILE IS NOT EMPTY
    if (k != indexG.nb) {
        bool trouv = false;
        //FIND THE ADRESS OF THE FIRST RECORD OF THE GRADE IN THE PRIMARY INDEX
        rechDicoTableIndex(indexG.tab[k].cle, &trouv, &s, indexP);
        if(trouv){
            i = indexP.tab[s].adress.nbBloc;
            j = indexP.tab[s].adress.nbEnrg;
            beforI = i;
            buf = *alloc_bloc(fichierSource);
            LireDir(fichierSource, i, &buf);
            //PRINT THE FIRST RECORD OF THE GRADE
            printf("%d/ %d %s  %s  %d  %d/%d/%d    %s  %s  %s  %s %s\n", 0, buf.tab[j].Matricule, buf.tab[j].Nom,
                   buf.tab[j].Prenom, buf.tab[j].Matricule, buf.tab[j].Date_Naissance.day,
                   buf.tab[j].Date_Naissance.month, buf.tab[j].Date_Naissance.year,
                   buf.tab[j].Wilaya_Naissance, buf.tab[j].Grade, buf.tab[j].Region_militaire,
                   buf.tab[j].Force_armee, getGradeAssocie(getIndiceGrade(buf.tab[j].Grade)));
        }
        trouv = false;
        k++;
        z = 1;
        // DO THE SAME FOR THE REST OF THE RECORDS OF THE GRADE
        while (k < nb) {
            if(indexG.tab[k].indice == indice) {
                int cle =0;
                cle =indexG.tab[k].cle;
                //FIND THE ADRESS OF THE RECORD IN THE PRIMARY INDEX
                rechDicoTableIndex(cle, &trouv, &sCopy, indexP);
                if(trouv){
                    s = sCopy;
                    j = indexP.tab[s].adress.nbEnrg;
                    i = indexP.tab[s].adress.nbBloc;
                    //WE READ A NEW BUFFER JUST IF THE RECORD ADDRESS IS IN A NEW BLOCK
                    if (i != beforI) {
                        buf = *alloc_bloc(fichierSource); // Refresh the buffer for each record
                        LireDir(fichierSource, i, &buf);
                    }
                    //PRINT THE RECORD
                    printf("%d/ %d %s  %s  %d  %d/%d/%d    %s  %s  %s  %s %s\n", z, buf.tab[j].Matricule, buf.tab[j].Nom,
                           buf.tab[j].Prenom, buf.tab[j].Matricule, buf.tab[j].Date_Naissance.day,
                           buf.tab[j].Date_Naissance.month, buf.tab[j].Date_Naissance.year,
                           buf.tab[j].Wilaya_Naissance, buf.tab[j].Grade, buf.tab[j].Region_militaire,
                           buf.tab[j].Force_armee,getGradeAssocie(getIndiceGrade(buf.tab[j].Grade)));
                    //UPDATE THE PREVIOUS BLOCK
                    beforI = i;
                    z++;
                }
            };
            k++;
        }
    } else {
        printf("il n'y a pas de militaire avec ce grade \n");
    }
    Fermer(fichierSource);
}

