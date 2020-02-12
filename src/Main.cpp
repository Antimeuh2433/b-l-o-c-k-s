#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
  std::cout << "henlo" << std::endl;
  sf::RenderWindow window(sf::VideoMode(100, 100), "test");
  while (window.isOpen()) {
    sf::Event evnt;
    while (window.pollEvent(evnt)) {
      if (evnt.type == sf::Event::Closed) {
        window.close();
      }
    }
  }
  return 0;
}