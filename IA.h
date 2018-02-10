
#ifndef _IA

#define _IA 1

#include "Terrain.h"

#include <cmath>
#include <random>
#include <chrono>

#include <SFML/Graphics.hpp>

#include <vector>
#include <list>

#ifdef _DEBUG
#include <iostream>
#endif
#include <fstream>
#include <sstream>
#include <iomanip>

#include <string>

#define _size 32

#define PI 3.14159265

class ClassTerrain;

struct CaseTerrain;

class Fourmiliere;

struct Parametre_IA
{
	float speed;
	float sand_speed;
	float water_speed;

	float detection_range;

	float Pheromone_max;

	int qantity_max;

	float max_angle_deviation;

	void operator=(Parametre_IA& in)
	{
		speed = in.speed;
		sand_speed = in.sand_speed;
		water_speed = in.water_speed;
		detection_range = in.detection_range;
		Pheromone_max = in.Pheromone_max;
		qantity_max = in.qantity_max;
		max_angle_deviation = in.max_angle_deviation;
	};
};

struct Pheromone
{
	Pheromone(float disipation_speed) : disipation_speed(disipation_speed) {};

	void operator=(float i)
	{
		value = i;
		clock.restart();
	};

	operator float()
	{
		value -= clock.restart().asSeconds() * disipation_speed;

		if (value < 0)
			value = 0;

		return value;
	};

	void set_disipation_speed(float disipation_speed) { this->disipation_speed = disipation_speed; };

private:
	float disipation_speed;

	sf::Clock clock;
	float value;
};

struct CasePheromones
{
	enum Type
	{
		none,
		home,
		food,
		water,
		enemy,
	};

	Pheromone Home = 0;
	Pheromone Food = 0;
	Pheromone Water = 0;
	Pheromone Enemy = 0;
	Pheromone None = 0;

	bool organised_search;

	Pheromone& operator[](Type T)
	{
		switch (T)
		{
		case CasePheromones::home:
			return Home;
			break;
		case CasePheromones::food:
			return Food;
			break;
		case CasePheromones::water:
			return Water;
			break;
		case CasePheromones::enemy:
			return Enemy;
			break;
		default:
			return None;
			break;
		}
	};

	void set_disipation_speed(float disipation_speed) { Home.set_disipation_speed(disipation_speed); Food.set_disipation_speed(disipation_speed); Water.set_disipation_speed(disipation_speed); Enemy.set_disipation_speed(disipation_speed); };
};

class Fourmie
{
	sf::Clock speed_clock;

	sf::RenderTarget& render;

	sf::Texture& texture;

	sf::RectangleShape Sprite;

	Fourmiliere& fourmiliere;

	ClassTerrain& Terrain;

	CasePheromones** Pheromone_Table;

	float x = 0, y = 0;

	int case_x = 0, case_y = 0;

	float dx = 0, dy = 0;

	float rotation = 90;

	int qantity = 0;

	//parametre de l'IA

	Parametre_IA parametre_IA;

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

	float Pheromone_current = 0;

	Fourmie(int x, int y, Parametre_IA parametre_IA, ClassTerrain& Terrain, sf::RenderTarget& render, sf::Texture& texture, CasePheromones**Pheromone_Table, Fourmiliere& fourmiliere);

	void deplacement();
	void analyse();
	void change_dest();
	void palce_pheromone();
	void action();

	void affiche();

private:
	void anti_hors_map(int& cx, int& cy);

	bool anti_wrong_case(int& cx, int& cy);

	void organised_search(int& cx, int& cy);

	void deviation(int& cx, int& cy, float& ndx, float& ndy);
};

class Fourmiliere
{
	sf::RenderTarget& render;

	sf::Texture& texture;

	ClassTerrain& Terrain;

	CasePheromones** Pheromone_Table;

	float x = 0, y = 0;

	//parametre des IA
	Parametre_IA parametre_IA;

	std::list<Fourmie*> Fourmies;

	bool Food_found = false;
	bool Water_found = false;

	float Pheromone_disipation_speed;

public:

	std::default_random_engine generator;
	std::normal_distribution<float> distribution;

	Fourmiliere(int x, int y, Parametre_IA parametre_IA, float Pheromone_disipation_speed, ClassTerrain& Terrain, sf::RenderTarget& render, sf::Texture& texture);

	void add_fourmie();

	void action();

	void affiche();

	void select_dest(Fourmie::Type_Destination& destination, Fourmie::Type_Destination& contenue);
};

void Simulation(sf::RenderWindow& window);

#endif