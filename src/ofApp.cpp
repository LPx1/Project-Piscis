#include "ofApp.h"
#include "time.h"
#include "ofMath.h"

//--------------------------------------------------------------
void ofApp::setup(){


	ofSetFrameRate(60);
	ofSetBackgroundColor(ofColor::lightSkyBlue);
	mainCamera.setDistance(50);
	mainCamera.setNearClip(.05);

	theCamera = &mainCamera;

	pos = glm::vec3(0, 0, 0); // testing real time 

	//GUI
//	sc.addBoid(Boid());
//	boids.push_back(new Boid());

	for (int i = 0; i <= 30; i++) {
		school.addBoid(Boid());
	}

	printf("%d", school.boids.size());

//	school.boids[0].setPosition(glm::vec3(1, 0, 0));
//	school.boids[0].rotation = glm::vec3(0, 1, 1);
//	school.boids = boids;
}

//--------------------------------------------------------------
void ofApp::update(){
	//pos += glm::vec3(1, 0, 0);

	for (int i = 1; i < school.boids.size(); i++) {
		school.boids[i].start(school.boids);
	}
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

//	ofDrawSphere(pos, 1);
//	school.run();

	for (int i = 1; i < school.boids.size() ; i++) {

		ofColor colors[10] = { ofColor::blue, ofColor::red, ofColor::green,
								ofColor::purple, ofColor::gold, ofColor::magenta,
	ofColor::teal, ofColor::blueSteel, ofColor::orangeRed, ofColor::oliveDrab };

		srand(time(NULL));
		int random = (rand() % 10); //Will select a random color from list of colors 

		ofSetColor(ofColor::red);
		school.boids[i].draw();
	}



	theCamera->end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case ' ':
		//boids.push_back(new Boid());
		school.addBoid(Boid());
		printf("%d \n", school.boids.size());
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
