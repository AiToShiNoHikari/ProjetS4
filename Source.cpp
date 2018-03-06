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

sf::Font Ressource::Arial;

void Menu(sf::RenderWindow& window)
{
	sf::Font font;
	if (!font.loadFromFile("Ressource/Police/arial.ttf"))
	{
		std::cout << "Erreur chargement Arial.ttf" << std::endl;
	}

	sf::Text titre("Fourmis Simulator", font);
	titre.setPosition((sf::VideoMode::getDesktopMode().width / 2 - 340), 50);
	titre.setCharacterSize(80);
	titre.setStyle(sf::Text::Bold);
	titre.setFillColor(sf::Color::White);


	Interface::Bouton BSimulation((sf::VideoMode::getDesktopMode().width / 2) - (sf::VideoMode::getDesktopMode().width / 4), sf::VideoMode::getDesktopMode().height / 2 - 50, 200, 50, window, "Simulation");
	BSimulation.set_bg_type(Interface::Bouton::BG_type::Rect);
	BSimulation.set_background_outline_thickness(2, 2, 2);
	BSimulation.set_text_color(sf::Color::Black, sf::Color::Black, sf::Color::Black);
	BSimulation.set_text_font(&Ressource::Arial);
	BSimulation.set_background_outline_color(sf::Color::White, sf::Color::Blue, sf::Color::Red);
	BSimulation.set_background_color(sf::Color::Transparent, sf::Color::Transparent, sf::Color(255, 255, 255, 128));
	BSimulation.set_text_pos_correction_y(-8, -8, -8);

	Interface::Bouton BEdition((sf::VideoMode::getDesktopMode().width / 2) + (sf::VideoMode::getDesktopMode().width / 4) - 200, sf::VideoMode::getDesktopMode().height / 2 - 50, 200, 50, window, "Edition");
	BEdition.set_bg_type(Interface::Bouton::BG_type::Rect);
	BEdition.set_background_outline_thickness(2, 2, 2);
	BEdition.set_text_color(sf::Color::Black, sf::Color::Black, sf::Color::Black);
	BEdition.set_text_font(&Ressource::Arial);
	BEdition.set_background_outline_color(sf::Color::White, sf::Color::Blue, sf::Color::Red);
	BEdition.set_background_color(sf::Color::Transparent, sf::Color::Transparent, sf::Color(255, 255, 255, 128));
	BEdition.set_text_pos_correction_y(-8, -8, -8);



	sf::Texture texture;
	if (!texture.loadFromFile("Ressource/Image/Fond.jpg"))
	{
		std::cout << "Erreur Fond" << std::endl;
	}
	
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(0, 0);

	int Fenetre = 0;

	while (window.isOpen())
	{
		window.clear();

		sf::Event event;


		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				BSimulation.get_state(event);
				BEdition.get_state(event);
				break;
			case sf::Event::MouseButtonPressed:
			{
				if (BSimulation.get_state(event) == Interface::Bouton::cliking)
				{
					Fenetre = 1;
				}
				if (BEdition.get_state(event) == Interface::Bouton::cliking)
				{
					Fenetre = 2;
				}
			}
			break;
			case sf::Event::MouseButtonReleased:
				BSimulation.update_state(event);
				BEdition.update_state(event);

				break;
			default:
				break;
			}
		}


		switch (Fenetre)
		{
		case 1:
			Simulation(window);
			break;
		case 2:
			Edition(window);
			break;
		}

		window.draw(sprite);
		window.draw(titre);
		BSimulation.affiche();
		BEdition.affiche();
		window.display();
	}
}

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


	if (Ressource::Arial.loadFromFile("./Ressource/Police/Arial.ttf"))
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

	Menu(window);
}

