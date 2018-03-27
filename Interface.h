#ifndef _Interface

#define _Interface true

#include <SFML/Graphics.hpp>

#include <vector>

#ifdef _DEBUG
#include <iostream>
#endif
#include <fstream>
#include <sstream>
#include <iomanip>

#include <string>

#include <list>

namespace Interface
{
	class ultra_personnalisable
	{
	protected:
		sf::Texture** background_texture = NULL;
		sf::Color* background_color = NULL;
		sf::Color* background_outline_color = NULL;
		int* background_outline_thickness = NULL;

		sf::Font** text_font = NULL;
		sf::Color* text_color = NULL;
		sf::Color* text_outline_color = NULL;
		int* text_outline_thickness = NULL;
		int* text_size = NULL;
		int* text_style = NULL;
		int* text_pos_correction_x = NULL;
		int* text_pos_correction_y = NULL;

	public:
		~ultra_personnalisable();

		virtual void set_background_texture(sf::Texture* bg1, sf::Texture* bg2 = NULL, sf::Texture* bg3 = NULL);
		virtual void set_background_color(sf::Color bg1, sf::Color bg2, sf::Color bg3);
		virtual void set_background_outline_color(sf::Color bg1, sf::Color bg2, sf::Color bg3);
		virtual void set_background_outline_thickness(int bg1, int bg2, int bg3);

		virtual void set_text_font(sf::Font* t1, sf::Font* t2 = NULL, sf::Font* t3 = NULL);
		virtual void set_text_color(sf::Color t1, sf::Color t2, sf::Color t3);
		virtual void set_text_outline_color(sf::Color t1, sf::Color t2, sf::Color t3);
		virtual void set_text_outline_thickness(int t1, int t2, int t3);
		virtual void set_text_size(int t1, int t2, int t3);
		virtual void set_text_style(int t1, int t2, int t3);
		virtual void set_text_pos_correction_x(int t1, int t2, int t3);
		virtual void set_text_pos_correction_y(int t1, int t2, int t3);

		virtual void set_bg() = 0;
		virtual void set_text() = 0;

		virtual void generation_bg() { set_bg(); };
		virtual void generation_text() { set_text(); };
	};

	class Bouton : public ultra_personnalisable
	{
	public:
		enum alignement { Gauche = 0, Center_Horizontal = 0b0001, Droite = 0b0010, Haut = 0, Center_Vertical = 0b0100, Bas = 0b1000, };

		enum state { standard = 0, overlay = 0b1, cliking = 0b10, selected = 0b10, bad_event = -1 };

		enum BG_type { none, Rect, Circle, Sprite };

	protected:
		sf::RenderTarget& render;
		sf::RenderWindow& window;

		sf::FloatRect rect;

		sf::Text text;

		sf::Drawable* background = NULL;

		int aligne_text = Center_Horizontal | Center_Vertical;

		state current_state = standard;

	public:

		BG_type bg_type = none;

		Bouton(sf::FloatRect rect, sf::RenderTarget& render, sf::RenderWindow& window, std::string text = "");
		Bouton(sf::Vector2f position, sf::Vector2f size, sf::RenderTarget& render, sf::RenderWindow& window, std::string text = "");
		Bouton(float x, float y, float w, float h, sf::RenderTarget& render, sf::RenderWindow& window, std::string text = "");
		Bouton(sf::FloatRect rect, sf::RenderWindow& window, std::string text = "");
		Bouton(sf::Vector2f position, sf::Vector2f size, sf::RenderWindow& window, std::string text = "");
		Bouton(float x, float y, float w, float h, sf::RenderWindow& window, std::string text = "");

		~Bouton();

		void set_bg_type(BG_type T);

		virtual void set_size(float w, float h);
		virtual void set_size(sf::Vector2f size);

		virtual void set_position(float x, float y);
		virtual void set_position(sf::Vector2f position);

		virtual void move(float dx, float dy);
		virtual void move(sf::Vector2f dposition);

		void set_text(std::string text);

		void set_aligne_text(int aligne);

		virtual void update_state(sf::Event event);

		state get_state(sf::Event event);
		state get_state();

		void set_bg();
		void set_text();

		void generation_bg();
		virtual void generation_text();

		virtual void affiche();

	private:

	};

	class Texte_Entry_Zone : public Bouton
	{

		sf::RenderTexture RenderText;
		sf::Texture texture;
		sf::Sprite SpriteText;

		float mx = 0, my = 0;
		bool monol = false;

		int max_char = 0;

	public:
		enum entry_result { standard = 0, enter = 1, tab = 2, bad_event = -1 };

		Texte_Entry_Zone(sf::FloatRect rect, sf::RenderTarget& render, sf::RenderWindow& window, bool is_selected = false);
		Texte_Entry_Zone(sf::Vector2f position, sf::Vector2f size, sf::RenderTarget& render, sf::RenderWindow& window, bool is_selected = false);
		Texte_Entry_Zone(float x, float y, float w, float h, sf::RenderTarget& render, sf::RenderWindow& window, bool is_selected = false);
		Texte_Entry_Zone(sf::FloatRect rect, sf::RenderWindow& window, bool is_selected = false);
		Texte_Entry_Zone(sf::Vector2f position, sf::Vector2f size, sf::RenderWindow& window, bool is_selected = false);
		Texte_Entry_Zone(float x, float y, float w, float h, sf::RenderWindow& window, bool is_selected = false);

		virtual void update_state(sf::Event event);

		std::string get_text();

		entry_result entry(sf::Event event);

		void select();
		void unselect();

		virtual void generation_text();

		virtual void affiche();

		void set_marge(float x = 0, float y = 0);
		void set_monol(bool is = true);
		void set_max_char(int nmx = 0);
	};

	class Scroll_Menu : public Texte_Entry_Zone
	{
		std::list<Bouton> bouton_list;
		std::list<std::string> string_list;

		sf::RenderTexture scroll_zone_RenderTexture;
		const sf::Texture* scroll_zone_Texture;
		sf::RectangleShape scroll_zone;

		int scroll_height = 12;
		int scroll_pos = 0;

	public:
		Scroll_Menu(sf::FloatRect rect, sf::RenderTarget& render, sf::RenderWindow& window, bool is_selected = false);
		Scroll_Menu(sf::Vector2f position, sf::Vector2f size, sf::RenderTarget& render, sf::RenderWindow& window, bool is_selected = false);
		Scroll_Menu(float x, float y, float w, float h, sf::RenderTarget& render, sf::RenderWindow& window, bool is_selected = false);
		Scroll_Menu(sf::FloatRect rect, sf::RenderWindow& window, bool is_selected = false);
		Scroll_Menu(sf::Vector2f position, sf::Vector2f size, sf::RenderWindow& window, bool is_selected = false);
		Scroll_Menu(float x, float y, float w, float h, sf::RenderWindow& window, bool is_selected = false);

		void add_choice(std::string str);

		void set_background_texture(sf::Texture* bg1, sf::Texture* bg2 = NULL, sf::Texture* bg3 = NULL);
		void set_background_color(sf::Color bg1, sf::Color bg2, sf::Color bg3);
		void set_background_outline_color(sf::Color bg1, sf::Color bg2, sf::Color bg3);
		void set_background_outline_thickness(int bg1, int bg2, int bg3);

		void set_text_font(sf::Font* t1, sf::Font* t2 = NULL, sf::Font* t3 = NULL);
		void set_text_color(sf::Color t1, sf::Color t2, sf::Color t3);
		void set_text_outline_color(sf::Color t1, sf::Color t2, sf::Color t3);
		void set_text_outline_thickness(int t1, int t2, int t3);
		void set_text_size(int t1, int t2, int t3);
		void set_text_style(int t1, int t2, int t3);
		void set_text_pos_correction_x(int t1, int t2, int t3);
		void set_text_pos_correction_y(int t1, int t2, int t3);

		void set_size(float w, float h);
		void set_size(sf::Vector2f size);

		void set_position(float x, float y);
		void set_position(sf::Vector2f position);

		void move(float dx, float dy);
		void move(sf::Vector2f dposition);

		void update_state(sf::Event event);
		
		void affiche();

		void scroll(sf::Event event);
	};
};
#endif