
#include "ofApp.h"
#include "Boid.h"

void Boid::start(vector<Boid> boids)
{

	group(boids);
	update();
	boundary();

}

void Boid::draw()
{


	ofDrawSphere(position, 2);
	//float theta = velocity.length Require the velocity's heading  ***********
	//ofDrawCone(position, 1, 3);

}

float Boid::mag(glm::vec3 vector)
{
	return 	sqrt(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
}

glm::vec3 Boid::limit(glm::vec3 vector, float value)
{
	if (mag(vector) > value)
	{
		vector = glm::normalize(vector);

		vector *= value;
	}

	return vector;
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

	sep *= 1.25;
	align *= 1.0;
	cohe *= 1.0;

	addForce(sep);
	addForce(align);
	addForce(cohe);
}

void Boid::boundary() //Wraparound meaning itll come back the other side
{
	if (position.x < -200) position.x = 200 ;
	if (position.y < -200) position.y = 200 ;
	if (position.z < -200) position.z = 200 ;
	if (position.x > 200 ) position.x = -200;
	if (position.y > 200 ) position.y = -200;
	if (position.z > 200 ) position.z = -200;
}

void Boid::update()
{
	//Update velocity
	velocity += acceleration;

	// Limit speed
	velocity = limit(velocity, maxVelocity);
	position += velocity;

	acceleration *= 0;

}

// Calculate the average velocity of each nearby boid
glm::vec3 Boid::alignment(vector<Boid> boids) 
{
	float neighbor = 20;
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

		return limit(steering,maxAccel);
	}
	else
	{
		return glm::vec3(0, 0, 0);
	}
}

//Calculates the distance between nearby boids and steers away
glm::vec3 Boid::seperation(vector<Boid> boids)
{
	seperationWeight = 10;
	glm::vec3 steering = glm::vec3(0, 0, 0);
	int count = 0; 

	for (Boid i : boids)
	{
		float distance = glm::distance(i.position, position);

		if ((distance > 0) && (distance < seperationWeight))
		{
			glm::vec3 difference = position - i.position; // Other boids position - the current boid's position
			
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

	return steering;


}

//Calculates and applies steering force towards target location
glm::vec3 Boid::seek(glm::vec3 target)
{
	glm::vec3 steering;
	//Vector pointing from the position of the boid to the target location 
	glm::vec3 desired = target - position;

	float distance = mag(desired);

//	float distance = glm::distance(desired, position);

	if (distance > 0)
	{
		desired = glm::normalize(desired);

		if (distance < 100)
		{
			desired *= (maxVelocity * ( distance/100));
		}
		else
		{
			desired *= maxVelocity;

			
		}

		glm::vec3 steering = desired - velocity;

		//steering = limit(steering, maxAccel);
	}
	else
	{
		glm::vec3 steering = glm::vec3(0, 0, 0);
	}

	return steering;

}

//Calculates the steering vector towards that position 
glm::vec3 Boid::cohesion(vector<Boid> boids)
{
	cohesionWeight = 20;

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


