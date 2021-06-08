#pragma once

#include "../../include/ShapeParser.h"
#include "../include/Shape.h"
#include "../include/Circle.h"
#include "../include/Rectangle.h"

namespace lab4 {
	std::string ShapeParser::get_first_word(std::string& source, std::string delimiter) {
		std::string res = source.substr(0, source.find(delimiter, 0));

		return res;
	}
	void ShapeParser::skip_word(std::string& source, std::string delimiter) {
		source = source.substr(source.find(delimiter, 0) + delimiter.length(), source.length() - source.find(delimiter, 0) - delimiter.length());
	}
	sf::Vector2f ShapeParser::get_vector_2f(std::string& source, std::string delimiter) {
		float x = std::stof(get_first_word(source, delimiter));
		skip_word(source, delimiter);

		float y = std::stof(get_first_word(source, delimiter));
		skip_word(source, delimiter);
		
		return sf::Vector2f(x, y);
	}
	sf::Color ShapeParser::get_color(std::string& source, std::string delimiter) {
		sf::Color c(std::stoul(get_first_word(source, delimiter)));
		skip_word(source, delimiter);
		return c;
	}
	float ShapeParser::get_float(std::string& source, std::string delimiter) {
		float f = std::stof(get_first_word(source, delimiter)); 
		skip_word(source, delimiter);
		return f;
	}

	ShapeType ShapeParser::determine_type(std::string &source, std::string delimiter) {
		if(source == "") return ShapeType::unknown;

		std::string type = get_first_word(source, delimiter);

		if (type == "Shape")
			return ShapeType::shape;
		if(type == "Circle")
			return ShapeType::circle;
		if (type == "Rectangle")
			return ShapeType::rectangle;

		
		return ShapeType::unknown;
	}
	Shape* ShapeParser::parse_shape(std::string& source, std::string delimiter) {
		if (determine_type(source, delimiter) != shape) return NULL;
		skip_word(source, delimiter);

		Shape* res = new Shape();

		res->set_position(get_vector_2f(source, delimiter));

		res->set_color(get_color(source, delimiter));

		return res;
	}
	Circle* ShapeParser::parse_circle(std::string& source, std::string delimiter) {
		if (determine_type(source, delimiter) != circle) return NULL;
		skip_word(source, delimiter);

		Circle* res = new Circle();

		res->set_position(get_vector_2f(source, delimiter));

		res->set_color(get_color(source, delimiter));

		res->set_radius(get_float(source, delimiter));
		return res;
	}
	Rectangle* ShapeParser::parse_rectangle(std::string& source, std::string delimiter) {
		if (determine_type(source, delimiter) != rectangle) return NULL;
		skip_word(source, delimiter);

		Rectangle* res = new Rectangle();

		res->set_position(get_vector_2f(source, delimiter));

		res->set_color(get_color(source, delimiter));

		res->set_size(get_vector_2f(source, delimiter));
		return res;
	}
}