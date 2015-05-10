#include <sqlite3.h>
#include "GestionBD.h"

static int callback(void *NotUsed, int argc, char **argv, char **szColName)
{
    for(int i = 0; i < argc; i++)
    {
        std::cout << szColName[i] << " = " << argv[i] << std::endl;
	cout << "Coucou" << endl;
    }
    
    std::cout << "\n";
    
    return 0;
}

GestionBD::GestionBD()
{
	char *szErrMsg = 0;
	rc = sqlite3_open("mp3.db", &db);
	if(rc)
	{
		cout << "Impossible d'ouvrir la base de donnée " << sqlite3_errmsg(db) << endl;
		exit(0);
	}
	else
		cout << "Ouverture de la base de donnée réussi" << endl;

	const char *pSQL[6];
    	pSQL[0] = "CREATE TABLE musique(chemin text, titre text, artiste text, album text, compo text)";
   	pSQL[1] = "SELECT * FROM musique";

	for(int i = 0; i < 2; i++)
    	{
        	rc = sqlite3_exec(db, pSQL[i], callback, 0, &szErrMsg);
        	if(rc != SQLITE_OK)
        	{
            		std::cout << "SQL Error: " << szErrMsg << std::endl;
            		sqlite3_free(szErrMsg);
            		break;
        	}
   	}
}
void GestionBD::ajouter(string chemin, string titre, string artiste, string album, string compo)
{
	char *szErrMsg = 0;
	const char *pSQL[1];
       	string lol = "INSERT INTO musique(chemin, titre, artiste, album, compo) VALUES ('"+ chemin  +"', '"+ titre  +"', '"+ artiste  +"', '"+ album  +"', '"+ compo  +"')";
	pSQL[0] = lol.c_str();
        
        for(int i = 0; i < 1; i++)
        {
                rc = sqlite3_exec(db, pSQL[i], callback, 0, &szErrMsg);
                if(rc != SQLITE_OK)
                {
                        std::cout << "SQL Error: " << szErrMsg << std::endl;
                        sqlite3_free(szErrMsg);
                        break;
                }
        }

}
void GestionBD::supprimer(string chemin)
{
	char *szErrMsg = 0;
        const char *pSQL[1];
        string lol = "DELETE FROM musique WHERE chemin = '" + chemin + "'";
        pSQL[0] = lol.c_str();

        for(int i = 0; i < 1; i++)
        {
                rc = sqlite3_exec(db, pSQL[i], callback, 0, &szErrMsg);
                if(rc != SQLITE_OK)
                {
                        std::cout << "SQL Error: " << szErrMsg << std::endl;
                        sqlite3_free(szErrMsg);
                        break;
                }
        }
}
list<FichierMP3> GestionBD::selectAll()
{
	string chemin;
	string titre;
	string artiste;
	string album;
	string compo;	
	
	list<FichierMP3> resulta;

	sqlite3_stmt *statement;
        const char *pSQL[1];
	pSQL[0] = "SELECT * FROM musique";
	if(sqlite3_prepare(db, pSQL[0], -1, &statement, 0 ) == SQLITE_OK )
	{
		int ctotal = sqlite3_column_count(statement);
        	int res = 0;
		while(1)         
        	{
            		res = sqlite3_step(statement);
	        	if ( res == SQLITE_ROW ) 
            		{
				chemin = (char*)sqlite3_column_text(statement, 0);
				titre = (char*)sqlite3_column_text(statement, 1);
				artiste = (char*)sqlite3_column_text(statement, 2);
				album = (char*)sqlite3_column_text(statement, 3);
				compo = (char*)sqlite3_column_text(statement, 4);
				resulta.push_back(FichierMP3(chemin,titre,artiste,album,compo));

            		}
              		if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            		{
                		cout << "done " << endl;
               			 break;
            		}    
        	}
	}
	return resulta;
}
void GestionBD::select(string chemin)
{
	char *szErrMsg = 0;
        const char *pSQL[1];
        string lol = "SELECT * FROM musique WHERE chemin = '" + chemin + "'";
        pSQL[0] = lol.c_str();

        for(int i = 0; i < 1; i++)
        {
                rc = sqlite3_exec(db, pSQL[i], callback, 0, &szErrMsg);
                if(rc != SQLITE_OK)
                {
                        std::cout << "SQL Error: " << szErrMsg << std::endl;
                        sqlite3_free(szErrMsg);
                        break;
                }
        }

}
GestionBD::~GestionBD()
{
	// close database
        if(db)
        {
                sqlite3_close(db);
        }
}
