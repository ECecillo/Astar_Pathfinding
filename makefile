CC=g++
CFLAGS=-Wall -O
# Chemin vers le/les execs.
EXEC_FOLDER = ./bin/
# Nom de l'exec
EXEC= $(EXEC_FOLDER)tp_10
# Chemin vers les fichiers .o 
OBJ_FOLDER = ./object/
# Chemin vers tous les fichiers .o
OBJ_EXEC = $(OBJ_FOLDER)altitude.o $(OBJ_FOLDER)Noeud.o $(OBJ_FOLDER)graph.o $(OBJ_FOLDER)main.o 
#Chemin vers le fichiers sources avec les .cpp
SRC_FOLDER = ./src/
#Chemin vers les fichiers .h 
MODULE_FOLDER = ./src/module/
#Chemin vers les fichiers de performance
DATA_FOLDER = ./data/


#Toutes les règles pour créer l'exe du programme.
all: Dossiers $(EXEC)

Dossiers: $(OBJ_FOLDER) $(EXEC_FOLDER) $(DATA_FOLDER)

$(EXEC): $(OBJ_EXEC) 
	 $(CC) -o $(EXEC) $(OBJ_EXEC)

$(OBJ_FOLDER)altitude.o: $(SRC_FOLDER)altitude.cpp
	$(CC) -o $(OBJ_FOLDER)altitude.o -c $(SRC_FOLDER)altitude.cpp $(CFLAGS)

$(OBJ_FOLDER)graph.o: $(SRC_FOLDER)graph.cpp $(MODULE_FOLDER)noeud.h $(MODULE_FOLDER)altitude.h  $(MODULE_FOLDER)indexed_priority_queue.h
	$(CC) -o $(OBJ_FOLDER)graph.o -c $(SRC_FOLDER)graph.cpp $(CFLAGS)

$(OBJ_FOLDER)Noeud.o: $(SRC_FOLDER)noeud.cpp $(MODULE_FOLDER)altitude.h
	$(CC) -o $(OBJ_FOLDER)Noeud.o -c $(SRC_FOLDER)noeud.cpp $(CFLAGS)	

$(OBJ_FOLDER)main.o: $(SRC_FOLDER)main.cpp $(MODULE_FOLDER)graph.h $(MODULE_FOLDER)noeud.h
	$(CC) -o $(OBJ_FOLDER)main.o -c $(SRC_FOLDER)main.cpp $(CFLAGS)

$(OBJ_FOLDER): 
	mkdir $(OBJ_FOLDER)
$(EXEC_FOLDER):
	mkdir $(EXEC_FOLDER)
$(DATA_FOLDER):
	mkdir $(DATA_FOLDER)

# Règle pour le nettoyage.
clean:
	rm -f $(OBJ_FOLDER)*.o $(EXEC)
mrproper: clean
	rm -rf $(EXEC_FOLDER) $(OBJ_FOLDER)


# Edité par CECILLON Enzo.