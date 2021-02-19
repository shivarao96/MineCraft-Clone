#pragma once
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <string>
#include "../entity/camera/camera.h"

class Application
{
public:
	Application(const std::string& name);
	void runApp();
	void pushState();
	void popState();
	Camera& getCamera();
	const sf::RenderWindow& getWindow() const;
private:
	void handleEvents();
	sf::RenderWindow m_window;
	Camera m_camera;
};

