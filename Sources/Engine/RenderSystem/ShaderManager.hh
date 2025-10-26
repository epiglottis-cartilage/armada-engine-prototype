#pragma once

#include <Common.hh>
#include <ShaderFactory.hh>
#include <GL/glew.h>
#include <filesystem>
#include <glm/glm.hpp>
#include <unordered_map>
#include <ConfigTypes.hh>
#include <GlobalContext.hh>

#include <Shader.hh>
#include <PhongShader.hh>

NAMESPACE_BEGIN

struct CameraMatrices {
    glm::mat4 matrixView;
    glm::mat4 matrixProjection;
    glm::vec3 positionCamera;
    float _padding;
};

class ShaderManager{
public:
    ShaderManager();
    ~ShaderManager();

    Shader* getOrCreate(const std::string& type) {
        if (auto it = shaders.find(type); it != shaders.end())
            return it->second.get();

        auto shader = ShaderFactory::instance().create(type);
        auto ptr = shader.get();
        shaders[type] = std::move(shader);
        return ptr;
    }

    Shader* get(const std::string& type) const {
        if (auto it = shaders.find(type); it != shaders.end())
            return it->second.get();
        return nullptr;
    }
    void clear() { shaders.clear(); }

    ShaderFactory& getShaderFactory() { return ShaderFactory::instance(); }

private:

    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
};



NAMESPACE_END