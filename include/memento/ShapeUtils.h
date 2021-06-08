#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

namespace lab4 {
	class ShapeMemento {
		friend class Shape;
		sf::Vector2f pos;
		sf::Color color;
	};

	class ShapeUtils {
	public:
		void save_state(Shape& shape);
		void load_state(Shape& shape);
		void save_to_file(std::string filename, Shape& shape);
		void load_from_file(std::string filename, Shape& shape);
	private:
		ShapeMemento memento;
	};
}