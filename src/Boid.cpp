
#include "ofApp.h"
#include "Boid.h"

void Boid::start(vector<Boid> boids)
{
	group(boids);
	update();
	// Check the boundaries 
	draw();
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
	acceleration =+ force;
}

//Calculate behavior based on allignment, seperation, cohesion (forces)
void Boid::group(vector<Boid> boids)
{
	glm::vec3 seperation;
	glm::vec3 align = alignment(boids);
	glm::vec3 cohesion;  

	seperation *= 1.5;
	align *= 1.0;
	cohesion *= 1.0;

//	addForce(seperation);
//	addForce(align);
//	addForce(cohesion);
}

void Boid::boundary() //Wraparound meaning itll come back the other side
{
	
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

	position += velocity;

	acceleration = glm::vec3(0, 0, 0);
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
		return steering;
	}
	else
	{
		return glm::vec3(0, 0, 0);
	}
}

//Calculates the distance between each 
glm::vec3 Boid::seperation(vector<Boid> boids)
{



	return glm::vec3(0, 0, 0);

}

glm::vec3 Boid::cohesion(vector<Boid> boids)
{
	return glm::vec3(0, 0, 0);
}


