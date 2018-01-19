
#ifndef _Terrain

#define _Terrain 1

#include "IA.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#ifdef _DEBUG
#include <iostream>
#endif


struct CaseTerrain 
{
	enum TypeTerrain { Base, Terre, Eau, Roche, Sable, Nourriture };

	TypeTerrain Type = Terre;
};

void Menu(sf::RenderWindow& window);

void MAJTexture(sf::View& vue, sf::RenderTexture& RTextureSol, sf::RectangleShape& TextureCase, sf::Texture& Tsol, CaseTerrain** Terrain);

void Camera(sf::RenderWindow& window);

#endif