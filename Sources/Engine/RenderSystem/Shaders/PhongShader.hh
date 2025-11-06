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

    std::string typeName() const override { return "Phong"; }
};

NAMESPACE_END