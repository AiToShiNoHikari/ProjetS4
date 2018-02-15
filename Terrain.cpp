#include "Terrain.h"


void Edition(sf::RenderWindow& window)
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


	int Change = 1;


	sf::Image ImageTexture;
	ImageTexture.create(32, 32);

	int PX = 30, 
		PY = 30;

	ImageTexture.copy(Ressource::TileMapTerre, 0, 0, sf::IntRect(0, 0, 32, 32));
	sf::Texture TBTerre;
	TBTerre.loadFromImage(ImageTexture);

	Interface::Bouton BTerre(PX + 80, PY, 50, 50, window);
	BTerre.set_bg_type(Interface::Bouton::BG_type::Rect);
	BTerre.set_background_texture(&TBTerre);
	BTerre.set_background_outline_thickness(2, 2, 2);
	BTerre.set_background_outline_color(sf::Color::White, sf::Color::Blue, sf::Color::Red);

	BTerre.set_background_color(sf::Color::White, sf::Color::White, sf::Color(255, 255, 255, 128));



	ImageTexture.copy(Ressource::TileMapEau, 0, 0, sf::IntRect(0, 0, 32, 32));
	sf::Texture TBEau;
	TBEau.loadFromImage(ImageTexture);

	Interface::Bouton BEau(PX + 160, PY, 50, 50, window);
	BEau.set_bg_type(Interface::Bouton::BG_type::Rect);
	BEau.set_background_texture(&TBEau);
	BEau.set_background_outline_thickness(2, 2, 2);
	BEau.set_background_outline_color(sf::Color::White, sf::Color::Blue, sf::Color::Red);

	BEau.set_background_color(sf::Color::White, sf::Color::White, sf::Color(255, 255, 255, 128));



	ImageTexture.copy(Ressource::TileMapRoche, 0, 0, sf::IntRect(0, 0, 32, 32));
	sf::Texture TBRoche;
	TBRoche.loadFromImage(ImageTexture);

	Interface::Bouton BRoche(PX + 240, PY, 50, 50, window);
	BRoche.set_bg_type(Interface::Bouton::BG_type::Rect);
	BRoche.set_background_texture(&TBRoche);
	BRoche.set_background_outline_thickness(2, 2, 2);
	BRoche.set_background_outline_color(sf::Color::White, sf::Color::Blue, sf::Color::Red);

	BRoche.set_background_color(sf::Color::White, sf::Color::White, sf::Color(255, 255, 255, 128));



	ImageTexture.copy(Ressource::TileMapSable, 0, 0, sf::IntRect(0, 0, 32, 32));
	sf::Texture TBSable;
	TBSable.loadFromImage(ImageTexture);

	Interface::Bouton BSable(PX + 320, PY, 50, 50, window);
	BSable.set_bg_type(Interface::Bouton::BG_type::Rect);
	BSable.set_background_texture(&TBSable);
	BSable.set_background_outline_thickness(2, 2, 2);
	BSable.set_background_outline_color(sf::Color::White, sf::Color::Blue, sf::Color::Red);

	BSable.set_background_color(sf::Color::White, sf::Color::White, sf::Color(255, 255, 255, 128));



	ImageTexture.copy(Ressource::TileMapBase, 0, 0, sf::IntRect(0, 0, 32, 32));
	sf::Texture TBBase;
	TBBase.loadFromImage(ImageTexture);

	Interface::Bouton BBase(PX + 400, PY, 50, 50, window);
	BBase.set_bg_type(Interface::Bouton::BG_type::Rect);
	BBase.set_background_texture(&TBBase);
	BBase.set_background_outline_thickness(2, 2, 2);
	BBase.set_background_outline_color(sf::Color::White, sf::Color::Blue, sf::Color::Red);

	BBase.set_background_color(sf::Color::White, sf::Color::White, sf::Color(255, 255, 255, 128));



	ImageTexture.copy(Ressource::TileMapNourriture, 0, 0, sf::IntRect(0, 0, 32, 32));
	sf::Texture TBNourriture;
	TBNourriture.loadFromImage(ImageTexture);

	Interface::Bouton BNourriture(PX + 480, PY, 50, 50, window);
	BNourriture.set_bg_type(Interface::Bouton::BG_type::Rect);
	BNourriture.set_background_texture(&TBNourriture);
	BNourriture.set_background_outline_thickness(2, 2, 2);
	BNourriture.set_background_outline_color(sf::Color::White, sf::Color::Blue, sf::Color::Red);

	BNourriture.set_background_color(sf::Color::White, sf::Color::White, sf::Color(255, 255, 255, 128));

	
	Interface::Bouton BSave(PX, PY, 50, 50, window);
	BSave.set_bg_type(Interface::Bouton::BG_type::Rect);
	BSave.set_background_texture(&Ressource::Save);
	BSave.set_background_outline_thickness(2, 2, 2);
	BSave.set_background_outline_color(sf::Color::White, sf::Color::Blue, sf::Color::Red);

	BSave.set_background_color(sf::Color::White, sf::Color::White, sf::Color(255, 255, 255, 128));

	bool Sauvegarde = false;

	while (window.isOpen() && !Sauvegarde)
	{
		window.clear();

		sf::Event event;
		while (window.pollEvent(event))
		{
			sf::Vector2f mousepos = RTextureSol.mapPixelToCoords(sf::Mouse::getPosition(window));
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				BTerre.get_state(event);
				BEau.get_state(event);
				BRoche.get_state(event);
				BSable.get_state(event);
				BBase.get_state(event);
				BNourriture.get_state(event);
				BSave.get_state(event);
				break;
			case sf::Event::MouseButtonPressed:
			{
				int MX = mousepos.x / _size;
				int MY = mousepos.y / _size;

				bool ChangeSave = true;

				if (BTerre.get_state(event) == Interface::Bouton::cliking)
				{
					Change = 1;
					ChangeSave = false;
				}
				if (BEau.get_state(event) == Interface::Bouton::cliking)
				{
					Change = 2;
					ChangeSave = false;
				}
				if (BRoche.get_state(event) == Interface::Bouton::cliking)
				{
					Change = 3;
					ChangeSave = false;
				}
				if (BSable.get_state(event) == Interface::Bouton::cliking)
				{
					Change = 4;
					ChangeSave = false;
				}
				if (BBase.get_state(event) == Interface::Bouton::cliking)
				{
					Change = 0;
					ChangeSave = false;
				}
				if (BNourriture.get_state(event) == Interface::Bouton::cliking)
				{
					Change = 5;
					ChangeSave = false;
				}
				if (BSave.get_state(event) == Interface::Bouton::cliking)
				{
					std::cout << "Save" << std::endl;
					Sauvegarde = true;
					ChangeSave = false;
				}


				if (ChangeSave)
				{
					ObjTerrain.Terrain[MX][MY].Type = (CaseTerrain::TypeTerrain)Change;
					ObjTerrain.MAJTexture(MX - 2, MY - 2, MX + 2, MY + 2);
					HaveChange = true;
				}

					std::cout << Change << std::endl;

			}
				break;
			case sf::Event::MouseButtonReleased:
				BTerre.update_state(event);
				BEau.update_state(event);
				BRoche.update_state(event);
				BSable.update_state(event);
				BBase.update_state(event);
				BNourriture.update_state(event);
				BSave.update_state(event);
				break;
			default:
				break;
			}
		
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

				Tsol = RTextureSol.getTexture();

				Ssol.setTextureRect(sf::IntRect(0, 0, Tsol.getSize().x, Tsol.getSize().y));
			}
			if (event.type == sf::Event::MouseWheelMoved)
			{
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
		
		window.draw(Ssol);
		BTerre.affiche();
		BEau.affiche();
		BRoche.affiche();
		BSable.affiche();
		BBase.affiche();
		BNourriture.affiche();
		BSave.affiche();
		window.display();
	}

	Interface::Texte_Entry_Zone NomMap(window.getSize().x / 2 - 250, window.getSize().y / 2 - 25, 500, 50, window);
	NomMap.set_bg_type(Interface::Texte_Entry_Zone::BG_type::Rect);
	NomMap.set_text_font(&Ressource::Arial);
	NomMap.set_background_outline_thickness(2, 2, 2);
	NomMap.set_background_outline_color(sf::Color::White, sf::Color::Blue, sf::Color::Red);

	NomMap.set_text_color(sf::Color::Black, sf::Color::Black, sf::Color::Black);
	NomMap.set_background_color(sf::Color::Transparent, sf::Color(255, 255, 255, 128), sf::Color::White);

	NomMap.select();
	NomMap.set_monol();

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
				NomMap.get_state(event);
				break;
			case sf::Event::MouseButtonPressed:
			{
				NomMap.get_state(event);

			}
			break;
			case sf::Event::MouseButtonReleased:
				NomMap.get_state(event);
				break;
			case sf::Event::TextEntered:
				if (NomMap.entry(event) == Interface::Texte_Entry_Zone::entry_result::enter)
				{
					SaveTerrain(NomMap.get_text(), ObjTerrain);
				};
				break;
			default:
				break;
			}
		}

		window.draw(Ssol);
		NomMap.affiche();
		window.display();
	}

}

void SaveTerrain(std::string name, ClassTerrain& Terrain)
{
	std::ofstream TerrainList("./Ressource/Sauvegarde/Terrain/Terrain_List.save.sl", std::ios::out | std::ios::app);

	std::ofstream NewTerrain("./Ressource/Sauvegarde/Terrain/" + name + ".save.st");

	TerrainList << name << std::endl;

	NewTerrain << Terrain.TX << " " << Terrain.TY;

	for (int i = 0; i < Terrain.TX; i++)
	{
		for (int j = 0; j < Terrain.TY; j++)
		{
			NewTerrain << " " << Terrain.Terrain[i][j].Type;
		}
	}

	TerrainList.close();
	NewTerrain.close();
};

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
	}

	MAJTexture();
}

void ClassTerrain::Affiche()
{
	Render.draw(SprtTerrain);
}