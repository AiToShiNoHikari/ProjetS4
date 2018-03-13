#ifndef _Multi_IA

#define _Multi_IA 1

#include "Terrain.h"

//#include <Windows.h>

#include <cmath>
#include <random>
#include <chrono>

#include <windows.h> 

#include <SFML/Graphics.hpp>

#include <vector>
#include <list>
#include <array>

#include <thread>
#include <mutex>

#ifdef _DEBUG
#include <iostream>
#endif
#include <fstream>
#include <sstream>
#include <iomanip>

#include <string>

#define _size 32

#define π 3.14159265

class ClassTerrain;

class CaseTerrain;

class Fourmiliere;
class Fourmiliere_1;
class Fourmiliere_2;

struct dest_point
{
	float angle;

	int force;
};

struct Parametre_IA
{
	float speed;
	float sand_speed;
	float water_speed;

	float detection_range;

	float Pheromone_max;

	int qantity_max;

	float max_angle_deviation;

	float life_time;

	float precision_angle;
	
	float sigma_deviation;

	int type_IA = 0;

	void operator=(Parametre_IA& in)
	{
		speed = in.speed;
		sand_speed = in.sand_speed;
		water_speed = in.water_speed;
		detection_range = in.detection_range;
		Pheromone_max = in.Pheromone_max;
		qantity_max = in.qantity_max;
		max_angle_deviation = in.max_angle_deviation;
		life_time = in.life_time;
		precision_angle = in.precision_angle;
		sigma_deviation = in.sigma_deviation;
		type_IA = in.type_IA;
	};
};

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

	Pheromone(float disipation_speed = 0) : disipation_speed(disipation_speed) {};

	void operator=(float i)
	{
		value = i;
		clock.restart();
	};

	virtual operator float()
	{
		value -= clock.restart().asSeconds() * disipation_speed;

		if (value < 0)
			value = 0;

		return value;
	};

	void set_disipation_speed(float disipation_speed) { this->disipation_speed = disipation_speed; };

protected:
	float disipation_speed = 0;

	sf::Clock clock;
	float value = 0;
};

struct PheromonePoint : public Pheromone
{
	float x;
	float y;
	Fourmiliere_2& fourmiliere;

	Pheromone::Type Type;

	PheromonePoint(float x, float y, float disipation_speed, Pheromone::Type Type, float value, Fourmiliere_2& fourmiliere) : x(x), y(y), Type(Type), Pheromone(disipation_speed), fourmiliere(fourmiliere) {};

	virtual operator float();
};

template <class Tclass>
struct CasePheromones
{
	float disipation_speed = 0;

	Tclass Home;
	Tclass Food;
	Tclass Water;
	Tclass Enemy;
	Tclass None;

	Tclass& operator[](Pheromone::Type T)
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
		default:
			return None;
			break;
		}
	};

	//void set_disipation_speed(float disipation_speed) { Home.set_disipation_speed(disipation_speed); Food.set_disipation_speed(disipation_speed); Water.set_disipation_speed(disipation_speed); Enemy.set_disipation_speed(disipation_speed); };
};

class Fourmie
{
private:
	Fourmie(const Fourmie &) = delete;
	Fourmie & operator = (const Fourmie &) = delete;

protected:
	std::mutex mutex;

	sf::Clock speed_clock;

	sf::Clock life_clock;

	sf::RenderTarget& render;

	sf::Texture& texture;

	sf::RectangleShape Sprite;

	Fourmiliere& fourmiliere;

	ClassTerrain& Terrain;

	int** organised_search;

	float x = 0, y = 0;

	int case_x = 0, case_y = 0;

	float dx = 0, dy = 0;

	float rotation = 90;

	int qantity = 0;

	int organized_turn = 0;

	bool Orga_Search = false;

	//parametre de l'IA
	Parametre_IA& parametre_IA;

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

	Type_Destination ex_destination = none;
	Type_Destination destination = none;
	Type_Destination contenue = none;

	float Pheromone_current = 0;

	bool in_life = true;

	void action();

	void affiche();

	Fourmie(int x, int y, Parametre_IA& parametre_IA, ClassTerrain& Terrain, sf::RenderTarget& render, sf::Texture& texture, int** organised_search, Fourmiliere& fourmiliere);

	virtual ~Fourmie() {};

protected:

	virtual void analyse() = 0;

	void deplacement();
	void change_dest();
	virtual void palce_pheromone() = 0;

	void anti_hors_map(int& cx, int& cy);

	bool anti_wrong_case(int& cx, int& cy);

	void Organised_Search(int& cx, int& cy);

	void deviation(float& cx, float& cy, float& ndx, float& ndy);

	void select_dest(float& fcx, float& fcy);

	void select_dest_point(std::list<dest_point>& dest_point_list);

	virtual void read_Pheromone(int min_x, int max_x, int min_y, int max_y, Pheromone::Type searched, float& cx, float& cy) = 0;

	virtual void read_Pheromone(int min_x, int max_x, int min_y, int max_y, Pheromone::Type searched, std::list<dest_point>& dest_point_list) = 0;

	void select_dest(float& fcx, float& fcy, std::list<dest_point>& dest_point_list);
};


class Fourmie_F1 : virtual public Fourmie
{
private:
	Fourmie_F1(const Fourmie_F1 &) = delete;
	Fourmie_F1 & operator = (const Fourmie_F1 &) = delete;

public:
	Fourmie_F1(int x, int y, Parametre_IA& parametre_IA, ClassTerrain& Terrain, sf::RenderTarget& render, sf::Texture& texture, int** organised_search, Fourmiliere_1& fourmiliere);

	virtual ~Fourmie_F1() {};
protected:
	CasePheromones<Pheromone>** Pheromone_Table;

	void palce_pheromone();

	void read_Pheromone(int min_x, int max_x, int min_y, int max_y, Pheromone::Type searched, float& cx, float& cy);

	void read_Pheromone(int min_x, int max_x, int min_y, int max_y, Pheromone::Type searched, std::list<dest_point>& dest_point_list);
};

class Fourmie_F2 : virtual public Fourmie
{
private:
	Fourmie_F2(const Fourmie_F2 &) = delete;
	Fourmie_F2 & operator = (const Fourmie_F2 &) = delete;

	Fourmiliere_2& fourmiliere2;

public:
	Fourmie_F2(int x, int y, Parametre_IA& parametre_IA, ClassTerrain& Terrain, sf::RenderTarget& render, sf::Texture& texture, int** organised_search, Fourmiliere_2& fourmiliere);

	virtual ~Fourmie_F2() {};
protected:
	CasePheromones<std::list<PheromonePoint*>>** Pheromone_list;

	void palce_pheromone();

	void read_Pheromone(int min_x, int max_x, int min_y, int max_y, Pheromone::Type searched, float& cx, float& cy);

	void read_Pheromone(int min_x, int max_x, int min_y, int max_y, Pheromone::Type searched, std::list<dest_point>& dest_point_list);
};


class Fourmie_1 : virtual public Fourmie
{
public:
	void analyse();

	Fourmie_1() {};

	virtual ~Fourmie_1() {};
};

class Fourmie_2 : virtual public Fourmie
{
public:
	void analyse();

	Fourmie_2() {};

	virtual ~Fourmie_2() {};
};


class Fourmie_1_F1 : public Fourmie_1, public Fourmie_F1
{
private:
	Fourmie_1_F1(const Fourmie_1_F1 &) = delete;
	Fourmie_1_F1 & operator = (const Fourmie_1_F1 &) = delete;

public:
	Fourmie_1_F1(int x, int y, Parametre_IA& parametre_IA, ClassTerrain& Terrain, sf::RenderTarget& render, sf::Texture& texture, int** organised_search, Fourmiliere_1& fourmiliere) : Fourmie(x, y, parametre_IA, Terrain, render, texture, organised_search, (Fourmiliere&)fourmiliere), Fourmie_F1(x, y, parametre_IA, Terrain, render, texture, organised_search, fourmiliere)
	{
		//std::thread life([this]() {this->action(); });
		//life.detach();
	};
};

class Fourmie_2_F1 : public Fourmie_2, public Fourmie_F1
{
private:
	Fourmie_2_F1(const Fourmie_2_F1 &) = delete;
	Fourmie_2_F1 & operator = (const Fourmie_2_F1 &) = delete;

public:
	Fourmie_2_F1(int x, int y, Parametre_IA& parametre_IA, ClassTerrain& Terrain, sf::RenderTarget& render, sf::Texture& texture, int** organised_search, Fourmiliere_1& fourmiliere) : Fourmie(x, y, parametre_IA, Terrain, render, texture, organised_search, (Fourmiliere&)fourmiliere), Fourmie_F1(x, y, parametre_IA, Terrain, render, texture, organised_search, fourmiliere)
	{
		//std::thread life([this]() {this->action(); });
		//life.detach();
	};
};

class Fourmie_1_F2 : public Fourmie_1, public Fourmie_F2
{
private:
	Fourmie_1_F2(const Fourmie_1_F2 &) = delete;
	Fourmie_1_F2 & operator = (const Fourmie_1_F2 &) = delete;

public:
	Fourmie_1_F2(int x, int y, Parametre_IA& parametre_IA, ClassTerrain& Terrain, sf::RenderTarget& render, sf::Texture& texture, int** organised_search, Fourmiliere_2& fourmiliere) : Fourmie(x, y, parametre_IA, Terrain, render, texture, organised_search, (Fourmiliere&)fourmiliere), Fourmie_F2(x, y, parametre_IA, Terrain, render, texture, organised_search, fourmiliere)
	{
		//std::thread life([this]() {this->action(); });
		//life.detach();
	};
};

class Fourmie_2_F2 : public Fourmie_2, public Fourmie_F2
{
private:
	Fourmie_2_F2(const Fourmie_2_F2 &) = delete;
	Fourmie_2_F2 & operator = (const Fourmie_2_F2 &) = delete;

public:
	Fourmie_2_F2(int x, int y, Parametre_IA& parametre_IA, ClassTerrain& Terrain, sf::RenderTarget& render, sf::Texture& texture, int** organised_search, Fourmiliere_2& fourmiliere) : Fourmie(x, y, parametre_IA, Terrain, render, texture, organised_search, (Fourmiliere&)fourmiliere), Fourmie_F2(x, y, parametre_IA, Terrain, render, texture, organised_search, fourmiliere)
	{
		//std::thread life([this]() {this->action(); });
		//life.detach();
	};
};


class Fourmiliere
{
protected:
	sf::RenderTarget& render;

	sf::Texture& texture;

	ClassTerrain& Terrain;

	int** organised_search;

	float x = 0, y = 0;

	//parametre de la fourmiliere
	int birth_Food_cost = 1000;
	int birth_Water_cost = 1000;

	//parametre des IA
	Parametre_IA parametre_IA;

	std::list<Fourmie*> Fourmies;

	bool Food_found = false;
	bool Water_found = false;

	int Food_value = 0;
	int Water_value = 0;

	int search_fourmi = 0;
	int food_fourmi = 0;
	int water_fourmi = 0;
	int enemy_fourmi = 0;

#ifdef _DEBUG
	bool is_launch = true;
#endif

public:
	std::default_random_engine generator;
	std::normal_distribution<float> distribution;

	float Pheromone_disipation_speed;

	Fourmiliere(int x, int y, Parametre_IA parametre_IA, float Pheromone_disipation_speed, ClassTerrain& Terrain, sf::RenderTarget& render, sf::Texture& texture);

	virtual void add_fourmie(int num_type = -1) = 0;

	virtual void action();

	void affiche();

	void select_dest(Fourmie::Type_Destination& destination, Fourmie::Type_Destination& contenue, int& value, Fourmie::Type_Destination ex_destination);

	~Fourmiliere();

#ifdef _DEBUG
	void affiche_info();
#endif
};


class Fourmiliere_1 : public Fourmiliere
{
public:
	CasePheromones<Pheromone>** Pheromone_Table;

	Fourmiliere_1 (int x, int y, Parametre_IA parametre_IA, float Pheromone_disipation_speed, ClassTerrain& Terrain, sf::RenderTarget& render, sf::Texture& texture);

	~Fourmiliere_1();

	void add_fourmie(int num_type = -1);
};

class Fourmiliere_2 : public Fourmiliere
{
public:
	CasePheromones<std::list<PheromonePoint*>>** Pheromone_list;

	std::list<PheromonePoint*> Pheromone_void_list;

	Fourmiliere_2(int x, int y, Parametre_IA parametre_IA, float Pheromone_disipation_speed, ClassTerrain& Terrain, sf::RenderTarget& render, sf::Texture& texture);

	~Fourmiliere_2();

	void add_fourmie(int num_type = -1);

	void action();
};


void Simulation(sf::RenderWindow& window);

double probabilite(double x , double p, double f, double s);

#endif
