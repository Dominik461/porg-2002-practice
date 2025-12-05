#ifndef MATRICES_H_
#define MATRICES_H_

#include <glm/ext.hpp>

class Matrices
{
public:
	Matrices();
	~Matrices();
	

	glm::mat4 setPerspectiveProjection(float fov, float aspectRatio, float nearPlane, float farPlane);
	glm::mat4 getIdentityMatrix() { return  IDENTITY_MAT; };
	glm::mat4 getViewMatrix(glm::vec3 pos, glm::vec3 ori, glm::vec3 up);
	glm::mat4 getTransformMatrix(glm::vec3 scale, glm::vec3 rotationVec, float rotationDeg, glm::vec3 translate);

private:
	const glm::mat4 IDENTITY_MAT;
};



#endif // !MATRICIES_H_
