#ifndef __ANALYZER_H__
#define __ANALYZER_H__

#include <stddef.h>

/**
   Structure utilisée pour faire des statistiques élémentaires
   sur une séquence d'opérations.
*/
typedef struct analyzer_s{
  // Coût de chaque opération. Peut représenter du temps ou une autre mesure.
  double * cost;
  // Coût cumulatif. La case i contient la somme des coûts des i premières opérations.
  // Permet de calculer le coût amorti d'une opération.
  float * cumulative_cost;
  // Carré du coût cumulatif. Sert à calculer la variance. On ne garde que la dernière valeur.
  float cumulative_square;
  // Capacité de stockage des tableaux
  size_t capacity;
  // Nombre d'éléments dans chaque tableaux.
  size_t size;   
} analyzer_t;

/**
   Fonction d'initialisation d'une analyse.
   Complexité en temps/espace, pire et meilleur cas : O(1)  
   @return Un pointeur sur une structure analyzer_t nouvellement allouée.
 */
analyzer_t * analyzer_create();

/**
   Fonction de libération de la mémoire occupée par une analyse.
   Complexité en temps/espace, pire et meilleur cas : O(1)  
   @param a est un pointeur vers l'espace mémoire que la fonction va libérer.
 */
void analyzer_destroy(analyzer_t * a);

/**
   Ajoute un coût, une valeur à l'analyse.
   Complexité en temps/espace, pire cas : O(size)
   Complexité en temps/espace, meilleur cas : O(1)
   Complexité amortie : O(1)
   @param a est l'analyse à laquelle on souhaite ajouter une valeur.
   @param cost est la valeur que l'on souhaite ajouter.
*/
void analyzer_append(analyzer_t * a, double cost);

/**
   Renvoie la somme des coûts enregistrés dans cette analyse.
   Complexité en temps/espace, pire cas : O(1)
   @param a est une analyse.
   @returns la somme des coûts enregistrés dans cette analyse.
*/
float get_total_cost(analyzer_t * a);

// =============================================================================


/**
 * Cette fonction va stocker le nombre minimal de population choisie,
 * la longueur totale du réseau ainsi que son cout (temps).
 * @param popMin est la population minimum par ville.
 * @param totalcost est le coût total (km) du réseau.
 * @param a est l'analyse que l'on souhaite sauvegarder.
 * @param path est le chemin du fichier dans lequel la sauvegarde est faite.
 */
void new_save_values(int popMin, int totalcost, analyzer_t * a, char * path) ;

#endif 
