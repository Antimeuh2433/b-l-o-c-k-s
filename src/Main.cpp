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

bool shapes[7][8] = {
	{true, true, true, false, false, true, false, false}, // T
	{true, true, true, false, false, false, true, false}, // J
	{true, true, true, false, true, false, false, false}, // L
	{false, true, true, false, false, true, true, false}, // O
	{true, true, false, false, false, true, true, false}, // Z
	{false, true, true, false, true, true, false, false}, // S
	{true, true, true, true, false, false, false, false} // I
};

//color vector
std::vector<sf::Color> colors = {sf::Color(128,0,128), sf::Color::Blue, sf::Color(255,165,0), sf::Color::Yellow, sf::Color::Red, sf::Color::Green, sf::Color::Cyan};

//sprite vector
std::vector<sf::Sprite> sprites;

//shape vector
std::vector<int> shapes_sprites;

//initialize tile texture
sf::Texture tile;

void createTiles(){
void createTiles() ;
	int shapenum = rand() % 7;
	shapes_sprites.push_back(shapenum);
	for (int i = 0; i < 8; i++) {
		if (shapes[shapenum][i]) {
			sprites.push_back(sf::Sprite(tile));
			sprites[sprites.size() - 1].setScale(2.f, 2.f);
			sprites[sprites.size() - 1].setColor(colors[shapenum]);
			if (i < 4) {
				sprites[sprites.size() - 1].setPosition(i * 32 + 96, 0);
			} else {
				sprites[sprites.size() - 1].setPosition((i - 4) * 32 + 96, 32);
			}
		}
	}
}

int main() {
	srand(time(NULL));
	//create and render window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(320, 640), "BLOCKS!", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	int changeX = 0;
	bool changeY = false;

	sf::Clock clock;

	//define tile texture
	if (!tile.loadFromFile("content/tile.png")) {
		std::cerr << "Can't load content/tile.png" << std::endl;
		return 0;
	}

	//create first tiles
	createTiles();

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
					changeY = true;
				} else if (event.key.code == sf::Keyboard::D) {
					changeX = 32;
				} else if (event.key.code == sf::Keyboard::Space or event.key.code == sf::Keyboard::W) {
					//rotate
					switch (shapes_sprites[shapes_sprites.size() - 1]) {

					}
				}
			}
		}
		//after 1 sec
		sf::Time elapsed = clock.getElapsedTime();
		if (elapsed.asMilliseconds() >= 1000 or changeY) {
			//moves downwards
			for (int i = 1; i <= 4; i++) {
				sprites[sprites.size() - i].move(0, 32);
			}
			clock.restart();
			changeY = false;
		}

		sf::Vector2f position1 = sprites[sprites.size() - 1].getPosition();
		sf::Vector2f position2 = sprites[sprites.size() - 2].getPosition();
		sf::Vector2f position3 = sprites[sprites.size() - 3].getPosition();
		sf::Vector2f position4 = sprites[sprites.size() - 4].getPosition();

		for (int i = 0; i < int(sprites.size() - 4); i++) {

			sf::Vector2f otherTilesPos = sprites[i].getPosition();

			//if tile spawns directly in other tile
			if ((position1.y == otherTilesPos.y and position1.y == 0 and position1.x == otherTilesPos.x) or (position2.y == otherTilesPos.y and position2.y == 0 and position2.x == otherTilesPos.x) or (position3.y == otherTilesPos.y and position3.y == 0 and position3.x == otherTilesPos.x) or (position4.y == otherTilesPos.y and position4.y == 0 and position4.x == otherTilesPos.x)) {
				std::cout << "Game over!";
				window.close();
				return 0;
			}

			//if current tile is on other tile
			if ((position1.y == otherTilesPos.y and position1.x == otherTilesPos.x) or (position2.y == otherTilesPos.y and position2.x == otherTilesPos.x) or (position3.y == otherTilesPos.y and position3.x == otherTilesPos.x) or (position4.y == otherTilesPos.y and position4.x == otherTilesPos.x)) {
				for (int i = 1; i < 5; i++) {
					sprites[sprites.size() - i].move(0, -32);
				}
				createTiles();
				position1 = sprites[sprites.size() - 1].getPosition();
				position2 = sprites[sprites.size() - 2].getPosition();
				position3 = sprites[sprites.size() - 3].getPosition();
				position4 = sprites[sprites.size() - 4].getPosition();
			}

			//block movement on x axis if a tile is already there
			if ((position1.x + changeX == otherTilesPos.x and position1.y == otherTilesPos.y) or (position2.x + changeX == otherTilesPos.x and position2.y == otherTilesPos.y) or (position3.x + changeX == otherTilesPos.x and position3.y == otherTilesPos.y) or (position4.x + changeX == otherTilesPos.x and position4.y == otherTilesPos.y)) {
				changeX = 0;
			}
		}

		//block movement on x axis if on border
		if ((position1.x == 0 and changeX < 0) or (position2.x == 0 and changeX < 0) or (position3.x == 0 and changeX < 0) or (position4.x == 0 and changeX < 0) or (position1.x == 288 and changeX > 0) or (position2.x == 288 and changeX > 0) or (position3.x == 288 and changeX > 0) or (position4.x == 288 and changeX > 0)) {
			changeX = 0;
		}

		//if current tile touches bottom
		if (position1.y >= 640 or position2.y >= 640 or position3.y >= 640 or position4.y >= 640) {
			for (int i = 0; i < 5; i++) {
				sprites[sprites.size() - i].move(0, -32);
			}
			createTiles();
		}

		//move with keyboard entries
		for (int i = 1; i < 5; i++) {
			sprites[sprites.size() - i].move(changeX, 0);
		}
		changeX = 0;

		//window display
		window.clear(sf::Color::Black);
		for (int i = 0; i < int(sprites.size()); i++) {
			window.draw(sprites[i]);
		}
		window.display();
	}
	return 0;
}
