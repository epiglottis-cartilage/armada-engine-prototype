#version 330 core

uniform sampler2D textureBaseColor;
out vec4 color;
in vec2 TexCoord;

void main()
{
    color = texture(textureBaseColor, TexCoord);
}









