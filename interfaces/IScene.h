#pragma once 
#include <SFML/Graphics.hpp>

namespace lab4 {
	class IScene {
	public:
		virtual bool run(sf::RenderWindow& window) = 0;
	};
}