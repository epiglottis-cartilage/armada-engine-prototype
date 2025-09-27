#pragma once

#include <Common.hh>
#include <ConfigTypes.hh>

NAMESPACE_BEGIN

#define MODELS_DIR "models"
#define SHADERS_DIR "shaders"
#define RESOURCES_DIR "resources"


/*
contains all assets directories 
*/
class AssetSystem {

public:
    AssetSystem() = delete;
    AssetSystem(const cfgAssetSystem& config);
    ~AssetSystem();

    const fs::path& getResourceRootDir() const { return resourceRootDir; }
    const fs::path& getShaderDir() const { return shaderDir; }
    const fs::path& getModelDir() const { return ModelDir; }

     // Tester method: check if file or directory exists
     static bool exists(const fs::path& path);

     // Tester method: get absolute file path string
     static string getAbsPathString(const fs::path& path);

private:
    fs::path resourceRootDir;
    fs::path shaderDir;
    /*this is the parent dir of all models. every models file are suppose to be put inside a directory with same name as model file.
    For example: backpack.obj should locate in ${ModelDir}/backpack/backpack.obj*/
    fs::path ModelDir;
    /*Currently all textures should be located at the same directory where the model files use them*/
    fs::path TextureDir;
    
    void parseconfig(const cfgAssetSystem& config);

};



NAMESPACE_END








