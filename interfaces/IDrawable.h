#pragma once

#include <SFML/Graphics.hpp>

namespace lab4 {
	class IDrawable {
	public:
		virtual void draw(sf::RenderWindow& window) = 0;
	};
}