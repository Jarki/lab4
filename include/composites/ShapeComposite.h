#pragma once

#include "../../interfaces/IShape.h"
#include "../../include/memento/ShapeCompositeUtils.h"
#include <iostream>
#include <sstream>

namespace lab4 {
	class ShapeComposite : public IShape {
	public:
		ShapeComposite();
		ShapeComposite(std::string _name);

		ShapeType get_type() override;

		ShapeComposite* get_parent();
		void set_parent(ShapeComposite* parent);

		std::string get_name();
		void set_name(std::string _name);
		ShapeComposite* get_by_name(std::string name);

		void add(IShape* shape);
		void remove(IShape* shape);

		void clear();

		bool check(sf::Vector2f point) override;
		IShape* get_by_position(sf::Vector2f point);

		void draw(sf::RenderWindow& window);

		void set_memento(ShapeCompositeMemento& memento);
		void get_memento(const ShapeCompositeMemento& memento);

		std::string to_string();
		bool from_string(std::string string);
	private:
		std::string name;
		std::vector<IShape*> shapes;

		bool check_name(std::string _name);
	};
}