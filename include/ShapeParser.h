#pragma once

#include "../interfaces/IShape.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace lab4 {
	class Shape;
	class Circle;
	class Rectangle;
	class ShapeParser {
	public:
		static ShapeType determine_type(std::string& source, std::string delimiter);
		static Shape* parse_shape(std::string& source, std::string delimiter);
		static Circle* parse_circle(std::string& source, std::string delimiter);
		static Rectangle* parse_rectangle(std::string& source, std::string delimiter);
	private:
		static std::string get_first_word(std::string &source, std::string delimiter);
		static void skip_word(std::string& source, std::string delimiter);
		static sf::Vector2f get_vector_2f(std::string& source, std::string delimiter);
		static sf::Color get_color(std::string& source, std::string delimiter);
		static float get_float(std::string& source, std::string delimiter);
		ShapeParser() {}
	};
}