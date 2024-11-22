#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
   /**/ ofBackground(0,0,0);
    ofDisableArbTex();
   // ofEnableAlphaBlending();
    ofSetFrameRate(60);



    gui.setup("settings.xml");
    gui.setDefaultWidth(300);
    gui.add(fadeAmnt);

    gui.add(bumpColorMult);
    gui.add(bumpLimit);

    gui.add(drawMesh);

    gui.add(drawSphere);
    gui.add(sphereRad);
    gui.add(sphereRes);
    gui.add(sphereRotspeed);



    gui.loadFromFile("settings.xml");



    shader.load("shaders/displace.vert", "shaders/displace.frag","");
    ofSetSphereResolution(sphereRes);
    colormap.load("mars_1k_color_2.jpg");
    bumpmap.load("normal_yellow_02.jpeg");

    // Event Listener for sphere resolution
    sphereRes.addListener(this, &ofApp::setSphereRes);

    mult = -1;

    light.setup();
    // 3d light tex mat
    shaderTex.load("shaders/sem.vert", "shaders/sem.frag","");
    mesh.load("uploads_files_886195_phazzzer_skull_free.ply");
    //ofSetBackgroundAuto(false);

    ofFboSettings s;
    s.width			= ofGetWidth();
    s.height			= ofGetHeight();
    s.internalformat   = GL_RGBA32F_ARB;
    s.useDepth			= true;
    s.numSamples        = 4;
    //s.useStencil        = true;

    fbo.allocate(s);
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();

}

void ofApp::setSphereRes(int & res) {
    ofSetSphereResolution(int(sphereRes));
}

//--------------------------------------------------------------
void ofApp::update(){

    /*ofSetWindowTitle(ofToString(ofGetFrameRate()));

    mult += 0.01;
    ofEnableAlphaBlending();
    fbo.begin();

    ofSetColor(0,0,0,40);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());


    cam.begin();
    ofEnableDepthTest();
    //shaderTex.begin();
    //shaderTex.setUniformTexture("tMatCap", colormap, 1);
    shader.begin();
    shader.setUniform3f("bumpColorMult",bumpColorMult.get());
    shader.setUniformTexture("colormap", colormap, 1);
    shader.setUniformTexture("bumpmap", bumpmap, 2);
    shader.setUniform1f("maxHeight", bumpLimit);
    shader.setUniform1f("time", ofGetElapsedTimef());

    ofPushMatrix();
    ofRotateYDeg(ofGetElapsedTimef() * sphereRotspeed);

    if(drawSphere)
        ofDrawSphere(0, 0, 0,  sphereRad);

    float scale = ofGetHeight() / 4;
    ofScale(scale, scale, scale);
    //ofRotateYDeg(sin(ofGetElapsedTimef()*1.2) * 45);
    ofRotateXDeg(20 + ofSignedNoise(ofGetElapsedTimef()*0.5, ofGetFrameNum()*0.01));

    if(drawMesh)
        mesh.draw();
    //mesh.drawVertices();
    ofPopMatrix();
    shader.end();
    ofSetColor(255);
    mesh.drawWireframe();
    //shaderTex.end();
    ofDisableDepthTest();
    cam.end();

    fbo.end();*/

    ofEnableAlphaBlending();

    //lets draw some graphics into our two fbos
    fbo.begin();
        drawFboTest();
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::drawFboTest(){
    //we clear the fbo if c is pressed.
    //this completely clears the buffer so you won't see any trails
    if( ofGetKeyPressed('c') ){
        ofClear(255,255,255, 0);
    }



    /*ofFill();
    ofSetColor(0,0,0, fadeAmnt);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());

    //2 - Draw graphics
    cam.begin();
    ofNoFill();
    ofSetColor(255,255,255);

    //we draw a cube in the center of the fbo and rotate it based on time
    ofPushMatrix();
        ofRotateDeg(ofGetElapsedTimef()*30, 1,0,0.5);
        ofDrawBox(0,0,0,100);
        ofSetColor(255);
        ofScale(200);
        mesh.drawWireframe();
    ofPopMatrix();

    cam.end();*/



}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255, 255, 255);
    //fbo.draw(0, 0);

    ofSetWindowTitle(ofToString(ofGetFrameRate()));

     mult += 0.01;

     ofSetColor(0,fadeAmnt);

     ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());

     cam.begin();

     shader.begin();
     shader.setUniform3f("bumpColorMult",bumpColorMult.get());
     shader.setUniformTexture("colormap", colormap, 1);
     shader.setUniformTexture("bumpmap", bumpmap, 2);
     shader.setUniform1f("maxHeight", bumpLimit);
     shader.setUniform1f("time", ofGetElapsedTimef());

     ofPushMatrix();
     ofPushStyle();

      //ofTranslate(ofGetWidth()*0.5, ofGetHeight()*0.5);
     ofRotateYDeg(ofGetElapsedTimef() * sphereRotspeed);
    ofEnableDepthTest();
     if(drawSphere) {

         ofDrawSphere(0, 0, 0,  sphereRad);
    }
     float scale = ofGetHeight() / 4;
     ofScale(scale, scale, scale);
     //ofRotateYDeg(sin(ofGetElapsedTimef()*1.2) * 45);
     ofRotateXDeg(20 + ofSignedNoise(ofGetElapsedTimef()*0.5, ofGetFrameNum()*0.01));


     if(drawMesh) {
         mesh.draw();
        //mesh.drawVertices();
         //mesh.drawWireframe();
     }
    ofDisableDepthTest();
    ofPopStyle();
     ofPopMatrix();

    shader.end();

     cam.end();

    //also draw based on our mouse position
    ofFill();

    //we move a line across the screen based on the time
    //the %400 makes the number stay in the 0-400 range.
    int shiftX   = (ofGetElapsedTimeMillis() / 8 ) % ofGetWidth();

    ofDrawRectangle(shiftX, fbo.getHeight()-30, 3, 30);

    gui.draw();
    //fog.drawGui();
    string alphaInfo = "Current alpha fade amnt = " + ofToString(fadeAmnt);
    //ofDrawBitmapString(alphaInfo, gui.getPosition().x, gui.getPosition().y + gui.getHeight() + 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'g') {
        isDebug = !isDebug;
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
