#ifndef SERVEURMP3_H
#define SERVEURMP3_H

#include "FichierMP3.h"
#include <list>
#include <iostream>
#include "ICEserveurMP3.h"
#include "vlc/libvlc.h"
#include "vlc/libvlc_vlm.h"


using namespace std;

class ServeurMP3
{
    private :
        int nbMP3;
        list<FichierMP3> listMP3;
        list<FichierMP3>::iterator itListMP3;
	libvlc_instance_t *vlc;
	string token;

    public:
        ServeurMP3();
        void ajouterMP3(string nom, string url);
        bool supprimerMP3(string nom);
        bool rechercherMP3(string nom);
        Serveur::listMP3 listerMP3();
	string jouerMP3(string nom);
	void play();
	void stop();
	string getToken();
};

#endif // SERVEURMP3_H
