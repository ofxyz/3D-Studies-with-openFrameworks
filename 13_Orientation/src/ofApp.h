#pragma once

#include "ofMain.h"

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
    
    
    void drawCube(glm::vec3 position = glm::vec3( 0, 0, 0 ), ofQuaternion orientation = ofQuaternion( 0, 0, 0, -1 ));
    void drawXYZ(glm::vec3 position = glm::vec3( 0, 0, 0 ), ofQuaternion orientation = ofQuaternion( 0, 0, 0, -1 ), uint32_t line_width = 1);
    
    ofLight    light;
    ofEasyCam cam;
    
    ofBoxPrimitive box;
    ofQuaternion orientation{ 0, 0, 0, -1 };
    
    bool rotating = true;

		
};
