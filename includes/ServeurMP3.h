#ifndef SERVEURMP3_H
#define SERVEURMP3_H

#include "FichierMP3.h"
#include <list>
#include <iostream>
#include "ICEserveurMP3.h"
#include "vlc/libvlc.h"
#include "vlc/libvlc_vlm.h"
#include "GestionBD.h"

using namespace std;

/**
* Classe permettant de gérer des fichiers mp3
* et de faire du streaming
*/
class ServeurMP3
{
    private :
        // Le nombre de fichier mp3
	int nbMP3;
	//La liste des fichier mp3
        list<FichierMP3> listMP3;
	//L'itérator de la liste des fichier mp3
        list<FichierMP3>::iterator itListMP3;
	//L'objet vlc permettant de faire du streaming
	libvlc_instance_t *vlc;
	//Le token pour avoir des conexion uniques
	string token;
	//L'objet permettant de faire des requets sur la base de données
	GestionBD * gestionBD;
	//Pour envoyer un message avec Storm
	Serveur::MoniteurPrx moniteur;

    public:
        ServeurMP3(Serveur::MoniteurPrx moniteur);
	void ajouterMP3(string chemin,string titre, string artiste, string album, string compo);
        bool supprimerMP3(string nom);
        bool rechercherMP3(string nom);
        Serveur::listMP3 listerMP3();
	string jouerMP3(string nom);
	string getArtiste(string nom);
	string getAlbum(string nom);
	string getCompo(string nom);
	void play();
	void stop();
	void envoyerMusique(string titre, string artiste, string album, string compo, Serveur::MusiqueByte musique);
	string getToken();
};

#endif // SERVEURMP3_H
