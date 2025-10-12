#pragma once

#include <Common.hh>
#include <ShaderFactory.hh>
#include <GL/glew.h>
#include <filesystem>
#include <glm/glm.hpp>
#include <unordered_map>
#include <ConfigTypes.hh>

#include <Shader.hh>
#include <PhongShader.hh>

NAMESPACE_BEGIN


class ShaderManager{
public:
    ShaderManager(); ;
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

    vector<GLuint> getUBOBinding() const { return uboBindings; }
    ShaderFactory& getShaderFactory() { return ShaderFactory::instance(); }

private:
    vector<GLuint> uboBindings;

    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
};



NAMESPACE_END