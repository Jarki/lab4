#pragma once

#include "../../include/memento/ShapeUtils.h"
#include "../../include/Shape.h"

namespace lab4 {
	void ShapeUtils::save_state(Shape& shape) {
		shape.set_memento(memento);
	}
	void ShapeUtils::load_state(Shape& shape) {
		shape.get_memento(memento);
	}
	void ShapeUtils::save_to_file(std::string filename, Shape& shape) {
		std::ofstream file(filename);
		file << shape;
		file.close();
	}
	void ShapeUtils::load_from_file(std::string filename, Shape& shape) {
		std::ifstream file(filename);
		file >> shape;
		file.close();
	}
}