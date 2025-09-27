#pragma once

#include <Common.hh>
#include "OpenglShader.hh"
#include <Shader.hh>
#include <GL/glew.h>
#include <filesystem>
#include <glm/glm.hpp>

NAMESPACE_BEGIN

#define UBOCAMERA "CameraMatrices"
#define MATPROJ "matrixProjection"
#define MATVIEW "matrixView"


enum class UBOType{
    Camera = 0,
};



class ShaderManager{
public:
    ShaderManager() = default;
    ~ShaderManager() = default;

    void bindUBO(UBOType type, Shader* shader);
    vector<GLuint> getUBOCamera() const { return uboCamera; }


private:
    vector<Shader*> shaders;
    vector<GLuint> uboCamera;



};

NAMESPACE_END