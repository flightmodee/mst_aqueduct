#include "heap.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// = = = = = = = = = = = = = = EXERCICE 2  = = = = = = = = = = = = = = = = = = = = = =
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


edge_t edge_create(int n1, int n2, long double poids)
{
  edge_t res;

  res.vertix1 = n1 ;
  res.vertix2 = n2 ;
  res.weight = poids ;

  return res ;
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


heap_t* heap_create(int max)
{
  heap_t* res = (heap_t*)malloc(sizeof(heap_t) );

  res->tab = (edge_t*) malloc(sizeof(edge_t) * max);
  res->max = max;
  res->taille = 0;
  
  return (res);
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


void inserer_heap (heap_t *T, edge_t x)
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


void echanger(heap_t * T, int pos1, int pos2){
    edge_t tmp = T->tab[pos2];
    T->tab[pos2] = T->tab[pos1];
    T->tab[pos1] = tmp;
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


int parent (int pos){
    return (pos-1)/2;
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


void entasser(heap_t * T, int pos)
{
    while (T->tab[pos].weight < T->tab[parent(pos)].weight && pos > 0)
    {
        echanger(T, pos, parent(pos));
        pos = parent(pos);
    }
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


void destroy_heap(heap_t * a)
{
  if( a != NULL ){
    if( a->tab != NULL )
      free( a->tab );
    free( a );
  }
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


int plus_petit_fils(heap_t * T, int pos)
{
  int fils_g = 2*pos+1;
  int fils_d = 2*pos+2;

  if( fils_g >= T->taille )
    return T->max;

  if (T->tab[fils_g].weight < T->tab[fils_d].weight)
    return fils_g;

  return fils_d;
}


void entasser_ext(heap_t * T)
{
	if(T->taille <= 1)
    return ;

  int pos =0;
  int fils = plus_petit_fils(T, pos);

  while (T->tab[pos].weight > T->tab[fils].weight && fils < T->taille-1)
  {
    echanger(T, pos,fils);
    pos = fils; 
    fils = plus_petit_fils(T, pos);
  }
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 


edge_t extraire_grande_prio(heap_t * T)
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

















