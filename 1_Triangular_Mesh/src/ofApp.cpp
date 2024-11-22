#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //ofSetVerticalSync(false);
    ofLogToConsole();
    ofBackground(0);
    
    t = ofRandom(10000);
    d = ofRandom(10000);
    
    quadPlane.setup();
    
    gui.setDefaultWidth(300);
    gui.setup("Project Parameters");
    gui.add(quadPlane.getGUI());
    
    gui.loadFromFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    /*And now we have a mesh, albeit a really simple one. Ok, actually, that's wrong, but it's wrong on purpose. As you can see, we have exactly duplicated some of our addVertex calls above. In a tiny little square it doesn't matter if we use a few extra vertices - but when you're modelling a giant particle blob or something like that, it'll matter a lot.
    */
    
    //drawQuad();
    
    /*
    That's where the index comes in. Indices are just a way of describing which sets of vertices in our vertex array go together to make triangles. The first 3 indices in the index array describe the vertices of the first triangle, the second 3 describe the second triangle, and so on. It's pretty rad and it saves you having to make and store more vertices than necessary. A more typical usage is something like the following:*/
    
    //drawTriangleMesh();

    
    gridGap = 50; // Gap between meshes
    margin  = 50; // margin from window edges
    
    ofPushMatrix();
    /*ofTranslate(margin, margin);
    
    
    // Draw triangle
    drawTriangle(100);
    
    // Draw square
    ofTranslate(100 + gridGap,0); // Move the coordinate system 100 + gridGap pixels to right
    drawSquare(100);*/
    
    cam.begin();
    ofScale(1,1);
    ofTranslate(-quadPlane.getWidth()*0.5,-quadPlane.getHeight()*0.5);
    //drawTriangleMesh();
    //drawQuad();
    quadPlane.draw();
    cam.end();
    ofPopMatrix();
    
    gui.draw();
    
    
    // Draw fps
    utils.drawFPS(ptAlignment::TR);
    
}

void ofApp::drawTriangle(int _edgeSize) {
    meshTri.setMode(OF_PRIMITIVE_LINES);
    
    meshTri.clear();
    meshTri.addVertex(ofVec3f(0,0,0));
    meshTri.addVertex(ofVec3f(_edgeSize,0,0));
    meshTri.addVertex(ofVec3f(_edgeSize,_edgeSize,0));
    
    meshTri.addIndex(0); // start from the 1st vertex point
    meshTri.addIndex(1); // move to 2nd vertex
    meshTri.addIndex(1); // from 2nd vertex
    meshTri.addIndex(2); // to 3rd vertex
    meshTri.addIndex(2); // from 3rd vertex
    meshTri.addIndex(0); // 1st vertex
    
    meshTri.draw();
    
}

void ofApp::drawSquare(int _edgeSize) {
    meshSquare.setMode(OF_PRIMITIVE_LINES);
    
    
    meshSquare.clear();
    meshSquare.addVertex(ofVec3f(0,0,0));
    meshSquare.addVertex(ofVec3f(_edgeSize,0,0));
    meshSquare.addVertex(ofVec3f(_edgeSize,_edgeSize,0));
    meshSquare.addVertex(ofVec3f(0,_edgeSize,0));
    
    meshSquare.addIndex(0);
    meshSquare.addIndex(1);
    meshSquare.addIndex(1);
    meshSquare.addIndex(2);
    meshSquare.addIndex(2);
    meshSquare.addIndex(3);
    meshSquare.addIndex(3);
    meshSquare.addIndex(0);
    
    meshSquare.draw();
}

void ofApp::drawTriangleMesh() {
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    int cc  = 0;
    meshGap = 50;                               // gap between vertex points
    meshW   = ofGetWidth() - meshGap * 2;           // total width of the mesh
    meshH   = ofGetHeight() - meshGap * 2;          // total height of the mesh
    
    // Calculate the grid size according to the give resolution
    meshRes = 80;
    meshW = floor(ofGetWidth() / meshRes);
    meshH = floor(ofGetHeight() / meshRes);
    
    //ofLog() << "meshW : " << meshW;
    //ofLog() << "meshH : " << meshH;
    
    
    
    
    for (int y = 0; y < meshH; y++){
        for (int x = 0; x < meshW; x++){
            mesh.addVertex(ofPoint(x*meshRes, y*meshRes, ofRandom(-10,10))); // make a new vertex
            mesh.addColor(ofFloatColor(1,1, 1));  // add a color at that vertex
            ofDrawBitmapStringHighlight(ofToString(cc), x*meshRes, y*meshRes);
            cc++;
        }
    }
    
    for (int y = 0; y < meshH-1; y++){
        for (int x=0; x < meshW-1; x++){
            mesh.addIndex(x+y*meshW);         // 0  meshH = 9, meshW = 12
            mesh.addIndex((x+1)+y*meshW);     // 1
            mesh.addIndex(x+(y+1)*meshW);     // 12
            
            mesh.addIndex((x+1)+y*meshW);     // 1
            mesh.addIndex((x+1)+(y+1)*meshW); // 13
            mesh.addIndex(x+(y+1)*meshW);     // 12
        }
    }
    mesh.drawWireframe();

}

void ofApp::drawQuad() {
    
    quad.setMode(OF_PRIMITIVE_LINES);
    
    int cc  = 0;
    meshGap = 50;                               // gap between vertex points
    meshW   = ofGetWidth() - meshGap * 2;           // total width of the mesh
    meshH   = ofGetHeight() - meshGap * 2;          // total height of the mesh
    
    // Calculate the grid size according to the give resolution
    meshRes = 80;
    meshW = floor(ofGetWidth() / meshRes);
    meshH = floor(ofGetHeight() / meshRes);
    
    //ofLog() << "meshW : " << meshW;
    //ofLog() << "meshH : " << meshH;
    
    quad.clear();
    
    float time = ofGetElapsedTimef();   // iterating value
    float freq = 3.0;                   // the speed of movement
    float displacementScale = 50;       // movement amount in pixels
    
    for (int y = 0; y < meshH; y++){
        for (int x = 0; x < meshW; x++){
            
            time +=0.2;                 // change this increment to alter movement difference between vertices
            float zVal = ofSignedNoise(time*freq) * displacementScale;
            quad.addVertex(ofPoint(x*meshRes, y*meshRes, zVal)); // make a new vertex
            quad.addColor(ofFloatColor(1,1, 1));  // add a color at that vertex
            //ofDrawBitmapStringHighlight(ofToString(cc), x*meshRes, y*meshRes);
            cc++;
        }
    }
   // ofLog() << "size: " <<  quad.getVertices().size() << ": : " << meshH*meshW;
    for (int y = 0; y < meshH-1; y++){
        for (int x=0; x < meshW-1; x++){
           
            quad.addIndex(x+y*meshW);         // 0  meshH = 9, meshW = 12
            quad.addIndex((x+1)+y*meshW);     // 1
            quad.addIndex((x+1)+y*meshW);     // 1
            quad.addIndex((x+1)+(y+1)*meshW); // 13
            quad.addIndex((x+1)+(y+1)*meshW); // 13
            quad.addIndex(x+(y+1)*meshW);     // 12
            quad.addIndex(x+(y+1)*meshW);     // 12
            quad.addIndex(x+y*meshW);         // 0
        }
    }
    
    quad.drawWireframe();
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
