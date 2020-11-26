#include "analyzer.h"
#include "citiesReader.h"
#include "heap.h"
#include "graph.h"

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

	int popMin, total_cost = 0;

	fprintf(stderr,"Enter a minimum population.\n");
	fprintf(stderr,"\n[Recommendations : 250000, 100000, 50000, 10000, 1000 ]\n\n");
	fprintf(stderr,"\nYour choice: ");
	scanf ("%d", &popMin);
	fprintf(stderr, "\n");

	ListOfCities* cities = citiesReader(popMin);

	//Here we create an empty adjacency matrix.
	int **complete_graph = adjacency_matrix_creation(cities->number);
	int **mst;
	//Structure used for benchmark purposes.
	analyzer_t *time_analysis = analyzer_create();
	struct timespec before, after, difference;
	clockid_t clk_id = CLOCK_REALTIME;

	//Here, we fill our matrix. It'll represent a complete
	//graph whose nodes are the cities passed as an argument.
	adjacency_matrix_filling(complete_graph, cities);

	clock_gettime(clk_id, &before);
	mst = kruskal(complete_graph, cities->number, &total_cost);
	clock_gettime(clk_id, &after);

	//We store the time taken by the process of the Prim algorithm.
	difference = diff(before, after);
	analyzer_append(time_analysis, difference.tv_nsec);

	//We store some information in a text file.
	new_save_values(popMin, total_cost, time_analysis, "../resultats/resultat_function_prim.txt") ;



	//Displaying some information on our benchmarks.
	fprintf(stderr, "The total cost (timewise) to process the MST is equal to %Lf\n", get_total_cost(time_analysis));
	fprintf(stderr, "The length of the found MST is equal to %d kilometers.\n\n", total_cost);
	fprintf(stderr, "======================================================================================\n\n");


	//Saving the graph in a text file
	saveGraph_alt(mst, cities->number, popMin);

	fprintf(stderr, "Now that an MST has been processed, please enter python3 visualisation.py to watch it.\n");

	free_matrix(mst, cities->number);
	free(time_analysis);
	freeListOfCities(cities);

	return (0);
}

