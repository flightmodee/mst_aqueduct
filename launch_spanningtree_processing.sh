RED='\033[0;31m'
NC='\033[0m' # No Color


cd src/
make

echo "${RED} ============================== Algorithme choisi : Kruskal ============================== ${NC}"


# Compilation et exécution en C:
./graphe

python3 visualisation.py

# Nettoyage
make clean

cd ..



