#pragma once

#include <Common.hh>


#define DEFAULT_TEXTURE_NAME "defaulttexture.png"

#include <string>
#include <vector>
#include <format>
#include <optional>
#include <filesystem>


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Exceptional.h>


#include <Shader.hh>
#include <Texture.hh>
#include <Logger.hh>

using namespace std;

NAMESPACE_BEGIN

enum class TextureType{
    BASE_COLOR,
    ROUGHNESS,
    METALIC,
    NORMAL,
    AMBIENT_OCCLUSION,
};
struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    GLuint id;
    string type = {};
    aiString path = {};
};

class Model 
{
public:
    class Material
    {
    public:
        vector<Texture> textures;
    };
    class Mesh
    {
    public:
        vector<Vertex> vertices;
        vector<GLuint> indices;
        int materialIndex;


        Mesh(vector<Vertex> vertices, vector<GLuint> indices, int texture, Model* parentmodel) :
            vertices(vertices), indices(indices), materialIndex(texture),
            parent_usedfortexture(parentmodel),
            VAO(0), VBO(0), EBO(0)
        {
            this->setupMesh();
        };

    //    void Draw(const Shader& shader, const glm::mat4& transform) const;
        GLuint getVAO() const { return this->VAO; }
        Model* getParentUsedForTexture() const { return this->parent_usedfortexture; }
    private:
        Model* parent_usedfortexture;
        GLuint VAO, VBO, EBO;
        void setupMesh();
    };


    Model(string path, bool flipuv=true)
    {
        ENGINE_INFO("DEPRECATE METHOD: Model(string path)");
        fs::path p = fs::path{path};
        ENGINE_INFO("loading model: {}\nValid: {}", p.string(), fs::exists(p));
        this->loadModel(path, flipuv);
    }

    Model(fs::path path, bool flipuv=true)
    {

        ENGINE_VALIDLOCATION(path);


        if(path.extension() != fs::path{".glb"} && path.extension() != fs::path{".gltf"}){
            ENGINE_ERROR("you are loading a model file with non glb/gltf extension, make sure assimp support it\n");
            return;
        }
        ENGINE_DEBUG("path after extension judge: {}", path.string());

        this->loadModel(path.string(), flipuv);
    }
//    void Draw(const Shader& shader) const; 
    //vaos, render relative infos.
    vector<Mesh> getMeshes() const { return meshes; }
    fs::path getDirectory() const { return directory; }
    glm::mat4 getTransform() const { return transform; }
    void setTransform(glm::mat4 transform) { this->transform = transform; }
    Shader* getShader() const { return shader; }
    void setShader(Shader* shader) { this->shader = shader; }
    vector<Material> getMaterials() const { return materials; }
    
private:
    glm::mat4 transform = glm::mat4(1.0f);
    vector<Mesh> meshes;
    vector<Material> materials;
    fs::path directory;
    
    Shader* shader;

    Material PBRload(aiMaterial* aimat, const aiScene* scene);
    void loadModel(string path, bool flipUVy = false);
    void loadMaterials(const aiScene* scene);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type );
    optional<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

    static Texture loadDefaultTexture() {

        Texture texture;
        ENGINE_DEBUG("loading default texture\n");

        texture.id = TextureSdlGl{ fs::path{fs::current_path() / DEFAULT_TEXTURE_NAME}.string() }.getTextureId();
        texture.type = "Default";
        texture.path = aiString{ DEFAULT_TEXTURE_NAME };

        return texture;
    }

};

NAMESPACE_END