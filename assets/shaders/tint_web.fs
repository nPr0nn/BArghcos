#version 100

precision mediump float;

varying vec2 fragTexCoord;
varying vec4 fragColor;

uniform vec4 tintColor;
uniform sampler2D texture0;

void main()
{ 
    vec4 texel = texture2D(texture0, fragTexCoord);  // Get texel color
    gl_FragColor = vec4(tintColor.rgb, texel.a);
}

