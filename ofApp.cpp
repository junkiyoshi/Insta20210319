#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);

	ofEnableDepthTest();

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 55, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	string word = "ROLL";
	auto path_list = font.getStringAsPoints(word, true, false);
	for (auto& path : path_list) {

		vector<ofPolyline> outline = path.getOutline();

		int y = 0;

		ofSetColor(39);
		ofFill();

		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			outline[outline_index] = outline[outline_index].getResampledByCount(500);
			auto vertices = outline[outline_index].getVertices();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				auto location = glm::vec3(vertices[vertices_index].x - this->font.stringWidth(word) * 0.5, y + vertices[vertices_index].y + this->font.stringHeight(word) * 0.5, 0);
				auto angle_y = ofMap(ofNoise(abs(location.x) * 0.003 + ofGetFrameNum() * 0.02), 0, 1, -PI * 3, PI * 3);
				auto rotation_z = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
				location = glm::vec4(location, 0) * rotation_z;

				ofVertex(location);
			}
		}
		ofEndShape(true);
		
		ofSetColor(239);
		ofNoFill();

		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			outline[outline_index] = outline[outline_index].getResampledByCount(500);
			auto vertices = outline[outline_index].getVertices();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				auto location = glm::vec3(vertices[vertices_index].x - this->font.stringWidth(word) * 0.5, y + vertices[vertices_index].y + this->font.stringHeight(word) * 0.5, 0);
				auto angle_y = ofMap(ofNoise(abs(location.x) * 0.003 + ofGetFrameNum() * 0.02), 0, 1, -PI * 3, PI * 3);
				auto rotation_z = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
				location = glm::vec4(location, 0) * rotation_z;

				ofVertex(location);
			}
		}
		ofEndShape(true);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}