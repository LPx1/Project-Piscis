#pragma once

#include "ofMain.h"
#include "ofApp.h"


class Boid {
	public:
		glm::vec3 position;
		glm::vec3 velocity;
		glm::vec3 acceleration;
		glm::vec3 rotation = glm::vec3(0, 0, 0);  
		glm::vec3 scale = glm::vec3(1, 1, 1);     
		glm::vec3 pivot = glm::vec3(0, 0, 0);		// rotate pivot


		float r = 20; 
		float maxAccel;
		float maxVelocity;

		//Weights 
		float perceptionRadius;
		float seperationWeight;
		float alighWeight;
		float cohesionWeight;

		ofColor myColor;


		Boid() {
			srand(time(NULL));
			float x = (rand() % 2 + (4));
			float y = (rand() % 2 + (4));
			float z = (rand() % 2 + (4));

			// Will randomize the spawning location of the boids (rand() % 3);
			position = glm::vec3(x, y, z);
			acceleration = glm::vec3(0, 0, 0);
			velocity = glm::vec3(glm::cos(x), glm::sin(y), glm::cos(z));

			maxVelocity = 1; //How fast each boid can move
			maxAccel = 0.75; //How fast each boid can change its direction
		}

		void start(vector<Boid> boids);
		void addForce(glm::vec3 force);
		void draw(); 
		void update();
		void boundary();
		float mag(glm::vec3 vector);
		float heading3D(glm::vec3 vector);
		glm::vec3 limit(glm::vec3 vector,float value);
		glm::vec3 seek(glm::vec3 target);
		void Boid::group(vector<Boid> boids);		
		glm::vec3 alignment(vector<Boid> boids);
		glm::vec3 seperation(vector<Boid> boids);
		glm::vec3 cohesion(vector<Boid> boids);
		glm::vec3 flee(vector<Boid> enemy);
		glm::mat3 lookAtMatrix(const glm::vec3 &pos, const glm::vec3 &aimPos, glm::vec3 upVector);

		// commonly used transformations
	//
		glm::mat4 getRotateMatrix() {
			return (glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z)));   // yaw, pitch, roll 
		}
		glm::mat4 getTranslateMatrix() {
			return (glm::translate(glm::mat4(1.0), glm::vec3(position.x, position.y, position.z)));
		}
		glm::mat4 getScaleMatrix() {
			return (glm::scale(glm::mat4(1.0), glm::vec3(scale.x, scale.y, scale.z)));
		}


		glm::mat4 getLocalMatrix() {

			// get the local transformations + pivot
			//
			glm::mat4 scale = getScaleMatrix();
			glm::mat4 rotate = getRotateMatrix();
			glm::mat4 trans = getTranslateMatrix();

			// handle pivot point  (rotate around a point that is not the object's center)
			//
			glm::mat4 pre = glm::translate(glm::mat4(1.0), glm::vec3(-pivot.x, -pivot.y, -pivot.z));
			glm::mat4 post = glm::translate(glm::mat4(1.0), glm::vec3(pivot.x, pivot.y, pivot.z));

			return (trans * post * rotate * pre * scale);

		}

		glm::mat4 getMatrix() 
		{
			// concatenate parent's transform (this is recursive)
			return getLocalMatrix();  // priority order is SRT
		}

		// get current Position in World Space
		//
		glm::vec3 getPosition() {
			return (getMatrix() * glm::vec4(0.0, 0.0, 0.0, 1.0));
		}

		// set position (pos is in world space)
		//
		void setPosition(glm::vec3 pos) {
			position = glm::inverse(getMatrix()) * glm::vec4(pos, 1.0);
		}

		// return a rotation  matrix that rotates one vector to another
		//
		glm::mat4 rotateToVector(glm::vec3 v1, glm::vec3 v2)
		{

			glm::vec3 axis = glm::cross(v1, v2);
			glm::quat q = glm::angleAxis(glm::angle(v1, v2), glm::normalize(axis));
			return glm::toMat4(q);
		}



};

class Predator : public Boid
{
	public:

	Predator()
	{
		srand(time(NULL));
		float x = (rand() % 2 + (4));
		float y = (rand() % 2 + (4));
		float z = (rand() % 2 + (4));

		// Will randomize the spawning location of the boids (rand() % 3);
		position = glm::vec3(x, y, z);
		acceleration = glm::vec3(0, 0, 0);
		velocity = glm::vec3(glm::cos(x), glm::sin(y), glm::cos(z));

		maxVelocity = 3; //How fast each boid can move
		maxAccel = 0.75; //How fast each boid can change its direction
			
	}

	float maxAccel = 10;

	ofColor myColor = ofColor::red;



	void start(vector<Boid> boids)
	{
		group(boids);
		printf("%f, %f, %f", position.x, position.y, position.z);
		update();
		boundary();
	}

	void draw()
	{
		ofSetColor(ofColor::red);
		ofDrawSphere(position, 5);
	}

	void group(vector<Boid> boids1)
	{
		glm::vec3 hunt = chase(boids1);

		addForce(hunt);

	}

	void update()
	{
		//Update velocity
		velocity += acceleration;

		// Limit speed
		velocity = limit(velocity, maxVelocity);
		position += velocity;

		acceleration *= 0;

	}

	glm::vec3 chase(vector<Boid> boids)
	{
		float chaseWeight = 100;
		glm::vec3 sum = glm::vec3(0, 0, 0);
		int count = 0;

		for (Boid i : boids)
		{
			float distance = glm::distance(i.position, position);
			distance = mag(i.position - position);

			//If the distance between the predator is not 0 then FASTER
			if ((distance != 0) && ( distance < chaseWeight ))
			{
				sum += i.position;
				count++;
			}
		}

		if (count > 0)
		{
			sum /= count;
			glm::vec3 approachVec = sum - position;
			approachVec = limit(approachVec, maxAccel);
			return approachVec;
		}
		else
		{
			return glm::vec3(0, 0, 0);
		}
	}


};
