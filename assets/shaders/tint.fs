#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform vec4 tintColor;
uniform sampler2D texture0;
out vec4 finalColor;

void main()
{ 
  vec4 texel = texture(texture0, fragTexCoord);   // Get texel color
  finalColor = vec4(tintColor.rgb, texel.a);
}


