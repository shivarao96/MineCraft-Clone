#pragma once
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "../entity/camera/camera.h"
#include "../states/baseState.h"
#include "../renderer/mainRenderer.h"

class Application
{
public:
	Application(const std::string& name);
	void runApp();
	template<typename T, typename... Args>
	void pushState(Args&&... args);
	void popState();
	Camera& getCamera();
	const sf::RenderWindow& getWindow() const;
private:
	void handleEvents();
	sf::RenderWindow m_window;
	Camera m_camera;
	std::vector<std::unique_ptr<BaseState>> m_states;
	bool m_shouldPopState = false;
	MainRenderer m_mainRenderer;
};

