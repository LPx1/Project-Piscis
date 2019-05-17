
#include "ofApp.h"
#include "Boid.h"
#include "ofMath.h"

void Boid::start(vector<Boid> boids)
{

	group(boids);
	update();
	boundary();

}

void Boid::draw()
{
	
	ofPushMatrix();
	glm::mat4 theta = lookAtMatrix(position, velocity, glm::vec3(0, 1, 0));
	ofMultMatrix(theta);
	ofDrawCone(position, 3, 8);
	ofPopMatrix();

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

glm::mat3 Boid::lookAtMatrix(const glm::vec3 &pos, const glm::vec3 &aimPos, glm::vec3 upVector) {
	glm::mat4 m;

	glm::vec3 zAxis = glm::normalize(pos - aimPos); //dir
	glm::vec3 xAxis = glm::normalize(glm::cross(glm::normalize(upVector), zAxis)); //right
	glm::vec3 yAxis = glm::cross(zAxis, xAxis); //newUp

	m[0][0] = xAxis.x;
	m[0][1] = xAxis.y;
	m[0][2] = xAxis.z;
	m[0][3] = 0;

	m[1][0] = yAxis.x;
	m[1][1] = yAxis.y;
	m[1][2] = yAxis.z;
	m[1][3] = 0;

	m[2][0] = zAxis.x;
	m[2][1] = zAxis.y;
	m[2][2] = zAxis.z;
	m[2][3] = 0;

	m[3][0] = pos.x;
	m[3][1] = pos.y;
	m[3][2] = pos.z;
	m[3][3] = 1;


	return m;
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
	else if (position.y < -200) position.y = 200 ;
	else if (position.z < -200) position.z = 200 ;
	else if (position.x > 200 ) position.x = -200;
	else if (position.y > 200 ) position.y = -200;
	else if (position.z > 200 ) position.z = -200;
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




