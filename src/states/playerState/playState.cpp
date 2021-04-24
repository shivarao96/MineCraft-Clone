#include "playState.h"
#include "../../application/application.h"
#include "../../renderer/mainRenderer.h"
#include <type_traits>
#include "../../world/chunk/chunkMeshBuilder/chunkMeshBuillder.h"
#include "../../math/ray/ray.h"
#include "../../world/Block/BlockId.h"
#include "../../renderer/mainRenderer.h"
#include "../../world/event/playerDigEvent/playerDigEvent.h"
#include <iostream>

PlayState::PlayState(Application& app): BaseState(app) {
	app.getCamera().hookEntity(m_player); // hooked the player into main camera entity in application
	
	// cross hair setup
	m_chTexture.loadFromFile("assets/textures/cross-hair.png");
	m_crossHair.setTexture(&m_chTexture);
	m_crossHair.setSize({ 25 ,25 });
	m_crossHair.setOrigin(
		m_crossHair.getGlobalBounds().width / 2, 
		m_crossHair.getGlobalBounds().height / 2
	);
	m_crossHair.setPosition(
		app.getWindow().getSize().x / 2,
		app.getWindow().getSize().y / 2
	);

	isStateInit = true;
}
void PlayState::handleEvents(sf::Event& e) {

}
void PlayState::handleInputs() {
	m_player.handleInput(m_pApplication->getWindow());
	static sf::Clock timer;
	glm::vec3 lastPosition;
	for (Ray ray(m_player.m_position, m_player.m_rotation); ray.getLength() < 6; ray.setStep(0.6)) {
		int x = ray.getEnd().x;
		int y = ray.getEnd().y;
		int z = ray.getEnd().z;
		auto block = m_world.getBlock(x, y, z);
		if (block != BlockId::AIR && block != BlockId::WATER) {
			if (timer.getElapsedTime().asSeconds() > 0.2) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					timer.restart();
					std::cout << "x: " << x << " z: " << z << std::endl;
					//m_world.setBlock(x, y, z, BlockId::AIR);
					m_world.addEvent<PlayerDigEvent>(sf::Mouse::Left, ray.getEnd(), m_player);
					break;
				}
				else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
					std::cout << "restore" << std::endl;
					timer.restart();
					//m_world.setBlock(lastPosition.x, lastPosition.y, lastPosition.z, BlockId::GRASS);
					m_world.addEvent<PlayerDigEvent>(sf::Mouse::Right, lastPosition, m_player);
					break;
				}
			}
		}
		lastPosition = ray.getEnd();
	}
}
void PlayState::update(float deltaTime) {
	//if (m_player.m_position.x < 0) m_player.m_position.x = 0;
	//if (m_player.m_position.z < 0) m_player.m_position.z = 0;

	m_fpsCounter.update();
	m_player.update(deltaTime, m_world);
	m_world.update(m_pApplication->getCamera());
}
void PlayState::render(MainRenderer& mainRenderer) {
	mainRenderer.drawSFMLObj(m_crossHair);
	m_world.renderWorld(mainRenderer, m_pApplication->getCamera());
	mainRenderer.drawSky();
	m_fpsCounter.renderFps(mainRenderer);
	m_player.draw(mainRenderer);
}
bool PlayState::isStateInitialized() const {
	return isStateInit;
}
void PlayState::onOpen() {
	m_pApplication->turnOffMouse();
}