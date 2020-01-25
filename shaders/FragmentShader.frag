#version 330 core

out vec4 fragColor;
in vec2 v_TexCoord;

//uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main() {
    fragColor = texture(u_Texture,v_TexCoord);
}