#version 150

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform sampler2D tex0;
uniform vec4 globalColor;
uniform vec2 offset;
uniform vec3 xPos;
uniform float counter;
uniform vec3 dist;
in vec4  position;
in mat4 pMat;
in mat4 mMat;
out vec4 color;

int iCount;

void main()
{
	iCount = int(counter);
	
	float instanceX = float(gl_InstanceID%(iCount) - iCount/2) / float(iCount);
	float instanceY = float(gl_InstanceID/(iCount) - iCount/2) / float(iCount);

        vec2 samplePos = vec2( instanceX-offset.x, instanceY-offset.y );
        vec4 pixelDepth = texture(tex0,samplePos);

        color = globalColor+pixelDepth;

        vec4 vPos = position;

        vPos = vPos + vec4(pixelDepth.g * iCount * dist.x, pixelDepth.g * iCount * dist.y,  pixelDepth.g * iCount * dist.z, 0);

	vPos.x = vPos.x + 4.0 * xPos.x * instanceX;
	vPos.y = vPos.y + 4.0 * xPos.y * instanceY;
        vPos.z = vPos.z + instanceX+instanceY * (10.0*xPos.z);

	gl_Position = projectionMatrix * modelViewMatrix * vPos;
}
