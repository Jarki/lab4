#pragma once

#include "../include/Button.h"

namespace lab4 {
	Button::Button(sf::Vector2f pos, sf::Vector2f size, sf::Font& font) {
		status = ButtonStatus::shown;

		body.set_position(pos);
		body.set_size(size);

		text.setFont(font);

		body.set_color(sf::Color::White);
		text.setFillColor(sf::Color::Black);

		text.setString("Button");
		text.setCharacterSize(14);

		center_text();
	}
	Button::Button(sf::Vector2f pos, sf::Vector2f size, sf::Color bg_color, sf::Font& font, sf::Color text_color) {
		status = ButtonStatus::shown;

		body.set_position(pos);
		body.set_size(size);
		text.setFont(font);
		body.set_color(bg_color);

		text.setFillColor(text_color);

		text.setString("Button");
		text.setCharacterSize(16);

		center_text();
	}

	void Button::hide() {
		sf::Color c = body.get_color();
		c.a = 0;
		body.set_color(c);

		c = text.getFillColor();
		c.a = 0;
		text.setFillColor(c);
		status = ButtonStatus::hidden;
	}
	void Button::show() {
		sf::Color c = body.get_color();
		c.a = 255;
		body.set_color(c);

		c = text.getFillColor();
		c.a = 255;
		text.setFillColor(c);
		status = ButtonStatus::shown;
	}
	bool Button::is_hidden() {
		return status == ButtonStatus::hidden ? true : false;
	}

	bool Button::check(sf::Vector2f point) {
		if (is_hidden()) return false;

		return body.check(point);
	}

	void Button::set_position(sf::Vector2f pos) {
		body.set_position(pos);
	}
	sf::Vector2f Button::get_position() {
		return body.get_position();
	}

	void Button::set_body_size(sf::Vector2f size) {
		body.set_size(size);
	}
	sf::Vector2f Button::get_body_size() {
		return body.get_size();
	}

	void Button::set_body_color(sf::Color color) {
		body.set_color(color);
	}
	sf::Color Button::get_body_color() {
		return body.get_color();
	}

	void Button::set_font(sf::Font& font) {
		text.setFont(font);
	}

	void Button::set_text(std::string _text) {
		text.setString(_text);
		center_text();
	}
	std::string Button::get_text() {
		return text.getString();
	}

	void Button::set_text_color(sf::Color color) {
		text.setFillColor(color);
	}
	sf::Color Button::get_text_color() {
		return text.getFillColor();
	}

	void Button::draw(sf::RenderWindow& window) {
		body.draw(window);

		window.draw(text);
	}

	void Button::center_text() {
		std::string s = text.getString();
		
		int first_line_length = s.find("\n") == std::string::npos ? text.getString().getSize() : s.find("\n");
		
		int number_of_lines = 1;
		int pos = 0;
		std::string target = "\n";
		while ((pos = s.find(target, pos)) != std::string::npos) {
			++number_of_lines;
			pos += target.length();
		}

		float x = body.get_position().x + body.get_size().x / 2 - first_line_length * text.getCharacterSize() * 0.33f;
		float y = body.get_position().y + body.get_size().y / 2 - number_of_lines * text.getCharacterSize() * (float)(0.8);
		text.setPosition({x, y});
	}
}