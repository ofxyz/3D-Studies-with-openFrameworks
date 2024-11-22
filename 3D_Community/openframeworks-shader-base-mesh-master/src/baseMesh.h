#ifndef _BASEMESH
#define _BASEMESH

#include "ofMain.h"
#include "waveFrontLoader.h"

class baseMesh {

public:

    baseMesh();
    void draw(glm::vec3 &_lightLocation, glm::vec3 &_lightAttenuation, glm::vec3 &_cameraLocation);
    void update();
    
    void setupImportMesh(const char *fileName, bool loadMaterial);
    void setupCubeMesh(float _length, float _width, float _height);
    void setupSphereMesh(float _radius, int _resolution);
    void setupPlaneMesh(float _width, float _height, int rows, int columns);
    
    void scaleMesh(float scaleAmount);
    
    void addColors(float red, float green, float blue, float alpha);
    
protected:
    
    ofMesh mesh;
    vector<glm::vec3> originalVertices;

private:
    
    enum MeshType {
        
        IMPORT,
        CUBE,
        SPHERE,
        PLANE
    };
    
    typedef struct {
        
        float r;
        float g;
        float b;
        
    }
    UnitRGB;
    
    waveFrontLoader *objLoader;
    ofShader lightShader;
    int shaderColorSource;
    
    UnitRGB unitColor;
    float alphaColor;
    
    ofVec3f lightLocation;
    ofVec3f lightAttenuation;
    ofVec3f cameraLocation;
    
    UnitRGB mapToUnitRGB(float red255, float green255, float blue255);
    
    void storeOriginalMesh();

};

#endif
