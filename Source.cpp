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


void ChoixMap(sf::RenderWindow& window)
{
	sf::Sprite sprite;
	sprite.setTexture(Ressource::FondMenu);
	sprite.setPosition(0, 0);
	
	std::list<Interface::Bouton*> BoutonNomMap;
	
	int NX = 0;
	int NY = 0;

	for (auto iterator = Ressource::ListTerrain.begin(); iterator != Ressource::ListTerrain.end(); iterator++)
	{
#ifdef _DEBUG
		std::cout << NX << " - " << NY << std::endl;
#endif

		Interface::Bouton* b = new Interface::Bouton(0,0, 200, 50, window, *iterator);

		b->set_bg_type(Interface::Bouton::BG_type::Rect);
		b->set_background_outline_thickness(2, 2, 2);
		b->set_text_color(sf::Color::Black, sf::Color::Black, sf::Color::Black);
		b->set_text_font(&Ressource::Arial);
		b->set_background_outline_color(sf::Color::White, sf::Color::Blue, sf::Color::Red);
		b->set_background_color(sf::Color::Transparent, sf::Color::Transparent, sf::Color(255, 255, 255, 128));
		b->set_text_pos_correction_y(-8, -8, -8);

		b->set_position(250 * NX + 50, 100 * NY + 50);

		sf::Vector2f PosStart(b->get_rect().left, b->get_rect().top);
		sf::Vector2f PosEnd(b->get_rect().left + b->get_rect().width, b->get_rect().top + b->get_rect().height);
		sf::FloatRect WindowsRect(0, 0, window.getSize().x, window.getSize().y);
		
		if (!WindowsRect.contains(PosStart) || !WindowsRect.contains(PosEnd))
		{
			NX = 0;
			NY++;

			b->set_position(250 * NX + 50, 100 * NY + 50);
		}

		b->set_position(250 * NX + 50, 100 * NY + 50);

		BoutonNomMap.push_back(b);
		NX++;
	}

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;			
			case sf::Event::Resized:
				{
					window.setSize(sf::Vector2u(event.size.width < 800 ? 800 : event.size.width, event.size.height < 600 ? 600 : event.size.height));

					// on met à jour la vue, avec la nouvelle taille de la fenêtre
					{
						sf::FloatRect visibleArea;
						visibleArea = sf::FloatRect(0, 0, window.getSize().x, window.getSize().y);
						window.setView(sf::View(visibleArea));
					}

#ifdef _DEBUG
					std::cout << window.getSize().x << " - " << window.getSize().y << std::endl;
#endif

					NY = 0;
					NX = 0;

					for (auto iterator = BoutonNomMap.begin(); iterator != BoutonNomMap.end(); iterator++)
					{
						(*iterator)->set_position(250 * NX + 50, 100 * NY + 50);

						sf::Vector2f PosStart((*iterator)->get_rect().left, (*iterator)->get_rect().top);
						sf::Vector2f PosEnd((*iterator)->get_rect().left + (*iterator)->get_rect().width, (*iterator)->get_rect().top + (*iterator)->get_rect().height);
						sf::FloatRect WindowsRect(0, 0, window.getSize().x, window.getSize().y);

#ifdef _DEBUG
						std::cout << WindowsRect.contains(PosStart) << " - " << WindowsRect.contains(PosEnd) << " - " << (*iterator)->get_rect().left << " - " << (*iterator)->get_rect().top << " - " << NX << " - " << NY << std::endl;
#endif

						if (!WindowsRect.contains(PosStart) || !WindowsRect.contains(PosEnd))
						{
							NX = 0;
							NY++;

							(*iterator)->set_position(250 * NX + 50, 100 * NY + 50);
						}

						NX++;

#ifdef _DEBUG
						std::cout << (*iterator)->get_rect().left << " - " << (*iterator)->get_rect().top << " - " << NX << " - " << NY << std::endl;
#endif
					}

#ifdef _DEBUG
					std::cout << "----------------------------------" << std::endl;
#endif
				}
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
						NY = 0;
						NX = 0;

						for (auto iterator = BoutonNomMap.begin(); iterator != BoutonNomMap.end(); iterator++)
						{
							(*iterator)->set_position(250 * NX + 50, 100 * NY + 50);

							sf::Vector2f PosStart((*iterator)->get_rect().left, (*iterator)->get_rect().top);
							sf::Vector2f PosEnd((*iterator)->get_rect().left + (*iterator)->get_rect().width, (*iterator)->get_rect().top + (*iterator)->get_rect().height);
							sf::FloatRect WindowsRect(0, 0, window.getSize().x, window.getSize().y);

#ifdef _DEBUG
							std::cout << WindowsRect.contains(PosStart) << " - " << WindowsRect.contains(PosEnd) << " - " << (*iterator)->get_rect().left << " - " << (*iterator)->get_rect().top << " - " << NX << " - " << NY << std::endl;
#endif

							if (!WindowsRect.contains(PosStart) || !WindowsRect.contains(PosEnd))
							{
								NX = 0;
								NY++;

								(*iterator)->set_position(250 * NX + 50, 100 * NY + 50);
							}

							NX++;

#ifdef _DEBUG
							std::cout << (*iterator)->get_rect().left << " - " << (*iterator)->get_rect().top << " - " << NX << " - " << NY << std::endl;
#endif
						}
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

		window.clear();

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
	
	Interface::Bouton CM((window.getSize().x / 2) - (window.getSize().x / 4), window.getSize().y / 2 - 50, 200, 50, window, "Charger map");
	CM.set_bg_type(Interface::Bouton::BG_type::Rect);
	CM.set_background_outline_thickness(2, 2, 2);
	CM.set_text_color(sf::Color::Black, sf::Color::Black, sf::Color::Black);
	CM.set_text_font(&Ressource::Arial);
	CM.set_background_outline_color(sf::Color::White, sf::Color::Blue, sf::Color::Red);
	CM.set_background_color(sf::Color::Transparent, sf::Color::Transparent, sf::Color(255, 255, 255, 128));
	CM.set_text_pos_correction_y(-8, -8, -8);

	Interface::Bouton NM((window.getSize().x / 2) + (window.getSize().x / 4) - 200, window.getSize().y / 2 - 50, 200, 50, window, "Nouvelle map");
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
			case sf::Event::Resized:
				{
					window.setSize(sf::Vector2u(event.size.width < 800 ? 800 : event.size.width, event.size.height < 600 ? 600 : event.size.height));

					// on met à jour la vue, avec la nouvelle taille de la fenêtre
					{
						sf::FloatRect visibleArea;
						visibleArea = sf::FloatRect(0, 0, event.size.width, event.size.height);
						window.setView(sf::View(visibleArea));
					}
					CM.set_position((window.getSize().x / 2) - (window.getSize().x / 4), window.getSize().y / 2 - 50);
					NM.set_position((window.getSize().x / 2) + (window.getSize().x / 4) - 200, window.getSize().y / 2 - 50);
				}
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
					CM.set_position((window.getSize().x / 2) - (window.getSize().x / 4), window.getSize().y / 2 - 50);
					NM.set_position((window.getSize().x / 2) + (window.getSize().x / 4) - 200, window.getSize().y / 2 - 50);
				}
				if (NM.get_state(event) == Interface::Bouton::cliking)
				{
					Edition(window, "");
					CM.set_position((window.getSize().x / 2) - (window.getSize().x / 4), window.getSize().y / 2 - 50);
					NM.set_position((window.getSize().x / 2) + (window.getSize().x / 4) - 200, window.getSize().y / 2 - 50);
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
	titre.setPosition((window.getSize().x / 2 - 340), 50);
	titre.setCharacterSize(80);
	titre.setStyle(sf::Text::Bold);
	titre.setFillColor(sf::Color::White);


	Interface::Bouton BSimulation((window.getSize().x / 2) - (window.getSize().x / 4), window.getSize().y / 2 - 50, 200, 50, window, "Simulation");
	BSimulation.set_bg_type(Interface::Bouton::BG_type::Rect);
	BSimulation.set_background_outline_thickness(2, 2, 2);
	BSimulation.set_text_color(sf::Color::Black, sf::Color::Black, sf::Color::Black);
	BSimulation.set_text_font(&Ressource::Arial);
	BSimulation.set_background_outline_color(sf::Color::White, sf::Color::Blue, sf::Color::Red);
	BSimulation.set_background_color(sf::Color::Transparent, sf::Color::Transparent, sf::Color(255, 255, 255, 128));
	BSimulation.set_text_pos_correction_y(-8, -8, -8);

	Interface::Bouton BEdition((window.getSize().x / 2) + (window.getSize().x / 4) - 200, window.getSize().y / 2 - 50, 200, 50, window, "Edition");
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
			case sf::Event::Resized:
			{
				window.setSize(sf::Vector2u(event.size.width < 800 ? 800 : event.size.width, event.size.height < 600 ? 600 : event.size.height));

				// on met à jour la vue, avec la nouvelle taille de la fenêtre
				{
					sf::FloatRect visibleArea;
					visibleArea = sf::FloatRect(0, 0, event.size.width, event.size.height);
					window.setView(sf::View(visibleArea));
				}
				BSimulation.set_position((window.getSize().x / 2) - (window.getSize().x / 4), window.getSize().y / 2 - 50);
				BEdition.set_position((window.getSize().x / 2) + (window.getSize().x / 4) - 200, window.getSize().y / 2 - 50); 
				titre.setPosition((window.getSize().x / 2 - 340), 50);
			}
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
			BSimulation.set_position((window.getSize().x / 2) - (window.getSize().x / 4), window.getSize().y / 2 - 50);
			BEdition.set_position((window.getSize().x / 2) + (window.getSize().x / 4) - 200, window.getSize().y / 2 - 50);
			titre.setPosition((window.getSize().x / 2 - 340), 50);
			break;
		case 2:
			ChoixOption(window);
			Fenetre = 0;
			BSimulation.set_position((window.getSize().x / 2) - (window.getSize().x / 4), window.getSize().y / 2 - 50);
			BEdition.set_position((window.getSize().x / 2) + (window.getSize().x / 4) - 200, window.getSize().y / 2 - 50);
			titre.setPosition((window.getSize().x / 2 - 340), 50);
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

	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height-70), "ProjetSemestre4");
	window.setPosition(sf::Vector2i(-10, 0));
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	Menu(window);
}

