#include<sqlite3.h>
#include <iostream>
#include <list>
#include "FichierMP3.h"

using namespace std;

class GestionBD
{

	private :
	
	sqlite3 *db;
	int rc;
	string sql;	
	char * zErrMsg;
	list<FichierMP3> listMP3;

	public :
	
	GestionBD();
	~GestionBD();
	void ajouter(string chemin, string titre, string artiste, string album, string compo);
	void supprimer(string chemin);
	list<FichierMP3> selectAll();
	void select(string chemin);
};
