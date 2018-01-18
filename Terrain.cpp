#include "Header.h"

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

void MAJTexture(sf::View& vue, sf::RenderTexture& RTextureSol, sf::RectangleShape& TextureCase, sf::Texture& Tsol, CaseTerrain** Terrain)
{
	sf::Vector2f position;

	position.x = vue.getCenter().x;
	position.y = vue.getCenter().y;

	std::cout << "X: " << position.x << " | Y: " << position.y << std::endl;


	RTextureSol.setView(vue);

	RTextureSol.clear();

	int i_mini = (position.x - vue.getSize().x / 2) / 100;
	if (i_mini < 0)
		i_mini = 0;
	int i_max = (position.x + vue.getSize().x / 2) / 100 + 1;
	if (i_max > 500)
		i_max = 500;

	int j_mini = (position.y - vue.getSize().y / 2) / 100;
	if (j_mini < 0)
		j_mini = 0;
	int j_max = (position.y + vue.getSize().y / 2) / 100 + 1;
	if (j_max > 500)
		j_max = 500;

	for (int i = i_mini; i < i_max; i++)
	{
		for (int j = j_mini; j < j_max; j++)
		{
			switch (Terrain[i][j].Type)
			{
			case CaseTerrain::Base:
				TextureCase.setFillColor(sf::Color::Cyan);
				break;
			case CaseTerrain::Terre:
				TextureCase.setFillColor(sf::Color::Green);
				break;
			case CaseTerrain::Eau:
				TextureCase.setFillColor(sf::Color::Blue);
				break;
			case CaseTerrain::Roche:
				TextureCase.setFillColor(sf::Color::Red);
				break;
			case CaseTerrain::Sable:
				TextureCase.setFillColor(sf::Color::Yellow);
				break;
			case CaseTerrain::Nourriture:
				TextureCase.setFillColor(sf::Color::White);
				break;
			}

			TextureCase.setPosition(i * 100, j * 100);

			RTextureSol.draw(TextureCase);
		}
	}
	RTextureSol.display();

	Tsol = RTextureSol.getTexture();
}

void Camera(sf::RenderWindow& window)
{
	CaseTerrain** Terrain = new CaseTerrain*[500];
	for (int i = 0; i < 500; i++)
	{
		Terrain[i] = new CaseTerrain[500];

		for (int j = 0; j < 500; j++)
		{
			Terrain[i][j].Type = (CaseTerrain::TypeTerrain) (rand() % 6);
		}
	}

	sf::RectangleShape TextureCase(sf::Vector2f(100, 100));
	sf::RenderTexture RTextureSol;


	/*sf::Texture T;
	if (!T.loadFromFile("images/sol.jpg"))
	{
		std::cout << "Erreur !" << std::endl;
	}

	TextureCase.setTexture(&T);*/

	RTextureSol.create(window.getSize().x, window.getSize().y);

	sf::Sprite Ssol;
	sf::Texture Tsol;
	sf::View vue;

	vue.setCenter(100 * 500 / 2, 100 * 500 / 2);

	// on met à jour la vue, avec la nouvelle taille de la fenêtre
	{
		sf::FloatRect visibleArea;
		visibleArea = sf::FloatRect(0, 0, window.getSize().x, window.getSize().y);
		window.setView(sf::View(visibleArea));

		float zoom = vue.getSize().x / RTextureSol.getSize().x;

		RTextureSol.create(window.getSize().x, window.getSize().y);

		vue.setSize(window.getSize().x, window.getSize().y);
		vue.zoom(zoom);

		MAJTexture(vue, RTextureSol, TextureCase, Tsol, Terrain);

		Ssol.setTextureRect(sf::IntRect(0, 0, Tsol.getSize().x, Tsol.getSize().y));
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

				float zoom = vue.getSize().x / RTextureSol.getSize().x;

				RTextureSol.create(window.getSize().x, window.getSize().y);

				vue.setSize(window.getSize().x, window.getSize().y);
				vue.zoom(zoom);

				MAJTexture(vue, RTextureSol, TextureCase, Tsol, Terrain);

				Ssol.setTextureRect(sf::IntRect(0, 0, Tsol.getSize().x, Tsol.getSize().y));
			}
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::MouseWheelMoved)
			{
				if (event.mouseWheel.delta == 1)
				{
					//vue.setCenter(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
					vue.zoom(0.9f);
				}
				if (event.mouseWheel.delta == -1)
				{					
					//vue.setCenter(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
					vue.zoom(1.1f);
				}

				MAJTexture(vue, RTextureSol, TextureCase, Tsol, Terrain);
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

			MAJTexture(vue, RTextureSol, TextureCase, Tsol, Terrain);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			sf::Vector2f position;

			position.x = vue.getCenter().x;
			position.y = vue.getCenter().y;

			if ((position.y + vue.getSize().y / 2) < 500 * 100)
			{
				vue.move(0, 4);
			}

			MAJTexture(vue, RTextureSol, TextureCase, Tsol, Terrain);
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

			MAJTexture(vue, RTextureSol, TextureCase, Tsol, Terrain);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			sf::Vector2f position;

			position.x = vue.getCenter().x;
			position.y = vue.getCenter().y;

			if ((position.y + vue.getSize().y / 2) < 500 * 100)
			{
				vue.move(4, 0);
			}

			MAJTexture(vue, RTextureSol, TextureCase, Tsol, Terrain);
		}

		Ssol.setTexture(Tsol);

		window.clear();
		window.draw(Ssol);
		window.display();
	}
}


int main()
{
#ifdef _DEBUG
	std::cout << ">>>>> Debug: <<<<<" << std::endl;
#else
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

	int TailleEcranH = sf::VideoMode::getDesktopMode().width;
	int TailleEcranV = sf::VideoMode::getDesktopMode().height;

	sf::RenderWindow window(sf::VideoMode(TailleEcranH, TailleEcranV), "ProjetSemestre4");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	//Menu(window);
	Camera(window);

	return 0;
}