#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char** argv){

    fs::path p = {"../../"};
    p = p / "resources" / "models" / "mi35m" / "mi35.glb";
    cout << "valid: " << fs::exists(p) << endl;

    Assimp::Importer importer;
	cout << "path loc: " << p.string() << endl;
    const aiScene* scene = importer.ReadFile(p.string(), aiProcess_Triangulate);





    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        
        cout << "error: " << importer.GetErrorString() << endl;
        return -1;
    }
    cout << "model loaded successfully" << endl;



    return 0;


}