#include "FichierMP3.h"

/**
* Constructeur de la classe FichierMP3.
*/
FichierMP3::FichierMP3(string nom,string url)
{
    	this->nom  = nom;
	this->url = url;
}
/**
* Permet de retourner le nom de la musique.
* @return nom Le nom du MP3.
*/
string FichierMP3::getNom()
{
        return nom;
}
string  FichierMP3::getUrl()
{
	return url;
}
