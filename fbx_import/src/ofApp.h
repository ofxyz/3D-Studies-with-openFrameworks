#pragma once

#include "ofMain.h"
#include "ofxFBX.h"
#include "ofxGui.h"
#include "ofxFBX.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofxPanel gui;
    ofParameterGroup camGUI;
    ofParameterGroup lightGUI;
    ofParameter<glm::vec3> camRot;
    ofParameter<glm::vec3> camPos;
    ofParameter<glm::vec3> gridPos;
    ofParameter<glm::vec3> lightPos;
    ofParameter<bool> isDebug;
    
    
    vector<ofParameter<bool>> items;
    void filesCallback(bool & _id);
    
    ofxPanel guiFolder;
    ofParameterGroup  itemList;
    
    //vector<ofxFBXScene> scene;
    ofEasyCam camera;
    vector<ofxFBX> fbxMan;
    
    
    bool bRenderNormals;
    bool bRenderMeshes;
    bool bDrawBones;
    bool bRenderWireFrame;
    
    ofLight light;
    
    //
    ofDirectory dir;
    vector<string> filePaths;
    int currentImage;
    void checkFolder();
    
    int selectedId,preId;

};
