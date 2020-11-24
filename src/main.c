#include "citiesReader.h"
#include "graph.h"
#include "heap.h"
#include "analyzer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

//This function is used to correct the negative values a time measurement
//might produce. Courtesy of https://stackoverflow.com/questions/17705786/getting-negative-values-using-clock-gettime

struct timespec diff(struct timespec start, struct timespec end)
{
	struct timespec temp;

	if ((end.tv_nsec-start.tv_nsec)<0){
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	}
	else{
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
		}

	return temp;
}


int main(int argc, char ** argv)
{

	srand(time(NULL));
	if( argc != 2 )
	{
		perror("Veuillez passer une population minimale en paramètre du programme\n");
		return EXIT_FAILURE;
	}

	int popMin = atoi(argv[1]), total_cost = 0;
	ListOfCities* cities = citiesReader(popMin);
	//Here we create an empty adjacency matrix.
	int **matrix = adjacency_matrix_creation(cities->number);
	//Structure used for benchmark purposes.
	analyzer_t *time_analysis = analyzer_create();
	struct timespec before, after, difference;
	clockid_t clk_id = CLOCK_REALTIME;

	//Here, we fill our matrix. It'll represent a complete
	//graph whose nodes are the cities passed as an argument.
	adjacency_matrix_filling(matrix, cities);

	//display_matrix (cities, matrix);
	clock_gettime(clk_id, &before);
	matrix = prim(matrix, cities->number, &total_cost);
	clock_gettime(clk_id, &after);
	save_values(time_analysis, "test1.txt");
	difference = diff(before, after);
	analyzer_append(time_analysis, difference.tv_nsec);

	//Displaying some information on our benchmarks.
	fprintf(stderr, "The total cost is %Lf\n", get_average_cost(time_analysis));
	fprintf(stderr, "The length of the found MST is equal to %d kilometers.\n", total_cost);


	//Saving the graph in a text file
	saveGraph_alt(matrix, cities->number);
	freeListOfCities(cities);

	return (0);
}

