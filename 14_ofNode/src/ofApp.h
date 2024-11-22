#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Root.h"

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

    Root main;

    Root main2;

    // easycam
    ofEasyCam cam;
    ofLight light;

    bool guiEnabled;
    ofxPanel gui;
    ofParameter<glm::vec3> lightPos = {"Light Pos", glm::vec3(0), glm::vec3(0), glm::vec3(2000)};
    ofParameter<float> boom = {"Light Boom", 0, 0, 1000};
};
