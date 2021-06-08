#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../interfaces/IShape.h"
#include "memento/ShapeUtils.h"
#include "ShapeParser.h"

namespace lab4{
	class ShapeParser;
	class ShapeComposite;
	class Shape : public IShape {
	public:
		Shape();
		Shape(sf::Vector2f _pos, sf::Color _color);

		virtual ShapeType get_type() override;
		void make_unknown();

		ShapeComposite* get_parent();
		void set_parent(ShapeComposite* parent);

		void set_position(sf::Vector2f _pos);
		sf::Vector2f get_position();
		virtual void update_position(sf::Vector2f _pos);

		virtual bool check(sf::Vector2f point);

		void set_color(sf::Color _color);
		sf::Color get_color();
		virtual void update_color(sf::Color _color);

		virtual void set_memento(ShapeMemento& memento);
		virtual void get_memento(const ShapeMemento& memento);

		virtual void draw(sf::RenderWindow& window);
		virtual Shape* clone();

		void copy(Shape source);

		virtual std::string to_string();
		virtual bool from_string(std::string string);
		friend std::ostream& operator<<(std::ostream& os, Shape& s)
		{
			os << s.to_string();
			return os;
		}
		friend std::istream& operator>>(std::istream& is, Shape& s)
		{
			std::string tmp;
			is >> tmp;

			s.from_string(tmp);
			return is;
		}
	protected:
		ShapeType type;
		sf::Vector2f pos;
		sf::Color color;
	};
}