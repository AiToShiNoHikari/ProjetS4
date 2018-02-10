#include "IA.h"

//IA
Fourmie::Fourmie(int x, int y, Parametre_IA parametre_IA, ClassTerrain& Terrain,sf::RenderTarget& render, sf::Texture& texture, CasePheromones** Pheromone_Table, Fourmiliere& fourmiliere) : Terrain(Terrain), render(render), texture(texture), fourmiliere(fourmiliere)
{
	this->x = x + 0.5;
	this->y = y + 0.5;

	this->parametre_IA = parametre_IA;

	this->Pheromone_Table = Pheromone_Table;

	Sprite.setSize(sf::Vector2f(_size / 2, _size));

	Sprite.setTexture(&texture);

	Sprite.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256, 1+rand() % 255));

	Sprite.setOrigin(_size / 4, _size / 2);

	change_dest();
};

void Fourmie::deplacement()
{
	float dtime = speed_clock.restart().asSeconds();

	x += (parametre_IA.speed * dx * dtime);
	y += (parametre_IA.speed * dy* dtime);

	Pheromone_current -= dtime;

	Sprite.setPosition(x*_size, y*_size);
};

void Fourmie::analyse()
{
	int cx = -1, cy = -1;

	case_x = (int)x, case_y = (int)y;

	if (case_x < 0 || case_y < 0 || case_x >= Terrain.TX || case_y >= Terrain.TY)
	{
		if (case_x < 0)
		{
			cx = 0;
		}
		else if (case_x >= Terrain.TX)
		{
			cx = Terrain.TX;
		}
		else 
		{
			cx = case_x;
		}

		if (case_y < 0)
		{
			cy = 0;
		}
		else if (case_y >= Terrain.TY)
		{
			cy = Terrain.TY;
		}
		else
		{
			cy = case_y;
		}
	};

	int min_x = ((int)(x - parametre_IA.detection_range))<0 ? 0 : ((int)(x - parametre_IA.detection_range));
	int max_x = ((int)(x + parametre_IA.detection_range)) >= Terrain.TX ? Terrain.TX : ((int)(x + parametre_IA.detection_range));
	int min_y = ((int)(y - parametre_IA.detection_range))<0 ? 0 : ((int)(y - parametre_IA.detection_range));
	int max_y = ((int)(y + parametre_IA.detection_range)) >= Terrain.TY ? Terrain.TY : ((int)(y + parametre_IA.detection_range));
	
	//analyse du terrain et change la direction ou la destination en fonction du resulta
	if (cx < 0)
	{
		for (int i = min_x; i < max_x; i++)
		{
			for (int j = min_y; j < max_y; j++)
			{
				switch (destination)
				{
				case Fourmie::home:
					if (Terrain.Terrain[i][j].Type == CaseTerrain::TypeTerrain::Base)
					{
						if (case_x == i && case_y == j)
						{
							change_dest();
							cx = -1, cy = -1;
						}
						else
						{
							if (!anti_wrong_case(i, j))
							{
								cx = i;
								cy = j;
							}
						}
					}
					break;
				case Fourmie::food:
					if (Terrain.Terrain[i][j].Type == CaseTerrain::TypeTerrain::Nourriture)
					{
						if (case_x == i && case_y == j)
						{
							change_dest();
							cx = -1, cy = -1;
						}
						else
						{
							if (!anti_wrong_case(i, j))
							{
								cx = i;
								cy = j;
							}
						}
					}
					break;
				case Fourmie::water:
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
							if (!anti_wrong_case(i, j))
							{
								cx = i;
								cy = j;
							}
						}
					}
					break;
				case Fourmie::enemy:
					if (Terrain.Terrain[i][j].Type == CaseTerrain::TypeTerrain::Base)
					{
						if (case_x == i && case_y == j)
						{
							change_dest();
							cx = -1, cy = -1;
						}
						else
						{
							if (!anti_wrong_case(i, j))
							{
								cx = i;
								cy = j;
							}
						}
					}
					break;
				case Fourmie::search:
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
								if (!anti_wrong_case(i, j))
								{
									cx = i;
									cy = j;
								}
							}
							else
							{
								if ((abs(x - cx) + abs(y - cy)) / 2.0 > (abs(x - i) + abs(y - j)) / 2.0)
								{
									if (!anti_wrong_case(i, j))
									{
										cx = i;
										cy = j;
									}
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
	}

	//suit les pheromones si aucune direction n'est prise
	if (cx < 0)
	{
		CasePheromones::Type searched;
		switch (destination)
		{
		case Fourmie::home:
			searched = CasePheromones::Type::home;
			break;
		case Fourmie::food:
			searched = CasePheromones::Type::food;
			break;
		case Fourmie::water:
			searched = CasePheromones::Type::water;
			break;
		case Fourmie::enemy:
			searched = CasePheromones::Type::enemy;
			break;
		default:
			searched = CasePheromones::Type::none;
			break;
		}

		if (searched != CasePheromones::Type::none)
		{
			float value = 0;

			for (int i = min_x; i < max_x; i++)
			{
				for (int j = min_y; j < max_y; j++)
				{
					Pheromone& valuec = Pheromone_Table[i][j][searched];
					
					if (valuec > 0)
					{
						if (value < valuec)
						{
							if (!anti_wrong_case(i, j))
							{
								cx = i;
								cy = j;
								value = valuec;
							}
						}
						else if (value == valuec)
						{
							if ((abs(x - cx) + abs(y - cy)) / 2.0 > (abs(x - i) + abs(y - j)) / 2.0)
							{
								if (!anti_wrong_case(i, j))
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
	}

	//si aucune direction n'a été prise
	if (cx < 0)
	{
		do
		{
			//cx = ((int)x + (rand() % 3) - 1);
			//cy = ((int)y + (rand() % 3) - 1);

			organised_search(cx, cy);

			anti_hors_map(cx, cy);

			if (cx >= 0)
			{
				if (anti_wrong_case(cx, cy))
				{
					cx = -1;
					cy = -1;
				}
			}

		} while ((cx == (int)x && cy == (int)y) || cx < 0);
	}

	float delta_dest_x = (cx + 0.5) - x;
	float delta_dest_y = (cy + 0.5) - y;

	float hypo = hypotf(delta_dest_x, delta_dest_y);
	float ndx = delta_dest_x / hypo, ndy = delta_dest_y / hypo;

	rotation = acos(ndx) * 180 / PI;

	if(ndy<0)
		rotation = 360 - rotation;

	rotation += 90;

	Sprite.setRotation(rotation);
	
	dx = ndx;
	dy = ndy;

	palce_pheromone();
};

void Fourmie::change_dest()
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
		fourmiliere.select_dest(destination, contenue);

		contenue = home;
	}

	Pheromone_current = parametre_IA.Pheromone_max;
};

void Fourmie::palce_pheromone()
{
	CasePheromones::Type place;
	switch (contenue)
	{
	case Fourmie::home:
		place = CasePheromones::Type::home;
		break;
	case Fourmie::food:
		place = CasePheromones::Type::food;
		break;
	case Fourmie::water:
		place = CasePheromones::Type::water;
		break;
	case Fourmie::enemy:
		place = CasePheromones::Type::enemy;
		break;
	default:
		place = CasePheromones::Type::none;
		break;
	}
	
	if (place != CasePheromones::Type::none)
	{
		if (case_x >= 0 && case_x < Terrain.TX && case_y >= 0 && case_y < Terrain.TY)
		{
			Pheromone& valuec = Pheromone_Table[case_x][case_y][place];

			if (valuec < Pheromone_current)
			{
				valuec = Pheromone_current;
			}
			else if (valuec > Pheromone_current)
			{
				Pheromone_current = (int)valuec;
			}

			//Pheromone_current--;

			if (Pheromone_current <= 0)
			{
				change_dest();
			}
		}
	}
};

void Fourmie::action()
{
	if (case_x != (int)x || case_y != (int)y)
		analyse();

	deplacement();
};

void Fourmie::affiche()
{
	render.draw(Sprite);

	//std::cout << "x: " << x << " y: " << y << " dest: " << destination << " cont: " << contenue << std::endl;
};

void Fourmie::anti_hors_map(int& cx, int& cy)
{
	if (cx < 0 || cy < 0 || cx >= Terrain.TX || cy >= Terrain.TY)
	{
		cx = -1;
		cy = -1;
	};
};

bool Fourmie::anti_wrong_case(int& cx, int& cy)
{
	if (cx < 0 || cy < 0 || cx >= Terrain.TX || cy >= Terrain.TY)
		return true;

	float delta_dest_x = (cx + 0.5) - x;
	float delta_dest_y = (cy + 0.5) - y;

	if (delta_dest_y == 0 && delta_dest_x == 0)
		return false;

	float hypo = hypotf(delta_dest_x, delta_dest_y);
	float ndx = delta_dest_x / hypo, ndy = delta_dest_y / hypo;

	float nx = x, ny = y;
	int enx = nx, eny = ny;

	while (true)
	{
		enx = (int)nx, eny = (int)ny;

		while (enx == (int)nx && eny == (int)ny)
		{
			nx += ndx;
			ny += ndy;
		}

		if (nx < 0 || ny < 0 || nx >= Terrain.TX || ny >= Terrain.TY)
			return true;

		switch (Terrain.Terrain[(int)nx][(int)ny].Type)
		{
		case CaseTerrain::Roche:
			return true;
			break;
		case CaseTerrain::Sable:
			if (parametre_IA.sand_speed <= 0)
				return true;
			break;
		default:
			break;
		}

		if (cx == (int)nx && cy == (int)ny)
			break;
	}

	return false;
};

void Fourmie::organised_search(int& cx, int& cy)
{
	cx = case_x;
	cy = case_y;

	bool test = Pheromone_Table[case_x][case_y].organised_search;

	int r = ((int)((rotation + 360 - 90 + (test ? 90 : -90) - 45) / 90.0)) % 4;

	switch (r)
	{
	case 0:
		cy--;
		break;
	case 1:
		cx++;
		break;
	case 2:
		cy++;
		break;
	case 3:
		cx--;
		break;
	}

	float delta_dest_x = (cx + 0.5) - x;
	float delta_dest_y = (cy + 0.5) - y;

	float hypo = hypotf(delta_dest_x, delta_dest_y);
	float ndx = delta_dest_x / hypo, ndy = delta_dest_y / hypo;

	rotation = acos(ndx) * 180 / PI;

	if (ndy<0)
		rotation = 360 - rotation;

	rotation += 90;

	if (!(cx < 0 || cy < 0 || cx >= Terrain.TX || cy >= Terrain.TY))
		Pheromone_Table[case_x][case_y].organised_search = !test;
};

//Fourmiliere

Fourmiliere::Fourmiliere(int x, int y, Parametre_IA parametre_IA, float Pheromone_disipation_speed, ClassTerrain& Terrain, sf::RenderTarget& render, sf::Texture& texture) : Terrain(Terrain), render(render), texture(texture)
{
	Pheromone_Table = new CasePheromones*[Terrain.TX];
	for (int i = 0; i < Terrain.TX; i++)
	{
		Pheromone_Table[i] = new CasePheromones[Terrain.TY];

		for (int j = 0; j < Terrain.TY; j++)
		{
			Pheromone_Table[i][j].organised_search = ((rand() % 1) == 1);
			Pheromone_Table[i][j].set_disipation_speed(Pheromone_disipation_speed);
		};
	};

	this->x = x;
	this->y = y;

	this->parametre_IA = parametre_IA;
};

void Fourmiliere::add_fourmie()
{
	Fourmies.push_back(new Fourmie(x, y, parametre_IA, Terrain, render, texture, Pheromone_Table, *this));
};

void Fourmiliere::action()
{
	for (std::list<Fourmie*>::iterator iterator = Fourmies.begin(); iterator != Fourmies.end(); iterator++)
	{
		(*iterator)->action();
	}
};

void Fourmiliere::affiche()
{
	int i = 0;

	for (std::list<Fourmie*>::iterator iterator = Fourmies.begin(); iterator != Fourmies.end(); iterator++)
	{
		//std::cout << "Fourmie " << i << ": ";
		i++;

		(*iterator)->affiche();
	}
	std::cout << std::endl;
};

void Fourmiliere::select_dest(Fourmie::Type_Destination& destination, Fourmie::Type_Destination& contenue)
{
	switch (contenue)
	{
	case Fourmie::Type_Destination::food:
		Food_found = true;
		break;
	case Fourmie::Type_Destination::water:
		Water_found = true;
		break;
	default:
		break;
	}

	if (!Food_found && !Water_found)
	{
		destination = Fourmie::Type_Destination::search;
	}
	else if (Food_found && Water_found)
	{
		switch (rand() % 2)
		{
		case 0:
			destination = Fourmie::Type_Destination::food;
			break;
		case 1:
			destination = Fourmie::Type_Destination::water;
			break;
		}
	}
	else if (Food_found && !Water_found)
	{
		switch (rand() % 2)
		{
		case 0:
			destination = Fourmie::Type_Destination::food;
			break;
		case 1:
			destination = Fourmie::Type_Destination::water;
			break;
		}
	}
	else if (!Food_found && Water_found)
	{
		switch (rand() % 2)
		{
		case 0:
			destination = Fourmie::Type_Destination::food;
			break;
		case 1:
			destination = Fourmie::Type_Destination::water;
			break;
		}
	}
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
	int pos_base_x = rand() % ObjTerrain.TX, pos_base_y = rand() % ObjTerrain.TY;

	ObjTerrain.Terrain[pos_base_x][pos_base_y].Type = CaseTerrain::Base;
	ObjTerrain.Terrain[rand() % ObjTerrain.TX][rand() % ObjTerrain.TY].Type = CaseTerrain::Nourriture;
	ObjTerrain.Terrain[rand() % ObjTerrain.TX][rand() % ObjTerrain.TY].Type = CaseTerrain::Eau;

	ObjTerrain.MAJTexture(0, 0, ObjTerrain.TX, ObjTerrain.TY);
	//fin terrain de test


	Parametre_IA parametre_IA;
	parametre_IA.detection_range = 2;
	parametre_IA.Pheromone_max = 40;
	parametre_IA.speed = 2.5;
	parametre_IA.sand_speed = 1.5;
	parametre_IA.water_speed = 1;

	Fourmiliere test(pos_base_x, pos_base_y, parametre_IA, 0.5, ObjTerrain, RenderTexture_AI_Calque_Simulation, Ressource::Fourmie);

	for (int i = 0; i < 1000; i++)
	{
		test.add_fourmie();
	};

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

	int ValZoom = 5;

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
					if (ValZoom < 10)
					{
						ValZoom++;
						vue.zoom(0.9f);
					}
				}
				if (event.mouseWheel.delta == -1)
				{
					vue.setCenter(mousepos.x, mousepos.y);
					if (ValZoom > 2)
					{
						ValZoom--;
						vue.zoom(1.0 / 0.9f);
					}
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
				vue.move(0, -ValZoom);

				HaveChange = true;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			sf::Vector2f position;

			position.x = vue.getCenter().x;
			position.y = vue.getCenter().y;

			if ((position.y + vue.getSize().y / 2) < ObjTerrain.TY * _size)
			{
				vue.move(0, ValZoom);

				HaveChange = true;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			sf::Vector2f position;

			position.x = vue.getCenter().x;
			position.y = vue.getCenter().y;

			if ((position.x - vue.getSize().x / 2) > 0)
			{
				vue.move(-ValZoom, 0);

				HaveChange = true;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			sf::Vector2f position;

			position.x = vue.getCenter().x;
			position.y = vue.getCenter().y;

			if ((position.x + vue.getSize().x / 2) < ObjTerrain.TX * _size)
			{
				vue.move(ValZoom, 0);

				HaveChange = true;
			}
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