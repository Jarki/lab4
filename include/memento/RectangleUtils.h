#pragma once

#include <SFML/Graphics.hpp>

namespace lab4 {
	class RectangleMemento {
		friend class Rectangle;
		sf::Vector2f pos;
		sf::Color color;
		sf::Vector2f size;
	};

	class RectangleUtils {
	public:
		void save_state(Rectangle& shape);
		void load_state(Rectangle& shape);
		void save_to_file(std::string filename, Rectangle& shape);
		void load_from_file(std::string filename, Rectangle& shape);
	private:
		RectangleMemento memento;
	};
}