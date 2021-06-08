#pragma once 

#include "../interfaces/IScene.h"
#include <SFML/Graphics.hpp>

namespace lab4 {
	class ShapeComposite;
	class SceneManager {
	public:
		static SceneManager* get_instance();

		void load_font(std::string path);

		bool run(sf::RenderWindow& window);
	private:
		SceneManager();
		sf::Font font;
		ShapeComposite* main_container;
	};
}