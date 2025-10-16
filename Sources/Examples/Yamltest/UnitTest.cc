#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char** argv){

    fs::path p = {"../../"};
    auto modelfileloc = p / "resources" / "models" / "mi35m" / "mi35.glb";
    cout << "valid: " << fs::exists(modelfileloc) << endl;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(modelfileloc.string(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        
        cout << "error: " << importer.GetErrorString() << endl;
        return -1;
    }
    cout << "model loaded successfully" << endl;

}