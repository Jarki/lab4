#pragma once

#include "../include/Shape.h"

namespace lab4 {
	Shape::Shape() {
		type = ShapeType::shape;
		parent = NULL;
	}
	Shape::Shape(sf::Vector2f _pos, sf::Color _color) {
		pos = _pos;
		color = _color;

		type = ShapeType::shape;

		update_position(_pos);
		update_color(_color);
	}

	ShapeType Shape::get_type() {
		return type;
	}
	void Shape::make_unknown() {
		type = ShapeType::unknown;
	}

	ShapeComposite* Shape::get_parent() {
		return parent;
	}	
	void Shape::set_parent(ShapeComposite* _parent) {
		parent = _parent;
	}

	void Shape::update_position(sf::Vector2f _pos) { }
	void Shape::set_position(sf::Vector2f _pos) {
		pos = _pos;
		update_position(_pos);
	}
	sf::Vector2f Shape::get_position() {
		return pos;
	}

	bool Shape::check(sf::Vector2f point) {
		return false;
	}

	void Shape::update_color(sf::Color _color) {}
	void Shape::set_color(sf::Color _color) {
		color = _color;
		update_color(_color);
	}
	sf::Color Shape::get_color() {
		return color;
	}

	void Shape::set_memento(ShapeMemento& memento) {
		memento.pos = pos;
		memento.color = color;
	};
	void Shape::get_memento(const ShapeMemento& memento) {
		pos = memento.pos;
		color = memento.color;

		update_position(pos);
		update_color(color);
	};

	void Shape::draw(sf::RenderWindow& window) {
	}
	Shape* Shape::clone() {
		return new Shape(pos, color);
	}

	void Shape::copy(Shape source) {
		pos = source.pos;
		color = source.color;
	}

	std::string Shape::to_string() {
		std::string res = "";

		//result string in format: type%%pos.x%%pos.y%%color%%type-specific_stuff (Since STRING_DELIMITER = "%%")
		res += "Shape" + STRING_DELIMITER;
		res += std::to_string(pos.x) + STRING_DELIMITER;
		res += std::to_string(pos.y) + STRING_DELIMITER;
		res += std::to_string(color.toInteger()) + STRING_DELIMITER;
		return res;
	}
	bool Shape::from_string(std::string string) {
		Shape tmp = *ShapeParser::parse_shape(string, STRING_DELIMITER);
		
		if (&tmp == NULL) return false;

		copy(tmp);

		return true;
	}
}