#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    
    terrainZPosOff = 0.1;
    
    scl = 20; // Set Scale of grids
    
    ofSetWindowShape(600, 600);
    
    terrainW = ofGetWidth() + 200;
    terrainH = ofGetHeight() + 200;


    e = 2.78;
    
    
    
    cols = terrainW / scl; // set rows per scl
    rows = terrainH / scl; // set columns per scl
    
    
    cout << "column: " << cols << endl;
    
    //mesh.setMode(OF_PRIMITIVE_POINTS);
    //mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    //mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    //mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    mesh.setMode(OF_PRIMITIVE_LINES);
    //mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    //mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
    
    flyingOff = -1;
    
    
    float randS = ofRandom(5);
    
    yoff = randS;
    terrainZPos = 50;
    
    float terrain[cols][rows];
    
    for (int j = 0; j < rows; j++) {
        xoff = randS;
        for (int i = 0 ; i < cols; i++) {
            
            
            terrain[i][j] = ofMap(ofNoise(yoff, xoff),0,1,0,50);
            float x = i*scl;
            float y = j*scl;
            //float z = ofRandom(-10,10);
            //float z = ofMap(ofNoise(yoff, xoff),0,1,0,50);
            
            
            float a = i * .05;
            float b = j * .05;
            
            float noise = ofMap(ofNoise(a, b),0,1,-50,50);
            
            
            float z = terrain[i][j];
            
            
            mesh.addVertex(ofVec3f(x,y,z));
            mesh.addColor(ofFloatColor(1,1,1));
            
            
            xoff += 0.05;
            
        }
         yoff += 0.05;
    }
    
    for (int j = 0; j < rows - 1 ; j++) {
        for (int i = 0 ; i < cols - 1; i++) {
    
            mesh.addIndex(i+j*cols);         // 0
            mesh.addIndex((i+1)+j*cols);     // 1
            mesh.addIndex(i+(j+1)*cols);     // 6
            
            mesh.addIndex((i+1)+j*cols);     // 1
            mesh.addIndex((i+1)+(j+1)*cols); // 7
            mesh.addIndex(i+(j+1)*cols);     // 6
        }
    }
    
    

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient( ofColor(40,40,40), ofColor(0,0,0), OF_GRADIENT_CIRCULAR);
    
    
    
    cam.begin();
    
    //-------------------------
    //-------------------------
    // START capture!
    //
    if(capture){
        ofBeginSaveScreenAsPDF("screenshot-"+ofGetTimestampString()+".ai", false);
    }
    //
    // START capture!
    //-------------------------
    //-------------------------
    
    
    ofPushMatrix();
    //
    ofTranslate(ofGetWidth()*0.5, ofGetHeight()*0.5 + 50);
    ofRotateX(0);
    //ofRotateZ(ofGetElapsedTimef()*10);
    
    ofTranslate(-terrainW*0.5, -terrainH*0.5);
    
    flyingOff -= 0.0005;
    //terrainZPos += terrainZPosOff;
    
    yoff = flyingOff;
    for (int j = 0; j < rows; j++) {
        xoff = 0;
        for (int i = 0 ; i < cols; i++) {
            float z = ofMap(ofNoise(xoff, yoff),0,1,terrainZPos,-1*terrainZPos);
            mesh.setVertex(i+j*cols, ofVec3f(mesh.getVertex(i+j*cols).x,mesh.getVertex(i+j*cols).y,z));
            xoff += 0.05;
        }
        yoff += 0.05;
    }

    
    if(terrainZPos > 60 || terrainZPos < 0)
        terrainZPosOff = terrainZPosOff*-1;
    
    //mesh.clear();
    //mesh.draw();
    
    mesh.drawWireframe();
    
    if(showIndices) {
        for (int j = 0; j < rows; j++) {
            for (int i = 0 ; i < cols; i++) {
                ofDrawBitmapStringHighlight(ofToString(i+j*cols), ofPoint(mesh.getVertex(i+j*cols).x,mesh.getVertex(i+j*cols).y));
            }
        }
    }
    ofPopMatrix();
    
    //-------------------------
    //-------------------------
    // End capture!
    //
    
    //once we have done all our drawing
    //we end the ouput which saves the file
    //and then we stop capturing
    if(capture){
        ofEndSaveScreenAsPDF();
        capture = false;
    }
    
    //
    // End capture!
    //-------------------------
    //-------------------------
    
    
    //ofBackground( 255, 255, 255 );
    /*
    ofSetColor( 0, 0, 0 );
    float time = ofGetElapsedTimef();
    for (int i=0; i<100; i++) {
        float ampX = ofGetWidth();
        float ampY = ofGetHeight();
        float speed = 0.1;
        float posX0 = i * 104.3 + 14.6;
        float posY0 = i * 53.3 + 35.2;
        
        //Get x and y using Perlin noise
        float x = ampX * ofNoise( time * speed + posX0 );
        float y = ampY * ofNoise( time * speed + posY0 );
        //ofCircle( x, y, 10 );
    }
    */
    cam.end();
    
    
    
   // drawFrameRate(); // Draw framerate
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //mesh.save("test.ply");
    
    if(key == 'c') {
        capture = true;
    }
    
    if(key == ' ')
        ofToggleFullscreen();
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
