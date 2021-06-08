#pragma once

#include "../include/Rectangle.h"

namespace lab4 {
	Rectangle::Rectangle(sf::Vector2f _pos, sf::Color _color, sf::Vector2f _size) : Shape(_pos, _color) {
		size = _size;

		update_position(_pos);
		update_color(_color);
		update_size(_size);
	}

	ShapeType Rectangle::get_type() {
		return ShapeType::rectangle;
	}

	void Rectangle::update_position(sf::Vector2f _pos) {
		rect.setPosition(_pos);
	}

	bool Rectangle::check(sf::Vector2f point) {
		return rect.getGlobalBounds().contains(point);
	}

	void Rectangle::update_color(sf::Color _color) {
		rect.setFillColor(_color);
	}

	void Rectangle::update_size(sf::Vector2f _size) {
		rect.setSize(_size);
	}
	void Rectangle::set_size(sf::Vector2f _size) {
		size = _size;

		update_size(_size);
	}
	sf::Vector2f Rectangle::get_size() {
		return size;
	}

	void Rectangle::set_memento(RectangleMemento& memento) {
		memento.pos = pos;
		memento.color = color;
		memento.size = size;
	};
	void Rectangle::get_memento(const RectangleMemento& memento) {
		pos = memento.pos;
		color = memento.color;
		size = memento.size;

		update_position(pos);
		update_color(color);
		update_size(size);
	};

	void Rectangle::draw(sf::RenderWindow& window) {
		window.draw(rect);
	}
	Shape* Rectangle::clone() {
		return new Rectangle(pos, color, size);
	}

	void Rectangle::copy(Rectangle source) {
		set_position(source.pos);
		set_color(source.color);
		set_size(source.size);
	}

	std::string Rectangle::to_string() {
		std::string res = "";
		res += "Rectangle" + STRING_DELIMITER;
		res += std::to_string(pos.x) + STRING_DELIMITER;
		res += std::to_string(pos.y) + STRING_DELIMITER;
		res += std::to_string(color.toInteger()) + STRING_DELIMITER;
		res += std::to_string(size.x) + STRING_DELIMITER;
		res += std::to_string(size.y) + STRING_DELIMITER;
		return res;
	}
	bool Rectangle::from_string(std::string string) {
		Rectangle tmp = *ShapeParser::parse_rectangle(string, STRING_DELIMITER);

		if (&tmp == NULL) return false;

		copy(tmp);
		return true;
	}
}