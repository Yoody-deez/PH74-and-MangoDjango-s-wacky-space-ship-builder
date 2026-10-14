#version 330 core

layout (location = 0) in vec2 aPos;    
layout (location = 1) in vec2 aTexCoord; 

out vec2 TexCoord;
out vec3 OurColor;

uniform mat4 uProjection;
uniform vec2 uPosition;
uniform vec2 uSize;

void main() {
    vec2 scaledPos = aPos * uSize + uPosition;
    gl_Position = uProjection * vec4(scaledPos, 0.0, 1.0);
    TexCoord = aTexCoord;
    OurColor = vec3(1.0);
}