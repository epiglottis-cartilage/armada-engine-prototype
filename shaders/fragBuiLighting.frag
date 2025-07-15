//# version 330
////currently this is calculated under world coordinates
//
////Strong point light
////standard bui model lighting, the light source must be render since it is consider as a strong point light
//
//uniform float objectAmbientCoefficient;
//uniform float fObjectSpectularCoefficient;
//uniform vec3 objectColor;
//
//uniform vec3 lightColor;
//uniform vec3 lightPos;
//
//uniform vec3 viewPos;
//
//in vec3 vertNormalOut;
//in vec3 FragPos;
//
//out vec4 color;
//
//void main(){
//
//    //ambient
//    vec3 ambientResult = objectAmbientCoefficient * lightColor * objectColor;
//
//    //diffuse
//    vec3 norm = normalize(vertNormalOut);
//    vec3 lightDir = normalize(lightPos-FragPos);
//    float diff = max(dot(norm, lightDir), 0.0f);
//    vec3 diffuseResult = diff * lightColor * objectColor;
////    diffuseResult = vec3(0.0f);
//
//    //specular
//    vec3 viewDir = normalize(viewPos-FragPos);
//    vec3 reflectDir = reflect(-lightDir, norm);
//    float tmpresult = pow(max(dot(viewDir, reflectDir), 0.0f), fObjectSpectularCoefficient);
//    vec3 specularResult = tmpresult * lightColor * objectColor;
////    vec3 specularResult = vec3(0.0f);
//
//    color = vec4(ambientResult + diffuseResult + specularResult, 1.0f);
//
//
////    color = vec4(lightColor * objectColor, 1.0f);
//}
//
//
//
//
//
//

# version 330

//standard bui model light with Strong sun light

struct Material {
    vec3 v3fAmbient;
    float fAmbientCoeff;
    vec3 v3fDiffuse;
    float fDiffuseCoeff;
    vec3 v3fSpecular;
    float fSpecularCoeff;
};


struct Light {
    vec3 v3fPosition;
    vec3 v3fAmbient;
    vec3 v3fDiffuse;
    vec3 v3fSpecular;

    float fconst;
    float flinear;
    float fquadratic;
};

uniform Material material;
uniform Light light;
uniform vec3 v3fViewPos;
uniform sampler2D texture0;

in vec3 vertNormalOut;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 color;


void main() {

    //ambient
//    vec3 ambientResult = material.fAmbientCoeff * light.v3fAmbient * material.v3fAmbient;
    vec3 ambientResult = material.fAmbientCoeff * light.v3fAmbient * vec3(texture(texture0, TexCoord));

    //diffuse
    vec3 norm = normalize(vertNormalOut);
    vec3 lightDir = normalize( light.v3fPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuseResult = diff * light.v3fDiffuse * vec3(texture(texture0, TexCoord));
//    diffuseResult = vec3(0.0f);

    //specular
    vec3 viewDir = normalize(v3fViewPos-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float tmpresult = pow(max(dot(viewDir, reflectDir), 0.0f), material.fSpecularCoeff);
    vec3 specularResult = tmpresult * light.v3fSpecular * material.v3fSpecular;
//    vec3 specularResult = vec3(0.0f);


    float lightdistance = length(light.v3fPosition - FragPos);
    float attenuation = 1.0f / (light.fconst + light.flinear * lightdistance + light.fquadratic * (lightdistance * lightdistance));


    
    color = vec4(ambientResult + diffuseResult + specularResult, 1.0f);

//    color = vec4(color.xyz * attenuation, color.w); // Apply attenuation to the final color


//    color = vec4(lightColor * objectColor, 1.0f);

}




