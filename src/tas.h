#ifndef __TAS_H__
#define __TAS_H__

#include <stddef.h>


typedef struct edge_s
{
  int vertix1 ;
  int vertix2 ;
  int weight ;
} edge_t ;


/**
   Structure utilisée pour faire des Tas pour les files de prioritées
*/
typedef struct tas_s
{
  // Tableau pour le tas.
  edge_t* tab;

  // Taille max du tableau.
  int max;

  // Taille du tableau actuellement occupé.
  int taille;
} tas_t;


/**
   Fonction d'initialisation d'une arête.
   @param n1 Le sommet départ.
   @param n2 Le sommet arrivé.
   @param poids Le poids du trajet.
   @return Un pointer vers une arête paramétré.
 */
edge_t* edge_create(int n1, int n2, int poids);


/**
   Fonction d'initialisation d'un tas.
   Complexité en temps/espace, pire et meilleur cas : O(1)  
   @param max est la taille max du tableau.
   @return Un pointeur sur une structure analyzer_t nouvellement allouée.
 */
tas_t * tas_create(int max);


/**
   Fonction qui renvoie la position du parents de l'argument
   @param pos la position de l'emplacement dont on cherche le parent
   @return la position du parent
 */
int parent (int pos);


/**
 *  Fonction insérant un entier dans un dans tas
 *  @param T Tas T
 *  @param x entier x à insérer
 *  @return une valeur dépendant s'il l'action a réussie ou non
 */
void inserer_tas (tas_t *T, edge_t x);


/**
   Fonction qui echange l'emplacement de deux élement du tableau d'un tas
   @param tas le tas que l'on va modifier
   @param pos1 la position du premier element a échanger
   @param pos2 la position du deuxieme element a modifier
 */
void echanger(tas_t * tas, int pos1, int pos2);


/**
   Fonction met un element a sa place dans le tas_max
   @param tas le tas que l'on va modifier
   @param pos la position de l'element que l'on va remonter
 */
void entasser(tas_t* tas, int pos);


/**
 *  Fonction libérant la mémoire occupée par le tas
 * @param a le tableau que l'on va désallouer
 */
void destroy_tas(tas_t * a);


/**
 *  Fonction qui swap le premier et dernie element, puis retire le dernier et va ensuite entasser le tas
 * @param a le tas
 * @return le nombre d'échanges effectués pour entasser le tas
 */
edge_t extraire_grande_prio(tas_t * T) ;


/**
 * Fonction qui entasse le tas
 * @param tas le tas
 * @return le nombre d'échanges effectués pour entasser le tas
 */
void entasser_ext(tas_t * tas);


/**
 * Fonction qui renvoie la position du plus grand fils
 * @param tas le tas
 * @param pos la position du noeud
 * @return la position du plus grand fils
 */
int plus_grands_fils(tas_t * tas, int pos);


#endif