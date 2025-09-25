#include <assetsystem.hh>

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


NAMESPACE_END

