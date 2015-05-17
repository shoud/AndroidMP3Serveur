#ifndef __GESTIONBD_H__
#define __GESTIONBD_H__

#include <sqlite3.h>
#include <iostream>
#include <list>
#include "FichierMP3.h"

using namespace std;

/**
* Classe permettant de se connecter à une base de donnée SQLite
*/
class GestionBD
{

	private :
	//Représentation de la base de donnée	
	sqlite3 *db;
	//Permet de recevoir le résultat de la requet
	int rc;
	//La requete SQL
	string sql;
	//Le message d'erreur	
	char * zErrMsg;
	//La liste de Fichier MP3 récupéré dans la base de données
	list<FichierMP3> listMP3;

	public :
	
	GestionBD();
	~GestionBD();
	void ajouter(string chemin, string titre, string artiste, string album, string compo);
	void supprimer(string chemin);
	list<FichierMP3> selectAll();
};
#endif
