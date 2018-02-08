#include "IA.h"
#include "Terrain.h"

sf::Image Ressource::TileMapBase;
sf::Image Ressource::TileMapTerre;
sf::Image Ressource::TileMapEau;
sf::Image Ressource::TileMapRoche;
sf::Image Ressource::TileMapSable;
sf::Image Ressource::TileMapNourriture;

sf::Texture Ressource::Save;

sf::Texture Ressource::Fourmie;

void main()
{
#ifdef _DEBUG
	std::cout << ">>>>> Debug: <<<<<" << std::endl;
#else
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

	if (Ressource::TileMapBase.loadFromFile("./Ressource/Image/TileMapBase.jpg"))
	{
		//Non Error
	}
	else
	{
		//Error
	}

	if (Ressource::TileMapTerre.loadFromFile("./Ressource/Image/TileMapTerre.jpg"))
	{
		//Non Error
	}
	else
	{
		//Error
	}

	if (Ressource::TileMapEau.loadFromFile("./Ressource/Image/TileMapEau.jpg"))
	{
		//Non Error
	}
	else
	{
		//Error
	}

	if (Ressource::TileMapRoche.loadFromFile("./Ressource/Image/TileMapRoche.jpg"))
	{
		//Non Error
	}
	else
	{
		//Error
	}

	if (Ressource::TileMapSable.loadFromFile("./Ressource/Image/TileMapSable.jpg"))
	{
		//Non Error
	}
	else
	{
		//Error
	}

	if (Ressource::TileMapNourriture.loadFromFile("./Ressource/Image/TileMapNourriture.jpg"))
	{
		//Non Error
	}
	else
	{
		//Error
	}

	if (Ressource::Fourmie.loadFromFile("./Ressource/Image/Fourmi.png"))
	{
		//Non Error
	}
	else
	{
		//Error
	}


	if (Ressource::Save.loadFromFile("./Ressource/Image/Save.png"))
	{
		//Non Error
	}
	else
	{
		//Error
	}

	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "ProjetSemestre4");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	//Menu(window);
	Edition(window);

}