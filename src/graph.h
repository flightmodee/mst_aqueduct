#ifndef __ADJACENCY_MATRIX__
#define __ADJACENCY_MATRIX__

#include <stddef.h>
#include <math.h>

/**Cette librairie contiendra les prototypes des fonctions en rapport avec les matrices d'adjacence.
 * Il ne s'agira ni plus ni moins que d'une matrice n * n, avec n le nombre de sommets d'un graphe.
 * Chaque case de la matrice représentera une valuation, ou distance entre deux villes.
 * Le choix de cette structure de données sera bien évidemment expliqué dans le rapport.
 */


/** This function calculates the valuation of an edge. The latter represents the distance between two cities
 * whose latitudes are passed as arguments, and the valuation is calculated using the Haversine formula.
 * @param lat_a the latitude of the first city
 * @param lat_b the latitude of the second city
 * @param lon_a the longitude of the first city
 * @param lon_b the longitude of the second city
 * @return the distance between those two cities
 */
int edge_valuation(float lat_a, float lat_b, float lon_a, float lon_b);

/**This function will create an adjacency matrix (which will 
 * represent our graph) with the data contained within the argument.
 * Said argument is a ListOfCities structure that contains
 * a precise amount of cities, and for each of the latter its name, population,
 * along with its latitude and longitude.
 * This function will create the matrix and each cell of said matrix will contain 
 * an edge valuation, representing the distance between two cities.
 * @param cities a pointer to a ListOfCities
 * @return the adjacency matrix representing the complete weighted graph of all
 * cities passed as an argument.
 */

int **adjacency_matrix_creation(ListOfCities *cities);


/**
 * This function displays the matrix of distance between chosen cities.
 * @param cities the cities which are going to be displayed
 */
void display_matrix (ListOfCities* cities, int** matrix);


/**This functions writes in a file each pair of vertixes which form an edge in our graph 
 * described by the matrix passed as argument.
 * We also need the dimension of the squared matrix to print everything
 * correctly.
 * @param matrix the matrix representing our graph.
 * @dimension the dimension of our matrix.
 */
void saveGraph_alt(int **matrix, int dimension);

#endif
