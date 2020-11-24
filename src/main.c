#include "citiesReader.h"
#include "graph.h"
#include "heap.h"
#include "analyzer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>



struct timespec diff(struct timespec start, struct timespec end)
{
    struct timespec temp;

    if ((end.tv_nsec-start.tv_nsec)<0)
    {
            temp.tv_sec = end.tv_sec-start.tv_sec-1;
            temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    }
    else 
    {
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
	int **matrix = adjacency_matrix_creation(cities->number);
	analyzer_t *time_analysis = analyzer_create();
	struct timespec before, after, difference;
	clockid_t clk_id = CLOCK_REALTIME;



	adjacency_matrix_filling(matrix, cities);

	for (int i = 0; i < 100; i++){
		//display_matrix (cities, matrix);
		clock_gettime(clk_id, &before);
		matrix = prim(matrix, cities->number);
		clock_gettime(clk_id, &after);
		save_values(time_analysis, "test1.txt");
		difference = diff(before, after);
		analyzer_append(time_analysis, difference.tv_nsec);

		//DIsplaying a few statistics on the experience.
	}

	printf("%Lf\n", get_average_cost(time_analysis));
	//printf("The length of the optimal network is of %d\n", total_cost);

	//Saving the graph in a text file

	saveGraph_alt(matrix, cities->number);
	freeListOfCities(cities);

	return 0;
}

