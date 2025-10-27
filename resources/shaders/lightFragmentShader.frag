#version 450 core
out vec4 color;
uniform float flIntensity;

void main() {
    color = colorLight * flIntensity;
}

