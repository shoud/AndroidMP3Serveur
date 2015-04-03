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
	//Le nom du mp3
        string nom;
	//Le chemin sur le disque du mp3
        string url;

    public:
        FichierMP3(string nom, string url);
        string getNom();
	string getUrl();
};    

#endif // FICHIERMP3_H
