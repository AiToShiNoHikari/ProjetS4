#ifndef _Ressource

#define _Ressource true

#include <SFML/Graphics.hpp>

struct Ressource
{
	static sf::Image TileMapBase;
	static sf::Image TileMapTerre;
	static sf::Image TileMapEau;
	static sf::Image TileMapRoche;
	static sf::Image TileMapSable;
	static sf::Image TileMapNourriture;

	static sf::Texture Save;

	static sf::Texture Fourmie;
};

#endif
