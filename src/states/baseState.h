#pragma once
#include <SFML/Graphics.hpp>

class Application;
class MainRenderer;

class BaseState {
public:
	BaseState(Application& app):m_pApplication(&app) {}
	~BaseState()                                    = default;
	virtual void handleEvents(sf::Event& e)         = 0;
	virtual void handleInputs()                     = 0;
	virtual void update(float deltaTime)            = 0;
	virtual void render(MainRenderer& mainRenderer) = 0;
protected:
	Application* m_pApplication;
};