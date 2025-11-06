#pragma once

#include <Common.hh>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <Logger.hh>

NAMESPACE_BEGIN

#define UBOCAMERA "CameraMatrices"
#define UBOLIGHTBUFFER "LightBuffer"
#define MATPROJ "matrixProjection"
#define MATVIEW "matrixView"


enum class UBOType{
    Camera = 0,
    LightBuffer,
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
    virtual ~Shader() ;

    virtual void setUniform(const std::string& name, const glm::mat4& value) const;
    virtual void setUniform(const std::string& name, const glm::vec3& value) const;
    virtual void setUniform(const std::string& name, float value) const;

    virtual std::string typeName() const = 0;

    virtual GLuint getID() const { return shaderID; }
protected:
    GLuint shaderID;

    class GLShader {

    public:
        /* construct a opengl shader from the location `shaderfilepath`*/
        GLShader(GLenum shadertype, fs::path shaderfilepath);
        GLuint shaderID;
    };

    //TODO: design a better architecture for shader UBO binding!!! 
    virtual void bindUBO(UBOType type);
};




NAMESPACE_END
