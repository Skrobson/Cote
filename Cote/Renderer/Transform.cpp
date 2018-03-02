#include "Transform.h"

using namespace cote;

Transform::Transform(const glm::vec3 & pos, const glm::vec3 & rot, const glm::vec3 & scale) :pos(pos), rot(rot), scale(scale)
{
	calcModel();
}


//TODO: poprawic tak by dzialalo dla axis
glm::mat4 Transform::rotateAround(glm::vec3 point, glm::vec3 axis, float angle)
{
	float distance = pow((point.z - pos.z), 2) + pow((point.x - pos.x), 2);
	distance = sqrt(distance);
	float offsetx = distance* sin(glm::radians(angle));
	float offsetz = distance*cos(glm::radians(angle));
	pos.x = offsetx;
	pos.z = offsetz;
	calcModel();
	return model;
}

glm::mat4 cote::Transform::rotate(glm::vec3 axis, float angle)
{
	model = glm::rotate(model, glm::radians(angle), axis);
	return model;
}

void Transform::calcModel()
{
	glm::mat4 posMat = glm::translate(pos);
	glm::mat4 scaleMat = glm::scale(scale);
	glm::mat4 rotX = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));
	glm::mat4 rotY = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 rotZ = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));
	glm::mat4 rotMat = rotX * rotY * rotZ;

	model = rotMat *posMat* scaleMat;
}