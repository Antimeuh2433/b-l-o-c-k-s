// B-L-0-C-K-S - Proof of Concept block game inspired by Tetris
// Copyright (C) 2020  Justin BAX and Chris YANG
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
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

bool shapes[7][8] = {	
	{false, true, false, false, true, true, true, false}, // T
	{false, false, true, false, true, true, true, false}, // L
	{true, false, false, false, true, true, true, false}, // J
	{false, true, true, false, false, true, true, false}, // O
	{true, true, false, false, false, true, true, false}, // Z
	{false, true, true, false, true, true, false, false}, // S
	{true, true, true, true, false, false, false, false} // I
};	

//color vector	
std::vector<sf::Color> colors = {sf::Color(128,0,128), sf::Color(255,165,0), sf::Color::Blue,sf::Color::Yellow, sf::Color::Red, sf::Color::Green, sf::Color::Cyan};	

//sprite vector	
std::vector<sf::Sprite> sprites;	

//shape vector	
std::vector<short int> shapes_sprites;	

//initialize tile texture	
sf::Texture tile;	

//initialize sound buffers
sf::SoundBuffer bumpBuffer;
sf::SoundBuffer clickBuffer;
sf::SoundBuffer blockBuffer;

//special state value for I rotation
short int state;

void rotate() {	
	if (shapes_sprites[shapes_sprites.size() - 1] == 3) {
		//case O
		return;
	}
	sf::Vector2f center;	
	if (shapes_sprites[shapes_sprites.size() - 1] == 0 or shapes_sprites[shapes_sprites.size() - 1] == 1 or shapes_sprites[shapes_sprites.size() - 1] == 2 or shapes_sprites[shapes_sprites.size() - 1] == 4) {	
		//case T, J, L, Z	
		center = sprites[sprites.size() - 2].getPosition();	
	} else if (shapes_sprites[shapes_sprites.size() - 1] == 5) {	
		//case S	
		center = sprites[sprites.size() - 1].getPosition();	
	} else if (shapes_sprites[shapes_sprites.size() - 1] == 6) {	
		//case I	
		center = sf::Vector2f(sprites[sprites.size() - 2].getPosition().x - 16, sprites[sprites.size() - 2].getPosition().y - 16);
		switch (state) {
			case 0:
				center.y += 32;
				break;
			case 1:
				break;
			case 2:
				center.x += 32;
				break;
			case 3:
				center.x += 32;
				center.y += 32;
				break;
		}
	}	
	sf::Vector2f currentPos, otherTilePos;	
	bool canRotate = true;	
	int newX[4], newY[4];	
	for (int i = 1; i < 5; i++) {	
		currentPos = sprites[sprites.size() - i].getPosition();	
		newX[i - 1] = center.x - (currentPos.y - center.y);	
		newY[i - 1] = center.y + (currentPos.x - center.x);	
		for (int i = 0; i < int(sprites.size() - 5); i++) {	
			otherTilePos = sprites[i].getPosition();	
			if (otherTilePos.x == currentPos.x and otherTilePos.y == currentPos.y) {	
				canRotate = false;	
				break;	
			}	
		}	
	}	
	if (canRotate) {	
		state++;
		if (state == 4) {
			state = 0;
		}
		for (int i = 1; i < 5; i++) {	
			sprites[sprites.size() - i].setPosition(newX[i - 1], newY[i - 1]);	
		}	
	}	
}	

void createTiles() {	
	state = 0;
	int shapenum = (rand() % 7);	
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
	std::cout << "b-l-0-c-k-s Copyright (C) 2020 Justin BAX and Chris YANG\nThis program comes with ABSOLUTELY NO WARRANTY.\nThis is free software, and you are welcome to redistribute it under certain conditions.\nSee LICENSE for more details\n";
	std::cout << "If you see this text, do not close this window while the game is running.\n";
	srand(time(NULL));
	//create and render window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(320, 640), "BLOCKS!", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	//load sounds
	if (!clickBuffer.loadFromFile("content/click.ogg")) {
		std::cerr << "Can't load content/click.ogg" << std::endl;
	}
	if (!bumpBuffer.loadFromFile("content/bump.ogg")) {
		std::cerr << "Can't load content/bump.ogg" << std::endl;
	}
	if (!blockBuffer.loadFromFile("content/block.ogg")) {
		std::cerr << "Can't load content/block.ogg" << std::endl;
	}

	//create sounds and set buffers
	sf::Sound click;
	click.setBuffer(clickBuffer);
	sf::Sound bump;
	bump.setBuffer(bumpBuffer);
	sf::Sound block;
	block.setBuffer(blockBuffer);

	//set window icon
	sf::Image icon;
	if (!icon.loadFromFile("content/icon.png")) {
		std::cerr << "Can't load content/icon.png" << std::endl;
	}
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

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
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed) {
				window.close();
			}
			//key pressed event
			else if (evnt.type == sf::Event::KeyPressed) {
				if (evnt.key.code == sf::Keyboard::Escape) {
					window.close();
				} else if (evnt.key.code == sf::Keyboard::A) {
					changeX = -32;
				} else if (evnt.key.code == sf::Keyboard::S) {
					changeY = true;
				} else if (evnt.key.code == sf::Keyboard::D) {
					changeX = 32;
				} else if (evnt.key.code == sf::Keyboard::Space or evnt.key.code == sf::Keyboard::W) {
					//rotate
					rotate();
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
				if (!bump.getStatus()) {
					bump.play();
				}
				std::cout << "Game over!" << std::endl;
				window.close();
				return 0;
			}

			//if current tile is on other tile
			if ((position1.y == otherTilesPos.y and position1.x == otherTilesPos.x) or (position2.y == otherTilesPos.y and position2.x == otherTilesPos.x) or (position3.y == otherTilesPos.y and position3.x == otherTilesPos.x) or (position4.y == otherTilesPos.y and position4.x == otherTilesPos.x)) {
				if (!bump.getStatus()) {
					bump.play();
				}
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
				if (!block.getStatus()) {
					block.play();
				}
				changeX = 0;
			}
		}

		//block movement on x axis if on border
		if ((position1.x == 0 and changeX < 0) or (position2.x == 0 and changeX < 0) or (position3.x == 0 and changeX < 0) or (position4.x == 0 and changeX < 0) or (position1.x == 288 and changeX > 0) or (position2.x == 288 and changeX > 0) or (position3.x == 288 and changeX > 0) or (position4.x == 288 and changeX > 0)) {
			if (!block.getStatus()) {
					block.play();
				}
			changeX = 0;
		}

		//if current tile touches bottom
		if (position1.y >= 640 or position2.y >= 640 or position3.y >= 640 or position4.y >= 640) {
			if (!bump.getStatus()) {
					bump.play();
				}
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

		//destroy completed line
		std::vector<int> spritesInRow;
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < int(sprites.size()); j++) {
				if (sprites[j].getPosition().y == 32 * i) {
					spritesInRow.push_back(j);
				}
			}
			if (spritesInRow.size() == 10) {
				for (int a = 0; a < 10; a++) {
					sprites[int(spritesInRow[a])].setOrigin(2, 2);
				}
				int spritesSize = int(sprites.size());
				for (int b = 0; b < spritesSize; b++) {
					if (sprites[b].getOrigin() == sf::Vector2f(2, 2)) {
						sprites.erase(sprites.begin() + b);
						spritesSize--;
						b--;
					}
				}
				for (int c = 0; c < spritesSize; c++) {
					sprites[c].setOrigin(0, 0);
					if (sprites[c].getPosition().y < 32 * i) {
						sprites[c].move(0, 32);
					}
				}
				createTiles();
			}
			spritesInRow.clear();
		}

		//window display
		window.clear(sf::Color::Black);
		for (int i = 0; i < int(sprites.size()); i++) {
			window.draw(sprites[i]);
		}
		window.display();
	}
	return 0;
}