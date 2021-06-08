#pragma once

#include "Shape.h"
#include "memento/CircleUtils.h"

namespace lab4 {
	class Circle : public Shape {
	public:
		Circle() { r = 0; };
		Circle(sf::Vector2f pos, sf::Color color, float radius);

		ShapeType get_type() override;

		void update_position(sf::Vector2f _pos) override;

		bool check(sf::Vector2f point) override;

		void update_color(sf::Color _color) override;

		void update_radius(float _r);
		void set_radius(float _r);

		void set_memento(CircleMemento& memento);
		void get_memento(const CircleMemento& memento);

		void draw(sf::RenderWindow &window) override;
		Shape* clone() override;

		void copy(Circle source);

		std::string to_string();
		bool from_string(std::string string);
		friend std::ostream& operator<<(std::ostream& os, Circle& c)
		{
			os << c.to_string();
			return os;
		}
		friend std::istream& operator>>(std::istream& is, Circle& c)
		{
			std::string tmp;
			is >> tmp;

			c.from_string(tmp);

			return is;
		}
	private:
		sf::CircleShape circle;
		float r;
	};
}