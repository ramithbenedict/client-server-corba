#Mode d’emploi 

##Création des exécutables

Pour pouvoir créer les exécutables client et serveur, il faut se placer dans le dossier du projet et exécuté la commande : make

$ make

##Configuration du client et du serveur

Une fois exécuté, vous aurez maintenant deux nouveaux fichiers client et server. Il faut avant tout exécuter la commande suivante :

$ orbd -ORBInitialPort 1234

Pour lancer le serveur​, exécutez la commande suivante :

$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:omniORB-4.2.1/lib
$ ./server -ORBInitRef NameService=corbaloc::localhost:1234/NameService

Pour lancer le Client​, exécutez la commande suivante :

$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:omniORB-4.2.1/lib
$ ./client -ORBInitRef NameService=corbaloc::localhost:1234/NameService

##Remarque :

La commande export

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:omniORB-4.2.1/lib Permet de mettre la

librairie omniORB-4.2.1 dans le path LD_LIBRARY_PATH.
