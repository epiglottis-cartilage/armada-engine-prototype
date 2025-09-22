#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 matrixModel;
uniform mat4 matrixView;
uniform mat4 matrixProjection;

void main()
{

    gl_Position = matrixProjection * matrixView * matrixModel  * vec4(position, 1.0f);

    
}








