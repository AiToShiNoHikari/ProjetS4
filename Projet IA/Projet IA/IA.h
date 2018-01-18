
#ifndef _IA

#define _IA true

#include <SFML/Graphics.hpp>

#include <vector>

#ifdef _DEBUG
#include <iostream>
#endif
#include <fstream>
#include <sstream>
#include <iomanip>

#include <string>

#endif

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
public:
	IA();
	~IA();

private:

};

IA::IA()
{
}

IA::~IA()
{
}