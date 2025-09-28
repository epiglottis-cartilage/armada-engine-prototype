#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 matrixModel;

layout (std140) uniform CameraMatrices
{
    mat4 matrixProjection;
    mat4 matrixView;
};

void main()
{

    gl_Position = matrixProjection * matrixView * matrixModel  * vec4(position, 1.0f);

    
}








