#include "playState.h"
#include "../../application/application.h"
#include "../../renderer/mainRenderer.h"
#include <type_traits>
#include "../../world/chunk/chunkMeshBuilder/chunkMeshBuillder.h"
#include "../../math/ray/ray.h"
#include "../../world/Block/BlockId.h"
#include <iostream>

PlayState::PlayState(Application& app): BaseState(app) {
	app.getCamera().hookEntity(m_player); // hooked the player into main camera entity in application
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
		if (block != 0) {
			if (timer.getElapsedTime().asSeconds() > 0.2) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					timer.restart();
					std::cout << "x: " << x << " z: " << z << std::endl;
					m_world.editBlock(x, y, z, BlockId::AIR);
					break;
				}
				else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
					std::cout << "restore" << std::endl;
					timer.restart();
					m_world.editBlock(lastPosition.x, lastPosition.y, lastPosition.z, BlockId::GRASS);
					break;
				}
			}
		}
		lastPosition = ray.getEnd();
	}
}
void PlayState::update(float deltaTime) {
	m_player.update(deltaTime);
}
void PlayState::render(MainRenderer& mainRenderer) {
	//mainRenderer.drawQuads({ 0,0,0 });
	//mainRenderer.drawCubes({ 0,0,0 });
	m_world.renderWorld(mainRenderer);
	mainRenderer.drawSky();
}
bool PlayState::isStateInitialized() const {
	return isStateInit;
}