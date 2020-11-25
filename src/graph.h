#ifndef __GRAPH_
#define __GRAPH__

#include <stddef.h>


/** This function calculates the valuation of an edge. The latter represents the distance between two cities
 * whose latitudes are passed as arguments, and the valuation is calculated using the Haversine formula.
 * @param cities the chosen cities
 * @param pos1 the position of a city
 * @param pos2 the position of a city
 * @return the distance between those two cities
 */
int edge_valuation(ListOfCities *cities, int pos1, int pos2);


/**This function will create an adjacency matrix (where each cell will be initialized
 * to 0. It isn't an actual matrix per se, but rather a pointer array. Indeed, adjacency matrixes
 * suffer from redundancy, which is why we decided to only consider the data stored on top or beneath
 * the zero diagonal. This allows us to save a lot of memory.
 * The integer passed as an argument will represent the number of cities considered.
 * @param cities_number the number of cities considered.
 * @return an "adjacency matrix" initialized to 0.
 */
int **adjacency_matrix_creation(int cities_number);


/**This function fills the matrix passed as an argument with the cities 
 * passed as an argument.
 * @param matrix the matrix we want to fill.
 * @param cities the list of cities we want to store within our matrix.
 */
void adjacency_matrix_filling(int **matrix, ListOfCities *cities);


/**This function displays the matrix of distance between the chosen cities.
 * @param cities the cities which are going to be displayed
 */
void display_matrix (ListOfCities* cities, int** matrix);


/**This functions writes in a file each pair of vertixes which form an edge in our graph 
 * described by the matrix passed as argument.
 * We also need the dimension of our matrix to print everything
 * correctly.
 * @param matrix the matrix representing our graph.
 * @param dimension the dimension of our matrix.
 */
void saveGraph_alt(int **matrix, int dimension, int popMin);

/**This function will add all of the outgoing edges from the vertex v passed as an argument.
 * To do so, it will first and foremost check if each edge doesn't point towards an alreay visited node.
 * If it isn't the case, it adds them to our priority queue. It'll explore the adjacency matrix
 * in order to retrieve the valuation of each edge, hence the node_number argument used to stay 
 * within bounds of our matrix.
 * @param matrix the adjacency matrix of a graph.
 * @param heap a pointer to a priority queue we want to fill.
 * @param v the node we're currently visiting and we want the outgoing edges of.
 * @param node_number the number of nodes of our graph.
 * @param visited an array keeping track of each vertix that has been visited.
 */
void adding_outgoing_edges(int **matrix, heap_t *heap, int v, int node_number, int *visited);


/**This is the main function. It processes an MST (minimum spanning tree) from a graphe
 * whose adjacency matrix is passed as an argument, using the Prim algorithm.
 * It will also store the total cost of the MST in an integer.
 * @param matrix the adjacency matrix of the graph we want to determine an MST of.
 * @param node_number the number of nodes in said graph.
 * @param total_cost a pointer to an integer that will store the total cost of the MST.
 * @return the adjacency matrix of the minimum spanning tree.
 */
int** prim(int** matrix, int node_number, int *total_cost);






#endif
