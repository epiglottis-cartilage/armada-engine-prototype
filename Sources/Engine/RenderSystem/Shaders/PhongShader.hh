#pragma once
#include <Common.hh>
#include <Shader.hh>
#include <iostream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>


NAMESPACE_BEGIN

#define PHONGVERTEXSHADER "phongVertexShader.vert"
#define PHONGFRAGMENTSHADER "phongFragmentShader.frag"

class PhongShader : public Shader {
public:

    explicit PhongShader(const fs::path& shaderdir) ;
    ~PhongShader();
    void setUniform(const std::string& name, const glm::mat4& value) const override ;
    void setUniform(const std::string& name, const glm::vec3& value) const override ;
    void setUniform(const std::string& name, float value) const override ;

    std::string typeName() const override { return "Phong"; }
};

NAMESPACE_END