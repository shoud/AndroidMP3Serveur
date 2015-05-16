CC=g++ -std=c++11
COPTS=-Iincludes/
SRC=sources/
INC=includes/
OBJ=objets/
ICE=ICE/
included = -IC:/SQLite-lib/include
linked = -LC:/SQLite-lib/ -lsqlite3

default: serveurMP3

all: slice default

slice: $(ICE)ICEserveurMP3.ice
	slice2cpp $< && mv ICEserveurMP3.cpp $(SRC) && mv ICEserveurMP3.h $(INC)

serveurMP3: $(OBJ)main.o $(OBJ)ServeurMP3.o $(OBJ)FichierMP3.o  $(OBJ)ICEserveurMP3.o  $(OBJ)GestionBD.o
	$(CC) $(COPTS) $(OBJ)main.o $(OBJ)ServeurMP3.o $(OBJ)FichierMP3.o $(OBJ)ICEserveurMP3.o $(OBJ)GestionBD.o -o serveurMP3 -lIce -lIceUtil -lpthread -Llib -lvlc -lsqlite3 -lIceStorm 

$(OBJ)ICEserveurMP3.o: $(SRC)ICEserveurMP3.cpp $(INC)ICEserveurMP3.h
	$(CC) $(COPTS) -c $(SRC)ICEserveurMP3.cpp -o $(OBJ)ICEserveurMP3.o 
 
$(OBJ)main.o: $(SRC)main.cpp $(INC)ServeurMP3.h
	$(CC) $(COPTS) -c $(SRC)main.cpp -o $(OBJ)main.o

$(OBJ)ServeurMP3.o: $(SRC)ServeurMP3.cpp $(INC)ServeurMP3.h
	$(CC) $(COPTS) -c $(SRC)ServeurMP3.cpp -I$(INC) -o $(OBJ)ServeurMP3.o

$(OBJ)FichierMP3.o: $(SRC)FichierMP3.cpp $(INC)FichierMP3.h
	$(CC) $(COPTS) -c $(SRC)FichierMP3.cpp -o $(OBJ)FichierMP3.o

$(OBJ)GestionBD.o: $(SRC)GestionBD.cpp $(INC)GestionBD.h
	$(CC) $(COPTS) -c $(SRC)GestionBD.cpp -lsqlite3 -o $(OBJ)GestionBD.o
