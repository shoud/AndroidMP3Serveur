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
#include "ICEserveurMP3.h"
#include "ServeurMP3.h"

using namespace std;

class ServeurMP3I : public Serveur::mp3 {
private :
	ServeurMP3 sm;
public:
    virtual void ajouterMP3(const string& nom,const string& url ,const Ice::Current&);
    virtual bool supprimerMP3(const string& nom, const Ice::Current&);
    virtual bool rechercherMP3(const string& nom, const Ice::Current&);
    virtual string jouerMP3(const string& nom, const Ice::Current&);
    virtual string getToken(const Ice::Current&);
    virtual void play(const Ice::Current&);
    virtual void stop(const Ice::Current&);
    virtual Serveur::listMP3 listerMP3(const Ice::Current&);

};

void ServeurMP3I::ajouterMP3(const string& nom,const string& url ,const Ice::Current&)
{
    return sm.ajouterMP3(nom, url);
}
bool ServeurMP3I::supprimerMP3(const string& nom, const Ice::Current&)
{
    return sm.supprimerMP3(nom);
}
bool ServeurMP3I::rechercherMP3(const string& nom, const Ice::Current&)
{
    return sm.rechercherMP3(nom);
}
string ServeurMP3I::jouerMP3(const string& nom, const Ice::Current&)
{
    sm.jouerMP3(nom);
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
