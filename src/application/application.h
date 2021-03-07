#pragma once
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "../entity/camera/camera.h"
#include "../states/baseState.h"
#include "../renderer/mainRenderer.h"
#include "./context/context.h"

class Application
{
public:
	Application(const std::string& name);
	void runApp();
	template<typename T, typename... Args>
	void pushState(Args&&... args) {
		m_states.push_back(
			std::make_unique<T>(std::forward<Args>(args)...)
		);
		auto& s = m_states.back();
		s->onOpen();
	}
	void popState();
	Camera& getCamera();
	const sf::RenderWindow& getWindow() const;
	void turnOffMouse();
	void turnOnMouse();
private:
	void handleEvents();
	std::vector<std::unique_ptr<BaseState>> m_states;
	Context m_context;
	Camera m_camera;
	MainRenderer m_mainRenderer;
	bool m_shouldPopState = false;
};

