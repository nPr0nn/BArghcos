#version 100

precision mediump float;

varying vec2 fragTexCoord;
varying vec4 fragColor;

uniform float time;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

uniform vec2 resolution;

void main()
{
    float baseOutlineSize = 4.0; // Base outline size
    float outlineSizeAmplitude = 4.0; // Amplitude of oscillation
    float outlineSizeFrequency = 1.0; // Frequency of oscillation
    vec4 outlineColor = vec4(0.8125, 0.9609, 0.9648, 1.0); 
    
    // Oscillate outlineSize with time
    float outlineSize = baseOutlineSize + outlineSizeAmplitude * sin(time * outlineSizeFrequency);
    
    vec4 texel = texture2D(texture0, fragTexCoord);   // Get texel color
    vec2 texelScale = vec2(0.0);

    texelScale.x = outlineSize / resolution.x;
    texelScale.y = outlineSize / resolution.y;

    // We sample four corner texels, but only for the alpha channel (this is for the outline)
    vec4 corners = vec4(0.0);
    corners.x = texture2D(texture0, fragTexCoord + vec2(texelScale.x, texelScale.y)).a;
    corners.y = texture2D(texture0, fragTexCoord + vec2(texelScale.x, -texelScale.y)).a;
    corners.z = texture2D(texture0, fragTexCoord + vec2(-texelScale.x, texelScale.y)).a;
    corners.w = texture2D(texture0, fragTexCoord + vec2(-texelScale.x, -texelScale.y)).a;
    float outline = min(dot(corners, vec4(1.0)), 1.0);
   
    vec4 color = mix(vec4(0.0), outlineColor, outline);

    // Output the final color
    gl_FragColor = mix(color, texel, texel.a);
}

