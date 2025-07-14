#version 330 core
uniform sampler2D wallTexture;
//uniform float offsetTransparent;
out vec4 color;
//in vec4 vertexColor;
in vec2 TexCoord;
void main()
{
    //color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    //color = mix(texture(wallTexture, TexCoord), vertexColor, offsetTransparent);
    color = texture(wallTexture, TexCoord);
}









