
#ifndef _IA

#define _IA 1

#include "Terrain.h"

#include <cmath>

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

#define PI 3.14159265

struct CaseTerrain;

struct Pheromone
{
	enum Type
	{
		none,
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
	enum Type_Destination;

	CaseTerrain** Terrain;

	Pheromone** Pheromone_Table;

	float x = 0, y = 0;

	int case_x = 0, case_y = 0;

	float dx = 0, dy = 0;

	float rotation = 0;

	//parametre de l'IA

	float speed = 1;

	float detection_range = 1;

	int Pheromone_max = 2000;

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

	Type_Destination destination = none;
	Type_Destination contenue = none;

	int Pheromone_current = 0;

	IA(CaseTerrain** Terrain);

	void deplacement();
	void analyse();
	void change_dest();
	void action();

private:

};

#endif