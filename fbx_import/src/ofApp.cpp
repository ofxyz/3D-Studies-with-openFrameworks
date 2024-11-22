#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofDisableArbTex();
    
    
    
    // Check for models folder
    checkFolder();
    
    ofxGuiSetFont( "../../../../../../assets/fonts/DIN.otf", 8 );
    ofxGuiSetDefaultWidth( 300 );
    ofxGuiSetFillColor(ofColor(255,204,0,200));
    
    string xmlSettingsPath = "settings.xml";
    gui.setup( "FBX Properties", xmlSettingsPath );
    gui.add(isDebug.set("ENABLE GUI INFO", true));
    // Cam Group
    camGUI.setName("Camera Properties");
    
    camGUI.add(camPos.set("Camera Position",glm::vec3(0,3,100),glm::vec3(-1000,-1000,-1000),glm::vec3(1000,1000,1000)));
    //camGUI.add(camRot.set("Camera Rotation",glm::vec3(0,0,0),glm::vec3(-1,-1,-1),glm::vec3(1,1,1)));
    
    lightGUI.setName("Light Props");
    lightGUI.add(lightPos.set("Position",glm::vec3(0,0,0),glm::vec3(-1000,-1000,-1000),glm::vec3(1000,1000,1000)));
    
    gui.add(camGUI);
    gui.add(lightGUI);
    
    gui.add(gridPos.set("Grid Position",glm::vec3(0,-100,0),glm::vec3(-1000,-1000,-1000),glm::vec3(1000,1000,1000)));
    
    gui.loadFromFile(xmlSettingsPath);
    
    
    // setup folder gui
    guiFolder.setup("Folder Items");
    
    
    
    // itemList = new ofParameterGroup();
    itemList.setName("Select File");
    
    // Drop down list
    items.resize(filePaths.size());
    selectedId = -1;
    preId = -1;
    for (int i = 0; i < filePaths.size(); i++) {
        items[i].set(dir.getFiles().at(i).getFileName(), false);
        items[i].addListener(this, &ofApp::filesCallback);
        itemList.add(items[i]);
    }
    
    guiFolder.add(itemList);
    
    
    camera.lookAt( glm::vec3(0,0,0) );
    camera.setDistance( 550 );
    camera.setFarClip(6000);
    camera.setNearClip( .5f );
    
    
    bRenderNormals  = false;
    bRenderMeshes   = true;
    bDrawBones      = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // perform any bone manipulation here //
    light.setPosition(lightPos);
    
    fbxMan[currentImage].earlyUpdate();
    
    glm::vec3 target( ofMap( ofGetMouseX(), 0, ofGetWidth(), -10, 10, true), fbxMan[currentImage].getPosition().y, fbxMan[currentImage].getPosition().z+10 );
    fbxMan[currentImage].lookAt( target );
    fbxMan[currentImage].panDeg( 180 );
    
    
    fbxMan[currentImage].lateUpdate();
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient( ofColor(40,40,40), ofColor(0,0,0), OF_GRADIENT_CIRCULAR);
    
    camera.setPosition( camPos->x, camPos->y, camPos->z);
    camera.draw();
    
    // draw a grid on the floor
    ofSetColor( ofColor(60) );
    ofPushMatrix();
    ofTranslate(gridPos->x, gridPos->y,gridPos->z);
    ofRotate(90, 0, 0, -1);
    
    ofDrawGridPlane( 100, 10, false );
    ofPopMatrix();
    
    
    
    ofSetColor(255, 255, 255);
    
    glEnable( GL_DEPTH_TEST );
    
    
    camera.begin();
    
    ofEnableLighting();
    light.enable();
    
    if( bRenderMeshes ) {
        ofSetColor( 255, 255, 255 );
        fbxMan[currentImage].draw();
    }
    
    if( bRenderWireFrame ) {
        ofSetColor( 255, 255, 255 );
        fbxMan[currentImage].drawMeshWireframes();
    }
    
    light.disable();
    ofDisableLighting();
    
    if(bDrawBones) {
        fbxMan[currentImage].drawSkeletons( 6. );
    }
    
    if( bRenderNormals ) {
        ofSetColor( 255, 0, 255 );
        fbxMan[currentImage].drawMeshNormals( 1, false );
    }
    
    
    ofSetColor( light.getDiffuseColor() );
    light.draw();
    
    camera.end();
    
    glDisable( GL_DEPTH_TEST );
    
    if(isDebug)
    {
        int numBones = 0;
        vector< shared_ptr<ofxFBXSkeleton> >& skeletons = fbxMan[currentImage].getSkeletons();
        for( int i = 0; i < skeletons.size(); i++ ) {
            numBones += skeletons[i]->getNumBones();
        }
        
        ofSetColor( 60, 60, 60 );
        stringstream ds;
        ds << "Render normals (n): " << bRenderNormals << endl;
        ds << "Render meshes (m): " << bRenderMeshes << endl;
        ds << "Render " << numBones << " bones (b): " << bDrawBones << endl;
        if( fbxMan[currentImage].areAnimationsEnabled() ) {
            ds << "Toggle play/pause (spacebar): playing: " << fbxMan[currentImage].getCurrentAnimation().isPlaying() << endl;
            ds << "Previous/Next animation (up/down): " << fbxMan[currentImage].getCurrentAnimation().name << endl;
        }
        ds << "Scale is " << fbxMan[currentImage].getScale() << endl;
        if( fbxMan[currentImage].getNumPoses() > 0 ) {
            ds << "Pose: " << fbxMan[currentImage].getCurrentPose()->getName() << " num poses: " << fbxMan[currentImage].getNumPoses() << " enabled (p): " << fbxMan[currentImage].arePosesEnabled() << endl;
        }
        ofDrawBitmapString( ds.str(), 50, 30 );
        
        
        for(int i = 0; i < fbxMan[currentImage].getNumAnimations(); i++ ) {
            stringstream ss;
            ofxFBXAnimation& anim = fbxMan[currentImage].getAnimation( i );
            if( i == fbxMan[currentImage].getCurrentAnimationIndex() ) {
                ss << "- ";
            }
            ss << "name: " << anim.name << " " << ofToString(anim.getPositionSeconds(), 3) << " | " << ofToString(anim.getDurationSeconds(), 3) << " frame: " << anim.getFrameNum() << " / " << anim.getTotalNumFrames() << endl;
            ofDrawBitmapString( ss.str(), 50, i * 30 + 150 );
        }
        
        
        
        gui.setPosition(ofGetWidth() - gui.getWidth() - 10, 0);
        gui.draw();
        
        
        guiFolder.setPosition(gui.getPosition().x - gui.getWidth() - 1,gui.getPosition().y);
        guiFolder.draw();
    }
}

void ofApp::checkFolder() {
    
    dir.listDir("models/");
    dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
    
    //allocate the vector to have as many ofImages as files
    if( dir.size() ){
        filePaths.resize(dir.size());
    }
    
    ofxFBXSource::Scene::Settings settings;
    settings.printInfo = false;
    settings.cacheMeshKeyframes = false;
    
    fbxMan.resize((int)dir.size());
    
    for(int i = 0; i < (int)dir.size(); i++){
        filePaths[i] = dir.getPath(i);
        
        settings.filePath = filePaths[i];
        
        ofLogNotice("Model " + ofToString(i) + ":" + filePaths[i]);
        
        if( fbxMan[i].load(settings) ) {
            cout << "ofApp :: loaded the scene OK" << endl;
        } else {
            cout << "ofApp :: Error loading the scene" << endl;
        }

        
        fbxMan[i].setAnimation(1);
    }
    currentImage = 0;
    
    camera.lookAt( glm::vec3(0,0,0) );
    camera.setDistance( 550 );
    camera.setFarClip(6000);
    camera.setNearClip( .5f );
    
    
    
}

void ofApp::filesCallback(bool & _val) {
    
    int i;
    
    if(_val) {
        for(i = 0; i < filePaths.size(); i++){
            if(&items[i].get() == &_val){
                selectedId = i;
                break;
            }
        }
        
        
        for(int i = 0; i < filePaths.size(); i++){
            items[i].removeListener(this, &ofApp::filesCallback);
            items[i].set(false);
            items[i].addListener(this, &ofApp::filesCallback);
        }
        
        items[selectedId] = true;
    }
    
    currentImage = selectedId;
    
    
    fbxMan[currentImage].transition(0, 1, 0.4);
    
    itemList.setName("Selected File :" + items[selectedId].getName());
    guiFolder.getGroup("Selected File :" + items[selectedId].getName()).minimize();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    //if(scene[currentImage].getNumAnimations() > 1) {
        if(key == OF_KEY_DOWN ) {
            int newAnimIndex = fbxMan[currentImage].getCurrentAnimationIndex()+1;
            if(newAnimIndex > fbxMan[currentImage].getNumAnimations()-1 ) {
                newAnimIndex = 0;
            }
            fbxMan[currentImage].setAnimation( newAnimIndex );
            
        }
        if(key == OF_KEY_UP ) {
            int newAnimIndex = fbxMan[currentImage].getCurrentAnimationIndex()-1;
            if(newAnimIndex < 0 ) {
                newAnimIndex = fbxMan[currentImage].getNumAnimations()-1;
            }
            fbxMan[currentImage].setAnimation( newAnimIndex );
        }
    //}
    
    if(key == OF_KEY_LEFT) {
        if (dir.size() > 0){
            currentImage++;
            currentImage %= dir.size();
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    if(key == ' ') {
        fbxMan[currentImage].getCurrentAnimation().togglePlayPause();
    }
    if(key == 'n') {
        bRenderNormals = !bRenderNormals;
    }
    if(key == 'm') {
        bRenderMeshes = !bRenderMeshes;
    }
    if(key == 'b') {
        bDrawBones = !bDrawBones;
    }
    
    if(key == 'w') {
        bRenderWireFrame = !bRenderWireFrame;
    }
    
    if(key == 'f') {
        ofToggleFullscreen();
    }
    
    if(key == 'g')
        isDebug = !isDebug;
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
