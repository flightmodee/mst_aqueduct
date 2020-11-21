#include "tas.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// = = = = = = = = = = = = = = EXERCICE 2  = = = = = = = = = = = = = = = = = = = = = =
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


tas_t * tas_create(int max)
{
  tas_t * res = (tas_t *) malloc( sizeof(tas_t) );
  res->tab = (int*) malloc( sizeof(int) * max);
  res->max = max;
  res->taille = 0;
  return res;
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


int inserer_tas (tas_t *T, int x)
{
  if (T==NULL) {
      printf("Tas non valide !\n\n") ;
      return -2 ;
    }
  
  else if (T->taille == T->max) {
      printf("Tas rempli !\n\n") ;
      return -1 ;
    }

  int nb_echanges = 0 ;

  T->tab[T->taille] = x ;
  T->taille += 1 ;

  nb_echanges = entasser(T, (T->taille)-1) ;

  return nb_echanges ; 
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


void echanger(tas_t * tas, int pos1, int pos2){
    int tmp = tas->tab[pos2];
    tas->tab[pos2] = tas->tab[pos1];
    tas->tab[pos1] = tmp;
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


int parent (int pos){
    return (pos-1)/2;
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


int entasser(tas_t * tas, int pos)
{
	int nb_echanges = 0 ;
    while (tas->tab[parent(pos)] < tas->tab[pos] && pos > 0)
    {
        echanger(tas, parent(pos),pos);
        pos = parent(pos);
        nb_echanges++ ;
    }
	return nb_echanges ;
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


int plus_grands_fils(tas_t * tas, int pos){
  int fils_g = 2*pos+1;
  int fils_d = 2*pos+2;
  if( fils_g >= tas->taille )
    return tas->max;
  if (tas->tab[fils_g] < tas->tab[fils_d])
    return fils_d;
  return fils_g;
}


int entasser_ext(tas_t * tas){
	if(tas->taille <= 1)
    return 0;
  int pos =0;
  int fils = plus_grands_fils(tas, pos);
  int nb_echanges = 0 ;
  while (tas->tab[pos] < tas->tab[fils] && fils < tas->taille-1)
  {
    echanger(tas, pos,fils);
    nb_echanges++;
    pos = fils; 
    fils = plus_grands_fils(tas, pos);
  }
	return nb_echanges ;
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


int extraire_grande_prio(tas_t * a)
{
  if (a == NULL || a->taille <= 1)
  {
    return 0 ;
  }

  int nb_echanges = 0 ;
  a->taille-- ;
  echanger(a, 0, a->taille) ;

  nb_echanges = entasser_ext(a) ;

  return nb_echanges ;
}

















