#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){



	ofSetBackgroundColor(ofColor::lightSkyBlue);
	mainCamera.setDistance(15);
	mainCamera.setNearClip(.05);

	theCamera = &mainCamera;

	//GUI
//	sc.addBoid(Boid());
//	boids.push_back(new Boid());

	for (int i = 0; i < 30; i++) {
		school.addBoid(Boid());
	}


//	school.boids[0].setPosition(glm::vec3(1, 0, 0));
//	school.boids[0].rotation = glm::vec3(0, 1, 1);
//	school.boids = boids;
}

//--------------------------------------------------------------
void ofApp::update(){
	school.run();
}

//--------------------------------------------------------------
void ofApp::draw(){
	gui.draw();
	theCamera->begin();

	ofDrawAxis(1);

	//for (Boid d : boids)
	//{
	//	d.start(boids);
	//	//d.draw();
	//}

	//for (int i = 0; i < boids.size; i++)
	//{
	//	boids[i]->start(boids);
	//}

//	sc.run();



	theCamera->end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case ' ':
		//boids.push_back(new Boid());
		school.addBoid(Boid());
		printf("New boid \n");
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
