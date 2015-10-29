#include "ParticleSystem.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::init()
{
	nParticles = glm::ivec3(100, 100, 100);
	speed = 35.0f;
	angle = 0.0f;

	bh1 = glm::vec4(5.0f, 0.0f, 0.0f, 1.0f);
	bh2 = glm::vec4(-5.0f, 0.0, 0.0f, 0.0f);

	totalParticles = nParticles.x * nParticles.y * nParticles.z;

	std::vector<GLfloat> initPos;
	std::vector<GLfloat> initVel(totalParticles * 4, 0.0f);
	glm::vec4 p(0.0f, 0.0f, 0.0f, 1.0f);
	GLfloat dx = 2.0f / (nParticles.x - 1),
		dy = 2.0f / (nParticles.y - 1),
		dz = 2.0f / (nParticles.z - 1);
	glm::mat4 transf = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, -1.0f, -1.0f));
	for (GLuint i = 0; i < nParticles.x; i++) 
	{
		for (GLuint j = 0; j < nParticles.y; j++) 
		{
			for (GLuint k = 0; k < nParticles.z; k++) 
			{
				p.x = dx * i;
				p.y = dy * j;
				p.z = dz * k;
				p.w = 1.0f;
				p = transf * p;
				initPos.push_back(p.x);
				initPos.push_back(p.y);
				initPos.push_back(p.z);
				initPos.push_back(p.w);
			}
		}
	}

	// We need buffers for position , and velocity.
	GLuint bufs[2];
	glGenBuffers(2, bufs);
	GLuint posBuf = bufs[0];
	GLuint velBuf = bufs[1];

	GLuint bufSize = totalParticles * 4 * sizeof(GLfloat);

	// The buffers for positions
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, posBuf);
	glBufferData(GL_SHADER_STORAGE_BUFFER, bufSize, &initPos[0], GL_DYNAMIC_DRAW);

	// Velocities
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, velBuf);
	glBufferData(GL_SHADER_STORAGE_BUFFER, bufSize, &initVel[0], GL_DYNAMIC_COPY);

	// Set up the VAO
	glGenVertexArrays(1, &particlesVao);
	glBindVertexArray(particlesVao);

	glBindBuffer(GL_ARRAY_BUFFER, posBuf);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	// Set up a buffer and a VAO for drawing the attractors (the "black holes")
	glGenBuffers(1, &bhBuf);
	glBindBuffer(GL_ARRAY_BUFFER, bhBuf);
	GLfloat data[] = { bh1.x, bh1.y, bh1.z, bh1.w, bh2.x, bh2.y, bh2.z, bh2.w };
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), data, GL_DYNAMIC_DRAW);

	glGenVertexArrays(1, &bhVao);
	glBindVertexArray(bhVao);

	glBindBuffer(GL_ARRAY_BUFFER, bhBuf);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void ParticleSystem::update()
{

}

void ParticleSystem::render(GLuint renderProg, GLuint compProg)
{
	glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 0, 1));
	glm::vec3 att1 = glm::vec3(rot*bh1);
	glm::vec3 att2 = glm::vec3(rot*bh2);

	glUseProgram(compProg);
	{
		glUniform3fv(glGetUniformLocation(compProg, "BlackHolePos1"), 1, glm::value_ptr(att1));
		glUniform3fv(glGetUniformLocation(compProg, "BlackHolePos2"), 1, glm::value_ptr(att2));
		glDispatchCompute(totalParticles / 1000, 1, 1);
		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	}

	glUseProgram(renderProg);
	{
		glPointSize(1.0f);
		glUniform4fv(glGetUniformLocation(renderProg, "Color"), 1, glm::value_ptr(glm::vec4(1.0f, 1.0f, 1.0f, 0.2f)));
		glBindVertexArray(particlesVao);
		glDrawArrays(GL_POINTS, 0, totalParticles);
		glBindVertexArray(0);

		// Draw the attractors
		glPointSize(5.0f);
		GLfloat data[] = { att1.x, att1.y, att1.z, 1.0f, att2.x, att2.y, att2.z, 1.0f };
		glBindBuffer(GL_ARRAY_BUFFER, bhBuf);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 8 * sizeof(GLfloat), data);
		glUniform4fv(glGetUniformLocation(renderProg, "Color"), 1, glm::value_ptr(glm::vec4(1, 1, 0, 1.0f)));
		glBindVertexArray(bhVao);
		glDrawArrays(GL_POINTS, 0, 2);
		glBindVertexArray(0);
	}
}