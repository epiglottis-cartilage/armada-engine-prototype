#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

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
