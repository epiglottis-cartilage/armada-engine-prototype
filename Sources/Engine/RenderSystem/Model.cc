#include <Model.hh>


#include <Texture.hh>
#include <cstddef>
#include <imgui.h>


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
    //set tangents;
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                         (GLvoid*)offsetof(Vertex, tangent));
    //set bitangents;
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                         (GLvoid*)offsetof(Vertex, bitangent));

    glBindVertexArray(0);

}

Model::Material Model::PBRload(aiMaterial* aimat, const aiScene* scene) {
    //push constructed Material into this->materials vector

// ---- DEBUG BLOCK: print material info ----
//    {
//        aiString matName;
//        if (AI_SUCCESS == aimat->Get(AI_MATKEY_NAME, matName)) {
//            ENGINE_INFO("Processing material: '{}'", matName.C_Str());
//        } else {
//            ENGINE_INFO("Processing unnamed material.");
//        }
//
//        // Define all texture types you want to check
//        std::vector<std::pair<aiTextureType, const char*>> texTypes = {
//            {aiTextureType_BASE_COLOR,        "BASE_COLOR"},
//            {aiTextureType_DIFFUSE,           "DIFFUSE"},
//            {aiTextureType_NORMALS,           "NORMALS"},
//            {aiTextureType_METALNESS,         "METALNESS"},
//            {aiTextureType_DIFFUSE_ROUGHNESS, "ROUGHNESS"},
//            {aiTextureType_AMBIENT_OCCLUSION, "AO"},
//            {aiTextureType_EMISSIVE,          "EMISSIVE"}
//        };
//
//        for (auto [type, name] : texTypes) {
//            unsigned int count = aimat->GetTextureCount(type);
//            if (count == 0) continue;
//
//            ENGINE_INFO("  TextureType: {} has {} piece(s) in total", name, count);
//            ENGINE_INFO("       they are:");
//            for (unsigned int i = 0; i < count; ++i) {
//                aiString texPath;
//                if (AI_SUCCESS == aimat->GetTexture(type, i, &texPath)) {
//                    ENGINE_INFO("{} NO.[{}] name: {}",name, i, texPath.C_Str());
//                }
//            }
//        }
//    }
// ---- END DEBUG BLOCK ----



    Model::Material mat = {};
    mat.textures.resize(static_cast<int>(TextureType::COUNT));

    TextureType::BASE_COLOR;
    Texture diffuse_or_alberto = {};
    aiString texturename;
    aimat->GetTexture(aiTextureType_BASE_COLOR, 0, &texturename);

    ENGINE_INFO("Base color texture name: {}\n", texturename.C_Str());
    string texturename_str = string{texturename.C_Str()};

    if(texturename.length == 0) {
        ENGINE_WARN("No base color texture found in material, trying diffuse...\n");
        aimat->GetTexture(aiTextureType_DIFFUSE, 0, &texturename);
    }
    if (texturename.length == 0) {
        ENGINE_WARN("No diffuse texture found in material, using default...\n");
        diffuse_or_alberto = loadDefaultTexture();
    }

    if(texturename_str[0] == '*') {
        ENGINE_INFO("base texture is inmem, now loaading...");
        if(texturename_str.size() <= 1) {
            ENGINE_ERROR("assimp inmem texture name length <= 1, something is wrong");
            diffuse_or_alberto = loadDefaultTexture();
        }
        string indexstr = texturename_str.substr(1);
        aiTexture* inmem = scene->mTextures[(std::stoi(indexstr))];
        diffuse_or_alberto.id = TextureSdlGl{inmem}.getTextureId();
    }
    mat.textures[static_cast<int>(TextureType::BASE_COLOR)] = diffuse_or_alberto;

//    TextureType::ROUGHNESS;
//    diffuse_or_alberto = {};
//    aimat->GetTexture(aiTextureType_DIFFUSE_ROUGHNESS, 0, &texturename);
//    if (texturename.length == 0) {
//        ENGINE_WARN("this model have no rough texture, using default...");
//    }
//    if(texturename_str[0] == '*') {
//        ENGINE_INFO("texture is inmem, now loaading...");
//        if(texturename_str.size() <= 1) {
//            ENGINE_ERROR("assimp inmem texture name length <= 1, something is wrong");
//            diffuse_or_alberto = loadDefaultTexture();
//        }
//        string indexstr = texturename_str.substr(1);
//        aiTexture* inmem = scene->mTextures[(std::stoi(indexstr))];
//        diffuse_or_alberto.id = TextureSdlGl{inmem}.getTextureId();
//    }
    mat.textures[static_cast<int>(TextureType::ROUGHNESS)] = diffuse_or_alberto;
//
//    TextureType::METALIC;
//    diffuse_or_alberto = {};
//    aimat->GetTexture(aiTextureType_METALNESS, 0, &texturename);
//    if (texturename.length == 0) {
//        ENGINE_WARN("this model have no rough texture, using default...");
//    }
//    if(texturename_str[0] == '*') {
//        ENGINE_INFO("texture is inmem, now loaading...");
//        if(texturename_str.size() <= 1) {
//            ENGINE_ERROR("assimp inmem texture name length <= 1, something is wrong");
//            diffuse_or_alberto = loadDefaultTexture();
//        }
//        string indexstr = texturename_str.substr(1);
//        aiTexture* inmem = scene->mTextures[(std::stoi(indexstr))];
//        diffuse_or_alberto.id = TextureSdlGl{inmem}.getTextureId();
//    }
    mat.textures[static_cast<int>(TextureType::METALIC)] = diffuse_or_alberto;

    TextureType::NORMAL;
    diffuse_or_alberto = {};
    aimat->GetTexture(aiTextureType_NORMAL_CAMERA, 0, &texturename);
    if (texturename.length == 0) {
        ENGINE_WARN("this model have no rough texture, using default...");
    }
    if(texturename_str[0] == '*') {
        ENGINE_INFO("texture is inmem, now loaading...");
        if(texturename_str.size() <= 1) {
            ENGINE_ERROR("assimp inmem texture name length <= 1, something is wrong");
            diffuse_or_alberto = loadDefaultTexture();
        }
        string indexstr = texturename_str.substr(1);
        aiTexture* inmem = scene->mTextures[(std::stoi(indexstr))];
        diffuse_or_alberto.id = TextureSdlGl{inmem}.getTextureId();
    }
    mat.textures[static_cast<int>(TextureType::NORMAL)] = diffuse_or_alberto;

    TextureType::AMBIENT_OCCLUSION;
    mat.textures[static_cast<int>(TextureType::AMBIENT_OCCLUSION)] = diffuse_or_alberto;
    return mat;
}

void Model::loadMaterials(const aiScene* scene) {
    ENGINE_INFO("Loading {} materials\n", scene->mNumMaterials);
    ENGINE_INFO("This model has {} textures in total\n", scene->mNumTextures);
    //resize the material vectors to size of actual materials
    this->materials.resize(scene->mNumMaterials);

    //for each materials, load the textures
    for (GLuint i = 0; i < scene->mNumMaterials; i++) {
        //got the ai mat, then throw it to pbrload. pbrload will construct the Material and push it to this->materials
        aiMaterial* aiMat = scene->mMaterials[i];


        this->materials[i] = this->PBRload(aiMat, scene);
    }
}



/*
flipUVy is False by default, which means no flip happens.
*/
void Model::loadModel(string path, bool flipUVy) {
    auto load_params = aiProcess_Triangulate | aiProcess_CalcTangentSpace;
    load_params = load_params | (flipUVy ? aiProcess_FlipUVs : 0);

    //assimp load the model into memory
    Assimp::Importer importer;
    const aiScene* scene;
    try{

        scene = importer.ReadFile(path, load_params); 
        if(!scene) {
            ENGINE_ERROR("ASSIMP::{}\n", importer.GetErrorString());
            return;
        }
    } catch (const DeadlyImportError& e) {
        ENGINE_ERROR("Assimp deadly error: {}\n", e.what());
    } catch (const std::exception& e) {
        ENGINE_ERROR("Assimp unknown error: {}\n", e.what());
    } catch (...) {
        ENGINE_ERROR("Assimp unknown error: {}\n", "Unknown error");
        return;
    }

    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        ENGINE_ERROR("ASSIMP::{}\n", importer.GetErrorString());
        return;
    }
    ENGINE_DEBUG("path debug: {}", path);
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
        //copy tangents and bitangents
        if (mesh->HasTangentsAndBitangents()) {
            vertex.tangent = glm::vec3{
                mesh->mTangents[i].x,
                mesh->mTangents[i].y,
                mesh->mTangents[i].z
            };
            vertex.bitangent = glm::vec3{
                mesh->mBitangents[i].x,
                mesh->mBitangents[i].y,
                mesh->mBitangents[i].z
            };
        }

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

    return Mesh{vertices, indices, material_index_tmp, this};
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