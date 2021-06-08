#pragma once

#include "Shape.h"
#include "memento/RectangleUtils.h"

namespace lab4 {
	class Rectangle : public Shape {
	public:
		Rectangle() {};
		Rectangle(sf::Vector2f pos, sf::Color color, sf::Vector2f size);

		ShapeType get_type() override;

		void update_position(sf::Vector2f _pos) override;

		bool check(sf::Vector2f point) override;

		void update_color(sf::Color _color) override;

		void update_size(sf::Vector2f _size);
		void set_size(sf::Vector2f _size);
		sf::Vector2f get_size();

		void set_memento(RectangleMemento& memento);
		void get_memento(const RectangleMemento& memento);

		void draw(sf::RenderWindow& window) override;
		Shape* clone() override;

		void copy(Rectangle source);

		std::string to_string();
		bool from_string(std::string string);
		friend std::ostream& operator<<(std::ostream& os, Rectangle& r)
		{
			os << r.to_string();
			return os;
		}
		friend std::istream& operator>>(std::istream& is, Rectangle& r)
		{
			std::string tmp;
			is >> tmp;

			r.from_string(tmp);

			return is;
		}
	private:
		sf::RectangleShape rect;
		sf::Vector2f size;
	};
}