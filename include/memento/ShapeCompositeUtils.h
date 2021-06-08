#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

namespace lab4 {
	class IShape;
	class ShapeComposite;
	class ShapeCompositeMemento {
		friend class ShapeComposite;
		std::vector<IShape*> shapes;
	};
	class ShapeCompositeUtils {
	public:
		void save_state(ShapeComposite& composite);
		void load_state(ShapeComposite& composite);
		void save_to_file(std::string filename, ShapeComposite& composite);
		void load_from_file(std::string filename, ShapeComposite& composite);
	private:
		ShapeCompositeMemento memento;
	};
}