#pragma once
#include "../../include/composites/ShapeComposite.h"
#include "../../include/Circle.h"
#include "../../include/Rectangle.h"

namespace lab4 {
	bool ShapeComposite::check_name(std::string _name) {
		if (_name == "") return false;

		if (_name.find("\n") != std::string::npos) return false;

		if (_name == "ShapeComposite") return false;

		if (_name == "ShapeCompositeEnd") return false;

		return true;
	}

	ShapeComposite::ShapeComposite() {
		set_name("DefaultComposite");
	}
	ShapeComposite::ShapeComposite(std::string _name){
		set_name(_name);
	}
	ShapeType ShapeComposite::get_type() {
		return ShapeType::shape_composite;
	}

	ShapeComposite* ShapeComposite::get_parent() {
		return parent;
	}
	void ShapeComposite::set_parent(ShapeComposite* _parent) {
		parent = _parent;
	}

	std::string ShapeComposite::get_name() {
		return name;
	}
	void ShapeComposite::set_name(std::string _name) {
		if(check_name(_name)) name = _name;
	}
	ShapeComposite* ShapeComposite::get_by_name(std::string name) {
		if (this->get_name() == name) return this;
		
		for (std::vector<IShape*>::iterator it = shapes.begin(); it != shapes.end(); ++it) {
			IShape* tmp = *it;

			if (tmp->get_type() == shape_composite) {
				ShapeComposite* c = dynamic_cast<ShapeComposite*>(tmp);
				return c->get_by_name(name);
			}
		}

		return NULL;
	}

	void ShapeComposite::add(IShape* shape) {
		shape->set_parent(this);
		shapes.push_back(shape);
	}
	void ShapeComposite::remove(IShape* shape) {
		int orig_size = shapes.size();
		shapes.erase(std::remove(shapes.begin(), shapes.end(), shape), shapes.end());

		if(shapes.size() == orig_size)
			for (std::vector<IShape*>::iterator it = shapes.begin(); it != shapes.end(); ++it) {
				IShape* tmp = *it;

				if (tmp->get_type() == shape_composite) {
					ShapeComposite* c = dynamic_cast<ShapeComposite*>(tmp);
					c->remove(shape);
				}
			}
	}

	void ShapeComposite::clear() {
		shapes.clear();
	}

	bool ShapeComposite::check(sf::Vector2f point) {
		for (auto& it : shapes) {
			if (it->check(point)) return true;
		}

		return false;
	}
	IShape* ShapeComposite::get_by_position(sf::Vector2f point) {
		for (std::vector<IShape*>::reverse_iterator it = shapes.rbegin(); it != shapes.rend(); ++it) {
			IShape* tmp = *it;
			if (tmp->check(point)) {
				if (tmp->get_type() == ShapeType::shape_composite) {
					ShapeComposite* c = dynamic_cast<ShapeComposite*>(tmp);
					return c->get_by_position(point);
				}
				else
					return tmp;
			}
		}
		Shape* not_found = new Shape();
		not_found->make_unknown();
		return not_found;
	}

	void ShapeComposite::draw(sf::RenderWindow& window) {
		for (auto& it : shapes) {
			it->draw(window);
		}
	}

	void ShapeComposite::set_memento(ShapeCompositeMemento& memento) {
		memento.shapes = std::vector<IShape*>(shapes);
	}
	void ShapeComposite::get_memento(const ShapeCompositeMemento& memento) {
		shapes = std::vector<IShape*>(memento.shapes);
	}

	std::string ShapeComposite::to_string() {
		std::string res = "";
		res += "ShapeComposite\n";
		res += get_name() + "\n";

		for (std::vector<IShape*>::iterator it = shapes.begin(); it != shapes.end(); ++it) {
			IShape* tmp = *it;
			res += tmp->to_string() + "\n";
		}
		res += "ShapeCompositeEnd";

		return res;
	}

	bool ShapeComposite::from_string(std::string string) {
		std::istringstream source(string);

		std::string current_string;

		std::getline(source, current_string);
		if (current_string != "ShapeComposite")
			return false;

		std::getline(source, current_string);
		set_name(current_string);

		IShape* tmp;
		ShapeType current_type;
		while (std::getline(source, current_string)) {
			if (current_string == "ShapeComposite") {
				int offset = 1;
				std::string res;

				int i = 0;
				while (current_string != "ShapeCompositeEnd" || offset != 0) {
					res += current_string + "\n";
					std::getline(source, current_string);

					if (current_string == "ShapeComposite")
						offset++;
					if (current_string == "ShapeCompositeEnd")
						offset--;
				}
				ShapeComposite* sc = new ShapeComposite;
				sc->from_string(res);

				add(sc);
			}
			else {
				current_type = ShapeParser::determine_type(current_string, STRING_DELIMITER);

				switch (current_type) {
				case shape:
					tmp = new Shape();
					break;
				case circle:
					tmp = new Circle();
					break;
				case rectangle:
					tmp = new Rectangle();
					break;
				case shape_composite:
					tmp = new ShapeComposite();
					break;
				case unknown:
					return false;
					break;
				default:
					return false;
					break;
				}

				tmp->from_string(current_string);
				add(tmp);
			}
		}

		return true;
	}

}