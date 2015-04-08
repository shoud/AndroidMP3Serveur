#ifndef FICHIERMP3_H
#define FICHIERMP3_H

#include <iostream>

using namespace std;
/**
* Classe représentant une musique en MP3
*/
class FichierMP3
{
    private :
        string nom; //Le titre de la musique
	string url; //Le chemin où est enregistré la musique
	string album;
	string compo;
	string chanteur;

    public:
        FichierMP3(string nom, string url);
      	void init();
	string getNom();
	string getUrl();
	string getAlbum();
	string getCompo();
	string getChanteur();
};    

#endif // FICHIERMP3_H
