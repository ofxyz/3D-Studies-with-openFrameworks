#pragma once

#include "ofMain.h"
#include "ptUtils.h"
#include "ofxGui.h"
#include "quadPlaneWireFrame.h"

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
		
    ofMesh quad;
    void drawQuad();
    int meshW, meshH, meshGap;
    int meshRes;
    
    ofMesh mesh;
    ofMesh meshTri;
    ofMesh meshSquare;

    void drawTriangleMesh();
    
    void drawTriangle(int _edgeSize);
    void drawSquare(int _edgeSize);
    
    
    int gridGap;
    int margin;
    
    float t;
    float d;
    
    ptUtils utils;
    ofEasyCam cam;
    quadPlaneWireFrame quadPlane;
    ofxPanel gui;
};
