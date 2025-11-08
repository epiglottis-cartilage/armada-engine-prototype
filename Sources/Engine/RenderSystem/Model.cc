#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_IMPLEMENTATION
#include <Model.hh>
#include <Texture.hh>
#include <entt/entity/entity.hpp>


NAMESPACE_BEGIN
    void Primitive::setupPrimitive() {
	glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    if (vertices.empty())
        ENGINE_WARN("Loading 0 vertex primitives into GPU!!!");
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
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        ENGINE_ERROR("Uploading Primitives Error: {}", static_cast<int>(err));
    }
}

void Primitive::drawPrimitive(const Shader& shader, const glm::mat4 transform, const Model* parentmodel) const {
    glUseProgram(shader.getID());

    string pbrnames[] = {
        "textureBaseColor",
        "textureRoughness",
        "textureMetalic",
        "textureNormalMap",
        "textureAmbientOcclusion",
    };

    for (GLuint i = 0; i < static_cast<int>(TextureType::COUNT); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glUniform1i(
            glGetUniformLocation(shader.getID(), pbrnames[static_cast<int>(i)].c_str()),
            i
        );
        glBindTexture(GL_TEXTURE_2D, parentmodel->getMaterials()[indexMaterial].textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    //apply transform
    shader.setUniform("matrixModel", transform );

    glBindVertexArray(VAO);
    glDrawElements(this->enumIndexMode, indicessizes, enumIndexType, NULL);
    glBindVertexArray(0);
    glUseProgram(0);
}


void Model::Mesh::setupMesh() {
    //free the vertex on cpu end for better memory control
    for (auto& eachprim: this->primitives) {
        vector<GLuint>().swap(eachprim.indices);
        vector<Vertex>().swap(eachprim.vertices);
    }
}


Texture Model::loadTexturefromGLB(const tinygltf::Model& gltfmodel,const tinygltf::Material& gltfmat, int index, TextureType textype) {
    const tinygltf::Texture& gltftexture = gltfmodel.textures[index];
    const tinygltf::Image& image = gltfmodel.images[gltftexture.source];

    ENGINE_INFO("Base color texture name: {}", gltftexture.name);
    ENGINE_DEBUG("Model loading: material-{} get type:{} "
                 "texture, image: {}", gltfmat.name,static_cast<int>(textype),image.name );

    Texture tex{0, textype, image.uri};

    GLenum format = GL_RGB;
    if (image.component == 1) format = GL_RED;
    else if (image.component == 3) format = GL_RGB;
    else if (image.component == 4) format = GL_RGBA;

    glGenTextures(1, &tex.id);
    glBindTexture(GL_TEXTURE_2D, tex.id);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        image.width,
        image.height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        image.image.data()
        );

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    return tex;
}

Model::Material Model::PBRload(tinygltf::Material& gltfmat, tinygltf::Model& gltfmodel) {
    //push constructed Material into this->materials vector
    Model::Material mat = {};
    mat.textures.resize(static_cast<int>(TextureType::COUNT));

    TextureType::BASE_COLOR;
    Texture current_texture = {};
    auto tex_index = gltfmat.pbrMetallicRoughness.baseColorTexture.index;
    if (tex_index >= 0 && tex_index < gltfmodel.textures.size()) {
        current_texture = loadTexturefromGLB(
            gltfmodel,
            gltfmat,
            tex_index,
            TextureType::BASE_COLOR);
    }else {
        //load default texture
        current_texture = loadDefaultTexture();
        ENGINE_WARN("No diffuse texture found in material, using default...");
    }
    mat.textures[static_cast<int>(TextureType::BASE_COLOR)] = current_texture;

    TextureType::METALIC;
    TextureType::ROUGHNESS;
    current_texture;
    tex_index = gltfmat.pbrMetallicRoughness.metallicRoughnessTexture.index;
    if (tex_index >= 0 && tex_index < gltfmodel.textures.size()) {
        current_texture = loadTexturefromGLB(
            gltfmodel,
            gltfmat,
            tex_index,
            TextureType::ROUGHNESS);
    }else {
        //load default texture
        current_texture = loadDefaultTexture();
        ENGINE_WARN("No diffuse texture found in material, using default...");
    }
    mat.textures[static_cast<int>(TextureType::ROUGHNESS)] = current_texture;


    TextureType::NORMAL;
    current_texture;
    tex_index = gltfmat.normalTexture.index;
    if (tex_index >= 0 && tex_index < gltfmodel.textures.size()) {
        current_texture = loadTexturefromGLB(
            gltfmodel,
            gltfmat,
            tex_index,
            TextureType::NORMAL);
    }else {
        //load default texture
        current_texture = loadDefaultTexture();
        ENGINE_WARN("No diffuse texture found in material, using default...");
    }
    mat.textures[static_cast<int>(TextureType::NORMAL)] = current_texture;

    TextureType::AMBIENT_OCCLUSION;
    current_texture;
    tex_index = gltfmat.occlusionTexture.index;
    if (tex_index >= 0 && tex_index < gltfmodel.textures.size()) {
        current_texture = loadTexturefromGLB(
            gltfmodel,
            gltfmat,
            tex_index,
            TextureType::AMBIENT_OCCLUSION);
    }else {
        //load default texture
        current_texture = loadDefaultTexture();
        ENGINE_WARN("No diffuse texture found in material, using default...");
    }
    mat.textures[static_cast<int>(TextureType::AMBIENT_OCCLUSION)] = current_texture;
    return mat;
}

void Model::loadMaterials(tinygltf::Model& model) {
    auto material_size = model.materials.size();
    if (material_size == 0) {
        ENGINE_INFO("this model have no materials, constructing default textures.....");
        this->materials.resize(1);
        vector<Texture> defaultmat; defaultmat.resize(int(TextureType::COUNT));
        for (int i = 0; i < int(TextureType::COUNT); i++)
            defaultmat[i] = loadDefaultTexture();
        this->materials[0] = {move(defaultmat)};;
        return;
    }
    ENGINE_INFO("Loading {} materials", material_size);
    ENGINE_INFO("This model has {} textures in total", model.textures.size());
    //resize the material vectors to size of actual materials
    this->materials.resize(material_size);

    //for each materials, load the textures
    for (GLuint i = 0; i < material_size; i++) {
        //got the ai mat, then throw it to pbrload. pbrload will construct the Material and push it to this->materials
        tinygltf::Material& gltfmat = model.materials[i];
        this->materials[i] = this->PBRload(gltfmat, model);
    }
}

/*
flipUVy is False by default, which means no flip happens.
*/
void Model::loadModel(string path, bool flipUVy) {
    //assimp load the model into memory
    tinygltf::TinyGLTF importer;
    tinygltf::Model model;
    try{
        string error = {}, warn = {};
        bool result = importer.LoadBinaryFromFile(&model, &error, &warn, path);
        if (!result) {
            ENGINE_ERROR("tinygltf model loading error");
        }
    } catch (const std::exception& e) {
        ENGINE_ERROR("tinygltf unknown error: {}", e.what());
    } catch (...) {
        ENGINE_ERROR("tinygltf unknown error: {}", "Unknown error");
        return;
    }
    const tinygltf::Scene* scene = &model.scenes[model.defaultScene];

    ENGINE_DEBUG("path debug: {}", path);
    this->directory = fs::path{path}.parent_path();

    ENGINE_INFO("Model now loading materials");

    this->loadMaterials(model);

    ENGINE_INFO("Model now processin nodes");
    for (auto& rootnodes : scene->nodes) {
        this->processNode(&model.nodes[rootnodes], &model);
    }


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


//convert disk glb structure into engine structure
void Model::processNode(tinygltf::Node* node, tinygltf::Model* model){
    //forward iterating
    //process all the primitives of current node
    if (auto resultmesh = processMesh(node, model))
        this->meshes.push_back(move(*resultmesh));
    // 递归处理该节点的子孙节点
    for(int i = 0; i < node->children.size(); i++){
        this->processNode(&model->nodes[node->children[i]], model);
    }
}

/*
convert assimp format mesh to engine format mesh
*/
optional<Model::Mesh> Model::processMesh(const tinygltf::Node* node, const tinygltf::Model* model) {
    if (node->mesh == -1)
        return nullopt;
    auto& meshes = model->meshes[node->mesh];

    std::vector<Primitive> primsarray;

    // 遍历该 mesh 下的所有 primitives
    for (const auto& prims : meshes.primitives) {
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;

        // ----------- 处理 POSITION ----------
        if (prims.attributes.find("POSITION") == prims.attributes.end()) continue;

        const tinygltf::Accessor& posAccessor = model->accessors[prims.attributes.at("POSITION")];
        const tinygltf::BufferView& posView = model->bufferViews[posAccessor.bufferView];
        const tinygltf::Buffer& posBuffer = model->buffers[posView.buffer];

        const unsigned char* posData =
            posBuffer.data.data() + posView.byteOffset + posAccessor.byteOffset;
        size_t posStride = posView.byteStride ? posView.byteStride : sizeof(float) * 3;

        vertices.resize(posAccessor.count);

        for (size_t i = 0; i < posAccessor.count; ++i) {
            const float* v = reinterpret_cast<const float*>(posData + i * posStride);
            vertices[i].Position = glm::vec3(v[0], v[1], v[2]);
        }

        // ----------- 处理 NORMAL ----------
        if (prims.attributes.find("NORMAL") != prims.attributes.end()) {
            const tinygltf::Accessor& normAccessor = model->accessors[prims.attributes.at("NORMAL")];
            const tinygltf::BufferView& normView = model->bufferViews[normAccessor.bufferView];
            const tinygltf::Buffer& normBuffer = model->buffers[normView.buffer];

            const unsigned char* normData =
                normBuffer.data.data() + normView.byteOffset + normAccessor.byteOffset;
            size_t normStride = normView.byteStride ? normView.byteStride : sizeof(float) * 3;

            for (size_t i = 0; i < normAccessor.count; ++i) {
                const float* n = reinterpret_cast<const float*>(normData + i * normStride);
                vertices[i].Normal = glm::normalize(glm::vec3(n[0], n[1], n[2]));
            }
        } else {
            for (auto& v : vertices) v.Normal = glm::vec3(0.0f, 0.0f, 1.0f);
        }

        // ----------- 处理 TEXCOORD_0 ----------
        if (prims.attributes.find("TEXCOORD_0") != prims.attributes.end()) {
            const tinygltf::Accessor& uvAccessor = model->accessors[prims.attributes.at("TEXCOORD_0")];
            const tinygltf::BufferView& uvView = model->bufferViews[uvAccessor.bufferView];
            const tinygltf::Buffer& uvBuffer = model->buffers[uvView.buffer];

            const unsigned char* uvData =
                uvBuffer.data.data() + uvView.byteOffset + uvAccessor.byteOffset;
            size_t uvStride = uvView.byteStride ? uvView.byteStride : sizeof(float) * 2;

            for (size_t i = 0; i < uvAccessor.count; ++i) {
                const float* uv = reinterpret_cast<const float*>(uvData + i * uvStride);
                // 注意：GLTF 的 V 坐标是反的
                vertices[i].TexCoords = glm::vec2(uv[0], 1.0f - uv[1]);
            }
        } else {
            for (auto& v : vertices) v.TexCoords = glm::vec2(0.0f);
        }

        // ----------- 处理 Tangent（可选） ----------
        if (prims.attributes.find("TANGENT") != prims.attributes.end()) {
            const tinygltf::Accessor& tanAccessor = model->accessors[prims.attributes.at("TANGENT")];
            const tinygltf::BufferView& tanView = model->bufferViews[tanAccessor.bufferView];
            const tinygltf::Buffer& tanBuffer = model->buffers[tanView.buffer];

            const unsigned char* tanData =
                tanBuffer.data.data() + tanView.byteOffset + tanAccessor.byteOffset;
            size_t tanStride = tanView.byteStride ? tanView.byteStride : sizeof(float) * 4;

            for (size_t i = 0; i < tanAccessor.count; ++i) {
                const float* t = reinterpret_cast<const float*>(tanData + i * tanStride);
                vertices[i].tangent = glm::vec3(t[0], t[1], t[2]);
                // bitangent 可以稍后由 cross(N, T) * t[3] 计算（t[3] 是方向系数）
                vertices[i].bitangent = glm::cross(vertices[i].Normal, vertices[i].tangent) * t[3];
            }
        }

        GLenum IndexType = GL_UNSIGNED_INT;
        // ----------- 处理 Indices ----------
        if (prims.indices >= 0) {
            const tinygltf::Accessor& idxAccessor = model->accessors[prims.indices];
            const tinygltf::BufferView& idxView = model->bufferViews[idxAccessor.bufferView];
            const tinygltf::Buffer& idxBuffer = model->buffers[idxView.buffer];

            switch (idxAccessor.componentType) {
                case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: IndexType= GL_UNSIGNED_BYTE; break;
                case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:IndexType= GL_UNSIGNED_SHORT; break;
                case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:  IndexType= GL_UNSIGNED_INT; break;
            }

            const unsigned char* idxData =
                idxBuffer.data.data() + idxView.byteOffset + idxAccessor.byteOffset;

            for (size_t i = 0; i < idxAccessor.count; ++i) {
                uint32_t index = 0;
                switch (idxAccessor.componentType) {
                    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
                        index = reinterpret_cast<const uint8_t*>(idxData)[i];
                        break;
                    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
                        index = reinterpret_cast<const uint16_t*>(idxData)[i];
                        break;
                    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
                        index = reinterpret_cast<const uint32_t*>(idxData)[i];
                        break;
                }
                indices.push_back(index);
            }
        }
        GLenum drawMode = GL_TRIANGLES;
        if (prims.mode >= 0) {
            switch (prims.mode) {
            case TINYGLTF_MODE_POINTS:         drawMode = GL_POINTS; break;
//            case TINYGLTF_MODE_LINES:          drawMode = GL_LINES; break;
            case TINYGLTF_MODE_LINE_LOOP:      drawMode = GL_LINE_LOOP; break;
            case TINYGLTF_MODE_LINE_STRIP:     drawMode = GL_LINE_STRIP; break;
            case TINYGLTF_MODE_TRIANGLES:      drawMode = GL_TRIANGLES; break;
            case TINYGLTF_MODE_TRIANGLE_STRIP: drawMode = GL_TRIANGLE_STRIP; break;
            case TINYGLTF_MODE_TRIANGLE_FAN:   drawMode = GL_TRIANGLE_FAN; break;
            default: drawMode = GL_TRIANGLES; break;
            }
        }
        // ----------- 构建 mesh -----------
        auto primes_meterial_index = (prims.material >= 0) ? prims.material : 0;
        Primitive prim = {std::move(vertices), std::move(indices), drawMode, IndexType, primes_meterial_index};
        primsarray.push_back(std::move(prim));
    }

    //calculate the transform
    glm::mat4 localMatrix(1.0f);

    if (node->matrix.size() == 16)
    {
        localMatrix = glm::make_mat4(node->matrix.data());
    }
    else
    {
        glm::vec3 translation(0.0f);
        glm::quat rotation(1.0f, 0.0f, 0.0f, 0.0f);
        glm::vec3 scale(1.0f);

        if (node->translation.size() == 3)
            translation = glm::make_vec3(node->translation.data());
        if (node->rotation.size() == 4)
            rotation = glm::make_quat(node->rotation.data());
        if (node->scale.size() == 3)
            scale = glm::make_vec3(node->scale.data());

        localMatrix = glm::translate(glm::mat4(1.0f), translation)
                    * glm::mat4_cast(rotation)
                    * glm::scale(glm::mat4(1.0f), scale);
    }

    Model::Mesh resultmesh = {localMatrix, std::move(primsarray) };
    return resultmesh;
}


NAMESPACE_END