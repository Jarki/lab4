#pragma once

#include "../../interfaces/IClickable.h"
#include "../../interfaces/IDrawable.h"
#include "../../include/Rectangle.h"
#include <SFML/Graphics.hpp>

namespace lab4 {
	enum ButtonStatus {
		hidden, 
		shown
	};
	class Button : public IClickable, public IDrawable {
	public:
		Button(sf::Vector2f pos, sf::Vector2f size, sf::Font& font);
		Button(sf::Vector2f pos, sf::Vector2f size, sf::Color bg_color, sf::Font& font, sf::Color text_color);

		void hide();
		void show();
		bool is_hidden();

		bool check(sf::Vector2f point) override;

		void set_position(sf::Vector2f pos);
		sf::Vector2f get_position();

		void set_body_size(sf::Vector2f size);
		sf::Vector2f get_body_size();

		void set_body_color(sf::Color color);
		sf::Color get_body_color();

		void set_font(sf::Font& font);

		void set_text(std::string _text);
		std::string get_text();

		void set_text_color(sf::Color color);
		sf::Color get_text_color();

		void draw(sf::RenderWindow& window);
	private:
		Rectangle body;
		sf::Text text;
		ButtonStatus status;
		void center_text();
	};
}