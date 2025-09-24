#include "modelloader.hh"


#include <texturesdlgl.hh>





void Mesh::setupMesh() {
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

/*
Warning: this function will implicit call glUseProgram(shader) to use the para shader to draw the mesh
After glDrawElements are called, glUseProgram(0) will be called by this function to clean the binding*/
void Mesh::Draw(ShaderFinal shader) {

    string pbrnames[] = {
        "textureBaseColor",
        "textureRoughness",
        "textureMetalic",
        "textureNormal",
        "textureAmbientOcclusion",
    };

    for (GLuint i = 0; i < this->textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);

        glUniform1i(
            glGetUniformLocation(shader.getGSP(), pbrnames[static_cast<int>(i)].c_str()),
            i
        );

        glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    glUseProgram(shader.getGSP());

    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}


void Model::Draw(ShaderFinal shader) {

    for (int i = 0; i < this->meshes.size(); i++) {
        this->meshes[i].Draw(shader);
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

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, load_params); 

    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        return;
    }
    this->directory = fs::path{path}.parent_path();

    this->processNode(scene->mRootNode, scene);

}


void Model::processNode(aiNode* node, const aiScene* scene)
{
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
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    for (GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        vertex.Position = {
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z,
        };

        vertex.Normal = {
            mesh->mNormals[i].x,
            mesh->mNormals[i].y,
            mesh->mNormals[i].z,
        };

        //#######????######### what does this do
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

    // 处理材质 (PBR)
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

//        vector<Texture> OGdiffuseMaps = this->loadMaterialTextures(material,
//            aiTextureType_DIFFUSE, "texture_diffuse");
//        textures.insert(textures.end(), OGdiffuseMaps.begin(), OGdiffuseMaps.end());

        Texture diffuseMap;

        optional<Texture> lookupresult = this->loadMaterialTextures(material, aiTextureType_BASE_COLOR, "Base");
        if (!lookupresult)
            lookupresult = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "Base");
        if (!lookupresult)
            lookupresult = loadDefaultTexture();

        diffuseMap = *lookupresult;
        textures.push_back(diffuseMap);

//        vector<Texture> specularMaps = this->loadMaterialTextures(material,
//            aiTextureType_SPECULAR, "texture_specular");
//        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

//        Texture specularMap = this->loadMaterialTextures(material, aiTextureType_DIFFUSE_ROUGHNESS, "Rough");
//        textures.push_back(specularMap);

    }

    return Mesh{vertices, indices, textures};
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

        dbgJellyfish::debug_log("Model class loading texture from file system" + string{str.C_Str()});

        int assimp_texture_type = static_cast<int>(type);

        if (str.length == 0) {
            cout << string{ format(
                "Performing lookup for {} {} on {} failed, returning default texture...", 
                typeName,
                string{mat->GetName().C_Str()},
                assimp_texture_type
            )} << endl;
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
    cout << "you called a abandoned function!!!!!" << endl;
    return {};
}
