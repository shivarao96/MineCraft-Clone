#include <iostream>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

int main() {

	std::cout << "Working !" << std::endl;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Window Testing !");
	sf::Event sfEvent;

	while (window.isOpen()) {
		while (window.pollEvent(sfEvent)) {
			if (sfEvent.type == sf::Event::Closed) {
				window.close();
			}
		}
	}
	return 0;
}