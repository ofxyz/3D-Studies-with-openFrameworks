#pragma once

#include "ofMain.h"
#include "baseMesh.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

    baseMesh *mesh;
    ofEasyCam camera;
    ofLight pointLight;
    glm::vec3 lightLocation,lightAttenuation,cameraLocation;

};
