#version 330 core

in vec2 TexCoord;
in vec3 OurColor;

out vec4 FragColor;

uniform sampler2D uTexture;

void main() {
    vec4 texColor = texture(uTexture, TexCoord);
    FragColor = texColor * vec4(OurColor, 1.0);
}