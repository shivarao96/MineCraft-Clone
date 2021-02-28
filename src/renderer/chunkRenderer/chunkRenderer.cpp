#include "chunkRenderer.h"

#include "../../entity/camera/camera.h"
#include "../../glActions/glFunctions.h"
#include "../../world/chunk/chunkMesh/chunkMesh.h"
#include "../../world/Block/blockDataBase/blockDataBase.h"

void ChunkRenderer::add(const ChunkMesh& mesh) {
	m_chunkMeshes.push_back(&mesh);
}
void ChunkRenderer::render(const Camera& camera) {
	glEnable(GL_CULL_FACE);
	m_chunkShader.useShader();
	BlockDataBase::get().m_textureAtlas.bindTexture();
	m_chunkShader.loadViewMatrix(camera.getViewMatrix());
	m_chunkShader.loadProjectionMatrix(camera.getProjectionMatrix());

	for (const ChunkMesh* mesh : m_chunkMeshes) {
		m_chunkShader.loadModelMatrix(glm::mat4(1.0f));
		const ChunkMesh& m = *mesh;
		m.getModel().bindVAO();		
		GlFunctions::drawElements(m.getModel().getIndicesCount());
	}
	m_chunkMeshes.clear();

}