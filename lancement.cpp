#include <vector>
#include "parsing.hpp"
#include <cstring>
#include <iostream>
using namespace std;
#include "execution.hpp"

//---------------------------------------------

void lancement(string saisie, bool& quitter)
{
	char * parametre ; vector<char*> monVecteur ; vector<vector<char*>> vecteurInter ; vector<vector<vector<char*>>> parametres;

	vector<compound_command_t> commands ; parse_line(saisie, commands); // Découpage des différentes commandes.

	for (auto compound_command : commands)
	{
		for (auto simple_command : compound_command)
		{
			for (auto param : simple_command)
			{
				parametre = new char[param.length()+1] ; strcpy(parametre, param.c_str());
				// Création d'un vecteur de vecteurs de vecteurs de char * contenant les différentes commandes.
				monVecteur.push_back(parametre);
			}
			vecteurInter.push_back(monVecteur) ; monVecteur.clear();
		}
		parametres.push_back(vecteurInter) ; vecteurInter.clear();
	}

	int i = 0;

	// Tant qu'on ne trouve pas la commande "quit" et que la totalité du vecteur de commandes n'a pas été parcourue.
	while(!(quitter) && i < parametres.size())
	{
		cout << "--------------------" << endl;

		if(parametres[i].size() == 1 && parametres[i][0].size() == 1)
		{
			string parametre = parametres[i][0][0];

			if(parametre == "quit")
			{
				quitter = true;
			}
			else
			{
				execution(parametres[i]) ; i += 1;
			}
		}
		else // Exécution des différentes commandes via la procédure execution() en lui passant chaque commande composée en paramètre.
		{
			execution(parametres[i]) ; i += 1;
		}
	}
}
