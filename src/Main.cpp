#include <iostream>
#include <vector>
#include "Main.hpp"

int main() {
	//render window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(640, 960), "BLOCKS!", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	int changeX = 0;
	int changeY = 0;

	sf::Clock clock;

	//create sprite vector
	sf::Texture tileTexture;
	if (!tileTexture.loadFromFile("content/tile.png")) {
		std::cerr << "Can't open content/tile.png" << std::endl;
		return 0;
	}
	std::vector<sf::Sprite> sprites;
	//create first sprite
	sprites.push_back(sf::Sprite(tileTexture));
	sprites[0].setColor(sf::Color::Red);
	sprites[0].setScale(2.f, 2.f);

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
		sf::Time elapsed = clock.getElapsedTime();
		if (elapsed.asMilliseconds() >= 1000) {
			sprites[sprites.size() - 1].move(0, 32);
			clock.restart();
		}
		sprites[sprites.size() - 1].move(changeX, changeY);
		changeX = 0;
		changeY = 0;
		window.clear(sf::Color::Black);
		window.draw(sprites[sprites.size() - 1]);
		window.display();
	}
	return 0;
}