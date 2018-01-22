
#ifndef _Terrain

#define _Terrain 1

#include "IA.h"
#include "Ressource.h"

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

/***** cette fonction te donnera l'image de la texture de la case *****/
sf::Image Texture(int x, int y, CaseTerrain** Terrain);

class ClassTerrain {
	sf::RenderTarget& Render;

	sf::Image ImgTerrain;
	sf::Texture TextTerrain;
	sf::Sprite SprtTerrain;

public:
	CaseTerrain** Terrain = NULL;

	ClassTerrain(int x, int y, sf::RenderTarget& Render);

	void MAJTexture(int i_mini = -1, int j_mini = -1, int i_max = -1, int j_max = -1);

	void Redimension(int x, int y);

	void Affiche();

	// Les éléments suivant sont les paramétres du terrain :
	int TX, TY;

private:
	/***** cette fonction te donnera l'image de la texture de la case *****/
	sf::Image Texture(int x, int y);
};

#endif