#include "Plane.h"
#include <Gizmos.h>

Plane::Plane()
	: PhysicsObject(PLANE) {

	m_normal = glm::vec2(0.f, 0.f);
	m_distanceToOrigin = 0.f;
}

Plane::Plane(glm::vec2 normal, float distanceToOrigin) 
	: PhysicsObject(PLANE){

	m_normal = normal;
	m_distanceToOrigin = distanceToOrigin;
}

void Plane::makeGizmo(){

	float lineSegment = 300;
	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 color(1, 1, 1, 1);
	glm::vec2 start = centerPoint + (parallel * lineSegment);
	glm::vec2 end = centerPoint - (parallel * lineSegment);

	aie::Gizmos::add2DLine(start, end, color);
}
