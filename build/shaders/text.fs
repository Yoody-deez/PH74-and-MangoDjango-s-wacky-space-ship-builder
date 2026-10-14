#version 330 core

in vec2 TexCoord;
in vec3 OurColor;

out vec4 FragColor;

uniform sampler2D uTexture;

void main() {
    vec4 texColor = texture(uTexture, TexCoord);
    
    float alpha = texColor.r; 

    if (alpha < 0.1) {
        discard;
    }

    FragColor = vec4(OurColor, alpha);
}