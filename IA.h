
#ifndef _IA

#define _IA 1

#include "Terrain.h"


#include <SFML/Graphics.hpp>

#include <vector>

#ifdef _DEBUG
#include <iostream>
#endif
#include <fstream>
#include <sstream>
#include <iomanip>

#include <string>

#define _nb_case_w 500
#define _nb_case_h 500
#define _size 32

struct CaseTerrain;

struct Pheromone
{
	enum Type
	{
		home,
		food,
		water,
		enemy,
	};

	float Home = 0;
	float Food = 0;
	float Water = 0;
	float Enemy = 0;

	float& operator[](Type T)
	{
		switch (T)
		{
		case Pheromone::home:
			return Home;
			break;
		case Pheromone::food:
			return Food;
			break;
		case Pheromone::water:
			return Water;
			break;
		case Pheromone::enemy:
			return Enemy;
			break;
		}
	};
};

class IA
{
	CaseTerrain** Terrain;

	Pheromone** Pheromone_Table;

	float x = 0, y = 0;

	float direction = 0;

public:
	enum Type_Destination
	{
		none,
		search,
		home,
		food,
		water,
		enemy,
	};

	IA(CaseTerrain** Terrain);

	void deplacement();

private:

};

#endif