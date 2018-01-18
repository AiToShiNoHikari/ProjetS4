#include "IA.h"

IA::IA(CaseTerrain** Terrain)
{
	this->Terrain = Terrain;

	Pheromone_Table = new Pheromone*[_nb_case_w];
	for (int i = 0; i < _nb_case_w; i++)
	{
		Pheromone_Table[i] = new Pheromone[_nb_case_h];
	}

	direction;
};

void IA::deplacement()
{

};