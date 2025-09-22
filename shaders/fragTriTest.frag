# version 330
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D textureBaseColor;

void main()
{
    FragColor = texture(textureBaseColor, TexCoords);
}