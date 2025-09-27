#include <AssetSystem.hh>

NAMESPACE_BEGIN


AssetSystem::AssetSystem(const cfgAssetSystem& config)
{


    this->parseconfig(config);
    this->ModelDir = this->resourceRootDir / MODELS_DIR;
    this->shaderDir = this->resourceRootDir / SHADERS_DIR;
}

void AssetSystem::parseconfig(const cfgAssetSystem& config)
{
    this->resourceRootDir = fs::path{config.assetpath} / RESOURCES_DIR;
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

