#include <fstream>
#include <iostream>
using namespace std;
#include "lancement.hpp"

//-------------------------------

int main(int argc, char * argv[])
{
	bool quitter = false ; string saisie;

	if(argc > 1) // Si nom de fichier passé en paramètre alors lecture de celui-ci.
	{
		string nom = argv[1] ; fstream f_mots;

		f_mots.open(nom, ios::in); // Ouverture du fichier passé en paramètre.

		if(f_mots.is_open()) // L'ouverture du fichier est un succès.
		{
			string temporaire ; f_mots >> temporaire;

			if(temporaire == "")
			{
				cout << "Le fichier est vide." << endl;
			}
			else
			{
				saisie = temporaire ; f_mots >> temporaire;

				while(not f_mots.eof()) // Parcours de la totalité du fichier.
				{
					saisie = saisie + ' ' + temporaire;
					// Une variable de type chaîne de caractères récupère les commandes présentes dans le fichier.
					f_mots >> temporaire;
    				}
    				f_mots.close(); // Fermeture du fichier.

				lancement(saisie, quitter); // Appel de la procédure lancement() en lui passant une chaîne de caractères contenant la totalité des commandes présentes dans le fichier ainsi que la variable quitter (en modification).
			}
		}
		else // Problème d'ouverture du fichier.
		{
			cout << "Le fichier " << nom << " n'a pas pu être ouvert en lecture." << endl;
		}
	}
	else // Si aucun nom de fichier ou si plusieurs noms de fichier passés en paramètre.
	{
		while(!(quitter))
		{
			// Saisie d'une ou plusieurs commandes en séquentiel et/ou en parallèle.
			cout << "mush : " ; getline(cin, saisie);

			// Appel de la procédure lancement() en lui passant une chaîne de caractères contenant la totalité des commandes présentes dans le fichier ainsi que la variable quitter (en modification).
			lancement(saisie, quitter);
		}
	}
	return 0; // Fermeture du programme si fichier passé en paramètre puis exécution de toutes les commandes présentes dans ce dernier ou si la commande "quit" a été saisie par l'utilisateur.
}
