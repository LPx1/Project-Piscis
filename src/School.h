#pragma once
#include "ofMain.h"
#include "ofApp.h"

//School (containing a list of all the boids)
class School {
	public:
		vector<Boid> boids; //Collection of all boids 

		void run() { //Passes the entire list of boids to each boid
			for (Boid d : boids)
			{
				//d.start(boids);
				//printf("%f\n",d.position);
				d.draw();
			}
		}

		void addBoid(Boid b)
		{
			boids.push_back(b);
		}

};