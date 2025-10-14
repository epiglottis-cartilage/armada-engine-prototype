#include "Model.hh"


#include <Texture.hh>
#include <cstddef>


NAMESPACE_BEGIN



void Model::Mesh::setupMesh() {
	glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), 
                 &this->vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), 
                 &this->indices[0], GL_STATIC_DRAW);

    // 设置顶点坐标指针
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
                         (GLvoid*)0);
    // 设置法线指针
    glEnableVertexAttribArray(1); 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
                         (GLvoid*)offsetof(Vertex, Normal));
    // 设置顶点的纹理坐标
    glEnableVertexAttribArray(2); 
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
                         (GLvoid*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);

}

void Model::PBRload(aiMaterial* aimat, const aiScene* scene) {
    //push constructed Material into this->materials vector
    Model::Material* mat = {};

    TextureType::BASE_COLOR;
    Texture diffuse_or_alberto;
    aiString texturename;
    aimat->GetTexture(aiTextureType_BASE_COLOR, 0, &texturename);

    ENGINE_INFO("Base color texture name: {}\n", texturename.C_Str());

    if(texturename.length == 0) {
        ENGINE_WARN("No base color texture found in material, trying diffuse...\n");
        aimat->GetTexture(aiTextureType_DIFFUSE, 0, &texturename);
        //TODO: add default texture loading here
    }//try another one

    if(texturename.C_Str()[0] == '*') {
        ENGINE_INFO("base texture is inmem, now loaading...");
        aiTexture* inmem = scene->mTextures[(std::stoi(std::string{texturename.C_Str()}) + 1)];
        diffuse_or_alberto.id = TextureSdlGl{inmem}.getTextureId();
    }

    //TODO: finish normal, roughness, metalic, ao

    mat->textures.push_back(diffuse_or_alberto);
}

void Model::loadMaterials(const aiScene* scene) {
    //resize the material vectors to size of actual materials
    this->materials.resize(scene->mNumMaterials);

    //for each materials, load the textures
    for (GLuint i = 0; i < scene->mNumMaterials; i++) {
        //got the ai mat, then throw it to pbrload. pbrload will construct the Material and push it to this->materials
        aiMaterial* aiMat = scene->mMaterials[i];

        //!!!this will modify the material vector field of this class!!!
        Model::PBRload(aiMat, scene);

    }
}



/*
flipUVy is False by default, which means no flip happens.
*/
void Model::loadModel(string path, bool flipUVy) {
    //path is the model file location
    int load_params;
    if (flipUVy) {
        load_params = aiProcess_Triangulate | aiProcess_FlipUVs;
    }
    else {
        load_params = aiProcess_Triangulate ;
    }

    //assimp load the model into memory
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, load_params); 

    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        ENGINE_ERROR("ASSIMP::{}\n", importer.GetErrorString());
        return;
    }
    this->directory = fs::path{path}.parent_path();

    ENGINE_INFO("Model now loading materials");
    this->loadMaterials(scene);

    ENGINE_INFO("Model now processin nodes");
    this->processNode(scene->mRootNode, scene);


    //found and process potential gl errors
    GLenum err = glGetError();
    if(err == GL_NO_ERROR) {
        ENGINE_INFO("Model loaded successfully: {}\n", this->directory.string());
        return;
    }
    while(err != GL_NO_ERROR) {
        ENGINE_ERROR("Model loading GL error: {}\n", err);
        err = glGetError();
    }
}


void Model::processNode(aiNode* node, const aiScene* scene)
{
    //forward iterating
    // 添加当前节点中的所有Mesh
    for(int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
        this->meshes.push_back(this->processMesh(mesh, scene)); 
    }
    // 递归处理该节点的子孙节点
    for(int i = 0; i < node->mNumChildren; i++)
    {
        this->processNode(node->mChildren[i], scene);
    }
}



/*
convert assimp format mesh to engine format mesh
*/
Model::Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    vector<Vertex> vertices;
    vector<GLuint> indices;

    ENGINE_INFO("Processing mesh: {}, vertices: {}\n", string{mesh->mName.C_Str()}, mesh->mNumVertices);
    for (GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        vertex.Position = {
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z,
        };

        if (mesh->HasNormals()) {
            vertex.Normal = {
                mesh->mNormals[i].x,
                mesh->mNormals[i].y,
                mesh->mNormals[i].z,
            };
        } else {
            vertex.Normal = glm::vec3(0.0f);
        }

        //#######????######### what does this do
        //load the first group of texture uv. 99% of the case it is alberto/basecolor. 
        //in case of second group existing, the [1] group is often light map, [2] is detail overlays, [3] is procedural mapping, ......
        if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        //#######????#########

        vertices.push_back(vertex);
    }
    // 处理顶点索引
    for (GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (GLuint j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }


    int material_index_tmp = 0;
    // copy the material index
    if (mesh->mMaterialIndex >= 0)
    {
        material_index_tmp = mesh->mMaterialIndex;
    }

    return Mesh{vertices, indices, material_index_tmp};
}



/*
load the texture image from filesystem by type, required by mat, return a engine material type. 
Noticed that this function only support up to 1 map for each type
*/
optional<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
	Texture texture;
//    for(GLuint i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, 0, &str);

        ENGINE_DEBUG("Model class loading texture from file system {}\n", string{str.C_Str()});

        int assimp_texture_type = static_cast<int>(type);

        if (str.length == 0) {
            ENGINE_INFO("Performing lookup for {} on model texture {}\n of assimp texture type {} failed, returning empty texture...\n",
                        typeName,
                        string{mat->GetName().C_Str()},
                        assimp_texture_type
                    );
            return {};

        }
        else {
			texture.id = TextureSdlGl{ fs::path{ this->directory / str.C_Str() }.string() }.getTextureId();
			texture.type = typeName;
			texture.path = str;
        }
    }
    return { texture };
}
vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type) {
    ENGINE_WARN("you called a abandoned function!!!!!\n");
    return {};
}

NAMESPACE_END