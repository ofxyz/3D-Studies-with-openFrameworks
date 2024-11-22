#version 120

uniform sampler2D colormap;
uniform sampler2D bumpmap;
varying vec2  TexCoord;
uniform float maxHeight;
uniform vec3 bumpColorMult;
uniform float time;
uniform float displacementY;


varying vec3 e;
varying vec3 n;

float mod(float x, float y) {
    return x - y * floor(x/y);
}

void main(void) {
    
    e = normalize( vec3( gl_ModelViewProjectionMatrix * vec4( gl_Vertex.xyz, 1.0 ) ) );
    n = normalize( gl_NormalMatrix * gl_Normal );
    
	TexCoord = gl_MultiTexCoord0.st;

	vec4 bumpColor = texture2D(bumpmap, TexCoord);
    
	float df = bumpColorMult.x * bumpColor.x
                + bumpColorMult.y * bumpColor.y
                + bumpColorMult.z * bumpColor.z;
    
    vec4 newVertexPos = vec4(0.);

   /* float displacementY = abs(sin(time * .52) * 3.);
    
	
    
    
   if ( sin(time * 0.25) < gl_Vertex.x + 0.01) {
       //pos.x += noiseFunction(vec2(pos.y, time));
       //pos.z += 0.1;
       newVertexPos = gl_Vertex;
   }else{
      
       //newVertexPos = vec4(gl_Normal * displacementY, 0.0) + gl_Vertex;
       newVertexPos = vec4(gl_Normal * df * float(maxHeight) * displacementY, 0.0) + gl_Vertex;
   }*/
    
    //newVertexPos = vec4(gl_Normal * df * float(maxHeight) * displacementY, 0.0) + gl_Vertex;

    newVertexPos = vec4(gl_Normal * df * float(maxHeight), 0.0) + gl_Vertex;
	gl_Position = gl_ModelViewProjectionMatrix * newVertexPos;
} 
