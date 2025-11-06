#version 450 core
layout (triangles) in;
layout (line_strip, max_vertices = 3) out;

const float MAGNITUDE = 0.4f;

in VS_OUT {
    vec3 fragPos;
    vec2 TexCoord;
    mat3 TBN;
} vs_out[];


uniform sampler2D textureNormalMap;

void GenerateLine(int index){

    vec3 normal = normalize(texture(textureNormalMap, vs_out[index].TexCoord).rgb * 2.0 - 1.0);
    normal = normalize(vs_out[index].TBN * normal);

    gl_Position = gl_in[index].gl_Position ;
    EmitVertex();

    gl_Position = gl_in[index].gl_Position + vec4(normal, 0.0f) * MAGNITUDE;
    EmitVertex();
    EndPrimitive();
}

void main() {
    for(int i = 0; i < 3; i++){
        GenerateLine(i);
    }
}