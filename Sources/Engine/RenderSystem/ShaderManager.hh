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
    ShaderManager() ;
    ~ShaderManager();

    void bindUBO(UBOType type, Shader* shader);
    vector<GLuint> getUBOCamera() const { return uboBindings; }


private:
    vector<Shader*> shaders;
    vector<GLuint> uboBindings;



};

NAMESPACE_END