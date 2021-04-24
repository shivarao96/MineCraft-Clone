#include "frustum.h"

float Plane::distanceToPoint(const glm::vec3& point) const {
	return glm::dot(point, normal) + distanceToOrigin; // to know how this came up follow this video: https://www.youtube.com/watch?v=4p-E_31XOPM
}

void Frustum::update(const glm::mat4& projViewMatrix) {
	/**
	* Follow following paper to know more about extraction of viewing frustum planes from the view-projection matrix
	* https://www.gamedevs.org/uploads/fast-extraction-viewing-frustum-planes-from-world-view-projection-matrix.pdf
	*
		// Left clipping plane
		 p_planes[0].a = comboMatrix._41 + comboMatrix._11;
		 p_planes[0].b = comboMatrix._42 + comboMatrix._12;
		 p_planes[0].c = comboMatrix._43 + comboMatrix._13;
		 p_planes[0].d = comboMatrix._44 + comboMatrix._14;
		 // Right clipping plane
		 p_planes[1].a = comboMatrix._41 - comboMatrix._11;
		 p_planes[1].b = comboMatrix._42 - comboMatrix._12;
		 p_planes[1].c = comboMatrix._43 - comboMatrix._13;
		 p_planes[1].d = comboMatrix._44 - comboMatrix._14;
		 // Top clipping plane
		 p_planes[2].a = comboMatrix._41 - comboMatrix._21;
		 p_planes[2].b = comboMatrix._42 - comboMatrix._22;
		 p_planes[2].c = comboMatrix._43 - comboMatrix._23;
		 p_planes[2].d = comboMatrix._44 - comboMatrix._24;
		 // Bottom clipping plane
		 p_planes[3].a = comboMatrix._41 + comboMatrix._21;
		 p_planes[3].b = comboMatrix._42 + comboMatrix._22;
		 p_planes[3].c = comboMatrix._43 + comboMatrix._23;
		 p_planes[3].d = comboMatrix._44 + comboMatrix._24;
		 // Near clipping plane
		 p_planes[4].a = comboMatrix._41 + comboMatrix._31;
		 p_planes[4].b = comboMatrix._42 + comboMatrix._32;
		 p_planes[4].c = comboMatrix._43 + comboMatrix._33;
		 p_planes[4].d = comboMatrix._44 + comboMatrix._34;
		 // Far clipping plane
		 p_planes[5].a = comboMatrix._41 - comboMatrix._31;
		 p_planes[5].b = comboMatrix._42 - comboMatrix._32;
		 p_planes[5].c = comboMatrix._43 - comboMatrix._33;
		 p_planes[5].d = comboMatrix._44 - comboMatrix._34;
	*/
	// left frustum
	m_planes[Planes::LEFT].normal.x = projViewMatrix[0][3] + projViewMatrix[0][0];
	m_planes[Planes::LEFT].normal.y = projViewMatrix[1][3] + projViewMatrix[1][0];
	m_planes[Planes::LEFT].normal.z = projViewMatrix[2][3] + projViewMatrix[2][0];
	m_planes[Planes::LEFT].distanceToOrigin = projViewMatrix[3][3] + projViewMatrix[3][0];
	// right frustum
	m_planes[Planes::RIGHT].normal.x = projViewMatrix[0][3] - projViewMatrix[0][0];
	m_planes[Planes::RIGHT].normal.y = projViewMatrix[1][3] - projViewMatrix[1][0];
	m_planes[Planes::RIGHT].normal.z = projViewMatrix[2][3] - projViewMatrix[2][0];
	m_planes[Planes::RIGHT].distanceToOrigin = projViewMatrix[3][3] - projViewMatrix[3][0];
	// Bottom clipping plane
	m_planes[Planes::BOTTOM].normal.x = projViewMatrix[0][3] + projViewMatrix[0][1];
	m_planes[Planes::BOTTOM].normal.y = projViewMatrix[1][3] + projViewMatrix[1][1];
	m_planes[Planes::BOTTOM].normal.z = projViewMatrix[2][3] + projViewMatrix[2][1];
	m_planes[Planes::BOTTOM].distanceToOrigin = projViewMatrix[3][3] + projViewMatrix[3][1];
	// Top clipping plane
	m_planes[Planes::TOP].normal.x = projViewMatrix[0][3] - projViewMatrix[0][1];
	m_planes[Planes::TOP].normal.y = projViewMatrix[1][3] - projViewMatrix[1][1];
	m_planes[Planes::TOP].normal.z = projViewMatrix[2][3] - projViewMatrix[2][1];
	m_planes[Planes::TOP].distanceToOrigin = projViewMatrix[3][3] - projViewMatrix[3][1];
	// Near clipping plane
	m_planes[Planes::NEAR].normal.x = projViewMatrix[0][3] + projViewMatrix[0][2];
	m_planes[Planes::NEAR].normal.y = projViewMatrix[1][3] + projViewMatrix[1][2];
	m_planes[Planes::NEAR].normal.z = projViewMatrix[2][3] + projViewMatrix[2][2];
	m_planes[Planes::NEAR].distanceToOrigin = projViewMatrix[3][3] + projViewMatrix[3][2];
	// Far clipping plane
	m_planes[Planes::FAR].normal.x = projViewMatrix[0][3] - projViewMatrix[0][2];
	m_planes[Planes::FAR].normal.y = projViewMatrix[1][3] - projViewMatrix[1][2];
	m_planes[Planes::FAR].normal.z = projViewMatrix[2][3] - projViewMatrix[2][2];
	m_planes[Planes::FAR].distanceToOrigin = projViewMatrix[3][3] - projViewMatrix[3][2];

	for (auto& plane : m_planes) {
		float length = glm::length(plane.normal);
		plane.normal /= length;
		plane.distanceToOrigin /= length;
	}
}

bool Frustum::isBoxInFrustum(const AABB& box) const noexcept {
	bool result = true;
	for (auto& plane : m_planes) {
		if (plane.distanceToPoint(box.getVP(plane.normal)) < 0) {
			return false;
		}
		else if (plane.distanceToPoint(box.getVN(plane.normal)) < 0) {
			result = true;
		}
	}
	return result;
}