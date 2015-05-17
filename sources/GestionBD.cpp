#include <sqlite3.h>
#include "GestionBD.h"

/**
* Fonction permettant d'afficher le résulta de la requete
*/
static int callback(void *NotUsed, int argc, char **argv, char **szColName)
{
    for(int i = 0; i < argc; i++)
    {
        std::cout << szColName[i] << " = " << argv[i] << std::endl;
    }
    
    std::cout << "\n";
    
    return 0;
}

/**
* Constructeur de l'objet permettant de gérer la base de donnée
* Il permet de créer une connexion avec la base de donnée et de 
* créer la table si elle n'existe pas
*/
GestionBD::GestionBD()
{
	//Initialisation du message d'erreur à 0
	char *szErrMsg = 0;
	//Connexion à la base de donnée
	rc = sqlite3_open("mp3.db", &db);
	//Si on ne peut pas ouvrir la base de donnée, affichage d'un message d'erreur
	if(rc)
	{
		cout << "Impossible d'ouvrir la base de donnée " << sqlite3_errmsg(db) << endl;
		exit(0);
	}
	//Sinon on affiche qu'on a bien pu ouvrir la base de donnée
	else
		cout << "Ouverture de la base de donnée réussi" << endl;

	//Création d'un tableau de requet SQL
	const char *pSQL[2];
	//Requet permettant de créer la table si elle n'existe pas
    	pSQL[0] = "CREATE TABLE musique(chemin text, titre text, artiste text, album text, compo text)";
	//Requet permettant de récupérer tout les mp3
   	pSQL[1] = "SELECT * FROM musique";
	//On lance les requets qui sont dans le tableau
	for(int i = 0; i < 2; i++)
    	{
        	//Execution de la requet
		rc = sqlite3_exec(db, pSQL[i], callback, 0, &szErrMsg);
        	//Si la requet rencontre une erreur
		if(rc != SQLITE_OK)
        	{
            		//On affiche le message d'erreur
			std::cout << "SQL Error: " << szErrMsg << std::endl;
			//Libere la mémoire en cas d'erreur
            		sqlite3_free(szErrMsg);
            		break;
        	}
   	}
}
/**
* Fonction permettant de rajouter une musique dans la base de donnée
* @param chemin Le chemin de la musique sur le disque
* @param titre Le titre de la musique
* @param artiste Le nom de l'artiste
* @param album Le nom de l'album
* @param compo Le nom du compositeur
*/
void GestionBD::ajouter(string chemin, string titre, string artiste, string album, string compo)
{
	//En cas d'erreur
	char *szErrMsg = 0;
	//Le tableau comportant la requet
	const char *pSQL[1];
	//La requete permettant de rajouter un mp3
       	string requet = "INSERT INTO musique(chemin, titre, artiste, album, compo) VALUES ('"+ chemin  +"', '"+ titre  +"', '"+ artiste  +"', '"+ album  +"', '"+ compo  +"')";
	//Permet de convertir la requet dans le bon format
	pSQL[0] = requet.c_str();
        //Execution de la requet
	rc = sqlite3_exec(db, pSQL[0], callback, 0, &szErrMsg);
        //Si il y a une erreur
	if(rc != SQLITE_OK)
         {
         	//affichage du message d'erreur
		std::cout << "SQL Erreur : " << szErrMsg << std::endl;
		//Libération de la mémoire
                sqlite3_free(szErrMsg);
         }

}
/**
* Fonction permettant de supprimer une musique de la base de donnée
* @param chemin Le chemin de la muisque sur le disque
*/
void GestionBD::supprimer(string chemin)
{
	//En cas d'erreur
	char *szErrMsg = 0;
	//Le tableau comportant la requet
        const char *pSQL[1];
        //Création de la requet
	string requet = "DELETE FROM musique WHERE chemin = '" + chemin + "'";
	//Conversion de la requet dans le bon format
        pSQL[0] = requet.c_str();
	//Execution de la requet
        rc = sqlite3_exec(db, pSQL[0], callback, 0, &szErrMsg);
	//Si il y a un probleme
        if(rc != SQLITE_OK)
        {
        	//Affichage du message d'erreur
		std::cout << "SQL Error: " << szErrMsg << std::endl;
		//Libération de la mémoire
                sqlite3_free(szErrMsg);
        }
}
/**
* Fonction permettant de retourner tout les mp3 enregistrés dans la base de donnée
* @return resulta La liste des FichierMP3
*/
list<FichierMP3> GestionBD::selectAll()
{
	//Le chemin de la musique
	string chemin;
	//Le titre de la musique
	string titre;
	//L'artiste de la musique
	string artiste;
	//L'album de la musique
	string album;
	//Le nom du compositeur de la musique
	string compo;	
	//La liste de FichierMP3 a créer et envoyer comme résulta
	list<FichierMP3> resulta;
	//Permet de récupérer ne colleciton de résulta
	sqlite3_stmt *statement;
	//Création du tableau pour la requet
        const char *pSQL[1];
	//Création de la requette
	pSQL[0] = "SELECT * FROM musique";
	//Execution de la requette
	if(sqlite3_prepare(db, pSQL[0], -1, &statement, 0 ) == SQLITE_OK )
	{
		//le nombre de résulta
		int ctotal = sqlite3_column_count(statement);
		//Vararible permettant de savoir quand on a tout lue
        	int res = 0;
		//Boucle pour lire tout les tuples
		while(1)         
        	{
			//Mise à jour de res pour savoir si c'est fini
            		res = sqlite3_step(statement);
			//Si res est un tuple alors on met à jour la liste de resulta
	        	if ( res == SQLITE_ROW ) 
            		{
				//Récupération du chemin de la musique
				chemin = (char*)sqlite3_column_text(statement, 0);
				//récupération du titre de la musique
				titre = (char*)sqlite3_column_text(statement, 1);
				//Récupération de l'artiste
				artiste = (char*)sqlite3_column_text(statement, 2);
				//Récupération de l'album
				album = (char*)sqlite3_column_text(statement, 3);
				//Récupération du compositeur
				compo = (char*)sqlite3_column_text(statement, 4);
				//On créer un fichierMP3 qu'on rajoute dans la liste de résulta
				resulta.push_back(FichierMP3(chemin,titre,artiste,album,compo));

            		}
			//Si il n'y a plus de tuple ou une erreur
              		if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
               			//On sort de la boucle infinie
				break;
        	}
	}
	//On retourn la liste de FichierMP3
	return resulta;
}
/**
* Destructeur de GestionBD
* Ferme la connexion à la base de donnée
*/
GestionBD::~GestionBD()
{
	//Si une connexion à la base de donnée 
        if(db)
        	//Fermeture de la connexion
		sqlite3_close(db);
}
