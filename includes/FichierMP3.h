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
        string titre; //Le titre de la musique
	string chemin; //Le chemin où est enregistré la musique
	string album; //l'album de la musique
	string compo; //Le compositeur de la musique
	string artiste; //l'artiste de la musique

    public:
        FichierMP3(string chemin, string titre, string artiste, string album, string compo);
      	void init();
	string getTitre();
	string getChemin();
	string getAlbum();
	string getCompo();
	string getArtiste();
};    

#endif // FICHIERMP3_H
