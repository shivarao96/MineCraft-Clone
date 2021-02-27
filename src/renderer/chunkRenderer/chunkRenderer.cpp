#include "chunkRenderer.h"

#include "../../entity/camera/camera.h"
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
		const ChunkMesh& m = *mesh;
		m.getModel().bindVAO();
		glDrawElements(
			GL_TRIANGLES,
			m.getModel().getIndicesCount(),
			GL_UNSIGNED_INT,
			nullptr
		);
	}
	m_chunkMeshes.clear();

}