//ICEserveurMP3.ice

module Serveur{
	sequence<string> listMP3;
	sequence<byte> MusiqueByte;
	interface mp3{
		bool supprimerMP3(string titre);
		bool rechercherMP3(string titre);
		string jouerMP3(string titre);
		string getToken();
		void play();
		void stop();
		void envoyerMusique(string titre, string artiste, string album, string compo, MusiqueByte musique); 
		listMP3 listerMP3();
	};
};
