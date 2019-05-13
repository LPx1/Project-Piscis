#pragma once

#include "ofMain.h"
#include "ofApp.h"

class Boid {
	public:
		glm::vec3 position;
		glm::vec3 velocity;
		glm::vec3 acceleration;

		float r;
		float maxForce;
		float maxSpeed;

		Boid() {
			srand(time(NULL));
			float x = 0;
			float y = 0;
			float z = 0;

			// Will randomize the spawning location of the boids (rand() % 3);
			position = glm::vec3(x, y, z);
			r = 1; //Radius for sphere testing
			maxSpeed = 2;
			maxForce = 0.04;
		}

		void start(vector<Boid> boids);
		void addForce(glm::vec3 force);
		void create();

		glm::vec3 alignment(vector<Boid> boids);
		glm::vec3 seperation(vector<Boid> boids);
		glm::vec3 cohesion(vector<Boid> boids);


};
