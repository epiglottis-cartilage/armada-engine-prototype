#include <AssetSystem.hh>

NAMESPACE_BEGIN


AssetSystem::AssetSystem(const cfgAssetSystem& config)
{


    this->parseconfig(config);
    this->ModelDir = this->resourceRootDir / MODELS_DIR;
    this->shaderDir = this->resourceRootDir / SHADERS_DIR;
    ENGINE_INFO("AssetSystem Model dir set to: {}", this->ModelDir.string());
    ENGINE_INFO("AssetSystem Shader dir set to: {}", this->shaderDir.string());
}

void AssetSystem::parseconfig(const cfgAssetSystem& config)
{
    this->resourceRootDir = fs::path{config.assetpath} / RESOURCES_DIR;
    ENGINE_INFO("AssetSystem resource root dir set to: {}", this->resourceRootDir.string());
}


// Tester method: check if file or directory exists
bool AssetSystem::exists(const fs::path& path) {
    return fs::exists(path);
}

// Tester method: get absolute file path string
string AssetSystem::getAbsPathString(const fs::path& path) {
    return fs::absolute(path).string();
}

NAMESPACE_END

