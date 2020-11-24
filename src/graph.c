#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "citiesReader.h"
#include "heap.h"
#include "graph.h"

#define M_PI 3.14159265358979323846


int edge_valuation(ListOfCities *cities, int pos1, int pos2)
{
	float pi, a, valuation;

	float lat_a = cities->lat[pos1], lon_a = cities->lon[pos1];
	float lat_b = cities->lat[pos2], lon_b = cities->lon[pos2];

	pi = M_PI/180 ;
	a = 0.5 - cos((lat_b - lat_a)*pi)/2 + cos(lat_a*pi) * cos(lat_b*pi) * (1 - cos((lon_b - lon_a)*pi))/2;
	valuation = 12742 * asin(sqrt(a)) ;

	return (valuation);
}


int **adjacency_matrix_creation(int cities_number){

	int **matrix;
	if ((matrix = (int **)malloc((cities_number-1) * sizeof(int *))) == NULL){
		perror("Memory allocation failed. Exit.\n");
		exit(EXIT_FAILURE);
	}

	int i, j;
	//Allocation of each row. However, using the diagonal properties
	//of an adjacency matrix, we do not need to create an n*n matrix.
	//We only need n*(n-1)/2 cells to store our valuations.
	//We use the calloc function to initialize each memory cell to 0
	for (i = 1; i < cities_number; i++)
		if ((matrix[i-1] = (int *)calloc(i, sizeof(int))) == NULL){
			perror("Memory allocation failed. Exit. \n");
			exit(EXIT_FAILURE);
		}

	return (matrix);
}


void adjacency_matrix_filling(int **matrix, ListOfCities *cities){

	for (int i = 0; i < cities->number-1; i++)
		for (int j = 0; j <= i; j++)
			matrix[i][j] = edge_valuation(cities, i+1, j);
}


void display_matrix (ListOfCities* cities, int** matrix)
{
	printf("\n\t") ;
	for (int x = 0 ; x < cities->number; x++)
		printf("%.5s \t", cities->name[x]);

	for (int i = 0; i < cities->number; i++)
	{
		printf("\n");
		printf("%.5s \t", cities->name[i]);

		for (int j = 0; j < i; j++)
			printf("%i \t", matrix[i-1][j]);
	}
	printf("\n\n") ;
}



void saveGraph_alt(int **matrix, int dimension){

	FILE *fileOut = NULL;
	fileOut = fopen("resuGraph.dat", "w");

	for (int i = 0; i < dimension-1; i++)
		for (int j = 0; j <= i; j++)
			if (matrix[i][j] != 0)
				fprintf(fileOut, "%i %i\n", i+1, j);

	fclose(fileOut);

}

void adding_outgoing_edges(int **matrix, heap_t *heap, int v, int node_number, int *visited){

		int i, valuation;
		edge_t *edge;

		for (i = 0; i < v; i++)
			if (!visited[i]){
				valuation = matrix[v-1][i];
				edge = edge_create(v, i, valuation);
				inserer_heap(heap, *edge);
			}

		for (int j = i; j < node_number-1; j++)
			if (!visited[j+1]){
				valuation = matrix[j][i];
				edge = edge_create(i, j+1, valuation);
				inserer_heap(heap, *edge);
			}
		visited[v] = 1;
}




int **prim(int **matrix, int node_number, int *total_cost){

	//First step: creating the binary heap.
	int size = node_number*(node_number-1);
	heap_t *heap = heap_create(size);

	//Here we create the matrix that will contain our final output.
	int **prim_matrix = adjacency_matrix_creation(node_number);

	//This array will keep track of the nodes already visited.
	//It basically is a boolean array. if visited[i] is true then it means 
	//the number i node has already been visited.
	//The calloc function will set each byte to zero.
	int *visited = (int*)calloc(node_number, sizeof(int));

	//The Prim algorithm starts on a random node. So we'll select a random node
	//between 0 and node_number-1
	srand(time(NULL));
	int v = rand()% (node_number);

	//To start things off, we add all of the outgoing edges of 
	//our v vertix to our priority queue.
	adding_outgoing_edges(matrix, heap, v, node_number, visited);
	int edge_number = 0;


	//BEGINNING OF THE PROCESS

	//We keep iterating until the priority queue is empty, or
	//we have formed an MST, as the number of edges within it is equal to
	//the number of vertices of the original graph minus 1.
	while (heap->taille != 0 && edge_number != node_number - 1){

		edge_t res = extraire_grande_prio(heap);
		int node_pointed = res.vertix2;

		//If the node pointed has already been selected, we keep polling.
		//Otheriwse, we update our output matrix, increment the value of
		//edge_number and add the weight of the extracted edge to our 
		//total_cost.
		if (!(visited[node_pointed])){
			if (res.vertix1 < res.vertix2)
				prim_matrix[res.vertix2-1][res.vertix1] = res.weight;
			else
				prim_matrix[res.vertix1-1][res.vertix2] = res.weight;
			edge_number++;
			*total_cost += res.weight;

			adding_outgoing_edges(matrix, heap, node_pointed, node_number, visited);
		}
	}

	return (prim_matrix);
}



