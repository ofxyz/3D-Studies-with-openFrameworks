#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255, 255, 255, 0);
    
    ofSetVerticalSync(true);
    
    light.setPosition(0, 2000, 0);
    light.setAmbientColor(ofFloatColor(1.0f, 1.0f, 1.0f));
    
    cam.setDistance(100);
    
    box.set(20);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofVec3f axis{ 1, 1, 1 };
    axis.normalize();
    float angle_deg = 1;
    ofQuaternion rotation(angle_deg, axis);
    orientation = orientation * rotation;
    
    ofVec3f position{ 0, 0, 0 };
    drawCube(position, orientation);
    drawXYZ(position, orientation, 3);
    drawXYZ();
}

void ofApp::drawCube(glm::vec3 position, ofQuaternion orientation) {
    ofPushMatrix();
    light.enable();
    cam.begin();
    
    ofEnableDepthTest();
    
    ofTranslate(position);
    
    float quat_angle;
    ofVec3f quat_vec;
    orientation.getRotate(quat_angle, quat_vec);
    
    ofRotateDeg(quat_angle, quat_vec.x, quat_vec.z, quat_vec.y);
    
    ofNoFill();
    ofSetColor(0, 0, 0);
    ofSetLineWidth(3);
    box.drawWireframe();
    
    cam.end();
    light.disable();
    ofPopMatrix();
}

void ofApp::drawXYZ(glm::vec3 position, ofQuaternion orientation, uint32_t line_width) {
    ofPushMatrix();
    light.enable();
    cam.begin();
    
    ofDisableDepthTest();
    
    ofTranslate(position);
    
    ofMatrix4x4 rotation_matrix = ofMatrix4x4::newRotationMatrix(orientation);
    ofMultMatrix(rotation_matrix);
    
    ofVec3f origin(0, 0, 0);
    ofVec3f x_unit(10, 0, 0);
    ofVec3f y_unit(0, 10, 0);
    ofVec3f z_unit(0, 0, 10);
    
    float angle{};
    ofVec3f axis{};
    orientation.getRotate(angle, axis);
    axis.scale(10);
    
    ofSetLineWidth(line_width);
    
    ofSetColor(255, 0, 0);
    ofDrawLine(origin, x_unit);
    
    ofSetColor(0, 255, 0);
    ofDrawLine(origin, y_unit);
    
    ofSetColor(0, 0, 255);
    ofDrawLine(origin, z_unit);
    
    if (angle != 0 and angle != 360) {
        ofSetLineWidth(line_width * 1.5);
        
        ofSetColor(255, 0, 255);
        ofDrawLine(origin, axis);
    }
    
    cam.end();
    light.disable();
    ofPopMatrix();
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
