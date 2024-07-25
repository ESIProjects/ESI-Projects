  /**--------------------------------------------------------**/
  /**       C o n v e r s i o n   Z vers C (Standard)        **/
  /**             Réalisée par Pr D.E ZEGOUR                 **/
  /**             E S I - Alger                              **/
  /**             Copywrite 2014                             **/
  /**--------------------------------------------------------**/

  #include <stdio.h>
  #include <stdlib.h>
  #include <Time.h>
  #include <math.h>

  typedef int bool ;

  #define True 1
  #define False 0

  /** Implémentation **\: ARBRE BINAIRE DE ENTIERS**/

  /** Arbres de recherche binaire **/

  typedef int Typeelem_Ai   ;
  typedef struct Noeud_Ai * Pointeur_Ai ;

struct Noeud_Ai{
      Typeelem_Ai  Val ;
      Pointeur_Ai Fg ;
      Pointeur_Ai Fd ;
      Pointeur_Ai Pere ;
} ;

Typeelem_Ai Info_Ai( Pointeur_Ai P )
{ return P->Val;   }

Pointeur_Ai Fg_Ai( Pointeur_Ai P)
{ return P->Fg ; }

Pointeur_Ai Fd_Ai( Pointeur_Ai P)
{ return P->Fd ; }

Pointeur_Ai Pere_Ai( Pointeur_Ai P)
{ return P->Pere ; }

void Aff_info_Ai ( Pointeur_Ai P, Typeelem_Ai Val){
       P->Val = Val ;
}

  void Aff_fg_Ai( Pointeur_Ai P, Pointeur_Ai Q)
    { P->Fg =  Q;  }

  void Aff_fd_Ai( Pointeur_Ai P, Pointeur_Ai Q)
    { P->Fd =  Q ; }

  void Aff_pere_Ai( Pointeur_Ai P, Pointeur_Ai Q)
    { P->Pere =  Q ; }

void Creernoeud_Ai( Pointeur_Ai *P){
      *P = (struct Noeud_Ai *) malloc( sizeof( struct Noeud_Ai))   ;
      (*P)->Fg = NULL;
      (*P)->Fd = NULL;
      (*P)->Pere = NULL;
}

  void Liberernoeud_Ai( Pointeur_Ai P)
    { free( P ) ; }


  /** Implémentation **\: PILE DE ARBRES BINAIRES DE ENTIERS**/
  /** Piles **/

  typedef Pointeur_Ai Typeelem_PAi ;
  typedef struct Maillon_PAi * Pointeur_PAi ;
  typedef   Pointeur_PAi  Typepile_PAi  ;

struct Maillon_PAi{
      Typeelem_PAi  Val ;
      Pointeur_PAi Suiv ;
} ;

  void Creerpile_PAi( Pointeur_PAi *P )
    { *P = NULL ; }

  bool Pilevide_PAi ( Pointeur_PAi P )
    { return  (P == NULL ); }

void Empiler_PAi ( Pointeur_PAi *P,  Typeelem_PAi Val ){
      Pointeur_PAi Q;

      Q = (struct Maillon_PAi *) malloc( sizeof( struct Maillon_PAi))   ;
      Q->Val = Val ;
      Q->Suiv = *P;
      *P = Q;
}

void Depiler_PAi ( Pointeur_PAi *P,  Typeelem_PAi *Val ){
      Pointeur_PAi Sauv;

      if (! Pilevide_PAi (*P) )
        {
          *Val = (*P)->Val ;
          Sauv = *P;
          *P = (*P)->Suiv;
          free(Sauv);
        }
      else printf ("%s \n", "Pile vide");
}

  /** Fonctions standards **/
  int Aleanombre( int N )
    { return ( rand() % N ); }

  /** Prototypes des fonctions **/

  void Liberer_ar (Pointeur_Ai *Rac);
  void Creer_ar (Pointeur_Ai *Racine , int X);
  void Rech (Pointeur_Ai Racine , int V , Pointeur_Ai *Per , Pointeur_Ai *Q);
  void Random_tree (Pointeur_Ai *Rac , int Nb_data);
  Pointeur_Ai Suiv_inordre (Pointeur_Ai Racine , int V) ;
  Pointeur_Ai Suiv_preordre (Pointeur_Ai Racine , int V) ;
  Pointeur_Ai Suiv_postordre (Pointeur_Ai Racine , int V) ;
  Pointeur_Ai Premier_inordre (Pointeur_Ai Racine) ;
  Pointeur_Ai Premier_preordre (Pointeur_Ai Racine) ;
  Pointeur_Ai Premier_postordre (Pointeur_Ai Racine) ;
  void Fusion_in_pre (Pointeur_Ai T1 , Pointeur_Ai T2 , Pointeur_Ai *T3);
  void Fusion_in_post (Pointeur_Ai T1 , Pointeur_Ai T2 , Pointeur_Ai *T3);
  void Fusion_pre_pre (Pointeur_Ai T1 , Pointeur_Ai T2 , Pointeur_Ai *T3);
  void Fusion_post_post (Pointeur_Ai T1 , Pointeur_Ai T2 , Pointeur_Ai *T3);
  void Fusion_pre_post (Pointeur_Ai T1 , Pointeur_Ai T2 , Pointeur_Ai *T3);
  int profondeur(Pointeur_Ai racine) ;
  int nbr_noeud(Pointeur_Ai racine , int niveau) ;
  int Hauteur_minimale(Pointeur_Ai racine) ;
  int Hauteur_maximale(Pointeur_Ai racine) ;
  Pointeur_Ai meilleur_arb(Pointeur_Ai T1 , Pointeur_Ai T2 , int niv) ;
  void Inordre (Pointeur_Ai Rac);
  void Preordre (Pointeur_Ai Rac);
  void Postordre (Pointeur_Ai Rac);

void Liberer_ar (Pointeur_Ai *Rac){
      /** Variables locales **/
      Pointeur_Ai _Px1=NULL;
      Pointeur_Ai _Px2=NULL;
      Pointeur_Ai _Px3=NULL;
      Pointeur_Ai _Px4=NULL;

      /** Corps du module **/
     if( ( *Rac != NULL )) {
       if( ( ( Fd_Ai ( *Rac ) == NULL ) && ( Fg_Ai ( *Rac ) == NULL ) )) {
         Liberernoeud_Ai ( *Rac ) ;
         }
       else
         {
         if( ( ( Fd_Ai ( *Rac ) != NULL ) && ( Fg_Ai ( *Rac ) != NULL ) )) {
           _Px1 =  Fd_Ai ( *Rac ) ;
           Liberer_ar ( &_Px1) ;
           _Px2 =  Fg_Ai ( *Rac ) ;
           Liberer_ar ( &_Px2) ;
           Liberernoeud_Ai ( *Rac ) ;
           }
         else
           {
           if( ( Fd_Ai ( *Rac ) != NULL )) {
             _Px3 =  Fd_Ai ( *Rac ) ;
             Liberer_ar ( &_Px3) ;
             Liberernoeud_Ai ( *Rac ) ;
             }
           else
             {
             _Px4 =  Fg_Ai ( *Rac ) ;
             Liberer_ar ( &_Px4) ;
             Liberernoeud_Ai ( *Rac ) ;

           }
         }
       } ;
       *Rac  =  NULL ;
     }
}

void Creer_ar (Pointeur_Ai *Racine , int X){
      /** Variables locales **/
      Pointeur_Ai R=NULL;

      /** Corps du module **/
     if( ( *Racine == NULL )) {
       Creernoeud_Ai (Racine ) ;
       Aff_info_Ai( *Racine , X ) ;
       }
     else
       {
       if( ( X <= Info_Ai( *Racine ) )) {
         R  =  Fg_Ai ( *Racine ) ;
         Creer_ar(&R , X ) ;
         Aff_fg_Ai (*Racine , R ) ;
         }
       else
         {
         R  =  Fd_Ai ( *Racine ) ;
         Creer_ar ( &R , X ) ;
         Aff_fd_Ai ( *Racine , R ) ;

       }
     }
}

void Rech (Pointeur_Ai Racine , int V , Pointeur_Ai *Per , Pointeur_Ai *Q){
      /** Variables locales **/
      bool Tr;

      /** Corps du module **/
     Tr  =  False ;
     *Per  =  NULL ;
     *Q  =  Racine ;
     while( ( *Q != NULL ) && ( Tr == False )) {
       if( ( V == Info_Ai ( *Q ) )) {
         Tr  =  True ;
         }
       else
         {
         *Per  =  *Q ;
         if( ( V < Info_Ai ( *Q ) )) {
           *Q  =  Fg_Ai ( *Q ) ;
           }
         else
           {
           *Q  =  Fd_Ai ( *Q ) ;

         }
       }
     }
}

void Random_tree (Pointeur_Ai *Rac , int Nb_data){
      /** Variables locales **/
      Pointeur_Ai P=NULL;
      Pointeur_Ai Q=NULL;
      int Cpt;
      int X;

      /** Corps du module **/
     Cpt  =  0 ;
     while( ( Cpt < Nb_data )) {
       X  =  Aleanombre(20000) ;
       Rech(*Rac , X , & P , & Q ) ;
       if( ( Q == NULL )) {
         Creer_ar ( Rac , X ) ;
         Cpt  =  Cpt + 1 ;

       }
     }
}

Pointeur_Ai Suiv_inordre (Pointeur_Ai Racine , int V){
      /** Variables locales **/
      Pointeur_Ai Suiv_inordre2 =NULL;
      Pointeur_Ai P=NULL;
      Pointeur_Ai Q=NULL;
      Pointeur_Ai T=NULL;
      Pointeur_PAi Pi=NULL;
      bool Tr;

      /** Corps du module **/
     Creerpile_PAi (&Pi ) ;
     Rech ( Racine , V , &P , &Q ) ;
     if( ( Q == NULL )) {
       Suiv_inordre2  =  NULL ;
       }
     else
       {
       if( ( Fd_Ai ( Q ) != NULL )) {
         T  =  Fd_Ai ( Q ) ;
         while( ( Fg_Ai ( T ) != NULL )) {
           T  =  Fg_Ai ( T ) ;

         } ;
         Suiv_inordre2  =  T ;
         }
       else
         {
         T  =  Racine ;
         P  =  NULL ;
         Tr  =  False ;
         while( ( Tr == False )) {
           if( ( T == Q )) {
             Tr  =  True ;

           } ;
           if( ( Info_Ai ( Q ) < Info_Ai ( T ) )) {
             P  =  T ;
             T  =  Fg_Ai ( T ) ;

           } ;
           if( ( Info_Ai ( Q ) > Info_Ai ( T ) )) {
             if( ( P == NULL )) {
               P  =  T ;
               T  =  Fd_Ai ( T ) ;
               }
             else
               {
               if( ( Fg_Ai ( P ) == T )) {
                 Empiler_PAi (& Pi , P ) ;

               } ;
               P  =  T ;
               T  =  Fd_Ai ( T ) ;

             }
           }
         } ;
         if( ( P == NULL )) {
           Suiv_inordre2  =  NULL ;
           }
         else
           {
           if( ( Fd_Ai ( P ) == T )) {
             if( ( Pilevide_PAi ( Pi ) )) {
               Suiv_inordre2  =  NULL ;
               }
             else
               {
               Depiler_PAi (& Pi , &T ) ;
               Suiv_inordre2  =  T ;

             } }
           else
             {
             Suiv_inordre2  =  P ;

           }
         }
       }
     }
     return Suiv_inordre2 ;
}

Pointeur_Ai Suiv_preordre (Pointeur_Ai Racine , int V){
      /** Variables locales **/
      Pointeur_Ai Suiv_preordre2 =NULL;
      Pointeur_Ai P=NULL;
      Pointeur_Ai Q=NULL;
      Pointeur_Ai T=NULL;
      Pointeur_PAi Pi=NULL;
      bool Tr;

      /** Corps du module **/
     Creerpile_PAi (& Pi ) ;
     Rech ( Racine , V , &P , &Q ) ;
     if( ( Q == NULL )) {
       Suiv_preordre2  =  NULL ;
       }
     else
       {
       if( ( Fg_Ai ( Q ) != NULL )) {
         Suiv_preordre2  =  Fg_Ai ( Q ) ;
         }
       else
         {
         T  =  Racine ;
         Tr  =  False ;
         while( ( Tr == False )) {
           if( ( Fd_Ai ( T ) != NULL )) {
             Empiler_PAi (& Pi , Fd_Ai ( T ) ) ;

           } ;
           if( ( T == Q )) {
             Tr  =  True ;
             }
           else
             {
             if( ( Info_Ai ( Q ) < Info_Ai ( T ) )) {
               T  =  Fg_Ai ( T ) ;
               }
             else
               {
               Depiler_PAi (&Pi , &T ) ;

             }
           }
         } ;
         if( ( Pilevide_PAi ( Pi ) )) {
           Suiv_preordre2  =  NULL ;
           }
         else
           {
           Depiler_PAi (& Pi , &T ) ;
           Suiv_preordre2  =  T ;

         }
       }
     }
     return Suiv_preordre2 ;
}

Pointeur_Ai Suiv_postordre (Pointeur_Ai Racine , int V){
      /** Variables locales **/
      Pointeur_Ai Suiv_postordre2 =NULL;
      Pointeur_Ai P=NULL;
      Pointeur_Ai Q=NULL;
      int _Px1;
      int _Px2;

      /** Corps du module **/
     Rech ( Racine , V , &P , &Q ) ;
     if( ( Q == NULL )) {
       Suiv_postordre2  =  NULL ;
       }
     else
       {
       if( ( P == NULL )) {
         Suiv_postordre2  =  NULL ;
         }
       else
         {
         if( ( ( Fd_Ai ( P ) == Q ) || ( Fd_Ai ( P ) == NULL ) )) {
           Suiv_postordre2  =  P ;
           }
         else
           {
           while( ( ( Fd_Ai ( Fd_Ai ( P ) ) != NULL ) && ( Fg_Ai ( Fd_Ai ( P ) ) == NULL ) )) {
             P  =  Fd_Ai ( P ) ;

           } ;
           _Px1 =  Info_Ai ( P ) ;
           P  =  Suiv_inordre ( Racine , _Px1) ;
           while( ( Fd_Ai ( P ) != NULL )) {
             _Px2 =  Info_Ai ( P ) ;
             P  =  Suiv_inordre ( Racine , _Px2) ;

           } ;
           Suiv_postordre2  =  P ;

         }
       }
     }
     return Suiv_postordre2 ;
}

Pointeur_Ai Premier_inordre (Pointeur_Ai Racine){
      /** Variables locales **/
      Pointeur_Ai Premier_inordre2 =NULL;
      Pointeur_Ai P=NULL;

      /** Corps du module **/
     P  =  Racine ;
     while( ( Fg_Ai ( P ) != NULL )) {
       P  =  Fg_Ai ( P ) ;

     } ;
     Premier_inordre2  =  P ;

     return Premier_inordre2 ;
}

Pointeur_Ai Premier_preordre (Pointeur_Ai Racine){
      /** Variables locales **/
      Pointeur_Ai Premier_preordre2 =NULL;

      /** Corps du module **/
     Premier_preordre2  =  Racine ;

     return Premier_preordre2 ;
}

Pointeur_Ai Premier_postordre (Pointeur_Ai Racine){
      /** Variables locales **/
      Pointeur_Ai Premier_postordre2 =NULL;
      Pointeur_Ai P=NULL;
      bool Tr;

      /** Corps du module **/
     P  =  Racine ;
     Tr  =  False ;
     while( ( Tr == False )) {
       while( ( Fg_Ai ( P ) != NULL )) {
         P  =  Fg_Ai ( P ) ;

       } ;
       if( ( Fd_Ai ( P ) != NULL )) {
         P  =  Fd_Ai ( P ) ;
         }
       else
         {
         Tr  =  True ;

       }
     } ;
     Premier_postordre2  =  P ;

     return Premier_postordre2 ;
}

void Fusion_in_pre (Pointeur_Ai T1 , Pointeur_Ai T2 , Pointeur_Ai *T3){
      /** Variables locales **/
      Pointeur_Ai P=NULL;
      Pointeur_Ai Q=NULL;
      int X;
      int Y;
      int Mini;
      int _Px1;
      int _Px2;
      int _Px3;
      int _Px4;

      /** Corps du module **/
     P  =  Premier_inordre ( T1 ) ;
     Q  =  Premier_preordre ( T2 ) ;
     while( ( ( P != NULL ) || ( Q != NULL ) )) {
       if( ( ( P != NULL ) && ( Q != NULL ) )) {
         X  =  Info_Ai ( P ) ;
         Y  =  Info_Ai ( Q ) ;
         if( ( X < Y )) {
           Mini  =  X ;
           _Px1 =  Info_Ai ( P ) ;
           P  =  Suiv_inordre ( T1 , _Px1) ;
           }
         else
           {
           Mini  =  Y ;
           _Px2 =  Info_Ai ( Q ) ;
           Q  =  Suiv_preordre ( T2 , _Px2) ;

         } }
       else
         {
         if( ( P != NULL )) {
           Mini  =  Info_Ai ( P ) ;
           _Px3 =  Info_Ai ( P ) ;
           P  =  Suiv_inordre ( T1 , _Px3) ;
           }
         else
           {
           Mini  =  Info_Ai ( Q ) ;
           _Px4 =  Info_Ai ( Q ) ;
           Q  =  Suiv_preordre ( T2 , _Px4) ;

         }
       } ;
       Creer_ar (T3 , Mini ) ;

     }
}

void Fusion_in_post (Pointeur_Ai T1 , Pointeur_Ai T2 , Pointeur_Ai *T3){
      /** Variables locales **/
      Pointeur_Ai P=NULL;
      Pointeur_Ai Q=NULL;
      int X;
      int Y;
      int Mini;
      int _Px1;
      int _Px2;
      int _Px3;
      int _Px4;

      /** Corps du module **/
     P  =  Premier_inordre ( T1 ) ;
     Q  =  Premier_postordre ( T2 ) ;
     while( ( ( P != NULL ) || ( Q != NULL ) )) {
       if( ( ( P != NULL ) && ( Q != NULL ) )) {
         X  =  Info_Ai ( P ) ;
         Y  =  Info_Ai ( Q ) ;
         if( ( X < Y )) {
           Mini  =  X ;
           _Px1 =  Info_Ai ( P ) ;
           P  =  Suiv_inordre ( T1 , _Px1) ;
           }
         else
           {
           Mini  =  Y ;
           _Px2 =  Info_Ai ( Q ) ;
           Q  =  Suiv_postordre ( T2 , _Px2) ;

         } }
       else
         {
         if( ( P != NULL )) {
           Mini  =  Info_Ai ( P ) ;
           _Px3 =  Info_Ai ( P ) ;
           P  =  Suiv_inordre ( T1 , _Px3) ;
           }
         else
           {
           Mini  =  Info_Ai ( Q ) ;
           _Px4 =  Info_Ai ( Q ) ;
           Q  =  Suiv_postordre ( T2 , _Px4) ;

         }
       } ;
       Creer_ar ( T3 , Mini ) ;

     }
}

void Fusion_pre_pre (Pointeur_Ai T1 , Pointeur_Ai T2 , Pointeur_Ai *T3){
      /** Variables locales **/
      Pointeur_Ai P=NULL;
      Pointeur_Ai Q=NULL;
      int X;
      int Y;
      int Mini;
      int _Px1;
      int _Px2;
      int _Px3;
      int _Px4;

      /** Corps du module **/
     P  =  Premier_preordre ( T1 ) ;
     Q  =  Premier_preordre ( T2 ) ;
     while( ( ( P != NULL ) || ( Q != NULL ) )) {
       if( ( ( P != NULL ) && ( Q != NULL ) )) {
         X  =  Info_Ai ( P ) ;
         Y  =  Info_Ai ( Q ) ;
         if( ( X < Y )) {
           Mini  =  X ;
           _Px1 =  Info_Ai ( P ) ;
           P  =  Suiv_preordre ( T1 , _Px1) ;
           }
         else
           {
           Mini  =  Y ;
           _Px2 =  Info_Ai ( Q ) ;
           Q  =  Suiv_preordre ( T2 , _Px2) ;

         } }
       else
         {
         if( ( P != NULL )) {
           Mini  =  Info_Ai ( P ) ;
           _Px3 =  Info_Ai ( P ) ;
           P  =  Suiv_preordre ( T1 , _Px3) ;
           }
         else
           {
           Mini  =  Info_Ai ( Q ) ;
           _Px4 =  Info_Ai ( Q ) ;
           Q  =  Suiv_preordre ( T2 , _Px4) ;

         }
       } ;
       Creer_ar ( T3 , Mini ) ;

     }
}

void Fusion_post_post (Pointeur_Ai T1 , Pointeur_Ai T2 , Pointeur_Ai *T3){
      /** Variables locales **/
      Pointeur_Ai P=NULL;
      Pointeur_Ai Q=NULL;
      int X;
      int Y;
      int Mini;
      int _Px1;
      int _Px2;
      int _Px3;
      int _Px4;

      /** Corps du module **/
     P  =  Premier_postordre ( T1 ) ;
     Q  =  Premier_postordre ( T2 ) ;
     while( ( ( P != NULL ) || ( Q != NULL ) )) {
       if( ( ( P != NULL ) && ( Q != NULL ) )) {
         X  =  Info_Ai ( P ) ;
         Y  =  Info_Ai ( Q ) ;
         if( ( X < Y )) {
           Mini  =  X ;
           _Px1 =  Info_Ai ( P ) ;
           P  =  Suiv_postordre ( T1 , _Px1) ;
           }
         else
           {
           Mini  =  Y ;
           _Px2 =  Info_Ai ( Q ) ;
           Q  =  Suiv_postordre ( T2 , _Px2) ;

         } }
       else
         {
         if( ( P != NULL )) {
           Mini  =  Info_Ai ( P ) ;
           _Px3 =  Info_Ai ( P ) ;
           P  =  Suiv_postordre ( T1 , _Px3) ;
           }
         else
           {
           Mini  =  Info_Ai ( Q ) ;
           _Px4 =  Info_Ai ( Q ) ;
           Q  =  Suiv_postordre ( T2 , _Px4) ;

         }
       } ;
       Creer_ar (T3 , Mini ) ;

     }
}

void Fusion_pre_post (Pointeur_Ai T1 , Pointeur_Ai T2 , Pointeur_Ai *T3){
      /** Variables locales **/
      Pointeur_Ai P=NULL;
      Pointeur_Ai Q=NULL;
      int X;
      int Y;
      int Mini;
      int _Px1;
      int _Px2;
      int _Px3;
      int _Px4;

      /** Corps du module **/
     P  =  Premier_preordre ( T1 ) ;
     Q  =  Premier_postordre ( T2 ) ;
     while( ( ( P != NULL ) || ( Q != NULL ) )) {
       if( ( ( P != NULL ) && ( Q != NULL ) )) {
         X  =  Info_Ai ( P ) ;
         Y  =  Info_Ai ( Q ) ;
         if( ( X < Y )) {
           Mini  =  X ;
           _Px1 =  Info_Ai ( P ) ;
           P  =  Suiv_preordre ( T1 , _Px1) ;
           }
         else
           {
           Mini  =  Y ;
           _Px2 =  Info_Ai ( Q ) ;
           Q  =  Suiv_postordre ( T2 , _Px2) ;

         } }
       else
         {
         if( ( P != NULL )) {
           Mini  =  Info_Ai ( P ) ;
           _Px3 =  Info_Ai ( P ) ;
           P  =  Suiv_preordre ( T1 , _Px3) ;
           }
         else
           {
           Mini  =  Info_Ai ( Q ) ;
           _Px4 =  Info_Ai ( Q ) ;
           Q  =  Suiv_postordre ( T2 , _Px4) ;

         }
       } ;
       Creer_ar ( T3 ,Mini ) ;

     }
}

int profondeur(Pointeur_Ai racine){
if (Fd_Ai(racine) == NULL && Fg_Ai(racine) == NULL ) return 0 ;
if(Fd_Ai(racine) == NULL ) return 1 + profondeur(Fg_Ai(racine)) ;
if(Fg_Ai(racine) == NULL ) return 1 + profondeur(Fd_Ai(racine)) ;
if(profondeur(Fd_Ai(racine)) > profondeur(Fg_Ai(racine))) return 1+profondeur(Fd_Ai(racine)) ;
return 1+profondeur(Fg_Ai(racine)) ;
}

int nbr_noeud(Pointeur_Ai racine , int niveau){
if(niveau == 0) return 1 ;
if(Fd_Ai(racine) == NULL && Fg_Ai(racine) == NULL) return 0 ;
if(Fd_Ai(racine) != NULL && Fg_Ai(racine) == NULL) return nbr_noeud(Fd_Ai(racine) , niveau - 1) ;
if(Fd_Ai(racine) == NULL && Fg_Ai(racine) != NULL) return nbr_noeud(Fg_Ai(racine) , niveau - 1) ;
return nbr_noeud(Fd_Ai(racine) , niveau - 1) + nbr_noeud(Fg_Ai(racine) , niveau - 1) ;
}

int Hauteur_minimale(Pointeur_Ai racine){
if(racine == NULL) return -1 ;
if (Fd_Ai(racine) == NULL && Fg_Ai(racine) == NULL ) return 0 ;
if(Fd_Ai(racine) == NULL ) return 1 + Hauteur_minimale(Fg_Ai(racine)) ;
if(Fg_Ai(racine) == NULL ) return 1 + Hauteur_minimale(Fd_Ai(racine)) ;
if(Hauteur_minimale(Fd_Ai(racine)) < Hauteur_minimale(Fg_Ai(racine))) return 1+Hauteur_minimale(Fd_Ai(racine)) ;
return 1+Hauteur_minimale(Fg_Ai(racine)) ;
}

int Hauteur_maximale(Pointeur_Ai racine){
if(racine == NULL) return -1 ;
if (Fd_Ai(racine) == NULL && Fg_Ai(racine) == NULL ) return 0 ;
if(Fd_Ai(racine) == NULL ) return 1 + Hauteur_maximale(Fg_Ai(racine)) ;
if(Fg_Ai(racine) == NULL ) return 1 + Hauteur_maximale(Fd_Ai(racine)) ;
if(Hauteur_maximale(Fd_Ai(racine)) < Hauteur_maximale(Fg_Ai(racine))) return 1+Hauteur_maximale(Fd_Ai(racine)) ;
return 1+Hauteur_maximale(Fg_Ai(racine)) ;
}

Pointeur_Ai meilleur_arb(Pointeur_Ai T1 , Pointeur_Ai T2 , int niv){ //simulation
int pointT1 = 0 , pointT2 = 0 ;
/*int H_Min1 = Hauteur_minimale(T1) , H_Min2 = Hauteur_minimale(T2) ;
int H_Max1 = Hauteur_maximale(T1) , H_Max2 = Hauteur_maximale(T2) ;*/ //enlevez ces commentaires tester les hauteurs , mais l'éxécution va ètre trés lente
int nbr1 , nbr2 ;
 for(int i = niv/2 ; i <= niv ; i++){ //vérifier de moitié de niveaux à niveau max qui a le plus de noeud dans cet niveau i
     nbr1 = nbr_noeud(T1,i);
     nbr2 = nbr_noeud(T2,i);
  if(nbr1 < nbr2) pointT2 ++ ;
  if(nbr1 > nbr2) pointT1 ++ ;
 }

/*if(H_Min1 < H_Min2) pointT2++ ; //plus hauteur minimale s'approche à la profondeur , c'est mieux
 if(H_Min1 > H_Min2) pointT1++ ;

 if(H_Max1 > H_Max2) pointT2++ ; //mème idée
 if(H_Max1 < H_Max2) pointT1++ ; *///enlevez ces commentaires tester les hauteurs , mais l'éxécution va ètre trés lente

 if(pointT1 < pointT2) return T2 ;
 if(pointT1 == pointT2) return NULL ;
 return T1 ;

}

void Inordre (Pointeur_Ai Rac){
     /** Corps du module **/
     if( Rac != NULL) {
       Inordre ( Fg_Ai(Rac)) ;
       printf ( " %d", Info_Ai(Rac) ) ;
       Inordre ( Fd_Ai(Rac)) ;
     }
}

void Preordre (Pointeur_Ai Rac){
      /** Corps du module **/
     if( Rac != NULL) {
       printf ( " %d", Info_Ai(Rac) ) ;
       Preordre (Fg_Ai ( Rac )) ;
       Preordre (Fd_Ai ( Rac )) ;
     }
}

void Postordre (Pointeur_Ai Rac){
      /** Corps du module **/
     if( Rac != NULL) {
       Postordre (Fg_Ai ( Rac )) ;
       Postordre (Fd_Ai ( Rac )) ;
       printf ( " %d", Info_Ai(Rac) ) ;
     }
    }

int main(int argc, char *argv[]){
     srand(time(NULL));
     /** Variables du programme principal **/
  Pointeur_Ai A1=NULL;
  Pointeur_Ai A2=NULL;
  Pointeur_Ai A3=NULL;
  Pointeur_Ai A4 = NULL ; //il va enregistrer la racine du dernière fusion
  int Best_Fusion ; //il va enregistrer la meilleur cas de fusion entre deux candidats
  int n  ;
  int Point_In_Pre = 0 ;
  int Point_In_Post = 0 ;
  int Point_Pre_Pre= 0 ;
  int Point_Post_Post = 0 ;
  int Point_Pre_Post = 0 ;
  int I;
  int J , K;
  int Niveau ;
  Pointeur_PAi P ; //pour empiler la dernière fusion ;
  Creerpile_PAi(&P) ;


     printf ("Bienvenue dans le TP ALGO03 !!\n" ) ;
     printf ("On espere de pouvoir vous montrer nos efforts avec ce programme\n" ) ;
     printf ("                          Realise par : Tati Youcef//Hamroun Mohamed Ali//Section B : G05\n" ) ;
     printf ("\n" ) ;
     printf ("\n" ) ;
     printf ("\n" ) ;
     printf ("\n" ) ;

     printf("choisissez le nombre d elements pour A1 et A2 : ");
     scanf("%d",&n) ; //l'utilisateur va choisir le nombre d'éléments de A1 et A2 (vous pouvez choisir 10000 pour suivre le TP)
     fflush(stdin) ; //pour éviter l'erreur des sauts des lectures
     printf("pressez 'entrer' pour commencer les fusions... ");
     getchar() ; //attendre bouton entrer
     Niveau = (int) log(2*n+1)/log(2) - 1;//niveau le plus bas et le plus équilibré est donné par l'expression car 2^(niv+1) - 1 = 2n ----> donc le plus haut niveau possible pour arbre strictemment binaire est "Niveau"
     system("cls") ; //clear screen

    /*----------------------------------COMMENCER LA GRANDE BOUCLE-----------------------------------*/
     for( I  =  1 ;I <=  3 ; ++I){
     Niveau = 10 ;
     printf("N = %d\n",2*n);

       printf ("***Generation de A1***\n" ) ;
       Random_tree ( &A1 , n) ; //générer A1 à n éléments

       /*printf ( "voici A1 en preordre : \n" ) ; //enlevez ces commentaires pour voir la validation
       Preordre ( A1 ) ;
       printf("\n") ;
       printf ("voici A1 en inordre : \n" ) ; //ces affichages servent à montrer au lecteur les données de A1
       Inordre ( A1 ) ;
       printf("\n") ;
       printf ("voici A1 en postordre : \n" ) ;
       Postordre ( A1 ) ;
       printf("\n") ;*/

       printf ("***Generation de A2***\n" ) ;
       Random_tree ( & A2 , n) ; //générer A2 à n éléments

      /* printf ("voici A2 en preordre : \n" ) ; //enlevez ces commentaires pour voir la validation
       Preordre ( A2 ) ;
       printf("\n") ;
       printf ( "voici A2 en postordre : \n" ) ; //ces affichages servent à montrer au lecteur les données de A2
       Postordre ( A2 ) ;                        //pas besoin de Inordre puisque c'est pas utilisée pour A2
       printf("\n") ;*/

    /*-------------------------------------COMMENCER TOUS LES FUSIONS-----------------------------*/
       for( J  =  1 ;J <=  5 ; ++J){
        switch(J){
         case 1 : /*-------------------------------------------Fusion Inordre_Preordre--------------------------------------------*/
        printf ("--------------------------------------------------------------\n" ) ;
          printf ("Fusion In_Pre:\n" ) ;
           Fusion_in_pre (  A1 ,  A2 , & A3 ) ; //Fusion et la générer dans A3

           /*printf ("preparer la validation de cette fusion : \n" ) ;
           printf ("voici le resultat A3: \n" ) ;  //enlevez ces commentaires pour voir la validation
           printf ("son preordre : \n" ) ;
           Preordre (  A3 ) ;
           printf("\n") ;
           printf ("son inordre : \n" ) ; //validation
           Inordre (  A3 ) ;
           printf("\n") ;
           printf ("son postordre : \n" ) ;
           Postordre (  A3 ) ;
           printf("\n") ;*/


           printf ("Fusion Inordre Preordre terminee\n" ) ;
           printf ("--------------------------------------------------------------\n" ) ;
           for(K = 0 ; K<=Niveau ; K++) printf("niveau %d : %d\n",K , nbr_noeud(A3 , K));
           printf ("--------------------------------------------------------------\n" ) ;

           A4 = A3 ; //pour enregistrer la racine
           A3 = NULL ;
         break ;
         case 2 :
/*-------------------------------------------Fusion Inordre_Postordre--------------------------------------------*/
          printf ("Fusion In_Post: \n" ) ;
          Fusion_in_post ( A1 , A2 , & A3 ) ; //Fusion et la générer dans A3

          /*printf ("preparer la validation de cette fusion : \n" ) ; //enlevez ces commentaires pour voir la validation
          printf ("voici le resultat A3: \n" ) ;
          printf ("son preordre : \n" ) ;
          Preordre (  A3 ) ;
          printf("\n") ;
          printf ( " %s", "son inordre : \n" ) ;
          Inordre (  A3 ) ;
          printf("\n") ;
          printf ( " %s", "son postordre : \n" ) ; //validation
          Postordre ( A3 ) ;
          printf("\n") ;*/
          printf ("Fusion Inordre Postordre terminee\n" ) ;
          printf ("--------------------------------------------------------------\n" ) ;
          for(K = 0 ; K<=Niveau ; K++) printf("niveau %d : %d\n",K , nbr_noeud(A3 , K));
          printf ("--------------------------------------------------------------\n" ) ;

  /*---------------------------------COMPARER ENTRE LA FUSION 1 ET 2 : -----------------------------------------*/
        if(meilleur_arb(A3 , A4 , Niveau)==NULL) Liberer_ar(&A3);//égualité , rien ne change
         else{
          if(meilleur_arb(A3 , A4 , Niveau) == A3){
           Liberer_ar(&A4) ;
           A4 = A3 ; //mis à jour de la racine gagnante et libérer la perdante
           Best_Fusion = 2 ; // cas 2 est pour le moment le plus efficace
           A3 = NULL ;
          } else {
           Liberer_ar(&A3) ; //libérer la perdante , A4 a gagné donc pas besoin de mis à jour
           Best_Fusion = 1 ;  // cas 1 est pour le moment le plus efficace
          }
        }
         break ;
         case 3 :
/*----------------------------------------Fusion Preordre_Preordre------------------------------------*/
          printf ("Fusion Pre_Pre:\n" ) ;
          Fusion_pre_pre ( A1 , A2 , & A3 ) ;//Fusion et la générer dans A3

          /*printf ("preparer la validation de cette fusion : \n" ) ; //enlevez ces commentaires pour voir la validation
          printf ("voici le resultat A3: \n" ) ;
          printf ("son preordre : \n" ) ;
          Preordre ( A3 ) ;
          printf("\n") ;
          printf ("son inordre : \n" ) ; //validation
          Inordre ( A3 ) ;
          printf("\n") ;
          printf ("son postordre : \n" ) ;
          Postordre ( A3 ) ;
          printf("\n") ;*/

          printf ("Fusion Preordre Preordre terminee\n" ) ;
          printf ("--------------------------------------------------------------\n" ) ;
          for(K = 0 ; K<=Niveau ; K++) printf("niveau %d : %d\n",K , nbr_noeud(A3 , K));
          printf ("--------------------------------------------------------------\n" ) ;

/*-------------------------------------COMPARER ENTRE LA FUSION gagnante avant ET 3 : ------------------------------------------*/
          if(meilleur_arb(A3 , A4 , Niveau)==NULL) Liberer_ar(&A3);//égualité , rien ne change
         else{
            if(meilleur_arb(A3 , A4 , Niveau) == A3){
           Liberer_ar(&A4) ;
           A4 = A3 ; //mis à jour de la racine gagnante et libérer la perdante
           Best_Fusion = 3 ; // cas 2 est pour le moment le plus efficace
           A3 = NULL ;
          } else  Liberer_ar(&A3) ; //libérer la perdante , A4 a gagné donc pas besoin de mis à jour
         }
         break ;
         case 4 :
/*--------------------------------------------Fusion Postordre_Postordre---------------------------------------------------*/
          printf ("Fusion Post_Post:\n" ) ;
          Fusion_post_post ( A1 , A2 , & A3 ) ;//Fusion et la générer dans A3

          /*printf ("preparer la validation de cette fusion : \n " ) ;
          printf ("voici le resultat A3: \n " ) ;
          printf ("son preordre : \n" ) ;
          Preordre ( A3 ) ;
          printf("\n") ;
          printf ("son inordre : \n " ) ; //validation
          Inordre ( A3 ) ;
          printf("\n") ;
          printf ("son postordre : \n" ) ;
          Postordre ( A3 ) ;
          printf("\n") ;*/

          printf ("Fusion Postordre Postordre terminee\n" ) ;
          printf ("--------------------------------------------------------------\n" ) ;
          for(K = 0 ; K<=Niveau ; K++) printf("niveau %d : %d\n",K , nbr_noeud(A3 , K));
           printf ("--------------------------------------------------------------\n" ) ;

/*----------------------------COMPARER ENTRE LA FUSION gagnante avant ET 4 : -------------------------------*/
         if(meilleur_arb(A3 , A4 , Niveau)==NULL) Liberer_ar(&A3);//égualité , rien ne change
         else{
           if(meilleur_arb(A3 , A4 , Niveau) == A3){
           Liberer_ar(&A4) ;
           A4 = A3 ; //mis à jour de la racine gagnante et libérer la perdante
           Best_Fusion = 4 ; // cas 2 est pour le moment le plus efficace
           A3 = NULL ;
          } else  Liberer_ar(&A3) ; //libérer la perdante , A4 a gagné donc pas besoin de mis à jour
         }
         break ;
         case 5 :
/*-------------------------------------Fusion Preordre_Postordre--------------------------------------------*/
         printf ("Fusion Pre_Post:\n" ) ;
         Fusion_pre_post ( A1 , A2 , & A3 ) ;//Fusion et la générer dans A3

         /*printf ("preparer la validation de cette fusion : \n" ) ;
         printf ("voici le resultat A3: \n" ) ;
         printf ("son preordre : \n" ) ;
         Preordre ( A3 ) ;
         printf("\n") ;
         printf ("son inordre : \n" ) ; //validation
         Inordre ( A3 ) ;
         printf("\n") ;
         printf ("son postordre : \n" ) ;
         Postordre ( A3 ) ;
         printf("\n") ;*/

         printf ("Fusion Preordre Postordre terminee\n" ) ;
         printf ("--------------------------------------------------------------\n" ) ;
         for(K = 0 ; K<=Niveau ; K++) printf("niveau %d : %d\n",K , nbr_noeud(A3 , K));
           printf ("--------------------------------------------------------------\n" ) ;

/*--------------------------COMPARER ENTRE LA FUSION gagnante avant ET 5 : ---------------------*/
         if(meilleur_arb(A3 , A4 , Niveau)==NULL) Liberer_ar(&A3);//égualité , rien ne change
         else{
           if(meilleur_arb(A3 , A4 , Niveau) == A3){
           Liberer_ar(&A4) ;
           A4 = A3 ; //mis à jour de la racine gagnante et libérer la perdante
           Best_Fusion = 5 ; // cas 2 est pour le moment le plus efficace
          } else  Liberer_ar(&A3) ; //libérer la perdante , A4 a gagné donc pas besoin de mis à jour
         }
         break ;
        }
       }
       if(A3 == NULL) Liberer_ar(&A4);
       else Liberer_ar(&A3) ;
       Liberer_ar(&A1) ;
       Liberer_ar(&A2) ;
       printf ("iteration numero %d terminee \n",I);
       printf("*******************************************************\n");

/*--------------------DONNER UN POINT AU FUSION GANGNANTE POUR CETTE BOUCLE :------------------------*/
 switch(Best_Fusion){
   case 1 : Point_In_Pre++ ;
    break ;
   case 2 : Point_In_Post++ ;
    break ;
   case 3 : Point_Pre_Pre++ ;
    break ;
   case 4 : Point_Post_Post++ ;
    break ;
   case 5 : Point_Pre_Post++ ;
    break ;
}

}

printf("\n") ;
printf("\n") ;
printf("\n") ;
printf("Fin de traitement !") ;
printf("\n") ;
printf("\n") ;
printf("pressez le bouton 'Enter' pour voir les resultats des fusions realisees ");
getchar() ;
system("cls") ;

printf("voici combien chaque Fusion etait la plus efficace entre les autres : \n");
printf("Fusion Inordre Preordre : %d\n",Point_In_Pre);
printf("Fusion Inordre Postordre : %d\n",Point_In_Post);
printf("Fusion Preordre Preordre : %d\n",Point_Pre_Pre);
printf("Fusion Postordre Postordre : %d\n",Point_Post_Post);
printf("Fusion Preordre Postordre: %d\n",Point_Pre_Post);

return 0;

}
