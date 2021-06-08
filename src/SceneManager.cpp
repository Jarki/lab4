#pragma once 

#include "../include/SceneManager.h"
#include "../include/memento/ShapeCompositeUtils.h"
#include "../include/memento/CircleUtils.h"
#include "../include/memento/RectangleUtils.h"
#include "../include/composites/ShapeComposite.h"
#include "../include/ShapeParser.h"
#include "../GUI/include/Button.h"
#include "../include/Circle.h"
#include <unordered_map>

namespace lab4 {
	SceneManager::SceneManager() {
		main_container = new ShapeComposite("MainContainer");
	}
	SceneManager* SceneManager::get_instance() {
		static SceneManager instance;

		return &instance;
	}
	void SceneManager::load_font(std::string path) {
		font.loadFromFile(path);
	}

	void set_temporary_color(IShape* s, sf::Color color);
	void remove_temporary_color(IShape* s);

	void show_shape_menu();
	void show_circle_menu();
	void show_rectangle_menu();
	void show_appropriate_buttons(IShape* s);

	void hide_shape_menu();
	void hide_circle_menu();
	void hide_rectangle_menu();
	void hide_appropriate_buttons(IShape* s);

	void update_status(std::string status, sf::RenderWindow& window);

	bool is_any_button_pressed(sf::Vector2f pos);

	static sf::Color HIGHLIGHT_COLOR(174, 213, 255);

	sf::Text status_bar;

	ShapeCompositeUtils composite_loader;
	ShapeUtils shape_loader;
	CircleUtils circle_loader;
	RectangleUtils rectangle_loader;

	std::vector<Button*> buttons;
	std::vector<Button*> shape_menu;
	std::vector<Button*> circle_menu;
	std::vector<Button*> rect_menu;

	Rectangle canvas;

	bool SceneManager::run(sf::RenderWindow& window) {
		sf::Event event;

		sf::Vector2f mouse_position;

		canvas.set_position({ 550, 0 });
		canvas.set_size({window.getSize().x - canvas.get_position().x, window.getSize().y - canvas.get_position().y});
		canvas.set_color(sf::Color::Black);

		status_bar.setCharacterSize(14);
		status_bar.setFont(font);
		status_bar.setFillColor(sf::Color::White);
		status_bar.setPosition({(float)window.getSize().x - 300, 0});
		
		Circle default_circle({ 200, 0 }, sf::Color::White, 40);
		Rectangle default_rectangle({ 200, 0 }, sf::Color::White, { 40, 40 });
		std::unordered_map<std::string, Shape*> default_shapes;
		
		default_shapes["circle"] = &default_circle;
		default_shapes["rectangle"] = &default_rectangle;
		//********Button declaration*********
		Button create_circle_buttton({ 50, 40 }, { 200, 40 }, font);
		create_circle_buttton.set_text("Create a circle");
		buttons.push_back(&create_circle_buttton);

		Button create_rectangle_button({ 50, 100 }, { 200, 40 }, font);
		create_rectangle_button.set_text("Create a rectangle");
		buttons.push_back(&create_rectangle_button);

		Button create_composite_button({ 50, 160 }, { 200, 40 }, font);
		create_composite_button.set_text("Create a composite");
		buttons.push_back(&create_composite_button);

		Button save_scene_button({ 50, (float)window.getSize().y - 60}, { 200, 40 }, font);
		save_scene_button.set_text("Save scene");
		buttons.push_back(&save_scene_button);

		Button load_scene_button({ 300, (float)window.getSize().y - 60 }, { 200, 40 }, font);
		load_scene_button.set_text("Load scene");
		buttons.push_back(&load_scene_button);

		Button save_composite_button({ 50, (float)window.getSize().y - 120 }, { 200, 40 }, font);
		save_composite_button.set_text("Save composite");
		buttons.push_back(&save_composite_button);

		Button load_composite_button({ 300, (float)window.getSize().y - 120 }, { 200, 40 }, font);
		load_composite_button.set_text("Load composite");
		buttons.push_back(&load_composite_button);

		Button change_position_button({ 300, 40 }, { 200, 40 }, font);
		change_position_button.set_text("Change position");
		buttons.push_back(&change_position_button);
		shape_menu.push_back(&change_position_button);
		change_position_button.hide();

		Button change_color_button({ 300, 100 }, { 200, 40 }, font);
		change_color_button.set_text("Change color");
		buttons.push_back(&change_color_button);
		shape_menu.push_back(&change_color_button);
		change_color_button.hide();

		Button remove_shape_button({ 300, 160 }, { 200, 40 }, font);
		remove_shape_button.set_text("Remove selected shape");
		buttons.push_back(&remove_shape_button);
		shape_menu.push_back(&remove_shape_button);
		remove_shape_button.hide();

		Button add_to_group_button({ 300, 220 }, { 200, 40 }, font);
		add_to_group_button.set_text("Add shape to a group");
		buttons.push_back(&add_to_group_button);
		shape_menu.push_back(&add_to_group_button);
		add_to_group_button.hide();

		Button change_radius_button({ 300, 280 }, { 200, 40 }, font);
		change_radius_button.set_text("Change radius of \nthe circle");
		buttons.push_back(&change_radius_button);
		circle_menu.push_back(&change_radius_button);
		change_radius_button.hide();

		Button change_rect_size_button({ 300, 280 }, { 200, 40 }, font);
		change_rect_size_button.set_text("Change size of the\n rect");
		buttons.push_back(&change_rect_size_button);
		rect_menu.push_back(&change_rect_size_button);
		change_rect_size_button.hide();

		//********Button declaration*********
		bool creating_circle = false;
		bool creating_rectangle = false;
		bool changing_position = false;

		IShape* selected_shape = NULL;
		IShape* click_target = NULL;

		while (window.isOpen())
		{
			while (window.pollEvent(event))
			{
				switch (event.type) {
				case sf::Event::Closed:
					window.close();
					return false;
					break;
				case sf::Event::MouseButtonPressed:
					mouse_position.x = (float)sf::Mouse::getPosition(window).x;
					mouse_position.y = (float)sf::Mouse::getPosition(window).y;

					if (creating_circle) {
						if (canvas.check(mouse_position)) {
							Circle* new_circle = dynamic_cast<Circle*>(default_shapes["circle"]->clone());
							new_circle->set_position(mouse_position);

							main_container->add(new_circle);

							creating_circle = false;
							update_status("Created a circle", window);
						}
						else
							update_status("Cannot create a circle there!", window);
					}
					else if (creating_rectangle) {
						if (canvas.check(mouse_position)) {
							Rectangle* new_rectangle = dynamic_cast<Rectangle*>(default_shapes["rectangle"]->clone());
							new_rectangle->set_position(mouse_position);

							main_container->add(new_rectangle);

							creating_rectangle = false;
							update_status("Created a rectangle", window);
						}
						else
							update_status("Cannot create a rectangle there!", window);
					}
					else if (changing_position) {
						if (canvas.check(mouse_position)) {
							Shape* s = dynamic_cast<Shape*>(selected_shape);

							remove_temporary_color(s);
							s->set_position(mouse_position);
							set_temporary_color(s, HIGHLIGHT_COLOR);

							changing_position = false;
						}
						else
							update_status("Cannot place a shape there!", window);
					}
					else {
						if (save_scene_button.check(mouse_position)) {
							std::cout << "Enter the name of the file to save to: ";
							std::string filename;

							std::cin >> filename;

							composite_loader.save_to_file(filename, *main_container);
						}
						if (load_scene_button.check(mouse_position)) {
							std::cout << "Enter the name of the file to load from: ";
							std::string filename;

							std::cin >> filename;

							composite_loader.load_from_file(filename, *main_container);
						}
						if (save_composite_button.check(mouse_position)) {
							std::cout << "Enter the composite name: ";

							std::string name;
							std::cin >> name;

							std::cout << "Enter the file name: ";

							std::string filename;
							std::cin >> filename;
							ShapeComposite* target = main_container->get_by_name(name);
							if (target != NULL) {
								composite_loader.save_to_file(filename, *target);
							}
							else
								std::cout << "Couldn't find a composite with that name\n";
						}
						if (load_composite_button.check(mouse_position)) {
							std::cout << "Enter the name of composite to load to: ";

							std::string name;
							std::cin >> name;

							std::cout << "Enter the file name: ";

							std::string filename;
							std::cin >> filename;
							ShapeComposite* target = main_container->get_by_name(name);
							if (target != NULL) {
								ShapeComposite* loaded = new ShapeComposite(); 
								composite_loader.load_from_file(filename, *loaded);

								target->add(loaded);
							}
							else
								std::cout << "Couldn't find a composite with that name\n";
						}

						if (create_circle_buttton.check(mouse_position)) creating_circle = true;
						if (create_rectangle_button.check(mouse_position)) creating_rectangle = true;
						if (create_composite_button.check(mouse_position)) {
							std::cout << "Enter the composite's name:";
							std::string name;
							std::cin >> name;

							std::cout << "Enter parent composite's name:";
							std::string parent_name;
							std::cin >> parent_name;
							ShapeComposite* parent = main_container->get_by_name(parent_name);
							if (parent != NULL) {
								parent->add(new ShapeComposite(name));
							}
							else
								std::cout << "Couldn't find a composite with that name\n";
						}
						if (change_position_button.check(mouse_position)) changing_position = true;
						if (change_color_button.check(mouse_position)) {
							int new_values[3];
							std::cout << "Enter the new r, g, b values: ";

							for (int i = 0; i < 3; i++) {
								int value;
								std::cin >> value;
								new_values[i] = value;
							}

							sf::Color new_color(new_values[0], new_values[1], new_values[2]);

							Shape* s = dynamic_cast<Shape*>(selected_shape);

							remove_temporary_color(s);
							s->set_color(new_color);
							set_temporary_color(s, HIGHLIGHT_COLOR);
						}
						if (remove_shape_button.check(mouse_position)) {
							main_container->remove(selected_shape);
						}
						if (add_to_group_button.check(mouse_position)) {
							std::cout << "Enter the group's name: ";

							std::string name;
							std::cin >> name;
							ShapeComposite* target = main_container->get_by_name(name);
							if (target != NULL) {
								ShapeComposite* parent = selected_shape->get_parent();

								target->add(selected_shape);
								parent->remove(selected_shape);
								update_status("Parent: " + selected_shape->get_parent()->get_name(), window);
							}
							else
								std::cout << "Couldn't find a composite with that name\n";

						}
						if (change_radius_button.check(mouse_position)) {
							int new_radius;

							std::cout << "Enter new radius: ";
							std::cin >> new_radius;

							Circle* tmp = dynamic_cast<Circle*>(selected_shape);

							remove_temporary_color(tmp);
							tmp->set_radius(new_radius);
							set_temporary_color(tmp, HIGHLIGHT_COLOR);
						}
						if (change_rect_size_button.check(mouse_position)) {
							float x, y;

							std::cout << "Enter new x an y: ";
							std::cin >> x;
							std::cin >> y;

							Rectangle* tmp = dynamic_cast<Rectangle*>(selected_shape);

							remove_temporary_color(tmp);
							tmp->set_size({ x, y });
							set_temporary_color(tmp, HIGHLIGHT_COLOR);
						}

						click_target = main_container->get_by_position(mouse_position);

						if (click_target->get_type() != ShapeType::unknown) {
							if (selected_shape == NULL) {
								selected_shape = click_target;
								show_appropriate_buttons(selected_shape);

								update_status("Parent: " + selected_shape->get_parent()->get_name(), window);

								set_temporary_color(selected_shape, HIGHLIGHT_COLOR);
							}
							else{
								if (selected_shape != click_target) {
									hide_appropriate_buttons(selected_shape);
									remove_temporary_color(selected_shape);

									selected_shape = click_target;

									update_status("Parent: " + selected_shape->get_parent()->get_name(), window);

									show_appropriate_buttons(selected_shape);
									set_temporary_color(selected_shape, HIGHLIGHT_COLOR);
								}
							}
						}
						else {
							if (selected_shape != NULL) {
								if (!is_any_button_pressed(mouse_position)) {
									hide_appropriate_buttons(selected_shape);
									remove_temporary_color(selected_shape);
									
									update_status("Click on a shape to select it", window);

									selected_shape = NULL;
								}
							}
						}
					}
				}
			}

			window.clear();
			canvas.draw(window);
			main_container->draw(window);

			for (std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
				Button* tmp = *it;
				tmp->draw(window);
			}
			window.draw(status_bar);
			window.display();
		}
		return true;
	}
	void show_shape_menu() {
		for(std::vector<Button*>::iterator it = shape_menu.begin(); it != shape_menu.end(); ++it)
		{
			Button* tmp = *it;
			tmp->show();
		}
	}
	void show_circle_menu() {
		show_shape_menu();
		for (std::vector<Button*>::iterator it = circle_menu.begin(); it != circle_menu.end(); ++it)
		{
			Button* tmp = *it;
			tmp->show();
		}
	}
	void show_rectangle_menu() {
		show_shape_menu();
		for (std::vector<Button*>::iterator it = rect_menu.begin(); it != rect_menu.end(); ++it)
		{
			Button* tmp = *it;
			tmp->show();
		}
	}
	void show_appropriate_buttons(IShape* s) {
		ShapeType type = s->get_type();

		switch (type)
		{
		case lab4::unknown:
			break;
		case lab4::shape:
			show_shape_menu();
			break;
		case lab4::circle:
			show_circle_menu();
			break;
		case lab4::rectangle:
			show_rectangle_menu();
			break;
		case lab4::shape_composite:
			break;
		default:
			break;
		}
	}
	void hide_shape_menu() {
		for (std::vector<Button*>::iterator it = shape_menu.begin(); it != shape_menu.end(); ++it)
		{
			Button* tmp = *it;
			tmp->hide();
		}
	}
	void hide_circle_menu() {
		hide_shape_menu();
		for (std::vector<Button*>::iterator it = circle_menu.begin(); it != circle_menu.end(); ++it)
		{
			Button* tmp = *it;
			tmp->hide();
		}
	}
	void hide_rectangle_menu() {
		hide_shape_menu();
		for (std::vector<Button*>::iterator it = rect_menu.begin(); it != rect_menu.end(); ++it)
		{
			Button* tmp = *it;
			tmp->hide();
		}
	}
	void hide_appropriate_buttons(IShape* s) {
		ShapeType type = s->get_type();

		switch (type)
		{
		case lab4::unknown:
			break;
		case lab4::shape:
			hide_shape_menu();
			break;
		case lab4::circle:
			hide_circle_menu();
			break;
		case lab4::rectangle:
			hide_rectangle_menu();
			break;
		case lab4::shape_composite:
			break;
		default:
			break;
		}
	}

	void update_status(std::string status, sf::RenderWindow& window) {
		status_bar.setString(status);
		status_bar.setPosition({ (float)window.getSize().x - status_bar.getString().getSize() * status_bar.getCharacterSize() / 9 * 6, 0 });
	}

	bool is_any_button_pressed(sf::Vector2f pos) {
		for (std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
			Button* tmp = *it;
			if (tmp->check(pos)) return true;
		}
		return false;
	}

	void set_temporary_color(IShape* s, sf::Color color) {
		if (s == NULL) return;

		Shape* subject = dynamic_cast<Shape*>(s);
		shape_loader.save_state(*subject);
		subject->set_color(color);
	}
	void remove_temporary_color(IShape* s) {
		if (s == NULL) return;

		Shape* subject = dynamic_cast<Shape*>(s);
		shape_loader.load_state(*subject);
	}
}