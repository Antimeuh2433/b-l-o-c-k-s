// B-L-0-C-K-S - Proof of Concept block game inspired by Tetris
// Copyright (C) 2019  Justin BAX
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

           

#include <iostream>
#include "Main.hpp"

int main() {
	//render window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(640, 960), "test", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	sf::Clock clock;
	while (window.isOpen()) {
		//tile texture
		sf::Texture tileTexture;
		if (!tileTexture.loadFromFile("content/tile.png")) {
			std::cout << "Can't load file content/tile.png" << std::endl;
			window.close();
			return 0;
		}
		sf::Sprite tileSprite;
		tileSprite.setTexture(tileTexture);
		tileSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
		tileSprite.setScale(3, 3);
		tileSprite.setColor(sf::Color(255, 0, 0));
		tileSprite.setPosition(60, 45);

		sf::Texture frameTexture;
		if (!frameTexture.loadFromFile("content/frame.png")) {
			std::cout << "Can't load file content/frame.png" << std::endl;
			window.close();
			return 0;
		}
		sf::Sprite frameSprite;
		frameSprite.setTexture(frameTexture);
		frameSprite.setScale(sf::Vector2f(2.f, 2.f));
		frameSprite.setPosition(0, -30);

		//event handling
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			//key pressed event
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				} else if (event.key.code == sf::Keyboard::W) {
					std::cout << "W" << std::endl;
				}
			}
		}
		sf::Time elapsed = clock.getElapsedTime();
		if (elapsed.asMilliseconds() >= 1000) {


			clock.restart();
		}
		window.clear(sf::Color::Black);
		window.draw(tileSprite);
		window.draw(frameSprite);
		window.display();
	}
	return 0;
}
