#pragma once

#include "../../include/memento/ShapeCompositeUtils.h"
#include "../../include/composites/ShapeComposite.h"

namespace lab4 {
	void ShapeCompositeUtils::save_state(ShapeComposite& composite) {
		composite.set_memento(memento);
	}
	void ShapeCompositeUtils::load_state(ShapeComposite& composite) {
		composite.get_memento(memento);
	}
	void ShapeCompositeUtils::save_to_file(std::string filename, ShapeComposite& composite) {
		std::ofstream file(filename);
		file << composite.to_string();
		file.close();
	}
	void ShapeCompositeUtils::load_from_file(std::string filename, ShapeComposite& composite) {
		std::ifstream file(filename);

		std::stringstream strStream;
		strStream << file.rdbuf();
		std::string source = strStream.str();

		file >> source;
		file.close();

		composite.clear();
		composite.from_string(source);
	}
}