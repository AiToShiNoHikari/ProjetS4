#include "IA.h"

IA::IA(int x, int y, float speed, float detection_range, int Pheromone_max, ClassTerrain& Terrain,sf::RenderTarget& render, sf::Texture& texture, Pheromone** Pheromone_Table) : Terrain(Terrain), render(render), texture(texture)
{
	this->x = x + 0.5;
	this->y = y + 0.5;

	this->speed = speed;
	this->detection_range = detection_range;
	this->Pheromone_max = Pheromone_max;

	this->Pheromone_Table = Pheromone_Table;

	Sprite.setSize(sf::Vector2f(_size, _size));

	Sprite.setTexture(&texture);
	Sprite.setOrigin(16, 16);

	change_dest();
};

void IA::deplacement()
{
	x += (speed * dx);
	y += (speed * dy);
};

void IA::analyse()
{
	int cx = -1, cy = -1;

	case_x = (int)x, case_y = (int)y;

	int min_x = ((int)(x - detection_range))<0 ? 0 : ((int)(x - detection_range));
	int max_x = ((int)(x + detection_range)) >= Terrain.TX ? Terrain.TX : ((int)(x + detection_range));
	int min_y = ((int)(y - detection_range))<0 ? 0 : ((int)(y - detection_range));
	int max_y = ((int)(y + detection_range)) >= Terrain.TY ? Terrain.TY : ((int)(y + detection_range));
	
	//analise du terrain et change la direction ou la destination en fonction du resulta
	for (int i = min_x; i < max_x; i++)
	{
		for (int j = min_y; j < max_y; j++)
		{
			switch (destination)
			{
			case IA::home:
				if (Terrain.Terrain[i][j].Type == CaseTerrain::TypeTerrain::Base)
				{
					if (case_x == i && case_y == j)
					{
						change_dest();
						cx = -1, cy = -1;
					}
					else
					{
						cx = i;
						cy = j;
					}
				}
				break;
			case IA::food:
				if (Terrain.Terrain[i][j].Type == CaseTerrain::TypeTerrain::Nourriture)
				{
					if (case_x == i && case_y == j)
					{
						change_dest();
						cx = -1, cy = -1;
					}
					else
					{
						cx = i;
						cy = j;
					}
				}
				break;
			case IA::water:
				if (Terrain.Terrain[i][j].Type == CaseTerrain::TypeTerrain::Eau)
				{
					if (case_x == i && case_y == j)
					{
						change_dest();
						contenue = water;
						cx = -1, cy = -1;
					}
					else
					{
						cx = i;
						cy = j;
					}
				}
				break;
			case IA::enemy:
				if (Terrain.Terrain[i][j].Type == CaseTerrain::TypeTerrain::Base)
				{
					if (case_x == i && case_y == j)
					{
						change_dest();
						cx = -1, cy = -1;
					}
					else
					{
						cx = i;
						cy = j;
					}
				}
				break;
			case IA::search:
				if (Terrain.Terrain[i][j].Type == CaseTerrain::TypeTerrain::Nourriture || Terrain.Terrain[i][j].Type == CaseTerrain::TypeTerrain::Eau)
				{
					if (case_x == i && case_y == j)
					{
						change_dest();
						cx = -1, cy = -1;
					}
					else
					{
						if (cx < 0)
						{
							cx = i;
							cy = j;
						}
						else
						{
							if ((abs(x - cx) + abs(y - cy)) / 2.0 > (abs(x - i) + abs(y - j)) / 2.0)
							{
								cx = i;
								cy = j;
							}
						}
					}
				}
				/*if (Terrain[i][j].Type == CaseTerrain::TypeTerrain::Base)
				{
					if (case_x == cx && case_y == cy)
					{
						change_dest();
						cx = -1, cy = -1;
					}
					else
					{
						if (cx < 0)
						{
							cx = i;
							cy = j;
						}
						else
						{
							if ((abs(x - cx) + abs(y - cy)) / 2.0 >(abs(x - i) + abs(y - j)) / 2.0)
							{
								cx = i;
								cy = j;
							}
						}
					}
				}//*/
				break;
			}
		}
	}

	//suit les pheromones si aucune direction n'est prise

	if (cx < 0)
	{
		Pheromone::Type searched;
		switch (destination)
		{
		case IA::home:
			searched = Pheromone::Type::home;
			break;
		case IA::food:
			searched = Pheromone::Type::food;
			break;
		case IA::water:
			searched = Pheromone::Type::water;
			break;
		case IA::enemy:
			searched = Pheromone::Type::enemy;
			break;
		default:
			searched = Pheromone::Type::none;
			break;
		}

		if (searched != Pheromone::Type::none)
		{
			float value = 0;

			for (int i = min_x; i < max_x; i++)
			{
				for (int j = min_y; j < max_y; j++)
				{
					float& valuec = Pheromone_Table[i][j][searched];
					
					if (valuec > 0)
					{
						if (value < valuec)
						{
							cx = i;
							cy = j;
							value = valuec;
						}
						else if (value == valuec)
						{
							if ((abs(x - cx) + abs(y - cy)) / 2.0 > (abs(x - i) + abs(y - j)) / 2.0)
							{
								cx = i;
								cy = j;
								value = valuec;
							}
						}
					}
				}
			}
		}
	}

	//si aucune direction n'a été prise

	if (cx < 0)
	{
		do
		{
			cx = ((int)x + (rand() % 3) - 1);
			cy = ((int)y + (rand() % 3) - 1);
		} while (cx == 0 && cy == 0);
	}

	float delta_dest_x = (cx + 0.5) - x;
	float delta_dest_y = (cy + 0.5) - y;

	float hypo = hypotf(delta_dest_x, delta_dest_y);
	float ndx = delta_dest_x / hypo, ndy = delta_dest_y / hypo;

	rotation = acos(ndx) * 180 / PI;

	if(ndy<0)
		rotation = 360 - rotation;

	rotation += 90;
	
	dx = ndx;
	dy = ndy;

	palce_pheromone();
};

void IA::change_dest()
{
	if (destination != home)
	{
		switch (Terrain.Terrain[case_x][case_y].Type)
		{
		case CaseTerrain::Base:
			contenue = enemy;
			break;
		case CaseTerrain::Eau:
			contenue = water;
			break;
		case CaseTerrain::Nourriture:
			contenue = food;
			break;
		default:
			contenue = none;
			break;
		}

		destination = home;
	}
	else //if (Terrain.Terrain[case_x][case_y].Type == CaseTerrain::Base)
	{
		contenue = home;

		destination = food;
	}

	Pheromone_current = Pheromone_max;
};

void IA::palce_pheromone()
{
	Pheromone::Type place;
	switch (contenue)
	{
	case IA::home:
		place = Pheromone::Type::home;
		break;
	case IA::food:
		place = Pheromone::Type::food;
		break;
	case IA::water:
		place = Pheromone::Type::water;
		break;
	case IA::enemy:
		place = Pheromone::Type::enemy;
		break;
	default:
		place = Pheromone::Type::none;
		break;
	}
	
	if (place != Pheromone::Type::none)
	{
		float& valuec = Pheromone_Table[case_x][case_y][place];

		if (valuec < Pheromone_current)
		{
			valuec = Pheromone_current;
		}
		else if (valuec > Pheromone_current)
		{
			Pheromone_current = (int)valuec;
		}

		Pheromone_current--;

		if (Pheromone_current <= 0)
		{
			change_dest();
		}
	}
};

void IA::action()
{
	if (case_x != (int)x || case_y != (int)y)
		analyse();

	deplacement();
};

void IA::affiche()
{
	Sprite.setRotation(rotation);

	Sprite.setPosition(x*_size, y*_size);

	render.draw(Sprite);

	std::cout << "x: " << x << " y: " << y << " dest: " << destination << " cont: " << contenue << std::endl;

};



void Simulation(sf::RenderWindow& window)
{
	bool HaveChange = true;

	sf::RenderTexture RenderTexture_BG_Simulation;
	RenderTexture_BG_Simulation.create(window.getSize().x, window.getSize().y);

	sf::RenderTexture RenderTexture_AI_Calque_Simulation;
	RenderTexture_AI_Calque_Simulation.create(window.getSize().x, window.getSize().y);

	ClassTerrain ObjTerrain(25, 25, RenderTexture_BG_Simulation);

	//terrain de test
	ObjTerrain.Terrain[10][13].Type = CaseTerrain::Base;
	ObjTerrain.Terrain[15][12].Type = CaseTerrain::Nourriture;

	ObjTerrain.MAJTexture(5, 12, 15, 14);
	ObjTerrain.MAJTexture(10, 11, 20, 13);
	//fin terrain de test

	//table de pheromone de test

	Pheromone** Pheromone_Table;

	Pheromone_Table = new Pheromone*[ObjTerrain.TX];
	for (int i = 0; i < ObjTerrain.TX; i++)
	{
		Pheromone_Table[i] = new Pheromone[ObjTerrain.TY];
	}
	// fin table de pheromone de test

	IA test(10, 13, 0.1, 1.5, 10, ObjTerrain, RenderTexture_AI_Calque_Simulation, Ressource::Fourmie, Pheromone_Table);

	sf::Sprite Sprite_AI_Calque_Simulation;
	sf::Texture Texture_AI_Calque_Simulation;
	sf::Sprite Sprite_BG_Simulation;
	sf::Texture Texture_BG_Simulation;
	sf::View vue;

	vue.setCenter(_size * ObjTerrain.TX / 2, _size * ObjTerrain.TY / 2);

	// on met à jour la vue, avec la taille de la fenêtre
	{
		sf::FloatRect visibleArea;
		visibleArea = sf::FloatRect(0, 0, window.getSize().x, window.getSize().y);
		window.setView(sf::View(visibleArea));

		float zoom = vue.getSize().x / RenderTexture_BG_Simulation.getSize().x;

		RenderTexture_BG_Simulation.create(window.getSize().x, window.getSize().y);
		RenderTexture_AI_Calque_Simulation.create(window.getSize().x, window.getSize().y);

		vue.setSize(window.getSize().x, window.getSize().y);
		vue.zoom(zoom);

		ObjTerrain.Affiche();
		Texture_BG_Simulation = RenderTexture_BG_Simulation.getTexture();
		Texture_AI_Calque_Simulation = RenderTexture_AI_Calque_Simulation.getTexture();

		Sprite_BG_Simulation.setTextureRect(sf::IntRect(0, 0, Texture_BG_Simulation.getSize().x, Texture_BG_Simulation.getSize().y));
		Sprite_AI_Calque_Simulation.setTextureRect(sf::IntRect(0, 0, Texture_AI_Calque_Simulation.getSize().x, Texture_AI_Calque_Simulation.getSize().y));
	}

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Resized)
			{

				window.setSize(sf::Vector2u(event.size.width < 800 ? 800 : event.size.width, event.size.height < 600 ? 600 : event.size.height));

				// on met à jour la vue, avec la nouvelle taille de la fenêtre
				{
					sf::FloatRect visibleArea;
					visibleArea = sf::FloatRect(0, 0, event.size.width, event.size.height);
					window.setView(sf::View(visibleArea));
				}

				float zoom = vue.getSize().x / RenderTexture_BG_Simulation.getSize().x;

				RenderTexture_BG_Simulation.create(window.getSize().x, window.getSize().y);
				RenderTexture_AI_Calque_Simulation.create(window.getSize().x, window.getSize().y);

				vue.setSize(window.getSize().x, window.getSize().y);
				vue.zoom(zoom);
				HaveChange = true;

				Texture_BG_Simulation = RenderTexture_BG_Simulation.getTexture();
				Texture_AI_Calque_Simulation = RenderTexture_AI_Calque_Simulation.getTexture();

				Sprite_BG_Simulation.setTextureRect(sf::IntRect(0, 0, Texture_BG_Simulation.getSize().x, Texture_BG_Simulation.getSize().y));
				Sprite_AI_Calque_Simulation.setTextureRect(sf::IntRect(0, 0, Texture_AI_Calque_Simulation.getSize().x, Texture_AI_Calque_Simulation.getSize().y));
			}
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::MouseWheelMoved)
			{
				sf::Vector2f mousepos = RenderTexture_BG_Simulation.mapPixelToCoords(sf::Mouse::getPosition(window));

				if (event.mouseWheel.delta == 1)
				{
					vue.setCenter(mousepos.x, mousepos.y);
					vue.zoom(0.9f);
				}
				if (event.mouseWheel.delta == -1)
				{
					vue.setCenter(mousepos.x, mousepos.y);
					vue.zoom(1.0 / 0.9f);
				}
				HaveChange = true;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			sf::Vector2f position;

			position.x = vue.getCenter().x;
			position.y = vue.getCenter().y;

			if ((position.y - vue.getSize().y / 2) > 0)
			{
				vue.move(0, -4);
			}
			HaveChange = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			sf::Vector2f position;

			position.x = vue.getCenter().x;
			position.y = vue.getCenter().y;

			if ((position.y + vue.getSize().y / 2) < ObjTerrain.TY * _size)
			{
				vue.move(0, 4);
			}
			HaveChange = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			sf::Vector2f position;

			position.x = vue.getCenter().x;
			position.y = vue.getCenter().y;

			if ((position.x - vue.getSize().x / 2) > 0)
			{
				vue.move(-4, 0);
			}
			HaveChange = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			sf::Vector2f position;

			position.x = vue.getCenter().x;
			position.y = vue.getCenter().y;

			if ((position.x + vue.getSize().x / 2) < ObjTerrain.TX * _size)
			{
				vue.move(4, 0);
			}
			HaveChange = true;
		}

		if (HaveChange)
		{
			sf::Vector2f position;

			position.x = vue.getCenter().x;
			position.y = vue.getCenter().y;

			RenderTexture_BG_Simulation.setView(vue);

			RenderTexture_BG_Simulation.clear();

			ObjTerrain.Affiche();

			RenderTexture_BG_Simulation.display();

			Texture_BG_Simulation = RenderTexture_BG_Simulation.getTexture();

			HaveChange = false;

			Sprite_BG_Simulation.setTexture(Texture_BG_Simulation);

			std::cout << "X: " << position.x << " | Y: " << position.y << std::endl;

		}

		test.action();

		RenderTexture_AI_Calque_Simulation.setView(vue);
		RenderTexture_AI_Calque_Simulation.clear(sf::Color::Transparent);
		test.affiche();
		RenderTexture_AI_Calque_Simulation.display();
		Texture_AI_Calque_Simulation = RenderTexture_AI_Calque_Simulation.getTexture();
		Sprite_AI_Calque_Simulation.setTexture(Texture_AI_Calque_Simulation);

		window.clear();
		window.draw(Sprite_BG_Simulation);
		window.draw(Sprite_AI_Calque_Simulation);
		window.display();
	}
}