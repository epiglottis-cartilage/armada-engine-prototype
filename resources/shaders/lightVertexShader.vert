#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform mat4 matrixModel;

layout (std140, binding = 0) uniform CameraMatrices
{
    mat4 matrixView;
    mat4 matrixProjection;
    vec3 positionCamera;
};

void main()
{

    gl_Position = matrixProjection * matrixView * matrixModel  * vec4(position, 1.0f);

}
