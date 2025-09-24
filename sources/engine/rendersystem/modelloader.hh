#ifndef MODELLOADER_HH
#define MODELLOADER_HH

#define DEFAULT_TEXTURE_NAME "defaulttexture.png"

#include <string>
#include <vector>
#include <format>
#include <optional>
#include <filesystem>


#include <glm/glm.hpp>
#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include <shaderfinal.hh>
#include <dbgJellyfish.hh>
#include <texturesdlgl.hh>

using namespace std;
namespace fs = std::filesystem;

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

    void Draw(ShaderFinal shader);

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
        void Draw(ShaderFinal shader); 
    private:
        vector<Mesh> meshes;
        fs::path directory;

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

#endif
