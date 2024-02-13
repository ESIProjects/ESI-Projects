//
// Created by  Apple on 12/22/23.
//

#include "machine_abtraite.h"
#include <stdio.h>


//--------------------------------------machine abstraite--------------------------
// Ouvrire : le fichier f de avec son nom est nom en mode ancien(mode =='A') ou bien mode nouveau(mode =='N')
/**
 * Opens a file with the specified name and mode.
 * If the mode is 'A', the file is opened for reading and writing, and the file header is read.
 * If the mode is 'N', the file is opened for writing, and the file header is initialized and written.
 * If the mode is neither 'A' nor 'N', an error message is printed and the file pointer is set to NULL.
 *
 * @param fichier A pointer to a file pointer.
 * @param nom The name of the file to be opened.
 * @param mode The mode in which to open the file ('A' for append, 'N' for new).
 */
void Ouvrire(FILE **fichier, char nom[30], char mode) {
    if (mode == 'A') {
        *fichier = fopen(nom, "rb+");
        header.nbBloc = entete(*fichier,1);
        header.nbEnrgDernierBloc = entete(*fichier,2);
//        fread(&header, sizeof(Entete), 1, *fichier);
    } else if (mode == 'N') {
        *fichier = fopen(nom, "wb+");
        aff_entete(*fichier, 1, 0);
        aff_entete(*fichier, 2, 0);
        fwrite(&header, sizeof(Entete), 1, *fichier);
    } else {
        printf("Erreur : le mode est incorrect\n\n");
        *fichier = NULL;
    }
}
//*******************************************************************************
/**
 * Closes the file and writes the header information to it.
 *
 * @param fichier The file to be closed.
 */
void Fermer(FILE *fichier) {
    fclose(fichier) ;
}
//*******************************************************************************

/**
 * Reads a specific buffer from a file.
 *
 * @param fichier The file to read from.
 * @param i The index of the buffer to read.
 * @param buffer The buffer to store the read data.
 */
//void LireDir(FILE *fichier , int i , Buffer *buffer) {
//    fseek(fichier , sizeof(Entete) , SEEK_SET) ;
//    fseek(fichier , sizeof(Buffer)*(i-1) , SEEK_CUR) ;
//    fread(buffer , sizeof(Buffer) , 1 , fichier ) ;
//}
bool LireDir(FILE* fichier, int i, Buffer* buff) {
    if (fichier == NULL || i <= 0 || fseek(fichier, (i - 1) * sizeof(Buffer) + sizeof(Entete), SEEK_SET) != 0) {
        return false;
    }

    if (fread(buff, sizeof(Buffer), 1, fichier) != 1) {
        return false;  // Check if the read was successful
    }
    Lecture+=1;
    return true;
}
//*******************************************************************************
/**
 * Writes the contents of a Buffer structure to a specific position in a file.
 *
 * @param fichier The file pointer to write to.
 * @param i The position in the file to write to (1-based index).
 */
void EcrireDir(FILE *fichier , int i , Buffer *buff) {
    fseek(fichier , sizeof(Entete) , SEEK_SET) ;
    fseek(fichier , sizeof(Buffer)*(i-1) , SEEK_CUR) ;
    fwrite(buff , sizeof(Buffer) , 1 , fichier ) ;
    Ecriture+=1;
}

//*******************************************************************************
/**
 * Retrieves information from the file header.
 *
 * @param fichier The file pointer to the file.
 * @param i The type of information to retrieve (1 for the last block number, 2 for the number of characters inserted).
 * @return The requested information, or -1 if an error occurs.
 */
int entete(FILE *fich , int i) {
    if (fich == NULL) {
        printf("Il faut ouvrir le fichier\n\n") ;
        return -1 ;
    }
    else {
        rewind(fich) ;
        fread(&header , sizeof(Entete) , 1 , fich) ;
        switch (i) {
            case 1: {
                return (header.nbBloc); // Returns the number of the last block
                break;
            }
            case 2: {
                return (header.nbEnrgDernierBloc); // Returns the number of characters inserted
                break;
            }
            default:
                return -1;
        }
    }
}

//*******************************************************************************
/**
 * Updates the file header.
 *
 * @param fichier The file pointer to the file.
 * @param i The type of information to update (1 for the last block number, 2 for the number of characters inserted).
 * @param valeur The new value of the information.
 */
void aff_entete(FILE *fichier, int i ,int valeur) {
    rewind(fichier) ;
    switch (i) {
        case 1 : {
            header.nbBloc = valeur;
            break;
        }
        case 2:{
            header.nbEnrgDernierBloc = valeur;
            break;
        }
        default: {
            printf("le caracteristique n\'exist pas!\n\n") ;
            exit(0) ;
        }
    }
    fwrite(&header , sizeof(Entete) , 1 , fichier) ;
}
//*******************************************************************************
/**
 * Allocates memory for a Buffer structure.
 *
 * @param fichier The file pointer.
 * @return A pointer to the allocated Buffer structure.
 */
Buffer* alloc_bloc(FILE *fichier){
    return (Buffer *)malloc(sizeof(Buffer));
}

//-----------------------------------------------------------------------------------------------//
/** Machine abstraite pour un fichier TOF (Dans notre cas : le fichier de sauvegarde d'index ) **/

void EcrireDirIP(FILE *fichier , int i , BufferIndexP *buffi) {
    fseek(fichier , sizeof(Entete) , SEEK_SET) ;
    fseek(fichier , sizeof(BufferIndexP)*(i-1) , SEEK_CUR) ;
    fwrite(buffi , sizeof(BufferIndexP) , 1 , fichier ) ;
    Ecriture+=1;
}


void LireDirIP(FILE *fichier , int i , BufferIndexP *buff) {
    fseek(fichier , sizeof(Entete) , SEEK_SET) ;
    fseek(fichier , sizeof(BufferIndexP)*(i-1) , SEEK_CUR) ;
    fread(buff , sizeof(BufferIndexP) , 1 , fichier ) ;
    Lecture+=1;
}


BufferIndexP *alloc_bloci() {
    return (BufferIndexP *)malloc(sizeof(BufferIndexP));
}




void EcrireDirIM(FILE *fichier , int i , BufferIndexM *buffi) {
    fseek(fichier , sizeof(Entete) , SEEK_SET) ;
    fseek(fichier , sizeof(BufferIndexM)*(i-1) , SEEK_CUR) ;
    fwrite(buffi , sizeof(BufferIndexM) , 1 , fichier ) ;
    Ecriture+=1;
}


void LireDirIM(FILE *fichier , int i , BufferIndexM *buffi) {
    fseek(fichier , sizeof(Entete) , SEEK_SET) ;
    fseek(fichier , sizeof(BufferIndexM)*(i-1) , SEEK_CUR) ;
    fread(buffi , sizeof(BufferIndexM) , 1 , fichier ) ;
    Lecture+=1;
}


BufferIndexM * alloc_blociM(){
    return (BufferIndexM *)malloc(sizeof(BufferIndexM));
}
