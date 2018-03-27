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

	/** Texte_Entry_Zone **/

	Texte_Entry_Zone::Texte_Entry_Zone(sf::FloatRect rect, sf::RenderTarget& render, sf::RenderWindow& window, bool is_selected) : Bouton(rect, render, window)
	{
		if (is_selected)
		{
			current_state = selected;
		}
		else
		{
			current_state = Interface::Bouton::standard;
		}
	};
	Texte_Entry_Zone::Texte_Entry_Zone(sf::Vector2f position, sf::Vector2f size, sf::RenderTarget& render, sf::RenderWindow& window, bool is_selected) : Bouton(position, size, render, window)
	{
		if (is_selected)
		{
			current_state = selected;
		}
		else
		{
			current_state = Interface::Bouton::standard;
		}
	};
	Texte_Entry_Zone::Texte_Entry_Zone(float x, float y, float w, float h, sf::RenderTarget& render, sf::RenderWindow& window, bool is_selected) : Bouton(x, y, w, h, render, window)
	{
		if (is_selected)
		{
			current_state = selected;
		}
		else
		{
			current_state = Interface::Bouton::standard;
		}
	};
	Texte_Entry_Zone::Texte_Entry_Zone(sf::FloatRect rect, sf::RenderWindow& window, bool is_selected) : Bouton(rect, window)
	{
		if (is_selected)
		{
			current_state = selected;
		}
		else
		{
			current_state = Interface::Bouton::standard;
		}
	};
	Texte_Entry_Zone::Texte_Entry_Zone(sf::Vector2f position, sf::Vector2f size, sf::RenderWindow& window, bool is_selected) : Bouton(position, size, window)
	{
		if (is_selected)
		{
			current_state = selected;
		}
		else
		{
			current_state = Interface::Bouton::standard;
		}
	};
	Texte_Entry_Zone::Texte_Entry_Zone(float x, float y, float w, float h, sf::RenderWindow& window, bool is_selected) : Bouton(x, y, w, h, window)
	{
		if (is_selected)
		{
			current_state = selected;
		}
		else
		{
			current_state = Interface::Bouton::standard;
		}
	};

	void Texte_Entry_Zone::update_state(sf::Event event)
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
				new_state = selected;
			}
			else
			{
				if (current_state == selected)
				{
					new_state = selected;
				}
				else
				{
					new_state = overlay;
				}
			}
		}
		else
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				new_state = Interface::Bouton::standard;
			}
			else
			{
				if (current_state == selected)
				{
					new_state = selected;
				}
				else
				{
					new_state = Interface::Bouton::standard;
				}
			}
		}

		if (new_state != current_state)
		{
			current_state = new_state;
			set_bg();
			generation_text();
		}
	};

	std::string Texte_Entry_Zone::get_text()
	{
		return text.getString();
	};

	Texte_Entry_Zone::entry_result Texte_Entry_Zone::entry(sf::Event event)
	{
		std::string msg = text.getString();

		if (current_state == selected)
		{
			if (sf::Event::TextEntered == event.type)
			{
				switch (event.text.unicode)
				{
				case 0x0A:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
					{
						if (!monol)
							msg += "\n";
						else
							return enter;
					}
					else
					{
						return enter;
					}
					break;
				case 0x0D:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
					{
						if (!monol)
							msg += "\n";
						else
							return enter;
					}
					else
					{
						return enter;
					}
					break;
				case 0x0A0D:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
					{
						if (!monol)
							msg += "\n";
						else
							return enter;
					}
					else
					{
						return enter;
					}
					break;
				case 0x09:
					return tab;
					break;
				case 0x08:
					if (msg.size())
						msg.pop_back();
					break;
				case 0x7F:
					msg.clear();
					break;
				case 0x20:
					if (msg.size())
						msg += event.text.unicode;
					break;
				default:
					if (!((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) ^ (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt))))
						msg += event.text.unicode;
					break;
				}

				while (max_char > 0 && msg.size() > max_char)
				{
					msg.pop_back();
				}

				text.setString(msg);

				generation_text();

				return standard;
			}

			return bad_event;
		}

		return standard;

	};

	void Texte_Entry_Zone::select()
	{
		current_state = selected;
		generation_text();
		generation_bg();
	};
	void Texte_Entry_Zone::unselect()
	{
		current_state = Interface::Bouton::standard;
		generation_text();
		generation_bg();
	};

	void Texte_Entry_Zone::generation_text()
	{
		set_text();

		float px = 0, py = 0, w = (rect.width - (2 * mx)), h = (rect.height - (2 * my));

		SpriteText.setTextureRect(sf::IntRect(0, 0, w, h));

		RenderText.create(w, h);
		RenderText.clear(sf::Color::Transparent);

		sf::FloatRect textr = text.getGlobalBounds();

		if (aligne_text & Center_Horizontal)
		{
			px = (textr.width < rect.width) ? (textr.width / 2.0) : (textr.width - ((rect.width / 2.0) - mx));
		}
		else if (aligne_text & Droite)
		{
			px = textr.width - ((rect.width / 2.0) - mx);
		}
		else
		{
			px = (textr.width < rect.width) ? ((rect.width / 2.0) - mx) : (textr.width - ((rect.width / 2.0) - mx));
		}

		if (aligne_text & Center_Vertical)
		{
			py = (textr.height < rect.height) ? (textr.height / 2.0) : (textr.height - ((rect.height / 2.0) - my));
		}
		else if (aligne_text & Bas)
		{
			py = textr.height - ((rect.height / 2.0) - my);
		}
		else
		{
			py = (textr.height < rect.height) ? ((rect.height / 2.0) - my) : (textr.height - ((rect.height / 2.0) - my));
		}

		SpriteText.setPosition(rect.left + mx, rect.top + my);

		px -= ((text_pos_correction_x != NULL) ? text_pos_correction_x[current_state] : 0);
		py -= ((text_pos_correction_y != NULL) ? text_pos_correction_y[current_state] : 0);

		sf::View view(sf::Vector2f(px, py), sf::Vector2f((rect.width - (2 * mx)), (rect.height - (2 * my))));

		RenderText.setView(view);

		text.setPosition(0, 0);
		text.setOrigin(0, 0);

		RenderText.draw(text);
		RenderText.display();

		texture = RenderText.getTexture();

		SpriteText.setTexture(texture);

	};

	void Texte_Entry_Zone::affiche()
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

		render.draw(SpriteText);
	};

	void Texte_Entry_Zone::set_marge(float x, float y)
	{
		mx = x;
		my = y;
	};
	void Texte_Entry_Zone::set_monol(bool is)
	{
		monol = is;
	};
	void Texte_Entry_Zone::set_max_char(int nmx)
	{
		max_char = nmx;
	};

	/** Scroll_Menu **/

	Scroll_Menu::Scroll_Menu(sf::FloatRect rect, sf::RenderTarget& render, sf::RenderWindow& window, bool is_selected) : Texte_Entry_Zone(rect, render, window, is_selected)
	{
		if (!scroll_zone_RenderTexture.create(window.getView().getSize().x, window.getView().getSize().y))
		{
			// erreur...
		}
		scroll_zone.setPosition(rect.left, rect.top + rect.height);
		scroll_zone.setSize(sf::Vector2f(rect.width, rect.height*scroll_height));
		scroll_zone.setTextureRect(sf::IntRect(scroll_zone.getPosition().x, scroll_zone.getPosition().x + rect.height, rect.width, rect.height*scroll_height));
		scroll_zone_RenderTexture.setView(sf::View(sf::FloatRect(0, rect.height*scroll_pos, window.getView().getSize().x, window.getView().getSize().y)));
	};
	Scroll_Menu::Scroll_Menu(sf::Vector2f position, sf::Vector2f size, sf::RenderTarget& render, sf::RenderWindow& window, bool is_selected) : Texte_Entry_Zone(position, size, render, window, is_selected)
	{
		if (!scroll_zone_RenderTexture.create(window.getView().getSize().x, window.getView().getSize().y))
		{
			// erreur...
		}
		scroll_zone.setPosition(rect.left, rect.top + rect.height);
		scroll_zone.setSize(sf::Vector2f(rect.width, rect.height*scroll_height));
		scroll_zone.setTextureRect(sf::IntRect(scroll_zone.getPosition().x, scroll_zone.getPosition().x + rect.height, rect.width, rect.height*scroll_height));
		scroll_zone_RenderTexture.setView(sf::View(sf::FloatRect(0, rect.height*scroll_pos, window.getView().getSize().x, window.getView().getSize().y)));
	};
	Scroll_Menu::Scroll_Menu(float x, float y, float w, float h, sf::RenderTarget& render, sf::RenderWindow& window, bool is_selected) : Texte_Entry_Zone(x, y, w, h, render, window, is_selected)
	{
		if (!scroll_zone_RenderTexture.create(window.getView().getSize().x, window.getView().getSize().y))
		{
			// erreur...
		}
		scroll_zone.setPosition(rect.left, rect.top + rect.height);
		scroll_zone.setSize(sf::Vector2f(rect.width, rect.height*scroll_height));
		scroll_zone.setTextureRect(sf::IntRect(scroll_zone.getPosition().x, scroll_zone.getPosition().x + rect.height, rect.width, rect.height*scroll_height));
		scroll_zone_RenderTexture.setView(sf::View(sf::FloatRect(0, rect.height*scroll_pos, window.getView().getSize().x, window.getView().getSize().y)));
	};
	Scroll_Menu::Scroll_Menu(sf::FloatRect rect, sf::RenderWindow& window, bool is_selected) : Texte_Entry_Zone(rect, window, is_selected)
	{
		if (!scroll_zone_RenderTexture.create(window.getView().getSize().x, window.getView().getSize().y))
		{
			// erreur...
		}
		scroll_zone.setPosition(rect.left, rect.top + rect.height);
		scroll_zone.setSize(sf::Vector2f(rect.width, rect.height*scroll_height));
		scroll_zone.setTextureRect(sf::IntRect(scroll_zone.getPosition().x, scroll_zone.getPosition().x + rect.height, rect.width, rect.height*scroll_height));
		scroll_zone_RenderTexture.setView(sf::View(sf::FloatRect(0, rect.height*scroll_pos, window.getView().getSize().x, window.getView().getSize().y)));
	};
	Scroll_Menu::Scroll_Menu(sf::Vector2f position, sf::Vector2f size, sf::RenderWindow& window, bool is_selected) : Texte_Entry_Zone(position, size, window, is_selected)
	{
		if (!scroll_zone_RenderTexture.create(window.getView().getSize().x, window.getView().getSize().y))
		{
			// erreur...
		}
		scroll_zone.setPosition(rect.left, rect.top + rect.height);
		scroll_zone.setSize(sf::Vector2f(rect.width, rect.height*scroll_height));
		scroll_zone.setTextureRect(sf::IntRect(scroll_zone.getPosition().x, scroll_zone.getPosition().x + rect.height, rect.width, rect.height*scroll_height));
		scroll_zone_RenderTexture.setView(sf::View(sf::FloatRect(0, rect.height*scroll_pos, window.getView().getSize().x, window.getView().getSize().y)));
	};
	Scroll_Menu::Scroll_Menu(float x, float y, float w, float h, sf::RenderWindow& window, bool is_selected) : Texte_Entry_Zone(x, y, w, h, window, is_selected)
	{
		if (!scroll_zone_RenderTexture.create(window.getView().getSize().x, window.getView().getSize().y))
		{
			// erreur...
		}
		scroll_zone.setPosition(rect.left, rect.top + rect.height);
		scroll_zone.setSize(sf::Vector2f(rect.width, rect.height*scroll_height));
		scroll_zone.setTextureRect(sf::IntRect(scroll_zone.getPosition().x, scroll_zone.getPosition().x + rect.height, rect.width, rect.height*scroll_height));
		scroll_zone_RenderTexture.setView(sf::View(sf::FloatRect(0, rect.height*scroll_pos, window.getView().getSize().x, window.getView().getSize().y)));
	};

	void Scroll_Menu::set_background_texture(sf::Texture* bg1, sf::Texture* bg2, sf::Texture* bg3)
	{
		Texte_Entry_Zone::set_background_texture(bg1, bg2, bg3);

		for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
		{
			iterator->set_background_texture(bg1, bg2, bg3);
		}
	};
	void Scroll_Menu::set_background_color(sf::Color bg1, sf::Color bg2, sf::Color bg3)
	{
		Texte_Entry_Zone::set_background_color(bg1, bg2, bg3);

		for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
		{
			iterator->set_background_color(bg1, bg2, bg3);
		}
	};
	void Scroll_Menu::set_background_outline_color(sf::Color bg1, sf::Color bg2, sf::Color bg3)
	{
		Texte_Entry_Zone::set_background_outline_color(bg1, bg2, bg3);

		for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
		{
			iterator->set_background_outline_color(bg1, bg2, bg3);
		}
	};
	void Scroll_Menu::set_background_outline_thickness(int bg1, int bg2, int bg3)
	{
		Texte_Entry_Zone::set_background_outline_thickness(bg1, bg2, bg3);

		for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
		{
			iterator->set_background_outline_thickness(bg1, bg2, bg3);
		}
	};

	void Scroll_Menu::set_text_font(sf::Font* t1, sf::Font* t2, sf::Font* t3)
	{
		Texte_Entry_Zone::set_text_font(t1, t2, t3);

		for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
		{
			iterator->set_text_font(t1, t2, t3);
		}
	};
	void Scroll_Menu::set_text_color(sf::Color t1, sf::Color t2, sf::Color t3)
	{
		Texte_Entry_Zone::set_text_color(t1, t2, t3);

		for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
		{
			iterator->set_text_color(t1, t2, t3);
		}
	};
	void Scroll_Menu::set_text_outline_color(sf::Color t1, sf::Color t2, sf::Color t3)
	{
		Texte_Entry_Zone::set_text_outline_color(t1, t2, t3);

		for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
		{
			iterator->set_text_outline_color(t1, t2, t3);
		}
	};
	void Scroll_Menu::set_text_outline_thickness(int t1, int t2, int t3)
	{
		Texte_Entry_Zone::set_text_outline_thickness(t1, t2, t3);

		for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
		{
			iterator->set_text_outline_thickness(t1, t2, t3);
		}
	};
	void Scroll_Menu::set_text_size(int t1, int t2, int t3)
	{
		Texte_Entry_Zone::set_text_outline_thickness(t1, t2, t3);

		for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
		{
			iterator->set_text_outline_thickness(t1, t2, t3);
		}
	};
	void Scroll_Menu::set_text_style(int t1, int t2, int t3)
	{
		Texte_Entry_Zone::set_text_style(t1, t2, t3);

		for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
		{
			iterator->set_text_style(t1, t2, t3);
		}
	};
	void Scroll_Menu::set_text_pos_correction_x(int t1, int t2, int t3)
	{
		Texte_Entry_Zone::set_text_pos_correction_x(t1, t2, t3);

		for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
		{
			iterator->set_text_pos_correction_x(t1, t2, t3);
		}
	};
	void Scroll_Menu::set_text_pos_correction_y(int t1, int t2, int t3)
	{
		Texte_Entry_Zone::set_text_pos_correction_y(t1, t2, t3);

		for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
		{
			iterator->set_text_pos_correction_y(t1, t2, t3);
		}
	};

	void Scroll_Menu::add_choice(std::string str)
	{
		string_list.push_back(str);

		sf::FloatRect btn_rect;
		
		btn_rect.height = rect.height;
		btn_rect.width = rect.width;
		btn_rect.top = rect.top + rect.height * (bouton_list.size() + 1);
		btn_rect.left = rect.left;

		bouton_list.push_back(Bouton(btn_rect, scroll_zone_RenderTexture, window, str));

		if (background_texture != NULL)
		{
			bouton_list.back().set_background_texture(background_texture[0], background_texture[1], background_texture[2]);
		}
		if (background_color != NULL)
		{
			bouton_list.back().set_background_color(background_color[0], background_color[1], background_color[2]);
		}
		if (background_outline_color != NULL)
		{
			bouton_list.back().set_background_outline_color(background_outline_color[0], background_outline_color[1], background_outline_color[2]);
		}
		if (background_outline_thickness != NULL)
		{
			bouton_list.back().set_background_outline_thickness(background_outline_thickness[0], background_outline_thickness[1], background_outline_thickness[2]);
		}

		if (text_font != NULL)
		{
			bouton_list.back().set_text_font(text_font[0], text_font[1], text_font[2]);
		}
		if (text_color != NULL)
		{
			bouton_list.back().set_text_color(text_color[0], text_color[1], text_color[2]);
		}
		if (text_outline_color != NULL)
		{
			bouton_list.back().set_text_outline_color(text_outline_color[0], text_outline_color[1], text_outline_color[2]);
		}
		if (text_outline_thickness != NULL)
		{
			bouton_list.back().set_text_outline_thickness(text_outline_thickness[0], text_outline_thickness[1], text_outline_thickness[2]);
		}
		if (text_size != NULL)
		{
			bouton_list.back().set_text_size(text_size[0], text_size[1], text_size[2]);
		}
		if (text_style != NULL)
		{
			bouton_list.back().set_text_style(text_style[0], text_style[1], text_style[2]);
		}
		if (text_pos_correction_x != NULL)
		{
			bouton_list.back().set_text_pos_correction_x(text_pos_correction_x[0], text_pos_correction_x[1], text_pos_correction_x[2]);
		}
		if (text_pos_correction_y != NULL)
		{
			bouton_list.back().set_text_pos_correction_y(text_pos_correction_y[0], text_pos_correction_y[1], text_pos_correction_y[2]);
		}

		bouton_list.back().set_bg_type(Interface::Bouton::BG_type::Rect);

		if (current_state == state::selected)
		{
			scroll_zone_RenderTexture.clear(sf::Color::Transparent);

			for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
			{
				iterator->affiche();
			}

			scroll_zone_RenderTexture.display();

			scroll_zone_Texture = &scroll_zone_RenderTexture.getTexture();

			scroll_zone.setTexture(scroll_zone_Texture);
		}
	};
	
	void Scroll_Menu::set_size(float w, float h)
	{
		Texte_Entry_Zone::set_size(w, h);

		int i = 0;

		for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
		{
			i++;

			iterator->set_size(w, h);
			iterator->set_position(rect.left, rect.top + rect.height * i);
		}

		if (!scroll_zone_RenderTexture.create(window.getView().getSize().x, window.getView().getSize().y))
		{
			// erreur...
		}
		scroll_zone.setPosition(rect.left, rect.top + rect.height);
		scroll_zone.setSize(sf::Vector2f(rect.width, rect.height*scroll_height));
		scroll_zone.setTextureRect(sf::IntRect(scroll_zone.getPosition().x, scroll_zone.getPosition().x + rect.height, rect.width, rect.height*scroll_height));
		scroll_zone_RenderTexture.setView(sf::View(sf::FloatRect(0, rect.height*scroll_pos, window.getView().getSize().x, window.getView().getSize().y)));
		if (current_state == state::selected)
		{
			scroll_zone_RenderTexture.clear(sf::Color::Transparent);

			for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
			{
				iterator->affiche();
			}

			scroll_zone_RenderTexture.display();

			scroll_zone_Texture = &scroll_zone_RenderTexture.getTexture();

			scroll_zone.setTexture(scroll_zone_Texture);
		}
	};
	void Scroll_Menu::set_size(sf::Vector2f size)
	{
		Texte_Entry_Zone::set_size(size);

		int i = 0;

		for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
		{
			i++;

			iterator->set_size(size);
			iterator->set_position(rect.left, rect.top + rect.height * i);
		}

		if (!scroll_zone_RenderTexture.create(window.getView().getSize().x, window.getView().getSize().y))
		{
			// erreur...
		}
		scroll_zone.setPosition(rect.left, rect.top + rect.height);
		scroll_zone.setSize(sf::Vector2f(rect.width, rect.height*scroll_height));
		scroll_zone.setTextureRect(sf::IntRect(scroll_zone.getPosition().x, scroll_zone.getPosition().x + rect.height, rect.width, rect.height*scroll_height));
		scroll_zone_RenderTexture.setView(sf::View(sf::FloatRect(0, rect.height*scroll_pos, window.getView().getSize().x, window.getView().getSize().y)));
		if (current_state == state::selected)
		{
			scroll_zone_RenderTexture.clear(sf::Color::Transparent);

			for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
			{
				iterator->affiche();
			}

			scroll_zone_RenderTexture.display();

			scroll_zone_Texture = &scroll_zone_RenderTexture.getTexture();

			scroll_zone.setTexture(scroll_zone_Texture);
		}
	};

	void Scroll_Menu::set_position(float x, float y)
	{
		Texte_Entry_Zone::set_position(x, y);

		int i = 0;

		for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
		{
			i++;

			iterator->set_position(rect.left, rect.top + rect.height * i);
		}

		if (!scroll_zone_RenderTexture.create(window.getView().getSize().x, window.getView().getSize().y))
		{
			// erreur...
		}
		scroll_zone.setPosition(rect.left, rect.top + rect.height);
		scroll_zone.setSize(sf::Vector2f(rect.width, rect.height*scroll_height));
		scroll_zone.setTextureRect(sf::IntRect(scroll_zone.getPosition().x, scroll_zone.getPosition().x + rect.height, rect.width, rect.height*scroll_height));
		scroll_zone_RenderTexture.setView(sf::View(sf::FloatRect(0, rect.height*scroll_pos, window.getView().getSize().x, window.getView().getSize().y)));
		if (current_state == state::selected)
		{
			scroll_zone_RenderTexture.clear(sf::Color::Transparent);

			for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
			{
				iterator->affiche();
			}

			scroll_zone_RenderTexture.display();

			scroll_zone_Texture = &scroll_zone_RenderTexture.getTexture();

			scroll_zone.setTexture(scroll_zone_Texture);
		}
	};
	void Scroll_Menu::set_position(sf::Vector2f position)
	{
		Texte_Entry_Zone::set_position(position);

		int i = 0;

		for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
		{
			i++;

			iterator->set_position(rect.left, rect.top + rect.height * i);
		}

		if (!scroll_zone_RenderTexture.create(window.getView().getSize().x, window.getView().getSize().y))
		{
			// erreur...
		}
		scroll_zone.setPosition(rect.left, rect.top + rect.height);
		scroll_zone.setSize(sf::Vector2f(rect.width, rect.height*scroll_height));
		scroll_zone.setTextureRect(sf::IntRect(scroll_zone.getPosition().x, scroll_zone.getPosition().x + rect.height, rect.width, rect.height*scroll_height));
		scroll_zone_RenderTexture.setView(sf::View(sf::FloatRect(0, rect.height*scroll_pos, window.getView().getSize().x, window.getView().getSize().y)));
		if (current_state == state::selected)
		{
			scroll_zone_RenderTexture.clear(sf::Color::Transparent);

			for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
			{
				iterator->affiche();
			}

			scroll_zone_RenderTexture.display();

			scroll_zone_Texture = &scroll_zone_RenderTexture.getTexture();

			scroll_zone.setTexture(scroll_zone_Texture);
		}
	};

	void Scroll_Menu::move(float dx, float dy)
	{
		Texte_Entry_Zone::set_position(dx, dy);

		int i = 0;

		for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
		{
			i++;

			iterator->set_position(rect.left, rect.top + rect.height * i);
		}

		if (!scroll_zone_RenderTexture.create(window.getView().getSize().x, window.getView().getSize().y))
		{
			// erreur...
		}
		scroll_zone.setPosition(rect.left, rect.top + rect.height);
		scroll_zone.setSize(sf::Vector2f(rect.width, rect.height*scroll_height));
		scroll_zone.setTextureRect(sf::IntRect(scroll_zone.getPosition().x, scroll_zone.getPosition().x + rect.height, rect.width, rect.height*scroll_height));
		scroll_zone_RenderTexture.setView(sf::View(sf::FloatRect(0, rect.height*scroll_pos, window.getView().getSize().x, window.getView().getSize().y)));
		if (current_state == state::selected)
		{
			scroll_zone_RenderTexture.clear(sf::Color::Transparent);

			for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
			{
				iterator->affiche();
			}

			scroll_zone_RenderTexture.display();

			scroll_zone_Texture = &scroll_zone_RenderTexture.getTexture();

			scroll_zone.setTexture(scroll_zone_Texture);
		}
	};
	void Scroll_Menu::move(sf::Vector2f dposition)
	{
		Texte_Entry_Zone::set_position(dposition);

		int i = 0;

		for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
		{
			i++;

			iterator->set_position(rect.left, rect.top + rect.height * i);
		}

		if (!scroll_zone_RenderTexture.create(window.getView().getSize().x, window.getView().getSize().y))
		{
			// erreur...
		}
		scroll_zone.setPosition(rect.left, rect.top + rect.height);
		scroll_zone.setSize(sf::Vector2f(rect.width, rect.height*scroll_height));
		scroll_zone.setTextureRect(sf::IntRect(scroll_zone.getPosition().x, scroll_zone.getPosition().x + rect.height, rect.width, rect.height*scroll_height));
		scroll_zone_RenderTexture.setView(sf::View(sf::FloatRect(0, rect.height*scroll_pos, window.getView().getSize().x, window.getView().getSize().y)));
		if (current_state == state::selected)
		{
			scroll_zone_RenderTexture.clear(sf::Color::Transparent);

			for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
			{
				iterator->affiche();
			}

			scroll_zone_RenderTexture.display();

			scroll_zone_Texture = &scroll_zone_RenderTexture.getTexture();

			scroll_zone.setTexture(scroll_zone_Texture);
		}
	};

	void Scroll_Menu::update_state(sf::Event event)
	{
		if (current_state == state::selected)
		{
			auto current_view = scroll_zone_RenderTexture.getView();

			auto event_view = window.getView();

			event_view.move(sf::Vector2f(0, rect.height * scroll_pos));

			scroll_zone_RenderTexture.setView(event_view);

			auto string_iterator = string_list.begin();

			for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
			{
				if (iterator->get_state(event) == state::cliking)
				{
					set_text(*string_iterator);
				}

				string_iterator++;
			}

			scroll_zone_RenderTexture.setView(current_view);
		}

		Texte_Entry_Zone::update_state(event);

		if (current_state == state::selected)
		{
			scroll_zone_RenderTexture.clear(sf::Color::Transparent);

			for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
			{
				iterator->update_state(event);
				iterator->affiche();
			}

			scroll_zone_RenderTexture.display();

			scroll_zone_Texture = &scroll_zone_RenderTexture.getTexture();

			scroll_zone.setTexture(scroll_zone_Texture);
		}
	};

	void Scroll_Menu::affiche()
	{
		Texte_Entry_Zone::affiche();
		
		if (current_state == state::selected)
		{
			if (!scroll_zone_RenderTexture.create(window.getView().getSize().x, window.getView().getSize().y))
			{
				// erreur...
			}
			scroll_zone.setPosition(rect.left, rect.top + rect.height);
			scroll_zone.setSize(sf::Vector2f(rect.width, rect.height*scroll_height));
			scroll_zone.setTextureRect(sf::IntRect(scroll_zone.getPosition().x, scroll_zone.getPosition().x + rect.height, rect.width, rect.height*scroll_height));
			scroll_zone_RenderTexture.setView(sf::View(sf::FloatRect(0, rect.height*scroll_pos, window.getView().getSize().x, window.getView().getSize().y)));

			scroll_zone_RenderTexture.clear(sf::Color::Transparent);

			for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
			{
				iterator->affiche();
			}

			scroll_zone_RenderTexture.display();

			const sf::Texture& texture = scroll_zone_RenderTexture.getTexture();

			scroll_zone_Texture = &scroll_zone_RenderTexture.getTexture();

			scroll_zone.setTexture(scroll_zone_Texture);

			render.draw(scroll_zone);
		}
	};

	void Scroll_Menu::scroll(sf::Event event)
	{
		if (current_state == state::selected)
		{
			if (event.type == sf::Event::MouseWheelMoved)
			{
				if (event.mouseWheel.delta == 1)
				{
					if (scroll_pos > 0)
					{
						scroll_pos--;
					}
				}
				if (event.mouseWheel.delta == -1)
				{
					if (scroll_pos < ((int)string_list.size() - scroll_height))
					{
						scroll_pos++;
					}
				}

				scroll_zone_RenderTexture.setView(sf::View(sf::FloatRect(rect.left, rect.top + (rect.height*(scroll_pos)), rect.width, rect.height*scroll_height)));
				if (current_state == state::selected)
				{
					scroll_zone_RenderTexture.clear(sf::Color::Transparent);

					for (auto iterator = bouton_list.begin(); iterator != bouton_list.end(); iterator++)
					{
						iterator->affiche();
					}

					scroll_zone_RenderTexture.display();

					scroll_zone_Texture = &scroll_zone_RenderTexture.getTexture();

					scroll_zone.setTexture(scroll_zone_Texture);
				}
			}
		}
	};
};