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

class ServeurMP3
{
    private :
        int nbMP3;
        list<FichierMP3> listMP3;
        list<FichierMP3>::iterator itListMP3;
	libvlc_instance_t *vlc;
	string token;
	GestionBD * gestionBD;
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
