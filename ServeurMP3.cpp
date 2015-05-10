#include "ServeurMP3.h"
#include "vlc/libvlc.h"
#include "vlc/libvlc_vlm.h"
#include <dirent.h>
#include <chrono>

/**
* Constructeur de la classe ServeurMP3
*/
ServeurMP3::ServeurMP3()
{
	nbMP3 = 0;

	//Permet de faire du streaming
	vlc = libvlc_new(0, NULL);
	//Connexion à la base de données
	gestionBD = new GestionBD();
	//On récupère tout les mp3 enregistré
	listMP3 = gestionBD->selectAll();	
}
/**
* Permet de rajouter un fichier MP3.
* @param nom Le nom du fichier MP3.
* @param chemin Où est enregistré le fichier MP3.
* @return true Le fichier a bien été rajouté.
* @return false Le fichier n'a pas pu être rajouté.
*/
void ServeurMP3::ajouterMP3(string chemin,string titre, string artiste, string album, string compo)
{
    	if((!rechercherMP3(titre)) && (titre != ""))
	{
	        listMP3.push_back(FichierMP3( chemin, titre, artiste, album, compo));
		gestionBD->ajouter(chemin, titre, artiste, album, compo);
	}
}
/**
* Permet de supprimer un fichier MP3.
* @param nom Nom du fichier à supprimer.
*/
bool ServeurMP3::supprimerMP3(string titre)
{
    for(itListMP3 = listMP3.begin(); itListMP3 != listMP3.end(); itListMP3++)
            if(itListMP3->getTitre() == titre)
            {
                listMP3.erase(itListMP3);
                gestionBD->supprimer(itListMP3->getChemin());
		return true;
            }
    return false;
}
/**
* Permet de rechercher un fichier MP3.
* @param nom Le nom du fichier à rechercher.
*/
bool ServeurMP3::rechercherMP3(string titre)
{
    for(itListMP3 = listMP3.begin(); itListMP3 != listMP3.end(); itListMP3++)
            if(itListMP3->getTitre() == titre)
                return true;
    return false;
}
string ServeurMP3::getArtiste(string titre)
{
    for(itListMP3 = listMP3.begin(); itListMP3 != listMP3.end(); itListMP3++)
            if(itListMP3->getTitre() == titre)
                return itListMP3->getArtiste();
    return "Inconnu";
}
string ServeurMP3::getAlbum(string titre)
{
    for(itListMP3 = listMP3.begin(); itListMP3 != listMP3.end(); itListMP3++)
            if(itListMP3->getTitre() == titre)
                return itListMP3->getAlbum();
    return "Inconnu";
}
string ServeurMP3::getCompo(string titre)
{
    for(itListMP3 = listMP3.begin(); itListMP3 != listMP3.end(); itListMP3++)
            if(itListMP3->getTitre() == titre)
                return itListMP3->getCompo();
    return "Inconnu";
}
/**
* Permet d'afficher la liste de MP3.
*/
Serveur::listMP3 ServeurMP3::listerMP3()
{
	Serveur::listMP3 res;
	if(!listMP3.empty())
    	{
        	for(itListMP3 = listMP3.begin(); itListMP3 != listMP3.end(); itListMP3++)
		res.push_back(itListMP3->getTitre());
    	}
	return res;
}
/**
* Permet de jouer une musique en streaming
*/
string ServeurMP3::jouerMP3(string titre)
{
	if(vlc == NULL)
		return "";
	auto duration = chrono::system_clock::now().time_since_epoch();
	token = to_string(chrono::duration_cast<chrono::nanoseconds>(duration).count());
	if(rechercherMP3(titre))
	{
		string stringUrl = "";
		string stringSout = "";
		const char *url; //Le chemin pour obtenir le fichier
		stringSout = "#transcode{acodec=mp3,ab=128,channels=2," \
                               "samplerate=44100}:http{dst=:8090/" + token + ".mp3}";

		const char *sout = stringSout.c_str();
	    	stringUrl = "mp3/" + titre + ".mp3";
		url = stringUrl.c_str(); 

	 	libvlc_vlm_add_broadcast(vlc, token.c_str(), url, sout, 0, nullptr, true, false);
		
		//Information console
		cout << "token = " << token << endl;
		cout << "url = " << url << endl;
		cout << "sout = " << sout << endl;
		cout << "titre = " << titre << endl;
		cout << "vlc = " << vlc << endl;
		
		return token;
	}
	else
	{
		cout << "La musique n'existe pas" << endl;
	}
	return "";
}
/**
* Permet de relancer une musique 
*/
void ServeurMP3::play()
{
	cout << "lecture de la musique" << endl; 
	libvlc_vlm_play_media(vlc, token.c_str());
}
/**
* Permet de mettre en pause une musique
*/
void ServeurMP3::stop()
{
	libvlc_vlm_stop_media(vlc, token.c_str());
}
/**
* Permet de renvoyer le token au client
*/
string ServeurMP3::getToken()
{
	return token;
}
void ServeurMP3::envoyerMusique(string titre, string artiste, string album, string compo, Serveur::MusiqueByte musique)
{
	cout << "Initialisation de l'envois de la musique" << endl;
	FILE* file;
	std::string chemin = "mp3/" + titre + ".mp3";
	file = fopen(chemin.c_str(), "a+");
	fseek(file, 0, SEEK_END);
	fwrite(&musique[0], 1, musique.size(), file);
	cout << "Musique enregistré dans : " << chemin << endl;
	fclose(file);
	ajouterMP3(chemin, titre, artiste, album, compo);	
}
