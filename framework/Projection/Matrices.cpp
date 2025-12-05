#include "Matrices.h"

Matrices::Matrices():
	IDENTITY_MAT(glm::mat4(1.0f))
{
}

Matrices::~Matrices()
{
}

glm::mat4 Matrices::setPerspectiveProjection(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	return glm::perspective(fov, aspectRatio, nearPlane, farPlane);
}

glm::mat4 Matrices::getViewMatrix(glm::vec3 pos, glm::vec3 ori, glm::vec3 up) 
{
	return glm::lookAt(pos, ori, up);
}

glm::mat4 Matrices::getTransformMatrix(glm::vec3 scale, glm::vec3 rotationVec, float rotationDeg, glm::vec3 translate)
{
	auto scaleMat = glm::scale(IDENTITY_MAT, scale);
	auto rotationMat = glm::rotate(IDENTITY_MAT, glm::radians(rotationDeg), rotationVec); // Returns materix with -nan(ind)
	auto translateMat = glm::translate(IDENTITY_MAT, translate);

	return translateMat * rotationMat * scaleMat;
}