CC=g++ -std=c++11
COPTS=-I.
INC=include/
included = -IC:/SQLite-lib/include
linked = -LC:/SQLite-lib/ -lsqlite3


mon_serveur: main.o ServeurMP3.o FichierMP3.o ICEserveurMP3.o GestionBD.o
	$(CC) $(COPTS) main.o ServeurMP3.o FichierMP3.o ICEserveurMP3.o GestionBD.o -o mon_serveur -lIce -lIceUtil -lpthread -Llib -lvlc -lsqlite3 -lIceStorm 

ICEserveurMP3.o: ICEserveurMP3.cpp ICEserveurMP3.h
	$(CC) $(COPTS) -c ICEserveurMP3.cpp 
 
main.o: main.cpp ServeurMP3.h
	$(CC) $(COPTS) -c main.cpp

ServeurMP3.o: ServeurMP3.cpp ServeurMP3.h
	$(CC) $(COPTS) -c ServeurMP3.cpp -I$(INC)

FichierMP3.o: FichierMP3.cpp FichierMP3.h
	$(CC) $(COPTS) -c FichierMP3.cpp

GestionBD.o: GestionBD.cpp GestionBD.h
	$(CC) $(COPTS) -c GestionBD.cpp -lsqlite3
