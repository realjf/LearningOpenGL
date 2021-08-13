#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light
{
public:
	Light();
	~Light();

	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity);
	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation);


private:
	glm::vec3 color;
	GLfloat ambientIntensity;
};

