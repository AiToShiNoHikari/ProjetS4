#include "Terrain.h"

void Menu(sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.display();
	}
}

void Camera(sf::RenderWindow& window)
{
	bool HaveChange = true;

	sf::RenderTexture RTextureSol;

	RTextureSol.create(window.getSize().x, window.getSize().y);

	ClassTerrain ObjTerrain(250, 250, RTextureSol);

	sf::Sprite Ssol;
	sf::Texture Tsol;
	sf::View vue;
	vue.setCenter(_size * ObjTerrain.TX / 2, _size * ObjTerrain.TY / 2);

	// on met à jour la vue, avec la nouvelle taille de la fenêtre
	{
		sf::FloatRect visibleArea;
		visibleArea = sf::FloatRect(0, 0, window.getSize().x, window.getSize().y);
		window.setView(sf::View(visibleArea));

		float zoom = vue.getSize().x / RTextureSol.getSize().x;

		RTextureSol.create(window.getSize().x, window.getSize().y);

		vue.setSize(window.getSize().x, window.getSize().y);
		vue.zoom(zoom);

		ObjTerrain.Affiche();
		Tsol = RTextureSol.getTexture();

		Ssol.setTextureRect(sf::IntRect(0, 0, Tsol.getSize().x, Tsol.getSize().y));
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

				float zoom = vue.getSize().x / RTextureSol.getSize().x;

				RTextureSol.create(window.getSize().x, window.getSize().y);

				vue.setSize(window.getSize().x, window.getSize().y);
				vue.zoom(zoom);
				HaveChange = true;

				Ssol.setTextureRect(sf::IntRect(0, 0, Tsol.getSize().x, Tsol.getSize().y));
			}
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::MouseWheelMoved)
			{
				sf::Vector2f mousepos = RTextureSol.mapPixelToCoords(sf::Mouse::getPosition(window));
				
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
				vue.move(0, ValZoom);
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
				vue.move(-ValZoom, 0);
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
				vue.move(ValZoom, 0);
			}
			HaveChange = true;
		}


		if (HaveChange)
		{
			sf::Vector2f position;

			position.x = vue.getCenter().x;
			position.y = vue.getCenter().y;

			RTextureSol.setView(vue);

			RTextureSol.clear();

			ObjTerrain.Affiche();

			RTextureSol.display();

			Tsol = RTextureSol.getTexture();

			HaveChange = false;


			Ssol.setTexture(Tsol);

			std::cout << "X: " << position.x << " | Y: " << position.y << std::endl;

		}


		window.clear();
		window.draw(Ssol);
		window.display();
	}
}

ClassTerrain::ClassTerrain(int x, int y, sf::RenderTarget& Render) : Render(Render)
{
	Redimension(x, y);
};

/***** cette fonction te donnera l'image de la texture de la case *****//*
sf::Image ClassTerrain::Texture(int x, int y)
{
	sf::Image ImageTexture;

	ImageTexture.create(32, 32);

	CaseTerrain::TypeTerrain test = Terrain[x][y].Type;

	sf::Image* PointeurTileMap = NULL;

	switch (test)
	{
	case CaseTerrain::Base:
		PointeurTileMap = &Ressource::TileMapBase;
		break;
	case CaseTerrain::Terre:
		PointeurTileMap = &Ressource::TileMapTerre;
		break;
	case CaseTerrain::Eau:
		PointeurTileMap = &Ressource::TileMapEau;
		break;
	case CaseTerrain::Roche:
		PointeurTileMap = &Ressource::TileMapRoche;
		break;
	case CaseTerrain::Sable:
		PointeurTileMap = &Ressource::TileMapSable;
		break;
	case CaseTerrain::Nourriture:
		PointeurTileMap = &Ressource::TileMapNourriture;
		break;
	}

	sf::Image& TileMap = *PointeurTileMap;

	enum dir
	{
		UP,
		DOWN,
		RIGHT,
		LEFT,
		UP_RIGHT,
		UP_LEFT,
		DOWN_RIGHT,
		DOWN_LEFT,
	};

	bool continu_texture_test[8] = { false, false, false, false, false, false, false, false };

	if (x + 1 < TX && y > 0)
	{
		continu_texture_test[UP_RIGHT] = (Terrain[x + 1][y - 1].Type == test);
	}
	if (x + 1 < TX)
	{
		continu_texture_test[RIGHT] = (Terrain[x + 1][y].Type == test);
	}
	if (x + 1 < TX && y + 1 < TY)
	{
		continu_texture_test[DOWN_RIGHT] = (Terrain[x + 1][y + 1].Type == test);
	}
	if (y + 1 < TY)
	{
		continu_texture_test[DOWN] = (Terrain[x][y + 1].Type == test);
	}
	if (y + 1 < TY && x > 0)
	{
		continu_texture_test[DOWN_LEFT] = (Terrain[x - 1][y + 1].Type == test);
	}
	if (x > 0)
	{
		continu_texture_test[LEFT] = (Terrain[x - 1][y].Type == test);
	}
	if (x > 0 && y > 0)
	{
		continu_texture_test[UP_LEFT] = (Terrain[x - 1][y - 1].Type == test);
	}
	if (y > 0)
	{
		continu_texture_test[UP] = (Terrain[x][y - 1].Type == test);
	}

	if (!(continu_texture_test[UP] || continu_texture_test[DOWN] || continu_texture_test[RIGHT] || continu_texture_test[LEFT]))
	{
		ImageTexture.copy(TileMap, 0, 0, sf::IntRect(0, 0, 32, 32));
	}
	else
	{
		sf::Vector2i size(16, 16);

		if (!(continu_texture_test[DOWN] || continu_texture_test[RIGHT]))
		{
			ImageTexture.copy(TileMap, 16, 16, sf::IntRect(sf::Vector2i(48, 80), size));
		}
		else if (continu_texture_test[DOWN] && continu_texture_test[RIGHT])
		{
			if (continu_texture_test[DOWN_RIGHT])
			{
				ImageTexture.copy(TileMap, 16, 16, sf::IntRect(sf::Vector2i(16, 48), size));
			}
			else
			{
				ImageTexture.copy(TileMap, 16, 16, sf::IntRect(sf::Vector2i(48, 16), size));
			}
		}
		else if (continu_texture_test[DOWN] && !continu_texture_test[RIGHT])
		{
			ImageTexture.copy(TileMap, 16, 16, sf::IntRect(sf::Vector2i(16, 80), size));
		}
		else if (!continu_texture_test[DOWN] && continu_texture_test[RIGHT])
		{
			ImageTexture.copy(TileMap, 16, 16, sf::IntRect(sf::Vector2i(48, 48), size));
		}

		if (!(continu_texture_test[DOWN] || continu_texture_test[LEFT]))
		{
			ImageTexture.copy(TileMap, 0, 16, sf::IntRect(sf::Vector2i(0, 80), size));
		}
		else if (continu_texture_test[DOWN] && continu_texture_test[LEFT])
		{
			if (continu_texture_test[DOWN_LEFT])
			{
				ImageTexture.copy(TileMap, 0, 16, sf::IntRect(sf::Vector2i(32, 48), size));
			}
			else
			{
				ImageTexture.copy(TileMap, 0, 16, sf::IntRect(sf::Vector2i(32, 16), size));
			}
		}
		else if (continu_texture_test[DOWN] && !continu_texture_test[LEFT])
		{
			ImageTexture.copy(TileMap, 0, 16, sf::IntRect(sf::Vector2i(32, 80), size));
		}
		else if (!continu_texture_test[DOWN] && continu_texture_test[LEFT])
		{
			ImageTexture.copy(TileMap, 0, 16, sf::IntRect(sf::Vector2i(0, 48), size));
		}

		if (!(continu_texture_test[UP] || continu_texture_test[LEFT]))
		{
			ImageTexture.copy(TileMap, 0, 0, sf::IntRect(sf::Vector2i(0, 32), size));
		}
		else if (continu_texture_test[UP] && continu_texture_test[LEFT])
		{
			if (continu_texture_test[UP_LEFT])
			{
				ImageTexture.copy(TileMap, 0, 0, sf::IntRect(sf::Vector2i(32, 64), size));
			}
			else
			{
				ImageTexture.copy(TileMap, 0, 0, sf::IntRect(sf::Vector2i(32, 0), size));
			}
		}
		else if (continu_texture_test[UP] && !continu_texture_test[LEFT])
		{
			ImageTexture.copy(TileMap, 0, 0, sf::IntRect(sf::Vector2i(32, 32), size));
		}
		else if (!continu_texture_test[UP] && continu_texture_test[LEFT])
		{
			ImageTexture.copy(TileMap, 0, 0, sf::IntRect(sf::Vector2i(0, 64), size));
		}

		if (!(continu_texture_test[UP] || continu_texture_test[RIGHT]))
		{
			ImageTexture.copy(TileMap, 16, 0, sf::IntRect(sf::Vector2i(48, 32), size));
		}
		else if (continu_texture_test[UP] && continu_texture_test[RIGHT])
		{
			if (continu_texture_test[UP_RIGHT])
			{
				ImageTexture.copy(TileMap, 16, 0, sf::IntRect(sf::Vector2i(16, 64), size));
			}
			else
			{
				ImageTexture.copy(TileMap, 16, 0, sf::IntRect(sf::Vector2i(48, 0), size));
			}
		}
		else if (continu_texture_test[UP] && !continu_texture_test[RIGHT])
		{
			ImageTexture.copy(TileMap, 16, 0, sf::IntRect(sf::Vector2i(16, 32), size));
		}
		else if (!continu_texture_test[UP] && continu_texture_test[RIGHT])
		{
			ImageTexture.copy(TileMap, 16, 0, sf::IntRect(sf::Vector2i(48, 64), size));
		}
	}

	return ImageTexture;
};//*/
/***** cette fonction te donnera l'image de la texture de la case *****/
sf::Image ClassTerrain::Texture(int x, int y)
{
	sf::Image ImageTexture;

	ImageTexture.create(32, 32);

	CaseTerrain::TypeTerrain test = Terrain[x][y].Type;

	sf::Image* PointeurTileMap = NULL;

	switch (test)
	{
	case CaseTerrain::Base:
		PointeurTileMap = &Ressource::TileMapBase;
		break;
	case CaseTerrain::Terre:
		PointeurTileMap = &Ressource::TileMapTerre;
		break;
	case CaseTerrain::Eau:
		PointeurTileMap = &Ressource::TileMapEau;
		break;
	case CaseTerrain::Roche:
		PointeurTileMap = &Ressource::TileMapRoche;
		break;
	case CaseTerrain::Sable:
		PointeurTileMap = &Ressource::TileMapSable;
		break;
	case CaseTerrain::Nourriture:
		PointeurTileMap = &Ressource::TileMapNourriture;
		break;
	}

	sf::Image& TileMap = *PointeurTileMap;

	char continu_texture_test = 0;

	if (x + 1 < TX && y > 0)
	{
		if (Terrain[x + 1][y - 1].Type == test)
			continu_texture_test = continu_texture_test | (1 << 0);
	}
	if (x + 1 < TX)
	{
		if (Terrain[x + 1][y].Type == test)
			continu_texture_test = continu_texture_test | (1 << 1);
	}
	if (x + 1 < TX && y + 1 < TY)
	{
		if (Terrain[x + 1][y + 1].Type == test)
			continu_texture_test = continu_texture_test | (1 << 2);
	}
	if (y + 1 < TY)
	{
		if (Terrain[x][y + 1].Type == test)
			continu_texture_test = continu_texture_test | (1 << 3);
	}
	if (y + 1 < TY && x > 0)
	{
		if (Terrain[x - 1][y + 1].Type == test)
			continu_texture_test = continu_texture_test | (1 << 4);
	}
	if (x > 0)
	{
		if (Terrain[x - 1][y].Type == test)
			continu_texture_test = continu_texture_test | (1 << 5);
	}
	if (x > 0 && y > 0)
	{
		if (Terrain[x - 1][y - 1].Type == test)
			continu_texture_test = continu_texture_test | (1 << 6);
	}
	if (y > 0)
	{
		if (Terrain[x][y - 1].Type == test)
			continu_texture_test = continu_texture_test | (1 << 7);
	}

	if (!(continu_texture_test & 0b10101010))
	{
		ImageTexture.copy(TileMap, 0, 0, sf::IntRect(0, 0, 32, 32));
	}
	else
	{
		if (!(continu_texture_test & 0b00000010) && !(continu_texture_test & 0b00001000))
		{
			ImageTexture.copy(TileMap, 16, 16, sf::IntRect(48, 80, 16, 16));
		}
		else if ((continu_texture_test & 0b00000010) && (continu_texture_test & 0b00001000))
		{
			if (continu_texture_test & 0b00000100)
			{
				ImageTexture.copy(TileMap, 16, 16, sf::IntRect(16, 48, 16, 16));
			}
			else
			{
				ImageTexture.copy(TileMap, 16, 16, sf::IntRect(48, 16, 16, 16));
			}
		}
		else if ((continu_texture_test & 0b00000010) && !(continu_texture_test & 0b00001000))
		{
			ImageTexture.copy(TileMap, 16, 16, sf::IntRect(16, 80, 16, 16));
		}
		else if (!(continu_texture_test & 0b00000010) && (continu_texture_test & 0b00001000))
		{
			ImageTexture.copy(TileMap, 16, 16, sf::IntRect(48, 48, 16, 16));
		}

		if (!(continu_texture_test & 0b00100000) && !(continu_texture_test & 0b00001000))
		{
			ImageTexture.copy(TileMap, 0, 16, sf::IntRect(0, 80, 16, 16));
		}
		else if ((continu_texture_test & 0b00100000) && (continu_texture_test & 0b00001000))
		{
			if (continu_texture_test & 0b00010000)
			{
				ImageTexture.copy(TileMap, 0, 16, sf::IntRect(32, 48, 16, 16));
			}
			else
			{
				ImageTexture.copy(TileMap, 0, 16, sf::IntRect(32, 16, 16, 16));
			}
		}
		else if ((continu_texture_test & 0b00100000) && !(continu_texture_test & 0b00001000))
		{
			ImageTexture.copy(TileMap, 0, 16, sf::IntRect(32, 80, 16, 16));
		}
		else if (!(continu_texture_test & 0b00100000) && (continu_texture_test & 0b00001000))
		{
			ImageTexture.copy(TileMap, 0, 16, sf::IntRect(0, 48, 16, 16));
		}

		if (!(continu_texture_test & 0b00100000) && !(continu_texture_test & 0b10000000))
		{
			ImageTexture.copy(TileMap, 0, 0, sf::IntRect(0, 32, 16, 16));
		}
		else if ((continu_texture_test & 0b00100000) && (continu_texture_test & 0b10000000))
		{
			if (continu_texture_test & 0b01000000)
			{
				ImageTexture.copy(TileMap, 0, 0, sf::IntRect(32, 64, 16, 16));
			}
			else
			{
				ImageTexture.copy(TileMap, 0, 0, sf::IntRect(32, 0, 16, 16));
			}
		}
		else if ((continu_texture_test & 0b00100000) && !(continu_texture_test & 0b10000000))
		{
			ImageTexture.copy(TileMap, 0, 0, sf::IntRect(32, 32, 16, 16));
		}
		else if (!(continu_texture_test & 0b00100000) && (continu_texture_test & 0b10000000))
		{
			ImageTexture.copy(TileMap, 0, 0, sf::IntRect(0, 64, 16, 16));
		}

		if (!(continu_texture_test & 0b00000010) && !(continu_texture_test & 0b10000000))
		{
			ImageTexture.copy(TileMap, 16, 0, sf::IntRect(48, 32, 16, 16));
		}
		else if ((continu_texture_test & 0b00000010) && (continu_texture_test & 0b10000000))
		{
			if (continu_texture_test & 0b00000001)
			{
				ImageTexture.copy(TileMap, 16, 0, sf::IntRect(16, 64, 16, 16));
			}
			else
			{
				ImageTexture.copy(TileMap, 16, 0, sf::IntRect(48, 0, 16, 16));
			}
		}
		else if ((continu_texture_test & 0b00000010) && !(continu_texture_test & 0b10000000))
		{
			ImageTexture.copy(TileMap, 16, 0, sf::IntRect(16, 32, 16, 16));
		}
		else if (!(continu_texture_test & 0b00000010) && (continu_texture_test & 0b10000000))
		{
			ImageTexture.copy(TileMap, 16, 0, sf::IntRect(48, 64, 16, 16));
		}
	}

	return ImageTexture;
};

void ClassTerrain::MAJTexture(int i_mini, int j_mini, int i_max, int j_max)
{
	if (i_mini < 0)
	{
		ImgTerrain.create(TX*_size, TY*_size);
		i_mini = 0;
		j_mini = 0;
		i_max = TX;
		j_max = TY;
	}


	for (int i = i_mini; i < i_max; i++)
	{
		for (int j = j_mini; j < j_max; j++)
		{
			ImgTerrain.copy(Texture(i, j), i*_size, j*_size);
		}
	}

	TextTerrain.loadFromImage(ImgTerrain);

	SprtTerrain.setTexture(TextTerrain);

	SprtTerrain.setTextureRect(sf::IntRect(0, 0, TextTerrain.getSize().x, TextTerrain.getSize().y));
}

void ClassTerrain::Redimension(int x, int y)
{
	if (Terrain != NULL)
	{
		for (int i = 0; i < TX; i++)
		{
			delete(Terrain[i]);
		}
		delete(Terrain);
	}

	TX = x;
	TY = y;

	Terrain = new CaseTerrain*[TX];
	for (int i = 0; i < TX; i++)
	{
		Terrain[i] = new CaseTerrain[TY];

		for (int j = 0; j < TY; j++)
		{
			Terrain[i][j].Type = (CaseTerrain::TypeTerrain) (rand() % 6);
		}
	}

	MAJTexture();
}

void ClassTerrain::Affiche()
{
	Render.draw(SprtTerrain);
}