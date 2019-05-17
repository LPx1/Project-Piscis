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

		srand(time(NULL));
		int random = (rand() % 10); //Will select a random color from list of colors 

//		ofSetColor(colors[random]);

		school.addBoid(Boid());
		school.boids[i].myColor = colors[random];
	}

	printf("%d", school.boids.size());

//	school.boids[0].setPosition(glm::vec3(1, 0, 0));
//	school.boids[0].rotation = glm::vec3(0, 1, 1);
//	school.boids = boids;
}

//--------------------------------------------------------------
void ofApp::update(){
	//pos += glm::vec3(1, 0, 0);

	for (int i = 0; i < school.boids.size(); i++) {
		school.boids[i].start(school.boids);
	}

	//for (int i = 0; i < school.predators.size(); i++) {
	//	school.predators[i].start(school.boids);
	//}
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
		ofSetColor(school.boids[i].myColor);
		school.boids[i].draw();
	}

	//for (int i = 0; i < school.predators.size(); i++) {
	//	ofSetColor(school.predators[i].myColor);
	//	school.predators[i].draw();
	//}



	theCamera->end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	int random = 0;

	switch (key)
	{
	case ' ':
		//boids.push_back(new Boid());
		school.addBoid(Boid());
		srand(time(NULL));
		random = (rand() % 10); //Will select a random color from list of colors 

		school.boids[school.boids.size() - 1].myColor = colors[random];

		printf("%d \n", school.boids.size());
		break;
	case 'Z':
	case 'z':
		school.addPred(Predator());
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
