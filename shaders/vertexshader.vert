#version 330 core
layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 color;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

uniform mat4 matrixModel;
uniform mat4 matrixView;
uniform mat4 matrixProjection;

//out vec4 vertexColor;
out vec2 TexCoord;
uniform mat3 matrixNormal;

out vec3 vertNormalOut;
out vec3 FragPos;

void main()
{

    vertNormalOut = mat3(transpose(inverse(matrixModel))) * normal;
//    vertNormalOut =  normal;

    FragPos = vec3(matrixModel * vec4(position, 1.0f));

    //gl_Position = vec4(position.x + offsetTriangle.x, -position.y + offsetTriangle.y, offsetTriangle.z, 1.0);
    gl_Position = matrixProjection * matrixView * matrixModel  * vec4(position, 1.0f);

    
    //vertexColor = vec4((gl_Position.xyz + 0.5f)/2.0f, 1.0f);
    //vertexColor = vec4(color, 1.0f);
    TexCoord = vec2(texCoord.x, 1.0f - texCoord.y);
}








