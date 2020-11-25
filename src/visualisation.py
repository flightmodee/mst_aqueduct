# Execution:
#   python visualisation.py

from matplotlib import pyplot
from numpy import loadtxt

# draw the cities
cities = loadtxt("resuCities.dat", dtype=float, delimiter=" ")
pyplot.scatter(cities[:,1], cities[:,2], s=cities[:,0]/1000, c=cities[:,0], alpha=0.5)


# graph's minimum number of population 
min_pop = loadtxt("resuGraph.dat", dtype=int, max_rows=1)
min_pop = min_pop[0]


# draw the graph
graph = loadtxt("resuGraph.dat", dtype=int, skiprows=1)
#print( "Number of edges : ", graph.shape[0])

for x in range(graph.shape[0]):
  edge = [graph[x,0], graph[x,1]]
  pyplot.plot(cities[edge,1], cities[edge,2], 'b')

pyplot.xlabel('Longitude', size=16)
pyplot.ylabel('Latitude', size=16)


# title
pyplot.title("Prim's Algorithm (min pop = %i)" %min_pop)





#   Example of file's name in folder 'resultats' : 'min_pop_250000.png'
filename = "resultats/min_pop_" + str(min_pop) + ".png"

# save in a PNG file
pyplot.savefig( filename )


# show the result
pyplot.show()
