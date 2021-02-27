#include "playState.h"
#include "../../application/application.h"
#include "../../renderer/mainRenderer.h"
#include <type_traits>
#include <iostream>

#include "../../world/chunk/chunkMeshBuilder/chunkMeshBuillder.h"

PlayState::PlayState(Application& app): BaseState(app) {
	app.getCamera().hookEntity(m_player); // hooked the player into main camera entity in application
	ChunkMeshBuillder builder(m_chunkSection);
	builder.buildMesh(m_chunkSection.m_chunkMesh);
	m_chunkSection.m_chunkMesh.bufferMesh();
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
	//mainRenderer.drawQuads({ 0,0,0 });
	//mainRenderer.drawCubes({ 0,0,0 });
	mainRenderer.drawChunk(m_chunkSection.m_chunkMesh);
}