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


#include <Shader.hh>
#include <Debugger.hh>
#include <Texture.hh>

using namespace std;

NAMESPACE_BEGIN

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};


struct Texture
{
    GLuint id;
    string type;
    aiString path;
};

class Mesh
{
public:
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> texture) :
        vertices(vertices), indices(indices), textures(texture), VAO(0), VBO(0), EBO(0)
    {
        this->setupMesh();
    };

    void Draw(const ShaderFinal& shader, const glm::mat4& transform) const;

private:


    GLuint VAO, VBO, EBO;
    void setupMesh();
};


class Model 
{

public:
    Model(string path)
    {
        this->loadModel(path);
    }
    Model(fs::path path)
    {
        this->loadModel(path.string());
    }
    void Draw(const ShaderFinal& shader) const; 
    //vaos, render relative infos.
    vector<Mesh> getMeshes() const { return meshes; }
    fs::path getDirectory() const { return directory; }
    bool getShown() const { return shown; }
    void setShown(bool shown) { this->shown = shown; }
    glm::mat4 getTransform() const { return transform; }
    void setTransform(glm::mat4 transform) { this->transform = transform; }
    ShaderFinal* getShader() const { return shader; }
    void setShader(ShaderFinal* shader) { this->shader = shader; }
    
private:
    glm::mat4 transform = glm::mat4(1.0f);
    vector<Mesh> meshes;
    fs::path directory;
    bool shown = true;
    ShaderFinal* shader;

    void loadModel(string path, bool flipUVy = false);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type );
    optional<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

    static Texture loadDefaultTexture() {

        Texture texture;
        cout << "loading default texture" << endl;

        texture.id = TextureSdlGl{ fs::path{fs::current_path() / DEFAULT_TEXTURE_NAME}.string() }.getTextureId();
        texture.type = "default";
        texture.path = aiString{ DEFAULT_TEXTURE_NAME };

        return texture;
    }

};

NAMESPACE_END