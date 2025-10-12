#pragma once

#include <Common.hh>
#include <Shader.hh>
#include <unordered_map>
#include <functional>
#include <memory>
#include <string>

NAMESPACE_BEGIN

/*Access the unique ShaderFactory using `ShaderFactory& xxx = ShaderFactory::instance()
Before using it, init it with ShaderFactory::init(shadersDirectory)
Currently*/
class ShaderFactory {
public:
    using Creator = std::function<std::unique_ptr<Shader>(const fs::path&)>;

    static void init(const fs::path& shaderdir) {
        shaderDirectory = shaderdir;
    }

    static ShaderFactory& instance() {
        static ShaderFactory factory;
        return factory;
    }

    void registerType(const std::string& name, Creator createFn) {
        creators[name] = std::move(createFn);
    }

    // return a shader, created by the callback function inside `creators` map, with the type `name`
    std::unique_ptr<Shader> create(const std::string& name) const {
        if (auto it = creators.find(name); it != creators.end())
            return it->second(shaderDirectory);
        throw std::runtime_error("ShaderFactory: Unknown shader type: " + name);
    }

private:
    std::unordered_map<std::string, Creator> creators;
    static fs::path shaderDirectory;

};




NAMESPACE_END