#pragma once

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

namespace gui
{
	/* Button class */
	class Button
	{
	private:
		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

		short unsigned buttonState;
		short unsigned id;

	public:
		// Constructor / Destructor
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id = 0);
		~Button();

		//Accessors
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		//Modifiers
		void setText(const std::string text);
		void setId(const short unsigned id);

		//Functions
		void update(const sf::Vector2i& mousePosWindow);
		void render(sf::RenderTarget& target);
	};

	/*		Button Timing/list	 */
	class DropDownList
	{
	private:
		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;

		float keytime;
		float keytimeMax;

	public:
		DropDownList(float x, float y, float width, float height,
			sf::Font& font, std::string list[],
			unsigned nrOfElements, unsigned default_index = 0);
		~DropDownList();

		//Accessors
		const unsigned short& getActiveElementId() const;

		//Functions
		const bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);
	};

	/* Texture Selector class */
	class TextureSelector
	{
	private:
		gui::Button* hide_btn;
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;

		float keytime;
		const float keytimeMax;
		float gridSize;
		bool active;
		bool hidden;

	public:
		// Constructor / Destructor
		TextureSelector(float x, float y, float width, float height,
			float gridSize, const sf::Texture* texture_sheet,
			sf::Font& font, std::string text);
		~TextureSelector();

		// Accessors
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;
		const bool getKeytime();

		// Update / Render
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);
	};

	class ProgressBar
	{
	private:
		std::string barString;
		sf::Text text;
		float maxWidth;
		int maxValue;
		sf::RectangleShape back;
		sf::RectangleShape inner;

	public:
		ProgressBar(float x, float y, float width, float height, int max_Value,
			sf::Color inner_color, unsigned character_size, sf::Font* font = NULL);
		~ProgressBar();

		//Accessors

		//Modifiers

		//Functions
		void update(const int current_value, const int max_value);
		void render(sf::RenderTarget& target);
	};

}