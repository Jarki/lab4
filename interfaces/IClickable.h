#pragma once

#include <SFML/Graphics.hpp>

namespace lab4 {
	class IClickable {
	public:
		virtual bool check(sf::Vector2f point) = 0;
	};
}