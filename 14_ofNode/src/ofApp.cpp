#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Init GUI
    guiEnabled = true;
    gui.setup("setting.xml");
    gui.setDefaultWidth(300);
    gui.add(lightPos);
    gui.add(boom);
    gui.add(main.camMoveSpeed);
    gui.add(main.camMoveRange);
    gui.add(main.wingSpeed);

    //ofxGuiEnableHiResDisplay();
    ofSetWindowShape(1080, 1080);
    ofDisableArbTex();
    ofSetWindowPosition(0,0);
    ofBackground(0);
    // init ofMain node class
    main.setup(glm::vec3(-100, 10,0));
    main2.setup(glm::vec3(100,-100,-100));
    light.setup();
    //light.setParent(main.getNode());

    gui.loadFromFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
    light.setPosition(lightPos);
    main.update();
    main2.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    ofEnableLighting();
    light.enable();
    cam.begin();
    //cam.lookAt(main.fly);


    ofPushMatrix();
    //ofRotateYDeg(ofGetElapsedTimef() * 10);
    //main.rotateDeg(2, glm::vec3(1,1,0));
    //main.move(sin(ofGetElapsedTimef()*4) * 100,0,0);
    main.draw();
    main2.draw();
    ofPopMatrix();

    if(guiEnabled)
        light.draw();

    cam.end();
    light.disable();
    ofDisableLighting();
    ofDisableDepthTest();

    if(guiEnabled) {
        gui.draw();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'g') {
        guiEnabled = !guiEnabled;
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
