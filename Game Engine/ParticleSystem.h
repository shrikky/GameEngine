#pragma once

#include <GLM/glm.hpp>
#include <GL/glew.h>

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void init();
	void update(); 
	void render(GLuint renderProg, GLuint compProg);

private:

	glm::ivec3 nParticles;
	GLuint totalParticles;

	GLfloat speed, angle;
	GLuint particlesVao;
	GLuint bhVao, bhBuf;  // black hole VAO and buffer
	glm::vec4 bh1, bh2;
};

