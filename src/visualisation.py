# Execution:
#   python visualisation.py

import matplotlib.pyplot as plt
from numpy import loadtxt

plt.figure(figsize=(10,8))

# draw the cities
cities = loadtxt("resuCities.dat", dtype=float, delimiter=" ")
plt.scatter(cities[:,1], cities[:,2], s=cities[:,0]/1000, c=cities[:,0], alpha=0.5)


# graph's minimum number of population 
min_pop = loadtxt("resuGraph.dat", dtype=int, max_rows=1)
min_pop = min_pop[0]


# draw the graph
graph = loadtxt("resuGraph.dat", dtype=int, skiprows=1)
print( "Number of edges in the MST: ", graph.shape[0])

for x in range(graph.shape[0]):
  edge = [graph[x,0], graph[x,1]]
  plt.plot(cities[edge,1], cities[edge,2], 'b')

plt.xlabel('Longitude', size=16)
plt.ylabel('Latitude', size=16)


# title
plt.title("Minimum Spanning Tree of the cities whose population is greater or equal to %i" %min_pop)




#   Example of file's name in folder 'resultats' : 'min_pop_250000.png'
filename = "../resultats/min_pop_" + str(min_pop) + ".png"

# save in a PNG file
plt.savefig( filename )


# show the result
plt.show()
