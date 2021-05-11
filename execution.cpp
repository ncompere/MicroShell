#include <vector>
#include <glob.h>
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

//---------------------------------------------

void execution(vector<vector<char*>> commandes) // Procédure nous permettant d'exécuter les différentes commandes en séquentiel et/ou en parallèle.
{
	int identifiants[commandes.size()];

	// Les différentes commandes de chaque commande composée sont exécutées. Il y aura autant de fils que de commandes en parallèle.
	for(int i = 0 ; i < commandes.size() ; i++)
	{
		glob_t para ; glob(commandes[i][0], GLOB_NOCHECK, nullptr, &para);

		for(int k = 1 ; k < commandes[i].size() ; k++)
		{
			glob(commandes[i][k], GLOB_NOCHECK | GLOB_APPEND, nullptr, &para);
		}

		int nombre = para.gl_pathc ; string temporaire = "";

		char * arguments[nombre]; // Création du tableau de char * qui doit être passé à la fonction execvp().

		for(int j = 0 ; j < nombre ; j++) // Récupération des différents paramètres dans le tableau de char *.
		{
			arguments[j] = para.gl_pathv[j] ; temporaire = temporaire + arguments[j] + ' ';
		}
		arguments[nombre] = nullptr;

		pid_t pid_enfant = fork() ; identifiants[i] = getpid(); // Création d'un fils.

		if(pid_enfant == 0) // Exécution du fils.
		{
			execvp(arguments[0], arguments); // Exécution de la commande.

			string escape = arguments[0];
			// Si l'exécution de la commande précédente a retournée une erreur.
			if(nombre == 1 && escape == "quit")
			{
				char * exit[3] = {"echo", "La commande quit ne peut être exécutée qu'en séquentielle.", nullptr};
				execvp(exit[0], exit);
			}
			else
			{
				char * maCommande = new char[temporaire.length()+1] ; strcpy(maCommande, temporaire.c_str());
				char * erreur[4] = {"echo", "Problème au niveau de l'exécution de la commande :", maCommande, nullptr};
				execvp(erreur[0], erreur);
			}
		}
	}
	for(int i = 0 ; i < commandes.size() ; i++) { wait(nullptr); } // Quand tous les fils ont terminé, le processus père reprend la main.
}
