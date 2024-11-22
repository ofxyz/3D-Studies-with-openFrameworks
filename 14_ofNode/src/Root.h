#ifndef ROOT_H
#define ROOT_H

class Root: public ofNode {
private:
    glm::vec3 vel, pos;


    ofBoxPrimitive lWing;
    ofBoxPrimitive rWing;
    ofBoxPrimitive lbWing;
    ofBoxPrimitive rbWing;
    ofConePrimitive head;
    ofConePrimitive tail;
public:
    ofParameter<float> camMoveSpeed = {"Fly Movement Speed", 0.0008, 0, 0.004};
    ofParameter<glm::vec3> camMoveRange = {"Fly Movement Range", glm::vec3(100), glm::vec3(0), glm::vec3(6000)};
    ofParameter<float> wingSpeed = {"Fly wing Speed", 12, 1, 40};
    ofNode fly;

    void setup(glm::vec3 p) {
        vel = glm::vec3(1, 0,0);
        pos = p;
        fly.move(p);

        glm::vec3 wingSize(180, 2, 30);
        glm::vec3 wingBackSize(160, 2, 30);
        glm::vec3 tailSize(8, 180, 2);

        head.setParent(fly);
        lWing.setParent(fly);
        rWing.setParent(fly);
        lbWing.setParent(fly);
        rbWing.setParent(fly);
        tail.setParent(fly);

        head.set(15,40);
        tail.set(tailSize.x, tailSize.y);

        glm::vec3 headOffset(0, -55, 0);
        for (auto&v : head.getMesh().getVertices())
        {
            v += headOffset / 2.0;
        }

        // Front wings
        lWing.set(wingSize.x, wingSize.y, wingSize.z);
        rWing.set(wingSize.x, wingSize.y, wingSize.z);

        glm::vec3 rWingOffset(wingSize.x, 0, -wingSize.z*0.5);

        //rWing.rotateDeg(90, glm::vec3(1,0,0));
        //lWing.setOrientation(glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
        //lWing.setGlobalOrientation(glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
        //move all the vertices so these start at 0,0
        for (auto&v : rWing.getMesh().getVertices())
        {
            v += rWingOffset / 2.0;
        }

        glm::vec3 lrWingOffset(-wingSize.x, 0, -wingSize.z*0.5);

        //move all the vertices so these start at 0,0
        for (auto&v : lWing.getMesh().getVertices())
        {
            v += lrWingOffset / 2.0;
        }


        // Back wings
        lbWing.set(wingBackSize.x, wingBackSize.y, wingBackSize.z);
        rbWing.set(wingBackSize.x, wingBackSize.y, wingBackSize.z);

        glm::vec3 rbWingOffset(wingBackSize.x, 0, -wingBackSize.z*2.1);

        for (auto&v : rbWing.getMesh().getVertices())
        {
            v += rbWingOffset / 2.0;
        }

        glm::vec3 lrbWingOffset(-wingBackSize.x, 0, -wingBackSize.z*2.1);

        //move all the vertices so these start at 0,0
        for (auto&v : lbWing.getMesh().getVertices())
        {
            v += lrbWingOffset / 2.0;
        }


        // Tail Offsett
        glm::vec3 tailOffset(0, -tailSize.y - wingSize.z*3, 0);

        //move all the vertices so these start at 0,0
        for (auto&v : tail.getMesh().getVertices())
        {
            v += tailOffset / 2.0;
        }
    }

    void update() {
        auto noise_seed     = glm::vec3(0.304, 0.096, 0.6);
        auto noise_location = glm::vec3(
                                        ofMap(ofNoise(noise_seed.x, ofGetFrameNum() * camMoveSpeed), 0, 1, -camMoveRange->x, camMoveRange->x),
                                        ofMap(ofNoise(noise_seed.y, ofGetFrameNum() * camMoveSpeed), 0, 1, -camMoveRange->y, camMoveRange->y),
                                        ofMap(ofNoise(noise_seed.z, ofGetFrameNum() * camMoveSpeed), 0, 1, -camMoveRange->z, camMoveRange->z));

        fly.setPosition(noise_location);
        fly.lookAt(noise_location);

        // Head orientation
        head.setOrientation(glm::angleAxis(ofMap(sin(ofGetElapsedTimef()*wingSpeed*0.125), -1, 1, PI * 0.125,  -PI*0.125), glm::vec3(1, 1, 0)));
        head.rotateDeg(-90, glm::vec3(1,0,0));

        // Front wings orientation
        lWing.setOrientation(glm::angleAxis(ofMap(sin(ofGetElapsedTimef()*wingSpeed), -1, 1, -PI * 0.25, PI*0.25), glm::vec3(0, 0, 1)));
        rWing.setOrientation(glm::angleAxis(ofMap(sin(ofGetElapsedTimef()*wingSpeed), -1, 1, PI * 0.25, -PI*0.25), glm::vec3(0, 0, 1)));

        // Back wings orientation
        lbWing.setOrientation(glm::angleAxis(ofMap(cos(ofGetElapsedTimef()*wingSpeed), -1, 1, -PI * 0.25, PI*0.25), glm::vec3(0, 0, 1)));
        rbWing.setOrientation(glm::angleAxis(ofMap(cos(ofGetElapsedTimef()*wingSpeed), -1, 1, PI * 0.25, -PI*0.25), glm::vec3(0, 0, 1)));

        // Tail orientation
        tail.setOrientation(glm::angleAxis(ofMap(cos(ofGetElapsedTimef()*wingSpeed*0.025), -1, 1, PI * 0.05,  -PI*0.05), glm::vec3(1, 1, 0)));
        tail.rotateDeg(90, glm::vec3(1,0,0));

    }

    void draw() {
        ofPushStyle();
        ofSetHexColor(0xffcc00);
        ofNoFill();
        fly.draw();
        head.drawWireframe();
        rWing.drawWireframe();
        lWing.drawWireframe();

        // back wings
        rbWing.drawWireframe();
        lbWing.drawWireframe();

        // draw tail
        tail.drawWireframe();

        //ofDrawSphere(100);
        ofDrawAxis(210);
        ofPopStyle();
    }
};

#endif // ROOT_H
