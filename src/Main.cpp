// B-L-0-C-K-S - Proof of Concept block game inspired by Tetris
// Copyright (C) 2019  Justin BAX
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

           

#include <iostream>
#include <vector>
#include "Main.hpp"

int main() {
	srand(time(NULL));
	//create and render window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(320, 640), "BLOCKS!", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	int changeX = 0;
	int changeY = 0;

	sf::Clock clock;

	//create color vector
	std::vector<sf::Color> colors = {sf::Color::White, sf::Color::Red, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta, sf::Color::Green, sf::Color::Cyan};

	//create sprite vector
	sf::Texture tileTexture;
	if (!tileTexture.loadFromFile("content/tile.png")) {
		std::cerr << "Can't open content/tile.png" << std::endl;
		return 0;
	}
	std::vector<sf::Sprite> sprites;

	//create first sprite
	sprites.push_back(sf::Sprite(tileTexture));
	sprites[0].setScale(2.f, 2.f);
	sprites[0].setColor(colors[rand() % 7]);
	sprites[0].setPosition(128, 0);


	while (window.isOpen()) {

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
				} else if (event.key.code == sf::Keyboard::A) {
					changeX = -32;
				} else if (event.key.code == sf::Keyboard::S) {
					changeY = 32;
				} else if (event.key.code == sf::Keyboard::D) {
					changeX = 32;
				}
			}
		}
		//after 1 sec
		sf::Time elapsed = clock.getElapsedTime();
		if (elapsed.asMilliseconds() >= 1000) {
			//moves downwards after 1 sec if possible
			sprites[sprites.size() - 1].move(0, 32);
			clock.restart();
		}

		sf::Vector2f position = sprites[sprites.size() - 1].getPosition();
		for (int i = 0; i < int(sprites.size()); i++) {
			//if current tile is in other tile
			sf::Vector2f otherTilesPos = sprites[i].getPosition();
			if (position.y + 32 == otherTilesPos.y and position.x == otherTilesPos.x) {
				//create next tile
				sprites.push_back(sf::Sprite(tileTexture));
				sprites[sprites.size() - 1].setScale(2.f, 2.f);
				sprites[sprites.size() - 1].setColor(colors[rand() % 7]);
				sprites[sprites.size() - 1].setPosition(128, 0);
			}

			//if tile spawns directly in other tile
			for (int i = 0; i < int(sprites.size() - 1); i++) {
				//if spawns on other tile
				sf::Vector2f otherTilePos = sprites[i].getPosition();
				if (position.y == otherTilePos.y and position.y == 0 and position.x == otherTilePos.x) {
					//game over
					std::cout << "Game over!";
					window.close();
					return 0;
				}
			}
		}
		//if current tile touches bottom
		if (position.y >= 586) {
			//create next tile
			sprites.push_back(sf::Sprite(tileTexture));
			sprites[sprites.size() - 1].setScale(2.f, 2.f);
			sprites[sprites.size() - 1].setColor(colors[rand() % 7]);
			sprites[sprites.size() - 1].setPosition(128, 0);
		}
		//block movement on x axis if a tile is already in place there
		for (int i = 0; i < int(sprites.size() - 1); i++) {
			sf::Vector2f otherTilePos = sprites[i].getPosition();
			if (position.x + changeX == otherTilePos.x and position.y == otherTilePos.y) {
				changeX = 0;
			}
		}
		//move with keyboard entries
		sprites[sprites.size() - 1].move(changeX, changeY);
		changeX = 0;
		changeY = 0;

		//window display
		window.clear(sf::Color::Black);
		for (int i = 0; i < int(sprites.size()); i++) {
			window.draw(sprites[i]);
		}
		window.display();
	}
	return 0;
}
