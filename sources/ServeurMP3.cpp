#include "ServeurMP3.h"
#include "vlc/libvlc.h"
#include "vlc/libvlc_vlm.h"
#include <dirent.h>
#include <chrono>

/**
* Constructeur de la classe ServeurMP3
* @param moniteur Le moniteur permettant d'envoyer des messages
*/
ServeurMP3::ServeurMP3(Serveur::MoniteurPrx moniteur)
{
	//le nombre de mp3
	nbMP3 = 0;
	//Le moniteur pour Storm
	this->moniteur = moniteur;
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
    	//On vérifie si le fichier n'est pas déjà présent ou si le titre et vide
	if((!rechercherMP3(titre)) && (titre != ""))
	{
	        //On rajoute le nouveau mp3 dans la liste dynamique
		listMP3.push_back(FichierMP3( chemin, titre, artiste, album, compo));
		//On rajoute le nouveau mp3 dans la base de donnée
		gestionBD->ajouter(chemin, titre, artiste, album, compo);
		//On envoi un message pour dire qu'il y a un nouveau mp3
		moniteur->rapport("ajouter",titre);
	}
}
/**
* Permet de supprimer un fichier MP3.
* @param nom Nom du fichier à supprimer.
*/
bool ServeurMP3::supprimerMP3(string titre)
{
 	//On parcour la liste de mp3 pour trouver le titre à supprimer
	for(itListMP3 = listMP3.begin(); itListMP3 != listMP3.end(); itListMP3++)
        	//Si le titre est présent
		if(itListMP3->getTitre().compare(titre) == 0)
            	{
			//Suppression du MP3 sur le disque
			remove(itListMP3->getChemin().c_str());
			//On supprimer le mp3 de la base de donnée
                        gestionBD->supprimer(itListMP3->getChemin());
			//On enleve le mp3 de la liste dynamique	
                	listMP3.erase(itListMP3);
			//On envoi un message pour dire qu'un titre a été supprimé
			moniteur->rapport("supprimer",titre);
			//On retourne comme quoi le fichier a bien été supprimé
			return true;
            	}
	//La fichier n'a pas pu etre supprimé
    	return false;
}
/**
* Permet de rechercher un fichier MP3.
* @param nom Le nom du fichier à rechercher.
*/
bool ServeurMP3::rechercherMP3(string titre)
{
	//On parcour la liste de mp3
	for(itListMP3 = listMP3.begin(); itListMP3 != listMP3.end(); itListMP3++)
		//Si le titre est présent
            	if(itListMP3->getTitre() == titre)
			//On retounre vraie
                	return true;
	//Sinon on retourne faux
    	return false;
}
/**
* Fonction permettant de retourner l'artiste d'une musique
* @param titre le titre de la musique
*/
string ServeurMP3::getArtiste(string titre)
{
	//On parcout toute la liste de muisque
	for(itListMP3 = listMP3.begin(); itListMP3 != listMP3.end(); itListMP3++)
		//Si le titre est présent
           	if(itListMP3->getTitre() == titre)
			//On retourn l'artiste
                	return itListMP3->getArtiste();
	//Sinon on retourn Inconnu comme nom de l'artiste
    	return "Inconnu";
}
/**
* Fonction permettant de retourner le nom de l'album
* @param titre le titre de la musique
*/
string ServeurMP3::getAlbum(string titre)
{
	//On parcour toute la liste de mp3
	for(itListMP3 = listMP3.begin(); itListMP3 != listMP3.end(); itListMP3++)
		//Si le titre est présent
            	if(itListMP3->getTitre() == titre)
			//on retourne le nom de l'album
                	return itListMP3->getAlbum();
	//Sinon on retourne inconnu
    	return "Inconnu";
}
/**
* Fonction permettant de retourner le nom du compositeur
* @param titre le titre de la musique
*/
string ServeurMP3::getCompo(string titre)
{
	//On parcou toute la liste de musique
	for(itListMP3 = listMP3.begin(); itListMP3 != listMP3.end(); itListMP3++)
		//Si le titre est présent
            	if(itListMP3->getTitre() == titre)
			//On retourn le nom du compositeur
                	return itListMP3->getCompo();
	//Sinon on retourne Inconnu
    	return "Inconnu";
}
/**
* Permet d'afficher la liste des MP3.
*/
Serveur::listMP3 ServeurMP3::listerMP3()
{
	//Création de la liste à retourner
	Serveur::listMP3 res;
	//Si la liste de mp3 n'est pas vide
	if(!listMP3.empty())
    	{
        	//On parcour toute la liste de mp3
		for(itListMP3 = listMP3.begin(); itListMP3 != listMP3.end(); itListMP3++)
			//on ajoute le titre à la liste à retourner
			res.push_back(itListMP3->getTitre());
    	}
	//On retourne la liste des titres de musique
	return res;
}
/**
* Permet de jouer une musique en streaming
* @param titre le titre de la musique à joeur
* @return token Le lien unique pour lire la musique 
*/
string ServeurMP3::jouerMP3(string titre)
{
	//On vérifie si vlc est bien instancié
	if(vlc == NULL)
		return "";
	//On récupére le temps actuel
	auto duration = chrono::system_clock::now().time_since_epoch();
	//Création du token unique
	token = to_string(chrono::duration_cast<chrono::nanoseconds>(duration).count());
	//Si le mp3 a jouer est bien présent
	if(rechercherMP3(titre))
	{
		//Les url pour vlc
		string stringUrl = "";
		string stringSout = "";
		//Le chemin où se trouve le fichier à lire
		const char *url;
		//Création du Sout pour vlc
		stringSout = "#transcode{acodec=mp3,ab=128,channels=2," \
                               "samplerate=44100}:http{dst=:8090/" + token + ".mp3}";
		//Converstion du sout dans le bon format
		const char *sout = stringSout.c_str();
		//Création de l'url où la musique sera lisible
	    	stringUrl = "mp3/" + titre + ".mp3";
		//Converstion dans le bon format de l'url de la musique
		url = stringUrl.c_str(); 
		//Lancement du stream
	 	libvlc_vlm_add_broadcast(vlc, token.c_str(), url, sout, 0, nullptr, true, false);
		
		//Information console
		cout << "token = " << token << endl;
		cout << "url = " << url << endl;
		cout << "sout = " << sout << endl;
		cout << "titre = " << titre << endl;
		cout << "vlc = " << vlc << endl;
		//On retourn le token pour le client
		return token;
	}
	//Si le musique n'existe pas
	else
		//On affiche un message dans la console
		cout << "La musique n'existe pas" << endl;
	//On retourne un token vide
	return "";
}
/**
* Permet de relancer une musique 
*/
void ServeurMP3::play()
{ 
	//Permet de relancer le stream de la musique
	libvlc_vlm_play_media(vlc, token.c_str());
}
/**
* Permet de mettre en pause une musique
*/
void ServeurMP3::stop()
{
	//met en pause le stream de la musique
	libvlc_vlm_stop_media(vlc, token.c_str());
}
/**
* Permet de renvoyer le token au client
* @return token Le jeton permettant d'avoir un lien unique pour le streaming
*/
string ServeurMP3::getToken()
{
	//Le token unique
	return token;
}
/**
* Fonction permettant d'envoyer une musique
* @param titre le titre de la musique
* @param artiste le nom de l'artiste de la musique
* @param album le nom de l'album de la musique
* @param compo Le compositeur de la musique
* @param musique le fichier reçu à enregistrer sur le disque
*/
void ServeurMP3::envoyerMusique(string titre, string artiste, string album, string compo, Serveur::MusiqueByte musique)
{
	//Création de l'objet permettant de gérer les fichiers
	FILE* file;
	//Création du chemin du fichier sur le disque
	string chemin = "mp3/" + titre + ".mp3";
	//Ouverture du chemin
	file = fopen(chemin.c_str(), "a+");
	//Permet de définir la position
	fseek(file, 0, SEEK_END);
	//Ecriture du fichier sur le disque
	fwrite(&musique[0], 1, musique.size(), file);
	//Fermeture du gestionaire de fichier 
	fclose(file);
	//On ajoute le mp3 dans le programme
	ajouterMP3(chemin, titre, artiste, album, compo);	
}
