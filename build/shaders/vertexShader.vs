#version 330 core

layout (location = 0) in vec2 aPos;    
layout (location = 1) in vec2 aTexCoord; 
layout (location = 2) in vec3 aColor;    
layout (location = 3) in vec2 aOffset; 

out vec2 TexCoord;
out vec3 OurColor;

uniform mat4 uProjection;

void main() {
    vec2 finalPos = aPos + aOffset;
    gl_Position = uProjection * vec4(finalPos, 0.0, 1.0);
    TexCoord = aTexCoord;
    OurColor = aColor;
}