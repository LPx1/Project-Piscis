
#include "ofApp.h"
#include "Boid.h"

void Boid::start(vector<Boid> boids)
{

	group(boids);
	update();
	boundary();
	// Check the boundaries 
//	draw();
//	printf("Called \n");
}

void Boid::draw()
{
	ofDrawSphere(position, 1);
	//float theta = velocity.length Require the velocity's heading  ***********
	//ofDrawCone(position, 1, 3);

}



void Boid::addForce(glm::vec3 force)
{
	acceleration += force;
}

//Calculate behavior based on allignment, seperation, cohesion (forces)
void Boid::group(vector<Boid> boids)
{
	glm::vec3 sep = seperation(boids);
	glm::vec3 align = alignment(boids);
	glm::vec3 cohe = cohesion(boids);

	sep *= 1.0;
	align *= 1.0;
	cohe *= 1.0;

	addForce(sep);
	addForce(align);
	addForce(cohe);
}

void Boid::boundary() //Wraparound meaning itll come back the other side
{
	if (position.x < -r) position.x = 200 + r;
	if (position.y < -r) position.y = 200 + r;
	if (position.z < -r) position.z = 200 + r;
	if (position.x > 200 + r) position.x = -r;
	if (position.y > 200 + r) position.y = -r;
	if (position.z > 200 + r) position.z = -r;
}

void Boid::update()
{
	//Update velocity
	velocity += acceleration;

	//if (velocity.length > maxVelocity)
//{
//	velocity.x =+
//}
	//^^^^
	// Slow down the velocity when it hits maxVelocity

	if (velocity.x > maxVelocity)
	{
		velocity.x = maxVelocity;

	}
	if (velocity.y > maxVelocity)
	{
		velocity.y = maxVelocity;
	}
	if (velocity.z > maxVelocity)
	{
		velocity.z = maxVelocity;
	}

	position += velocity;

	acceleration *= glm::vec3(0, 0, 0);
}

// Calculate the average velocity of each nearby boid
glm::vec3 Boid::alignment(vector<Boid> boids) 
{
	float neighbor = 50;
	glm::vec3 sum = glm::vec3(0, 0, 0);
	int count = 0;

	for (Boid i : boids)
	{
		float distance = glm::distance(i.position, position);
		if ((distance > 0) && (distance < neighbor))
		{
			sum += i.velocity;
			count++;
		}
	}
	if (count > 0)
	{
		//Steering

		glm::vec3 norm = glm::normalize(sum);
		norm *= maxVelocity;
		glm::vec3 steering = norm - velocity;

		if (steering.x > maxAccel)
		{
			steering.x = maxAccel;

		}
		if (steering.y > maxAccel)
		{
			steering.y = maxAccel;
		}
		if (steering.z > maxAccel)
		{
			steering.z = maxAccel;
		}


		return steering;
	}
	else
	{
		return glm::vec3(0, 0, 0);
	}
}

//Calculates the distance between nearby boids and steers away
glm::vec3 Boid::seperation(vector<Boid> boids)
{
	seperationWeight = 25;
	glm::vec3 steering = glm::vec3(0, 0, 0);
	int count = 0; 
	for (Boid i : boids)
	{
		float distance = glm::distance(i.position, position);
		if ((distance > 0) && (distance < seperationWeight))
		{
			glm::vec3 difference = i.position - position; // Other boids position - the current boid's position
			difference = glm::normalize(difference);
			difference = difference / distance;
			steering += difference;
			count++;
		}
	}
	//get the average
	if (count > 0)
	{
		steering /= count;
	}

	float mag = pow(steering.x, 2) + pow(steering.y, 2) + pow(steering.z, 2);

	if (mag > 0) //************Getting magnitude of a vector
	{
		steering = glm::normalize(steering);
		steering = (steering * maxVelocity) - velocity;

		if (steering.x > maxAccel)
		{
			steering.x -= maxAccel;

		}
		if (steering.y > maxAccel)
		{
			steering.y -= maxAccel;
		}
		if (steering.z > maxAccel)
		{
			steering.z -= maxAccel;
		}

		return steering;
	}
	else
	{
		return glm::vec3(0, 0, 0);
	}

}

//Calculates and applies steering force towards target location
glm::vec3 Boid::seek(glm::vec3 target)
{
	glm::vec3 desired = target - position;
	desired = glm::normalize(desired);
	desired *= maxVelocity;

	glm::vec3 steering = desired - velocity;
	return steering;
}

//Calculates the steering vector towards that position 
glm::vec3 Boid::cohesion(vector<Boid> boids)
{
	cohesionWeight = 50;
	glm::vec3 sum = glm::vec3(0, 0, 0);
	int count = 0;
	for (Boid i : boids)
	{
		float distance = glm::distance(i.position, position);
		if ((distance > 0) && (distance < i.cohesionWeight))
		{
			sum += i.position;
			count++;
		}
	}
	if (count > 0)
	{
		sum /= count;
		return seek(sum);
	}
	else
	{
		return glm::vec3(0, 0, 0);
	}
}


