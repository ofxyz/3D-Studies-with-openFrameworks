#version 120


uniform sampler2D colormap;
uniform sampler2D bumpmap;
varying vec2  TexCoord;

varying vec3 e;
varying vec3 n;

void main(void) {
    
    vec3 r = reflect( e, n );
    //r = e - 2. * dot( n, e ) * n;
    float m = 2. * sqrt( pow( r.x, 2. ) + pow( r.y, 2. ) + pow( r.z + 1., 2. ) );
    vec2 vN = r.xy / m + .5;

    vec3 base = texture2D( colormap, vN ).rgb;

    //gl_FragColor = vec4( base, 1.);
    
	gl_FragColor = texture2D(colormap, TexCoord );
    
    
    // make cpu running slow
    //gl_FragColor = mix (texture2D(colormap, TexCoord), texture2D(colormap, vN), 0.5);
    
}
