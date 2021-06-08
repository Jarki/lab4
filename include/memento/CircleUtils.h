#pragma once

#include <SFML/Graphics.hpp>

namespace lab4 {
	class CircleMemento {
		friend class Circle;
	public:
		sf::Vector2f pos;
		sf::Color color;
		float r;
	};

	class CircleUtils {
	public:
		void save_state(Circle& shape);
		void load_state(Circle& shape);
		void save_to_file(std::string filename, Circle& shape);
		void load_from_file(std::string filename, Circle& shape);
	private:
		CircleMemento memento;
	};
}