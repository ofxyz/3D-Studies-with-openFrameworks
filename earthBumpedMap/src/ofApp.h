#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAutoReloadedShader.h"

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
    
    
    ofImage colormap,bumpmap;
    ofxAutoReloadedShader shader;

    ofVboMesh mesh;
    ofxAutoReloadedShader shaderTex;

    ofxPanel gui;
    ofParameter<int> fadeAmnt = {"Fade Amount", 40, 1, 255};
    ofParameter<glm::vec3> bumpColorMult = {"Bump Color Multiplier", glm::vec3(0.3,0.59,0.11), glm::vec3(-1), glm::vec3(1)};
    ofParameter<int> sphereRad = {"Sphere Radius", 200, 10, 1000};
    ofParameter<int> sphereRes = {"Sphere Resolution", 400, 10, 1000};
    ofParameter<float> bumpLimit = {"Bump Limit", 0.5, 0., 1.};
    ofParameter<float> sphereRotspeed = {"Rotation speed", 1., 0., 100};

    ofParameter<bool> drawSphere = {"Draw Sphere", true};
    ofParameter<bool> drawMesh = {"Draw Mesh", false};

    void setSphereRes(int & res);

    ofEasyCam cam;
    float mult;
    ofLight light;
    ofFbo fbo;


    void drawFboTest(); // draws some test graphics into the two fbos
    bool isDebug;

};
