#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

struct CaseTerrain 
{
	enum TypeTerrain { Base, Terre, Eau, Roche, Sable, Nourriture };

	TypeTerrain Type = Terre;
};
