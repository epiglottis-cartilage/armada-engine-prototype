#pragma once

#include <Common.hh>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <Logger.hh>

NAMESPACE_BEGIN

#define UBOCAMERA "CameraMatrices"
#define MATPROJ "matrixProjection"
#define MATVIEW "matrixView"


enum class UBOType{
    Camera = 0,
};

/*
TODO: decide whether shader init should use string or enum*/
enum class ShaderType{
    General = 0,
    PBR = 1,
};

class Shader {
public:
    explicit Shader(const fs::path& shaderdir);
    virtual ~Shader() = default;

    virtual void setUniform(const std::string& name, const glm::mat4& value) const;
    virtual void setUniform(const std::string& name, const glm::vec3& value) const;
    virtual void setUniform(const std::string& name, float value) const;

    virtual std::string typeName() const = 0;

    virtual GLuint getID() const { return shaderID; }
protected:
    GLuint shaderID;


    //TODO: design a better architecture for shader UBO binding!!! 
    virtual void bindUBO(UBOType type);
};




NAMESPACE_END
