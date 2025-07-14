# version 330
in vec2 TexCoordOutput;
out vec4 FragColor;

uniform sampler2D texture0;

void main()
{
    FragColor = texture(texture0, TexCoordOutput);
    //* vec4(1.0, 0.0, 0.0, 1.0);
}