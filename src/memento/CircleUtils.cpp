#pragma once

#include "../../include/memento/CircleUtils.h"
#include "../../include/Circle.h"

namespace lab4 {
	void CircleUtils::save_state(Circle& circle) {
		circle.set_memento(memento);
	}
	void CircleUtils::load_state(Circle& circle) {
		circle.get_memento(memento);
	}
	void CircleUtils::save_to_file(std::string filename, Circle& shape) {
		std::ofstream file(filename);
		file << shape;
		file.close();
	}
	void CircleUtils::load_from_file(std::string filename, Circle& shape) {
		std::ifstream file(filename);
		file >> shape;
		file.close();
	}
}