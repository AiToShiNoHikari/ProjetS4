
#ifndef _IA

#define _Terrain

//#include "IA.h"

#endif

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>


struct CaseTerrain 
{
	enum TypeTerrain { Base, Terre, Eau, Roche, Sable, Nourriture };

	TypeTerrain Type = Terre;
};

void Menu(sf::RenderWindow& window);

void MAJTexture(sf::View& vue, sf::RenderTexture& RTextureSol, sf::RectangleShape& TextureCase, sf::Texture& Tsol, CaseTerrain** Terrain);

void Camera(sf::RenderWindow& window);