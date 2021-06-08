#pragma once

#include "../../include/memento/RectangleUtils.h"
#include "../../include/Rectangle.h"

namespace lab4 {
	void RectangleUtils::save_state(Rectangle& rect) {
		rect.set_memento(memento);
	}
	void RectangleUtils::load_state(Rectangle& rect) {
		rect.get_memento(memento);
	}
	void RectangleUtils::save_to_file(std::string filename, Rectangle& shape) {
		std::ofstream file(filename);
		file << shape;
		file.close();
	}
	void RectangleUtils::load_from_file(std::string filename, Rectangle& shape) {
		std::ifstream file(filename);
		file >> shape;
		file.close();
	}
}