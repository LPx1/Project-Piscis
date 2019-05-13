#pragma once
#include "ofMain.h"
#include "ofApp.h"

class School {
	public:
		vector<Boid> boids; //Collection of all boids 

		void run() { //Passes the entire list of boids to each boid
			for (Boid d : boids)
			{
				d.start(boids);
			}
		}

		void addBoid(Boid b)
		{
			boids.push_back(b);
		}
};