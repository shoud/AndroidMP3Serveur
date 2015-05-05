//ICEserveurMP3.ice

module Serveur{
	sequence<string> listMP3;
	sequence<byte> MusiqueByte;
	interface mp3{
		void ajouterMP3(string nom,string url);
		bool supprimerMP3(string nom);
		bool rechercherMP3(string nom);
		string jouerMP3(string nom);
		string getToken();
		void play();
		void stop();
		void envoyerMusique(string nom, MusiqueByte musique); 
		listMP3 listerMP3();
	};
};
