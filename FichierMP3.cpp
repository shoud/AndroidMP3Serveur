#include "FichierMP3.h"

void FichierMP3::init()
{
	this->nom = "inconnue";
	this->url = "inconnue";
	this->album = "inconnue";
	this->compo = "inconnue";
	this->chanteur = "inconnue";
}
/**
* Constructeur de la classe FichierMP3.
*/
FichierMP3::FichierMP3(string nom,string url)
{
	//init(); 
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
string FichierMP3::getAlbum()
{
	return album;
}
string FichierMP3::getCompo()
{
	return compo;
}
string FichierMP3::getChanteur()
{
	return chanteur;
}
