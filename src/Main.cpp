#include <iostream>
#include <vector>
#include "Main.hpp"

int main() {
	srand(time(NULL));
	//create and render window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(640, 960), "BLOCKS!", sf::Style::Default, settings);
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
	sprites[0].setColor(colors[(rand() % 7) - 1]);


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
		//move downwards after 1sec
		sf::Time elapsed = clock.getElapsedTime();
		if (elapsed.asMilliseconds() >= 1000) {
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
				sprites[sprites.size() - 1].setColor(colors[(rand() % 7) - 1]);
			}
		}
		//if current tile touches bottom
		if (position.y >= 700) {
			//create next tile
			sprites.push_back(sf::Sprite(tileTexture));
			sprites[sprites.size() - 1].setScale(2.f, 2.f);
			sprites[sprites.size() - 1].setColor(colors[(rand() % 7) - 1]);
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