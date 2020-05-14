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
#include <vector>

#include "block.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#ifdef __BUILD_APPLICATION_OSX__
#include <CoreFoundation.framework/Versions/A/Headers/CoreFoundation.h>
#endif

void createTiles(sf::Texture* tile, std::vector<Piece>* pieceVec) {	
	short int shapenum = rand() % 7;
	Piece* ptr = new Piece(shapenum, pieceVec, tile);
	std::vector<Piece>::iterator it;
	it = (*pieceVec).begin();
	it = (*pieceVec).insert(it, *ptr);
	delete ptr;
}	


int main() {
	std::cout << "b-l-0-c-k-s Copyright (C) 2020 Justin BAX and Chris YANG\nThis program comes with ABSOLUTELY NO WARRANTY.\nThis is free software, and you are welcome to redistribute it under certain conditions.\nSee LICENSE for more details\n";
	std::cout << "If you see this text, do not close this window while the game is running.\n";
	srand(time(NULL));
	//create and render window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(640, 1280), "BLOCKS!", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	//load sounds
	sf::SoundBuffer bumpBuffer;
	sf::SoundBuffer clickBuffer;
	sf::SoundBuffer blockBuffer;
	//window icon
	sf::Image icon;
	//tile and grid textures
	sf::Texture tile[4];
	sf::Texture gridTexture;

	#ifdef __BUILD_APPLICATION_OSX__
		CFBundleRef mainBundle = CFBundleGetMainBundle();
		CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
		char path[512];
		if (!CFURLGetFileSystemRepresentation(resourcesURL, true, (UInt8*)path, 512)) {
			std::cerr << "Can't find resources path" << std::endl;
		}
		CFRelease(resourcesURL);
	#else
		std::string path = "content";
	#endif

	try {
		if (!clickBuffer.loadFromFile(std::string(path + std::string("/click.ogg")))) {
			throw 101;
		}
		if (!bumpBuffer.loadFromFile(std::string(path + std::string("/bump.ogg")))) {
			throw 102;
		}
		if (!blockBuffer.loadFromFile(std::string(path + std::string("/block.ogg")))) {
			throw 103;
		}
		if (!icon.loadFromFile(std::string(path + std::string("/icon.png")))) {
			throw 104;
		}
		if (!gridTexture.loadFromFile(std::string(path + std::string("/grid.png")))) {
			throw 105;
		}
		if (!tile[0].loadFromFile(std::string(path + std::string("/tiles/tile-01.png")))) {
			throw 106;
		}
		if (!tile[1].loadFromFile(std::string(path + std::string("/tiles/tile-02.png")))) {
			throw 107;
		}
		if (!tile[2].loadFromFile(std::string(path + std::string("/tiles/tile-03.png")))) {
			throw 108;
		}
		if (!tile[3].loadFromFile(std::string(path + std::string("/tiles/tile-04.png")))) {
			throw 109;
		}
	} catch (int i) {
		std::cerr << "Integer exception cought with value " << i << std::endl;
		std::cerr << "Exceptions 10X : can't load file content/**" << std::endl;
	}

	//create sounds and set buffers
	sf::Sound click;
	click.setBuffer(clickBuffer);
	sf::Sound bump;
	bump.setBuffer(bumpBuffer);
	sf::Sound block;
	block.setBuffer(blockBuffer);

	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	int changeX = 0;
	bool changeY = false;

	sf::Clock clock;

	std::vector<Piece> pieceVec;

	//create first tiles
	createTiles(&tile[rand() % 4], &pieceVec);

	//load grid
	sf::Sprite grid;
	grid.setTexture(gridTexture);
	grid.setScale(4, 4);
	grid.setPosition(sf::Vector2f(0, 0));
	grid.setColor(sf::Color(255, 255, 255, 32));

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
					changeX = -64;
				} else if (evnt.key.code == sf::Keyboard::S) {
					changeY = true;
				} else if (evnt.key.code == sf::Keyboard::D) {
					changeX = 64;
				} else if (evnt.key.code == sf::Keyboard::Space) {
					pieceVec[0].rotateClockwise(&pieceVec);
				} else if (evnt.key.code == sf::Keyboard::C) {
					pieceVec[0].rotateCounterClockwise(&pieceVec);
				}
			}
		}

		//after 1 sec
		sf::Time elapsed = clock.getElapsedTime();
		if (elapsed.asMilliseconds() >= 1000 or changeY) {
			//moves downwards
			for (int i = 0; i < 4; i++) {
				pieceVec[0].blocks[i].sprite.move(0, 64);
			}
			clock.restart();
			changeY = false;
		}

		sf::Vector2f position1 = pieceVec[0].blocks[0].sprite.getPosition();
		sf::Vector2f position2 = pieceVec[0].blocks[1].sprite.getPosition();
		sf::Vector2f position3 = pieceVec[0].blocks[2].sprite.getPosition();
		sf::Vector2f position4 = pieceVec[0].blocks[3].sprite.getPosition();
		for (int i = 1; i < pieceVec.size(); i++) {
			for (int j = 0; j < 4; j++) {
				if (pieceVec[i].blocks[j].exists and i != 0) {
					sf::Vector2f otherTilesPos = pieceVec[i].blocks[j].sprite.getPosition();
					//if tile spawns directly on other tile
					if (i != 0 and ((position1.y == otherTilesPos.y and position1.y == 0 and position1.x == otherTilesPos.x) or (position2.y == otherTilesPos.y and position2.y == 0 and position2.x == otherTilesPos.x) or (position3.y == otherTilesPos.y and position3.y == 0 and position3.x == otherTilesPos.x) or (position4.y == otherTilesPos.y and position4.y == 0 and position4.x == otherTilesPos.x))) {
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
						for (int k = 0; k < 4; k++) {
							pieceVec[0].blocks[k].sprite.move(0, -64);
						}
						createTiles(&tile[rand() % 4], &pieceVec);
						position1 = pieceVec[0].blocks[0].sprite.getPosition();
						position2 = pieceVec[0].blocks[1].sprite.getPosition();
						position3 = pieceVec[0].blocks[2].sprite.getPosition();
						position4 = pieceVec[0].blocks[3].sprite.getPosition();
					}
					
					//block movement on x axis if a tile is already there
					if ((position1.x + changeX == otherTilesPos.x and position1.y == otherTilesPos.y) or (position2.x + changeX == otherTilesPos.x and position2.y == otherTilesPos.y) or (position3.x + changeX == otherTilesPos.x and position3.y == otherTilesPos.y) or (position4.x + changeX == otherTilesPos.x and position4.y == otherTilesPos.y)) {
						if (!block.getStatus()) {
							block.play();
						}
						changeX = 0;
					}
				}
			}
		}

		//block movement on x axis if on border
		if ((position1.x == 0 and changeX < 0) or (position2.x == 0 and changeX < 0) or (position3.x == 0 and changeX < 0) or (position4.x == 0 and changeX < 0) or (position1.x == 576 and changeX > 0) or (position2.x == 576 and changeX > 0) or (position3.x == 576 and changeX > 0) or (position4.x == 576 and changeX > 0)) {
			if (!block.getStatus()) {
				block.play();
			}
			changeX = 0;
		}

		//if current tile touches bottom
		if (position1.y >= 1280 or position2.y >= 1280 or position3.y >= 1280 or position4.y >= 1280) {
			if (!bump.getStatus()) {
					bump.play();
				}
			for (int i = 0; i < 4; i++) {
				pieceVec[0].blocks[i].sprite.move(0, -64);
			}
			createTiles(&tile[rand() % 4], &pieceVec);
		}

		//move with keyboard entries
		for (int i = 0; i < 4; i++) {
			pieceVec[0].blocks[i].sprite.move(changeX, 0);
		}
		changeX = 0;

		//destroy completed line
		std::vector<int> spritesInRowNum;
		std::vector<int> spritesInRowPos;
		for (int i = 0; i < 20; i++) {
			for (int j = 1; j < pieceVec.size(); j++) {
				if (pieceVec[j].isInRow(i, &spritesInRowPos)) {
					spritesInRowNum.push_back(j);
				}
			}
			if (spritesInRowPos.size() == 10) {
				for (int j = 1; j < pieceVec.size(); j++) {
					for (int k = 0; k < 4; k++) {
						if (pieceVec[j].blocks[k].inRow and pieceVec[j].blocks[k].exists) {
							pieceVec[j].blocks[k].die();
						}
					}
				}
				for (int j = 0; j < pieceVec.size(); j++) {
					for (int k = 0; k < 4; k++) {
						if (pieceVec[j].blocks[k].sprite.getPosition().y < 64 * i and pieceVec[j].blocks[k].exists) {
							pieceVec[j].blocks[k].sprite.move(0, 64);
						}
					}
				}
			}
			spritesInRowNum.clear();
			spritesInRowPos.clear();
		}
		//window display
		window.clear(sf::Color::Black);
		for (int i = 0; i < pieceVec.size(); i++) {
			for (int j = 0; j < 4; j++) {
				if (pieceVec[i].blocks[j].exists) {
					window.draw(pieceVec[i].blocks[j].sprite);
				}
			}
		}
		window.draw(grid);
		window.display();
	}
	return 0;
}