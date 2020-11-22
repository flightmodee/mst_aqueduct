#include "tas.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// = = = = = = = = = = = = = = EXERCICE 2  = = = = = = = = = = = = = = = = = = = = = =
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


edge_t* edge_create(int n1, int n2, int poids)
{
  edge_t* res = (edge_t*) malloc(sizeof(edge_t)) ;

  res->vertix1 = n1 ;
  res->vertix2 = n2 ;
  res->weight = poids ;

  return res ;
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


tas_t* tas_create(int max)
{
  tas_t* res = (tas_t*) malloc( sizeof(tas_t) );

  res->tab = (edge_t*) malloc( sizeof(edge_t) * max );
  res->max = max;
  res->taille = 0;
  
  return res;
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


void inserer_tas (tas_t *T, edge_t x)
{
  if (T==NULL) {
      printf("Tas non valide !\n\n") ;
      return ;
    }
  
  else if (T->taille == T->max) {
      printf("Tas rempli !\n\n") ;
      return ;
    }

  T->tab[T->taille] = x ;
  T->taille += 1 ;

  entasser(T, (T->taille)-1) ;
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


void echanger(tas_t * tas, int pos1, int pos2){
    edge_t tmp = tas->tab[pos2];
    tas->tab[pos2] = tas->tab[pos1];
    tas->tab[pos1] = tmp;
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


int parent (int pos){
    return (pos-1)/2;
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


void entasser(tas_t * tas, int pos)
{
    while (tas->tab[parent(pos)].weight < tas->tab[pos].weight && pos > 0)
    {
        echanger(tas, parent(pos),pos);
        pos = parent(pos);
    }
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


void destroy_tas(tas_t * a)
{
  if( a != NULL ){
    if( a->tab != NULL )
      free( a->tab );
    free( a );
  }
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


int plus_grands_fils(tas_t * tas, int pos)
{
  int fils_g = 2*pos+1;
  int fils_d = 2*pos+2;

  if( fils_g >= tas->taille )
    return tas->max;

  if (tas->tab[fils_g].weight < tas->tab[fils_d].weight)
    return fils_d;

  return fils_g;
}


void entasser_ext(tas_t * tas)
{
	if(tas->taille <= 1)
    return ;

  int pos =0;
  int fils = plus_grands_fils(tas, pos);

  while (tas->tab[pos].weight < tas->tab[fils].weight && fils < tas->taille-1)
  {
    echanger(tas, pos,fils);
    pos = fils; 
    fils = plus_grands_fils(tas, pos);
  }
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


edge_t extraire_grande_prio(tas_t * T)
{
  if (T == NULL || T->taille <= 1)
  {
    printf("ERROR in function extraire_grande_prio\n\n") ;
  }

  else
  {
    edge_t edge_min = T->tab[0] ;

    T->taille-- ;
    echanger(T, 0, T->taille) ;
    entasser_ext(T) ;

    return edge_min ;
  }
}

















