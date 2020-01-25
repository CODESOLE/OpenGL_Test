#version 330 core
layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
uniform mat4 u_MVP;

void main() {
     gl_Position = u_MVP * inPosition; 
     v_TexCoord = texCoord;
}