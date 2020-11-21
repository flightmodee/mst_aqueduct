CC= gcc
CXXFLAGS= -Wall -Werror -ansi --pedantic -O3

CPP_O_FILE = citiesReader.o graph.o main.o
LIB = -lm


all: $(CPP_O_FILE)
	$(CC) $(CXXFLAGS) -o graphe $(CPP_O_FILE) $(LIB)

clean:
	rm -rf *.o
	rm -rf *~
	rm -rf graphe
