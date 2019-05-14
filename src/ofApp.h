#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Boid.h"
#include "School.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		//Cameras 
		ofEasyCam mainCamera;
		ofCamera sideCamera;
		ofCamera topCamera;
		ofCamera *theCamera;

		//GUI
		ofxPanel gui;

		School school = School();
		vector<Boid> boids;

		glm::vec3 pos;

		
};
