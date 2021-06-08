#pragma once

#include "../include/Circle.h"

namespace lab4 {
	Circle::Circle(sf::Vector2f _pos, sf::Color _color, float _r) : Shape(_pos, _color) {
		r = _r;

		update_position(_pos);
		update_color(_color);
		update_radius(_r);
	}

	ShapeType Circle::get_type() {
		return ShapeType::circle;
	}

	void Circle::update_position(sf::Vector2f _pos) {
		circle.setPosition(_pos);
	}

	bool Circle::check(sf::Vector2f point) {
		return circle.getGlobalBounds().contains(point);
	}

	void Circle::update_color(sf::Color _color) {
		circle.setFillColor(_color);
	}

	void Circle::update_radius(float _r) {
		circle.setRadius(r);
	}
	void Circle::set_radius(float _r){
		r = _r;

		update_radius(_r);
	}

	void Circle::set_memento(CircleMemento& memento) {
		memento.pos = pos;
		memento.color = color;
		memento.r = r;
	};
	void Circle::get_memento(const CircleMemento& memento) {
		pos = memento.pos;
		color = memento.color;
		r = memento.r;

		update_position(pos);
		update_color(color);
		update_radius(r);
	};

	void Circle::draw(sf::RenderWindow &window) {
		window.draw(circle);
	}
	Shape* Circle::clone() {
		return new Circle(pos, color, r);
	}

	void Circle::copy(Circle source) {
		set_position(source.pos);
		set_color(source.color);
		set_radius(source.r);
	}

	std::string Circle::to_string() {
		std::string res = "";
		res += "Circle" + STRING_DELIMITER;
		res += std::to_string(pos.x) + STRING_DELIMITER;
		res += std::to_string(pos.y) + STRING_DELIMITER;
		res += std::to_string(color.toInteger()) + STRING_DELIMITER;
		res += std::to_string(r) + STRING_DELIMITER;
		return res;
	}
	bool Circle::from_string(std::string string) {
		Circle tmp = *ShapeParser::parse_circle(string, STRING_DELIMITER);

		if (&tmp == NULL) return false;

		copy(tmp);
		return true;
	}
}