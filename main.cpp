/**
* Application serveur du TP Lecteur MP3
* Il doit permettre de gérer les fichiers MP3
* Fonctionnalités :
*   -Ajout d'un morceau
*   -Suppresion d'un morceau
*   -Afficher toute la liste des morceaux.
*   -Rechercher un morceaux.
*/

#include <Ice/Ice.h>
#include <IceStorm/IceStorm.h>
#include "ICEserveurMP3.h"
#include "ServeurMP3.h"

using namespace std;

class ServeurMP3I : public Serveur::mp3 {
private :
	ServeurMP3 sm;
public:
    virtual bool supprimerMP3(const string& titre, const Ice::Current&);
    virtual bool rechercherMP3(const string& titre, const Ice::Current&);
    virtual string jouerMP3(const string& titre, const Ice::Current&);
    virtual string getToken(const Ice::Current&);
    virtual string getArtiste(const string& titre, const Ice::Current&);
    virtual string getAlbum(const string& titre, const Ice::Current&);
    virtual string getCompo(const string& titre, const Ice::Current&);
    virtual void play(const Ice::Current&);
    virtual void stop(const Ice::Current&);
    virtual Serveur::listMP3 listerMP3(const Ice::Current&);
    virtual void envoyerMusique(const std::string& titre, const std::string& artiste, const std::string& album, const std::string& compo, const Serveur::MusiqueByte& musique, const Ice::Current&);
};

void ServeurMP3I::envoyerMusique(const std::string& titre, const std::string& artiste, const std::string& album, const std::string& compo, const Serveur::MusiqueByte& musique, const Ice::Current&)
{
    sm.envoyerMusique(titre,artiste,album,compo,musique);
}
bool ServeurMP3I::supprimerMP3(const string& titre, const Ice::Current&)
{
    return sm.supprimerMP3(titre);
}
bool ServeurMP3I::rechercherMP3(const string& titre, const Ice::Current&)
{
    return sm.rechercherMP3(titre);
}
string ServeurMP3I::jouerMP3(const string& titre, const Ice::Current&)
{
    sm.jouerMP3(titre);
}
string ServeurMP3I::getArtiste(const string& titre, const Ice::Current&)
{
    return sm.getArtiste(titre);
}
string ServeurMP3I::getAlbum(const string& titre, const Ice::Current&)
{
    return sm.getAlbum(titre);
}
string ServeurMP3I::getCompo(const string& titre, const Ice::Current&)
{
    return sm.getCompo(titre);
}
string ServeurMP3I::getToken(const Ice::Current&)
{
	return sm.getToken();
}
void ServeurMP3I::play(const Ice::Current&)
{
	sm.play();
}
void ServeurMP3I::stop(const Ice::Current&)
{
	sm.stop();
}
Serveur::listMP3 ServeurMP3I::listerMP3(const Ice::Current&)
{
    return sm.listerMP3();
}

int main(int argc, char* argv[])
{
   int status = 0;
   Ice::CommunicatorPtr ic;
   try
   {
        ic = Ice::initialize(argc, argv);
        //Service de messagerie
	Ice::ObjectPrx obj = ic->stringToProxy("IceStorm/TopicManager:tcp -h shoud.ovh -p 5038");
	IceStorm::TopicManagerPrx topicManager = IceStorm::TopicManagerPrx::checkedCast(obj);
	IceStorm::TopicPrx topic;
	while (!topic)
	{
		try
		{
			topic = topicManager->retrieve("StreamPlayerNotifs");
			std::cout << "Retrieving topic...\n";
		} catch (const IceStorm::NoSuchTopic&) {
			std::cout << "No topic!\n";
			try {
				topic = topicManager->create("StreamPlayerNotifs");
				std::cout << "Creating topic...\n";
			} catch(const IceStorm::TopicExists&) {
			}
		}
	}
	std::cout << "Topic active!\n";
	Ice::ObjectPrx pub = topic->getPublisher()->ice_twoway();
	Serveur::MoniteurPrx moniteur;
	moniteur = Serveur::MoniteurPrx::uncheckedCast(pub);
	std::cout << "Moniteur activé\n";


	//Serveur MP3
	Ice::ObjectAdapterPtr adapter = ic->createObjectAdapterWithEndpoints("SimpleServeurMP3Adapter", "default -p 10000");
        Ice::ObjectPtr object = new ServeurMP3I;
        adapter->add(object, ic->stringToIdentity("SimpleServeurMP3"));
        adapter->activate();
        ic->waitForShutdown();
    }
    catch(const Ice::Exception& e)
    {
        cerr << e << endl;
        status = 1;
    }
    catch(const char* msg)
    {
        cerr << msg << endl;
        status = 1;
    }
    if (ic)
    {
        try
        {
            ic->destroy();
        }
        catch(const Ice::Exception& e)
        {
            cerr << e << endl;
            status = 1;
        }
    }
    return status;
}
