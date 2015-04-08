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
	DIR* rep = nullptr;
	struct dirent* fichierLu = nullptr;
	string titreMP3 = "";
	rep = opendir("./mp3");
	if(rep != NULL)
	{
		while((fichierLu = readdir(rep)) != NULL)
		{
			titreMP3 = fichierLu->d_name;
			size_t pos = titreMP3.find(".");
			titreMP3 = titreMP3.substr(0, pos);	
			ajouterMP3(titreMP3,"test");	
		}
		closedir(rep);
	}
	else
	{
		cout << "pas de repertoire" << endl;
	}
}
/**
* Permet de rajouter un fichier MP3.
* @param nom Le nom du fichier MP3.
* @param chemin Où est enregistré le fichier MP3.
* @return true Le fichier a bien été rajouté.
* @return false Le fichier n'a pas pu être rajouté.
*/
void ServeurMP3::ajouterMP3(string nom,string url)
{
    if((!rechercherMP3(nom)) && (nom != ""))
        listMP3.push_back(FichierMP3(nom, url));
}
/**
* Permet de supprimer un fichier MP3.
* @param nom Nom du fichier à supprimer.
*/
bool ServeurMP3::supprimerMP3(string nom)
{
    for(itListMP3 = listMP3.begin(); itListMP3 != listMP3.end(); itListMP3++)
            if(itListMP3->getNom() == nom)
            {
                listMP3.erase(itListMP3);
                return true;
            }
    return false;
}
/**
* Permet de rechercher un fichier MP3.
* @param nom Le nom du fichier à rechercher.
*/
bool ServeurMP3::rechercherMP3(string nom)
{
    for(itListMP3 = listMP3.begin(); itListMP3 != listMP3.end(); itListMP3++)
            if(itListMP3->getNom() == nom)
                return true;
    return false;
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
		res.push_back(itListMP3->getNom());
    	}
	return res;
}
/**
* Permet de jouer une musique en streaming
*/
string ServeurMP3::jouerMP3(string nom)
{
	vlc = libvlc_new(0, NULL);
	if(vlc == NULL)
		return "";
	auto duration = chrono::system_clock::now().time_since_epoch();
	token = to_string(chrono::duration_cast<chrono::nanoseconds>(duration).count());
	if(rechercherMP3(nom))
	{
		string stringUrl = "";
		string stringSout = "";
		const char *url; //Le chemin pour obtenir le fichier
		stringSout = "#transcode{acodec=mp3,ab=128,channels=2," \
                               "samplerate=44100}:http{dst=:8090/" + token + ".mp3}";

		const char *sout = stringSout.c_str();
	    	stringUrl = "mp3/" + nom + ".mp3";
		url = stringUrl.c_str(); 

	 	libvlc_vlm_add_broadcast(vlc, token.c_str(), url, sout, 0, nullptr, true, false);
		
		//Information console
		cout << "token = " << token << endl;
		cout << "url = " << url << endl;
		cout << "sout = " << sout << endl;
		cout << "titre = " << nom << endl;
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
