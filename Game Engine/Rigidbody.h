#pragma once

// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Rigidbody
{
public:
	struct State {
		//primary states
		glm::vec3 position;
		glm::vec3 momentum;
		glm::quat orientation;
		glm::vec3 angularMomentum;

		// secondary states
		glm::vec3 velocity;
		glm::quat spin;
		glm::vec3 angularVelocity;
		glm::mat4 bodyToWorld;
		glm::mat4 worldToBody;

		// constant state
		GLfloat size;
		GLfloat mass;
		GLfloat inverseMass;
		GLfloat inertiaTensor;
		GLfloat inverseInertiaTensor;
		void recalculate() {
			velocity = momentum * inverseMass;
			angularVelocity = angularMomentum * inverseInertiaTensor;
			glm::normalize(orientation);
			spin = 0.5f * glm::quat(0, angularVelocity.x, angularVelocity.y, angularVelocity.z) * orientation;
			glm::mat4 translation;
			glm::translate(translation, position);
			bodyToWorld = translation * glm::mat4_cast(orientation);
			worldToBody = glm::inverse(bodyToWorld);
		}
	};

	void update(GLfloat t, GLfloat dt) {
		previous = current;
		integrate(current, t, dt);
	}

	void Rigidbody_Init();
	Rigidbody();
	~Rigidbody();

private:
	State previous;
	State current;

	struct Derivative
	{
		glm::vec3 velocity;
		glm::vec3 force;
		glm::quat spin;
		glm::vec3 torque;
	};

	static State interpolate(const State &a, const State &b, GLfloat alpha) {
		State state = b;
		state.position = a.position*(1 - alpha) + b.position*alpha;
		state.momentum = a.momentum*(1 - alpha) + b.momentum*alpha;
		state.orientation = glm::slerp(a.orientation, b.orientation, alpha);
		state.angularMomentum = a.angularMomentum*(1 - alpha) + b.angularMomentum*alpha;
		state.recalculate();
		return state;
	}

	static Derivative evaluate(const State &state, GLfloat t) {
		Derivative output;
		output.velocity = state.velocity;
		output.spin = state.spin;
		forces(state, t, output.force, output.torque);
		return output;
	}

	static Derivative evaluate(State state, GLfloat t, GLfloat dt, const Derivative &derivative) {
		state.position += derivative.velocity * dt;
		state.momentum += derivative.force * dt;
		state.orientation += derivative.spin * dt;
		state.angularMomentum += derivative.torque * dt;
		state.recalculate();

		Derivative output;
		output.velocity = state.velocity;
		output.spin = state.spin;
		forces(state, t + dt, output.force, output.torque);
		return output;
	}

	static void integrate(State &state, GLfloat t, GLfloat dt) {
		Derivative a = evaluate(state, t);
		Derivative b = evaluate(state, t, dt*0.5f, a);
		Derivative c = evaluate(state, t, dt*0.5f, b);
		Derivative d = evaluate(state, t, dt, c);

		state.position += 1.0f / 6.0f * dt * (a.velocity + 2.0f*(b.velocity + c.velocity) + d.velocity);
		state.momentum += 1.0f / 6.0f * dt * (a.force + 2.0f*(b.force + c.force) + d.force);
		state.orientation += 1.0f / 6.0f * dt * (a.spin + 2.0f*(b.spin + c.spin) + d.spin);
		state.angularMomentum += 1.0f / 6.0f * dt * (a.torque + 2.0f*(b.torque + c.torque) + d.torque);

		state.recalculate();
	}

	static void forces(const State &state, GLfloat t, glm::vec3 &force, glm::vec3 &torque) {

		// attract towards origin

		force = -10.0f * state.position;

		// sine force to add some randomness to the motion

		force.x += 10 * glm::sin(t*0.9f + 0.5f);
		force.y += 11 * glm::sin(t*0.5f + 0.4f);
		force.z += 12 * glm::sin(t*0.7f + 0.9f);

		// sine torque to get some spinning action

		torque.x = 1.0f * glm::sin(t*0.9f + 0.5f);
		torque.y = 1.1f * glm::sin(t*0.5f + 0.4f);
		torque.z = 1.2f * glm::sin(t*0.7f + 0.9f);

		// damping torque so we dont spin too fast

		torque -= 0.2f * state.angularVelocity;
	}
};

