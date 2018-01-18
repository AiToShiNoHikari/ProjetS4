#include "Interface.h"

namespace Interface
{
	/** ultra_personnalisable **/
	ultra_personnalisable::~ultra_personnalisable()
	{
		delete(background_texture);
		delete(background_color);
		delete(background_outline_color);
		delete(background_outline_thickness);

		delete(text_font);
		delete(text_color);
		delete(text_outline_color);
		delete(text_outline_thickness);
		delete(text_size);
		delete(text_style);
		delete(text_pos_correction_x);
		delete(text_pos_correction_y);
	};

	void ultra_personnalisable::set_background_texture(sf::Texture* bg1, sf::Texture* bg2, sf::Texture* bg3)
	{
		if (background_texture == NULL)
		{
			background_texture = new sf::Texture*[3];
		}

		background_texture[0] = bg1;

		if (bg2 == NULL)
		{
			background_texture[1] = background_texture[0];
		}
		else
		{
			background_texture[1] = bg2;
		}

		if (bg3 == NULL)
		{
			background_texture[2] = background_texture[1];
		}
		else
		{
			background_texture[2] = bg3;
		}

		set_bg();
	};
	void ultra_personnalisable::set_background_color(sf::Color bg1, sf::Color bg2, sf::Color bg3)
	{
		if (background_color == NULL)
		{
			background_color = new sf::Color[3];
		}

		background_color[0] = bg1;
		background_color[1] = bg2;
		background_color[2] = bg3;
		set_bg();
	};
	void ultra_personnalisable::set_background_outline_color(sf::Color bg1, sf::Color bg2, sf::Color bg3)
	{
		if (background_outline_color == NULL)
		{
			background_outline_color = new sf::Color[3];
		}

		background_outline_color[0] = bg1;
		background_outline_color[1] = bg2;
		background_outline_color[2] = bg3;
		set_bg();
	};
	void ultra_personnalisable::set_background_outline_thickness(int bg1, int bg2, int bg3)
	{
		if (background_outline_thickness == NULL)
		{
			background_outline_thickness = new int[3];
		}

		background_outline_thickness[0] = bg1;
		background_outline_thickness[1] = bg2;
		background_outline_thickness[2] = bg3;
		set_bg();
	};

	void ultra_personnalisable::set_text_font(sf::Font* t1, sf::Font* t2, sf::Font* t3)
	{
		if (text_font == NULL)
		{
			text_font = new sf::Font*[3];
		}

		text_font[0] = t1;

		if (t2 == NULL)
		{
			text_font[1] = text_font[0];
		}
		else
		{
			text_font[1] = t2;
		}

		if (t3 == NULL)
		{
			text_font[2] = text_font[1];
		}
		else
		{
			text_font[2] = t3;
		}

		generation_text();
	};
	void ultra_personnalisable::set_text_color(sf::Color t1, sf::Color t2, sf::Color t3)
	{
		if (text_color == NULL)
		{
			text_color = new sf::Color[3];
		}

		text_color[0] = t1;
		text_color[1] = t2;
		text_color[2] = t3;

		set_text();
	};
	void ultra_personnalisable::set_text_outline_color(sf::Color t1, sf::Color t2, sf::Color t3)
	{
		if (text_outline_color == NULL)
		{
			text_outline_color = new sf::Color[3];
		}

		text_outline_color[0] = t1;
		text_outline_color[1] = t2;
		text_outline_color[2] = t3;

		set_text();
	};
	void ultra_personnalisable::set_text_outline_thickness(int t1, int t2, int t3)
	{
		if (text_outline_thickness == NULL)
		{
			text_outline_thickness = new int[3];
		}

		text_outline_thickness[0] = t1;
		text_outline_thickness[1] = t2;
		text_outline_thickness[2] = t3;

		generation_text();
	};
	void ultra_personnalisable::set_text_size(int t1, int t2, int t3)
	{
		if (text_size == NULL)
		{
			text_size = new int[3];
		}

		text_size[0] = t1;
		text_size[1] = t2;
		text_size[2] = t3;

		generation_text();
	};
	void ultra_personnalisable::set_text_style(int t1, int t2, int t3)
	{
		if (text_style == NULL)
		{
			text_style = new int[3];
		}

		text_style[0] = t1;
		text_style[1] = t2;
		text_style[2] = t3;

		generation_text();
	};
	void ultra_personnalisable::set_text_pos_correction_x(int t1, int t2, int t3)
	{
		if (text_pos_correction_x == NULL)
		{
			text_pos_correction_x = new int[3];
		}

		text_pos_correction_x[0] = t1;
		text_pos_correction_x[1] = t2;
		text_pos_correction_x[2] = t3;

		generation_text();
	};
	void ultra_personnalisable::set_text_pos_correction_y(int t1, int t2, int t3)
	{
		if (text_pos_correction_y == NULL)
		{
			text_pos_correction_y = new int[3];
		}

		text_pos_correction_y[0] = t1;
		text_pos_correction_y[1] = t2;
		text_pos_correction_y[2] = t3;

		generation_text();
	};

	/** Bouton **/

	Bouton::Bouton(sf::FloatRect rect, sf::RenderTarget& render, sf::RenderWindow& window, std::string text) : render(render), window(window)
	{
		this->rect = rect;
		this->text.setString(text);
		aligne_text = (Center_Horizontal | Center_Vertical);

		background = NULL;

		generation_text();
		generation_bg();
	};
	Bouton::Bouton(sf::Vector2f position, sf::Vector2f size, sf::RenderTarget& render, sf::RenderWindow& window, std::string text) : render(render), window(window)
	{
		sf::FloatRect rect(position, size);
		this->rect = rect;
		this->text.setString(text);
		aligne_text = (Center_Horizontal | Center_Vertical);

		background = NULL;

		generation_text();
		generation_bg();
	};
	Bouton::Bouton(float x, float y, float w, float h, sf::RenderTarget& render, sf::RenderWindow& window, std::string text) : render(render), window(window)
	{
		sf::FloatRect rect(x, y, w, h);
		this->rect = rect;
		this->text.setString(text);
		aligne_text = (Center_Horizontal | Center_Vertical);

		background = NULL;

		generation_text();
		generation_bg();
	};
	Bouton::Bouton(sf::FloatRect rect, sf::RenderWindow& window, std::string text) : render(window), window(window)
	{
		this->rect = rect;
		this->text.setString(text);
		aligne_text = (Center_Horizontal | Center_Vertical);

		background = NULL;

		generation_text();
		generation_bg();
	};
	Bouton::Bouton(sf::Vector2f position, sf::Vector2f size, sf::RenderWindow& window, std::string text) : render(window), window(window)
	{
		sf::FloatRect rect(position, size);
		this->rect = rect;
		this->text.setString(text);
		aligne_text = (Center_Horizontal | Center_Vertical);

		background = NULL;

		generation_text();
		generation_bg();
	};
	Bouton::Bouton(float x, float y, float w, float h, sf::RenderWindow& window, std::string text) : render(window), window(window)
	{
		sf::FloatRect rect(x, y, w, h);
		this->rect = rect;
		this->text.setString(text);
		aligne_text = (Center_Horizontal | Center_Vertical);

		background = NULL;

		generation_text();
		generation_bg();
	};

	Bouton::~Bouton()
	{
		delete(background);
	}

	void Bouton::set_bg_type(BG_type T)
	{
		if (T != bg_type)
		{
			bg_type = T;

			delete(background);

			background = NULL;

			if (T != none)
				generation_bg();
		}
	};

	void Bouton::set_size(float w, float h)
	{
		rect.width = w;
		rect.height = h;
		generation_bg();
		generation_text();
	};
	void Bouton::set_size(sf::Vector2f size)
	{
		rect.width = size.x;
		rect.height = size.y;
		generation_bg();
		generation_text();
	};

	void Bouton::set_position(float x, float y)
	{
		rect.left = x;
		rect.top = y;
		generation_bg();
		generation_text();
	};
	void Bouton::set_position(sf::Vector2f position)
	{
		rect.left = position.x;
		rect.top = position.y;
		generation_bg();
		generation_text();
	};

	void Bouton::move(float dx, float dy)
	{
		rect.left += dx;
		rect.top += dy;
		generation_bg();
	};
	void Bouton::move(sf::Vector2f dposition)
	{
		rect.left += dposition.x;
		rect.top += dposition.y;
		generation_bg();
	};

	void Bouton::set_text(std::string text)
	{
		this->text.setString(text);
	};

	void Bouton::set_aligne_text(int aligne)
	{
		aligne_text = aligne;
	};

	void Bouton::update_state(sf::Event event)
	{
		if (event.type != sf::Event::MouseButtonPressed && event.type != sf::Event::MouseButtonReleased && event.type != sf::Event::MouseMoved)
			return;

		sf::Vector2i window_pos = sf::Mouse::getPosition(window);

		sf::Vector2f render_pos = render.mapPixelToCoords(window_pos);

		state new_state;

		if (rect.contains(render_pos))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				new_state = cliking;
			}
			else
			{
				new_state = overlay;
			}
		}
		else
		{
			new_state = standard;
		}

		if (new_state != current_state)
		{
			current_state = new_state;
			set_bg();
			generation_text();
		}
	};

	Bouton::state Bouton::get_state(sf::Event event)
	{
		if (event.type != sf::Event::MouseButtonPressed && event.type != sf::Event::MouseButtonReleased && event.type != sf::Event::MouseMoved)
			return Interface::Bouton::state::bad_event;

		update_state(event);

		return current_state;
	};
	Bouton::state Bouton::get_state()
	{
		return current_state;
	};

	void Bouton::set_bg()
	{
		switch (bg_type)
		{
		case Interface::Bouton::Rect:
			if (background_texture != NULL)
			{
				((sf::RectangleShape*)background)->setTexture(background_texture[current_state]);
			}
			if (background_color != NULL)
			{
				((sf::RectangleShape*)background)->setFillColor(background_color[current_state]);
			}
			if (background_outline_color != NULL)
			{
				((sf::RectangleShape*)background)->setOutlineColor(background_outline_color[current_state]);
			}
			if (background_outline_thickness != NULL)
			{
				((sf::RectangleShape*)background)->setOutlineThickness(background_outline_thickness[current_state]);
			}
			break;
		case Interface::Bouton::Circle:
			if (background_texture != NULL)
			{
				((sf::CircleShape*)background)->setTexture(background_texture[current_state]);
			}
			if (background_color != NULL)
			{
				((sf::CircleShape*)background)->setFillColor(background_color[current_state]);
			}
			if (background_outline_color != NULL)
			{
				((sf::CircleShape*)background)->setOutlineColor(background_outline_color[current_state]);
			}
			if (background_outline_thickness != NULL)
			{
				((sf::CircleShape*)background)->setOutlineThickness(background_outline_thickness[current_state]);
			}
			break;
		case Interface::Bouton::Sprite:
			if (background_texture != NULL)
			{
				((sf::Sprite*)background)->setTexture(*(background_texture[current_state]));
			}
			if (background_color != NULL)
			{
				((sf::Sprite*)background)->setColor(background_color[current_state]);
			}
			break;
		}
	};
	void Bouton::set_text()
	{
		if (text_font != NULL)
		{
			text.setFont(*(text_font[current_state]));
		}
		if (text_color != NULL)
		{
			text.setFillColor(text_color[current_state]);
		}
		if (text_outline_color != NULL)
		{
			text.setOutlineColor(text_outline_color[current_state]);
		}
		if (text_outline_thickness != NULL)
		{
			text.setOutlineThickness(text_outline_thickness[current_state]);
		}
		if (text_size != NULL)
		{
			text.setCharacterSize(text_size[current_state]);
		}
		if (text_style != NULL)
		{
			text.setStyle(text_style[current_state]);
		}
	};

	void Bouton::generation_bg()
	{
		sf::Vector2f position(rect.left, rect.top);

		switch (bg_type)
		{
		case Interface::Bouton::Rect:
			if (background == NULL)
			{
				background = new sf::RectangleShape(sf::Vector2f(rect.width, rect.height));
			}
			else
			{
				((sf::RectangleShape*)background)->setSize(sf::Vector2f(rect.width, rect.height));
			}
			((sf::RectangleShape*)background)->setPosition(rect.left, rect.top);
			break;
		case Interface::Bouton::Circle:
			if (background == NULL)
			{
				background = new sf::CircleShape(rect.width < rect.height ? rect.width : rect.height);
			}
			else
			{
				((sf::CircleShape*)background)->setRadius(rect.width < rect.height ? rect.width : rect.height);
			}
			((sf::CircleShape*)background)->setPosition(position);
			break;
		case Interface::Bouton::Sprite:
			if (background == NULL)
			{
				background = new sf::Sprite;
			}
			((sf::Sprite*)background)->setPosition(position);
			break;
		}

		set_bg();
	};
	void Bouton::generation_text()
	{
		set_text();

		float ox = 0, oy = 0, px = rect.left, py = rect.top;

		sf::FloatRect textr = text.getGlobalBounds();

		if (aligne_text & Center_Horizontal)
		{
			ox = textr.width / 2.0;
			px = rect.left + (rect.width / 2.0) + ((text_pos_correction_x != NULL) ? text_pos_correction_x[current_state] : 0);
		}
		else if (aligne_text & Droite)
		{
			ox = textr.width;
			px = rect.left + rect.width + ((text_pos_correction_x != NULL) ? text_pos_correction_x[current_state] : 0);
		}
		else
		{
			ox = 0;
			px = rect.left + ((text_pos_correction_x != NULL) ? text_pos_correction_x[current_state] : 0);
		}

		if (aligne_text & Center_Vertical)
		{
			oy = textr.height / 2.0;
			py = rect.top + (rect.height / 2.0) + ((text_pos_correction_y != NULL) ? text_pos_correction_y[current_state] : 0);
		}
		else if (aligne_text & Bas)
		{
			oy = textr.height;
			py = rect.top + rect.height + ((text_pos_correction_y != NULL) ? text_pos_correction_y[current_state] : 0);
		}
		else
		{
			oy = 0;
			py = rect.top + ((text_pos_correction_y != NULL) ? text_pos_correction_y[current_state] : 0);
		}

		text.setOrigin(sf::Vector2f(ox, oy));
		text.setPosition(sf::Vector2f(px, py));
	};

	void Bouton::affiche()
	{
		switch (bg_type)
		{
		case Interface::Bouton::Rect:
			render.draw(*((sf::RectangleShape*)background));
			break;
		case Interface::Bouton::Circle:
			render.draw(*((sf::CircleShape*)background));
			break;
		case Interface::Bouton::Sprite:
			render.draw(*((sf::Sprite*)background));
			break;
		}

		render.draw(text);
	};
};