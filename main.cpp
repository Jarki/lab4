#include <SFML/Graphics.hpp>
#include "include/SceneManager.h"

int main()
{
	sf::RenderWindow app(sf::VideoMode(1820, 860), "Lab4");

	lab4::SceneManager::get_instance()->load_font("SpaceMono-Regular.ttf");

	lab4::SceneManager::get_instance()->run(app);

	return 0;
}