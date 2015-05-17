#include "FichierMP3.h"

/**
* Constructeur de la classe FichierMP3.
* Elle permet de créer un fichier mp3
* @param chemin Le chemin physique sur la machine du fichier
* @param titre Le titre de la musique
* @param artiste Le nom du chanteur de la musique
* @param album Le nom de l'album contenant la musique
* @param compo Le nom du compositeur de la musique
*/
FichierMP3::FichierMP3(string chemin,string titre, string artiste, string album, string compo)
{
   	//Récupération du titre
	this->titre  = titre;
	//Récupération du chemin
	this->chemin = chemin;
	//Récupération de l'artiste
	this->artiste = artiste;
	//Récupération de l'album
	this->album = album;
	//Récupération du compositeur
	this->compo = compo;
}
/**
* Permet de retourner le titre de la musique.
* @return titre Le titre du MP3.
*/
string FichierMP3::getTitre()
{
        return titre;
}
/**
* Permet de retourner le chemin de la musique
* @return chemin Le chemin sur le disque de la musique
*/
string  FichierMP3::getChemin()
{
	return chemin;
}
/**
* Permet de retourner l'album de la muisque
* @return album L'album de la musique
*/
string FichierMP3::getAlbum()
{
	return album;
}
/**
* Permet de retourner le compositeur de la musique
* @param compo Le compositeur de la musique
*/
string FichierMP3::getCompo()
{
	return compo;
}
/**
* Permet de retourner l'artiste de la musique
* @param artiste L'artiste de la musique
*/
string FichierMP3::getArtiste()
{
	return artiste;
}
