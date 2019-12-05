#include <iostream>
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

	sf::Texture tileTexture;
	if (!tileTexture.loadFromFile("content/tile.png")) {
		std::cerr << "Can't load file content/tile.png" << std::endl;
		window.close();
		return 0;
	}

	sf::Sprite tileSprite;
	tileSprite.setTexture(tileTexture);
	tileSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	tileSprite.setScale(2, 2);
	tileSprite.setColor(sf::Color(255, 0, 0));
	tileSprite.setPosition(60, 45);


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
				} else if (event.key.code == sf::Keyboard::W) {
					changeY = -32;
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


			clock.restart();
		}
		tileSprite.move(changeX, changeY);
		changeX = 0;
		changeY = 0;
		window.clear(sf::Color::Black);
		window.draw(tileSprite);
		window.display();
	}
	return 0;
}