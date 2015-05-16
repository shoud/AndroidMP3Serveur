#include "FichierMP3.h"

/**
* Constructeur de la classe FichierMP3.
*/
FichierMP3::FichierMP3(string chemin,string titre, string artiste, string album, string compo)
{
   	this->titre  = titre;
	this->chemin = chemin;
	this->artiste = artiste;
	this->album = album;
	this->compo = compo;
}
/**
* Permet de retourner le nom de la musique.
* @return nom Le nom du MP3.
*/
string FichierMP3::getTitre()
{
        return titre;
}
string  FichierMP3::getChemin()
{
	return chemin;
}
string FichierMP3::getAlbum()
{
	return album;
}
string FichierMP3::getCompo()
{
	return compo;
}
string FichierMP3::getArtiste()
{
	return artiste;
}
