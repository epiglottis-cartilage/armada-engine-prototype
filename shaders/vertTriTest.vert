# version 330
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 TexCoord;
out vec2 TexCoordOutput;
void main(){

    gl_Position = vec4(aPos, 1.0, 1.0);
    TexCoordOutput = TexCoord;
    
}