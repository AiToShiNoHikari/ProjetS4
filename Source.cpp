#include "Multi_IA.h"
#include "Terrain.h"

sf::Image Ressource::TileMapBase;
sf::Image Ressource::TileMapTerre;
sf::Image Ressource::TileMapEau;
sf::Image Ressource::TileMapRoche;
sf::Image Ressource::TileMapSable;
sf::Image Ressource::TileMapNourriture;

sf::Texture Ressource::Save;

sf::Texture Ressource::Fourmie;

sf::Texture Ressource::FondMenu;

std::list<std::string> Ressource::ListTerrain;

sf::Font Ressource::Arial;

/*void test(sf::RenderWindow& window)
{
	Interface::Scroll_Menu test_sc(10, 10, 200, 50, window, true);

	test_sc.set_bg_type(Interface::Bouton::BG_type::Rect);
	test_sc.set_background_outline_thickness(2, 2, 2);
	test_sc.set_text_color(sf::Color::White, sf::Color::Red, sf::Color::White);
	test_sc.set_text_font(&Ressource::Arial);
	test_sc.set_background_outline_color(sf::Color::White, sf::Color::Blue, sf::Color::Red);
	test_sc.set_background_color(sf::Color::Blue, sf::Color::Black, sf::Color(255, 255, 255, 128));
	test_sc.set_text_pos_correction_y(-8, -8, -8);

	for (auto iterator = Ressource::ListTerrain.begin(); iterator != Ressource::ListTerrain.end(); iterator++)
	{
		test_sc.add_choice(*iterator);
	}

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
				test_sc.get_state(event);
				break;
			case sf::Event::MouseButtonPressed:
			{
				test_sc.get_state(event);
			}
			break;
			case sf::Event::MouseButtonReleased:
				test_sc.get_state(event);
				break;
			case sf::Event::MouseWheelMoved:
				test_sc.scroll(event);
				break;
			default:
				break;
			}
		}

		test_sc.affiche();
		window.display();
	}
}*/

void ChoixMap(sf::RenderWindow& window)
{
	sf::Sprite sprite;
	sprite.setTexture(Ressource::FondMenu);
	sprite.setPosition(0, 0);
	
	std::list<Interface::Bouton*> BoutonNomMap;
	

	int Val = 0;
	for (auto iterator = Ressource::ListTerrain.begin(); iterator != Ressource::ListTerrain.end(); iterator++)
	{
#ifdef _DEBUG
		std::cout << *iterator << std::endl;
#endif

		Interface::Bouton* b = new Interface::Bouton(((sf::VideoMode::getDesktopMode().width / 2) - (sf::VideoMode::getDesktopMode().width / 4))*Val + 100, sf::VideoMode::getDesktopMode().height / 2 - 50, 200, 50, window, *iterator);

		b->set_bg_type(Interface::Bouton::BG_type::Rect);
		b->set_background_outline_thickness(2, 2, 2);
		b->set_text_color(sf::Color::Black, sf::Color::Black, sf::Color::Black);
		b->set_text_font(&Ressource::Arial);
		b->set_background_outline_color(sf::Color::White, sf::Color::Blue, sf::Color::Red);
		b->set_background_color(sf::Color::Transparent, sf::Color::Transparent, sf::Color(255, 255, 255, 128));
		b->set_text_pos_correction_y(-8, -8, -8);

		BoutonNomMap.push_back(b);
		Val++;
	}

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

				for (auto iterator = BoutonNomMap.begin(); iterator != BoutonNomMap.end(); iterator++)
				{
					(*iterator)->update_state(event);
				}
				break;
			case sf::Event::MouseButtonPressed:
			{
				auto iterator = Ressource::ListTerrain.begin();

				for (auto iterator1 = BoutonNomMap.begin(); iterator1 != BoutonNomMap.end(); iterator1++)
				{
					if ((*iterator1)->get_state(event) == Interface::Bouton::state::cliking)
					{

						iterator;

						Edition(window, *iterator);
					}

					iterator++;
				}
			}
			break;
			case sf::Event::MouseButtonReleased:
				for (auto iterator = BoutonNomMap.begin(); iterator != BoutonNomMap.end(); iterator++)
				{
					(*iterator)->update_state(event);
				}
				break;
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Escape)
				{
					return;
				}
				break;
			default:
				break;
			}
		}

		window.draw(sprite);
		for (auto iterator = BoutonNomMap.begin(); iterator != BoutonNomMap.end(); iterator++)
		{
			(*iterator)->affiche();
		}

		window.display();
	}

	for (auto iterator = BoutonNomMap.begin(); iterator != BoutonNomMap.end(); iterator++)
	{
		delete (*iterator);
	}
}

void ChoixOption(sf::RenderWindow& window)
{
	sf::Sprite sprite;
	sprite.setTexture(Ressource::FondMenu);
	sprite.setPosition(0, 0);
	
	Interface::Bouton CM((sf::VideoMode::getDesktopMode().width / 2) - (sf::VideoMode::getDesktopMode().width / 4), sf::VideoMode::getDesktopMode().height / 2 - 50, 200, 50, window, "Charger map");
	CM.set_bg_type(Interface::Bouton::BG_type::Rect);
	CM.set_background_outline_thickness(2, 2, 2);
	CM.set_text_color(sf::Color::Black, sf::Color::Black, sf::Color::Black);
	CM.set_text_font(&Ressource::Arial);
	CM.set_background_outline_color(sf::Color::White, sf::Color::Blue, sf::Color::Red);
	CM.set_background_color(sf::Color::Transparent, sf::Color::Transparent, sf::Color(255, 255, 255, 128));
	CM.set_text_pos_correction_y(-8, -8, -8);

	Interface::Bouton NM((sf::VideoMode::getDesktopMode().width / 2) + (sf::VideoMode::getDesktopMode().width / 4) - 200, sf::VideoMode::getDesktopMode().height / 2 - 50, 200, 50, window, "Nouvelle map");
	NM.set_bg_type(Interface::Bouton::BG_type::Rect);
	NM.set_background_outline_thickness(2, 2, 2);
	NM.set_text_color(sf::Color::Black, sf::Color::Black, sf::Color::Black);
	NM.set_text_font(&Ressource::Arial);
	NM.set_background_outline_color(sf::Color::White, sf::Color::Blue, sf::Color::Red);
	NM.set_background_color(sf::Color::Transparent, sf::Color::Transparent, sf::Color(255, 255, 255, 128));
	NM.set_text_pos_correction_y(-8, -8, -8);

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
				CM.get_state(event);
				NM.get_state(event);
				break;
			case sf::Event::MouseButtonPressed:
			{
				if (CM.get_state(event) == Interface::Bouton::cliking)
				{
					ChoixMap(window);
				}
				if (NM.get_state(event) == Interface::Bouton::cliking)
				{
					Edition(window, "");
				}
			}
			break;
			case sf::Event::MouseButtonReleased:
				CM.update_state(event);
				NM.update_state(event);
				break;
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Escape)
				{
					return;
				}
				break;
			default:
				break;
			}
		}
		window.draw(sprite);
		NM.affiche();
		CM.affiche();
		window.display();
	}
}

void Menu(sf::RenderWindow& window)
{
	sf::Text titre("Fourmis Simulator", Ressource::Arial);
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
		
	sf::Sprite sprite;
	sprite.setTexture(Ressource::FondMenu);
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
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
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
			Fenetre = 0;
			break;
		case 2:
			ChoixOption(window);
			Fenetre = 0;
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

	if (Ressource::FondMenu.loadFromFile("./Ressource/Image/Fond.jpg"))
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

	std::ifstream SaveListTerrain("./Ressource/Sauvegarde/Terrain/Terrain_List.save.sl");

	if (SaveListTerrain)
	{
		std::string Nom;
		while (getline(SaveListTerrain, Nom))
		{
			Ressource::ListTerrain.push_back(Nom);
		}

		SaveListTerrain.close();
	}

	for (auto iterator = Ressource::ListTerrain.begin(); iterator != Ressource::ListTerrain.end(); iterator++)
	{
#ifdef _DEBUG
		std::cout << *iterator << std::endl;
#endif
	}

	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "ProjetSemestre4");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	//test(window);
	Menu(window);
}

