#include "playState.h"
#include "../../application/application.h"
#include "../../renderer/mainRenderer.h"
#include <type_traits>
#include <iostream>

PlayState::PlayState(Application& app): BaseState(app) {
	app.getCamera().hookEntity(m_player); // hooked the player into main camera entity in application
}
void PlayState::handleEvents(sf::Event& e) {

}
void PlayState::handleInputs() {
	m_player.handleInput(m_pApplication->getWindow());
}
void PlayState::update(float deltaTime) {
	m_player.update(deltaTime);
}
void PlayState::render(MainRenderer& mainRenderer) {
	mainRenderer.drawQuads({ 0,0,0 });
}