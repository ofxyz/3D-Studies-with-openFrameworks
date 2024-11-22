#version 150

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;

uniform vec4 globalColor = vec4(1.0);

in vec4  position;
in vec2  texcoord;
in vec4  color_coord;
in vec3  normal;

out vec4 colorVarying;
out vec2 texCoordVarying;

void main()
{

	int iCount = 128;
	
	float instanceX = float(gl_InstanceID%(iCount) - iCount/2) / 128.0;
	float instanceY = float(gl_InstanceID/(iCount) - iCount/2) / 128.0;

	colorVarying = globalColor;
	
	vec4 vPos = position;
	vPos = vPos + vec4(instanceX*15*128,instanceY*15*128, 0,0);
	gl_Position = projectionMatrix * modelViewMatrix * vPos  ;
}
