
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
#define _size 100

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

	float Home;
	float Food;
	float Water;
	float Enemy;

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

public:
	IA();

private:

};

#endif