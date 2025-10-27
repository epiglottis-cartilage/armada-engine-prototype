#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out VS_OUT {
    vec3 fragPos;
    vec3 normal;
    vec2 TexCoord;
} vs_out;

//transform to camera , to screen
layout (std140) uniform CameraMatrices
{
    mat4 matrixView;
    mat4 matrixProjection;
    vec3 positionCamera;
};


uniform mat4 matrixModel;

void main()
{
    vs_out.fragPos = vec3(matrixModel * vec4(position, 1.0f));//what does this do???
    vs_out.normal = mat3(transpose(inverse(matrixModel))) * normal;
    gl_Position = matrixProjection * matrixView * matrixModel  * vec4(position, 1.0f);
    vs_out.TexCoord = texCoords;
}








