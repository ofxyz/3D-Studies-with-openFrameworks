#include "var.h"
#include "ofGLProgrammableRenderer.h"
#include "ofxAssimpModelLoader.h"

class xApp : public ofBaseApp{

	public:
		ofxAssimpModelLoader model;
		ofVboMesh mesh;

		void setup() {
		        ofSetFrameRate(60);
		        ofSetVerticalSync(true);

			bAnimate = false;
			bAnimateMouse = false;
			animationPosition = 0;
			model.loadModel("model/wolf.dae");
			model.setPosition( ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0 );
			model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
			model.playAllAnimations();

			if(!bAnimate) {
			        model.setPausedForAllAnimations(true);
			}

			w=ofGetScreenWidth();
			h=ofGetScreenHeight();

		        shader.load( "shaders/instanced.vert", "shaders/instanced.frag" );

			camera.setFarClip(100000);

			mesh=model.getMesh(0);//!
		}

		void update() {
			ofSetWindowTitle(ofToString(ofGetFrameRate()));
			model.update();
		       	animationPosition = ofMap(counter,0,55,0.0,1.0);
			counter++;
			if(counter>55)
				counter=0;
			model.setPositionForAllAnimations(animationPosition);
		}

		void draw() {
			ofBackgroundGradient( ofColor(210), ofColor(10), OF_GRADIENT_BAR);

			ofEnableDepthTest();
			camera.begin();

			shader.begin();
			shader.setUniform4f("globalColor",1.0,0.4,0.1,1.0);
			glEnable(GL_CULL_FACE);
		        glCullFace(GL_BACK);

				  ofPushMatrix();
				  mesh.drawInstanced(OF_MESH_WIREFRAME, 128*128);
				  ofPopMatrix();

		        glDisable(GL_CULL_FACE);
			shader.end();
			ofDisableDepthTest();
			camera.end();

		}

		void keyPressed(int key) {
			if(key == 'f')
				ofToggleFullscreen();
			if(key == '1'){
				model.loadModel("model/wolf.dae");
				mesh=model.getMesh(0);//!
			}
			if(key == '2'){
				model.loadModel("model/elephant.dae");
				mesh=model.getMesh(0);//!
			}
		}

};

int main(){
    ofGLWindowSettings settings;
    settings.setSize(1024, 768);
    settings.setGLVersion(3, 2);
    ofCreateWindow(settings);
    
    //ofAppGlutWindow window;
    //ofSetupOpenGL(&window, 1280, 720, OF_WINDOW);
    ofRunApp(new xApp());
}
