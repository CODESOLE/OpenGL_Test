#version 330 core

out vec4 fragColor;
in vec4 v_color;



void main() {
    fragColor = v_color;
}