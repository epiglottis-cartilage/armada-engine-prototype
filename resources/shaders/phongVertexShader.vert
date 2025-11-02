#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out VS_OUT {
    vec3 fragPos;
    vec2 TexCoord;
    mat3 TBN;
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
    vec3 T = normalize(mat3(matrixModel) * tangent);
    vec3 B = normalize(mat3(matrixModel) * bitangent);
    vec3 N = normalize(mat3(matrixModel) * normal);

    T = normalize(T - dot(T, N) * N);
    B = cross(N, T);

    vs_out.TBN = mat3(T, B, N);
    vs_out.fragPos = vec3(matrixModel * vec4(position, 1.0f));//what does this do???
//    vs_out.normal = mat3(transpose(inverse(matrixModel))) * normal;
    gl_Position = matrixProjection * matrixView * matrixModel  * vec4(position, 1.0f);
    vs_out.TexCoord = texCoords;
}








