#include "citiesReader.h"
#include "disjointsets.h"
#include "heap.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>


float edge_valuation(ListOfCities *cities, int pos1, int pos2)
{
	float pi, a, valuation;

	float lat_a = cities->lat[pos1], lon_a = cities->lon[pos1];
	float lat_b = cities->lat[pos2], lon_b = cities->lon[pos2];

	pi = M_PI/180.0;
	a = 0.5 - cos((lat_b - lat_a)*pi)/2 + cos(lat_a*pi) * cos(lat_b*pi) * (1 - cos((lon_b - lon_a)*pi))/2 ;
	valuation = 12742 * asin(sqrt(a));

	return (valuation);
}


float **adjacency_matrix_creation(int cities_number){

	float**matrix;
	if ((matrix = (float**)malloc((cities_number-1) * sizeof(float*))) == NULL){
		perror("Memory allocation failed. Exit.\n");
		exit(EXIT_FAILURE);
	}

	int i, j;
	//Allocation of each row. However, using the diagonal properties
	//of an adjacency matrix, we do not need to create an n*n matrix.
	//We only need n*(n-1)/2 cells to store our valuations.
	//We use the calloc function to initialize each memory cell to 0
	for (i = 1; i < cities_number; i++)
		if ((matrix[i-1] = (float*)calloc(i, sizeof(float))) == NULL){
			perror("Memory allocation failed. Exit. \n");
			exit(EXIT_FAILURE);
		}

	return (matrix);
}


void free_matrix(float **matrix, int node_number){
	for (int i = 0; i < node_number - 1; i++)
		free(matrix[i]);

	free(matrix);
}


void adjacency_matrix_filling(float **matrix, ListOfCities *cities){

	for (int i = 0; i < cities->number-1; i++)
		for (int j = 0; j <= i; j++)
			matrix[i][j] = edge_valuation(cities, i+1, j);
}



void display_matrix (ListOfCities* cities, float **matrix)
{
	printf("\n\t") ;
	for (int x = 0 ; x < cities->number; x++)
		printf("%.5s \t", cities->name[x]);

	for (int i = 0; i < cities->number; i++)
	{
		printf("\n");
		printf("%.5s \t", cities->name[i]);

		for (int j = 0; j < i; j++)
			printf("%f \t", matrix[i-1][j]);
	}
	printf("\n\n") ;
}



void saveGraph_alt(float **matrix, int dimension, int popMin){

	FILE *fileOut = NULL;
	fileOut = fopen("resuGraph.dat", "w");

	for (int i = 0; i < dimension-1; i++)
		for (int j = 0; j <= i; j++)
			if (matrix[i][j] != 0)
				fprintf(fileOut, "%i %i\n", i+1, j);

	fclose(fileOut);
}


void filling_heap(float**matrix, heap_t *heap, int node_number){

	edge_t edge;
	for (int i = 0; i < node_number-1; i++){
		for (int j = 0; j <= i; j++){
			float valuation = matrix[i][j];
			edge = edge_create(i+1, j, valuation);
			inserer_heap(heap, edge);
		}
	}
}



float **kruskal(float**matrix, int node_number, float *total_cost){

	//First step: creating the binary heap.
	//A complete graph Kn has exactly n*(n-1)/2 edges, so we reserve
	//that many slots in our binary heap.
	int size = node_number*(node_number-1)/2;
	int i, j, edge_number = 0;
	heap_t *heap = heap_create(size);

	//Here we create the matrix that will contain our final output.
	float **prim_matrix = adjacency_matrix_creation(node_number);

	//création et initialisation de notre tableau des représentant
	node_t **representative = (node_t **)malloc(node_number * sizeof(node_t*));

	for(i = 0; i < node_number; i++)
		representative[i] = make_set();

	//Mise en place de notre tas min avec les valeurs de la matrice
	filling_heap(matrix, heap, node_number);


	//tant que nous n'avons pas un seul représantant (1 seul graphe conexxe)
	while (edge_number != node_number - 1)
	{
		//on extrait de notre tas_min
		edge_t tmp = extraire_grande_prio(heap);
		int ville1 = tmp.vertix1;
		int ville2 = tmp.vertix2;

		//si leurs représentant sont différent on lie les deux arbres
		if (find_set(representative[ville1]) != find_set(representative[ville2])){
			//tout les anciennes villes qui avant comme représantant ville2 ont maintenant ville1 comme représentant.
			set_union(representative[ville1], representative[ville2]);
			//on ajoute les valeurs dans notre matrice finale.

			prim_matrix[ville1-1][ville2] = tmp.weight;
			edge_number++;
			*total_cost += tmp.weight;
		}
	}


	for (i = 0; i < node_number; i++)
		free(representative[i]);

	free(representative);
	destroy_heap(heap);
	return prim_matrix;
}


