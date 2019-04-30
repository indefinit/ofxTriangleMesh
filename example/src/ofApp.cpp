#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	testFont.load("Batang.ttf", 160, true, true, true);
	std::string letters = "hello world";
	std::vector<char> chars(letters.begin(), letters.end());
	
	bool vflip = true;
	bool filled = true;
	
	filled = false;
	for(auto &c : chars){
		
		testCharContour = testFont.getCharacterAsPoints(c, vflip, filled);
		//get the outline from our test character
		auto outline = testCharContour.getOutline();
		//loop through all the polylines of our outline
		//and for every polyline, add its vertices to our line
		//KS TODO: need to add space compensation to each letter so shapes are not drawing on top of eachother.
		for(auto &lins : outline){
			auto pts = lins.getVertices();
			for(auto &pt : pts){
				line.addVertex(glm::vec3(pt.x, pt.y, 0));
				ofLogNotice() << "added vertex at" << pt.x << " " << pt.y << endl;
			}
			
		}
	}
	
	if (line.size() > 2){
		
		ofPolyline lineRespaced = line;
		
		// add the last point (so when we resample, it's a closed polygon)
		lineRespaced.addVertex(lineRespaced[0]);
		// resample
		lineRespaced = lineRespaced.getResampledBySpacing(20);
		// I want to make sure the first point and the last point are not the same, since triangle is unhappy:
		lineRespaced.getVertices().erase(lineRespaced.getVertices().begin());
		// if we have a proper set of points, mesh them:
		if (lineRespaced.size() > 5){
			
			// angle constraint = 28
			// size constraint = -1 (don't constraint triangles by size);
			
			mesh.triangulate(lineRespaced, 28, -1);
			
			
			// this is an alternative, constrain on size not angle:
			//mesh.triangulate(lineRespaced, -1, 200);
			// see ofxTriangleMesh.h for info.
			
		}
	}

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor::white, ofColor(200,200,200), OF_GRADIENT_LINEAR);
	
	ofTranslate(100,ofGetWidth()/2);
	line.draw();
	
	
	mesh.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
