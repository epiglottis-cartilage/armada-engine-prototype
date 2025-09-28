#include "Shader.hh"

NAMESPACE_BEGIN

Shader::Shader(std::string sourceGeneralVertexPath, std::string sourceGeneralFragmentPath) {
    CustShader* tmpvertshader = new CustShader(GL_VERTEX_SHADER, sourceGeneralVertexPath);
    CustShader* tmpfragshader = new CustShader(GL_FRAGMENT_SHADER, sourceGeneralFragmentPath);
    std::optional<GLuint> tmpshaderprogram = CustShader::shaderLink(*tmpvertshader, *tmpfragshader);
    if (tmpshaderprogram.has_value()) {
        this->generalShader = tmpshaderprogram.value();
    }else{
    }
    delete tmpvertshader;
    delete tmpfragshader;
}

Shader::Shader(fs::path sourceGeneralVertexPath, fs::path sourceGeneralFragmentPath) {
    ENGINE_INFO("Loading shader from path: {} \n valid: {}", sourceGeneralVertexPath.string(), fs::exists(sourceGeneralVertexPath));
    ENGINE_INFO("Loading shader from path: {} \n valid: {}", sourceGeneralFragmentPath.string(), fs::exists(sourceGeneralFragmentPath));

    CustShader* tmpvertshader = new CustShader(GL_VERTEX_SHADER, sourceGeneralVertexPath.string());
    CustShader* tmpfragshader = new CustShader(GL_FRAGMENT_SHADER, sourceGeneralFragmentPath.string());
    std::optional<GLuint> tmpshaderprogram = CustShader::shaderLink(*tmpvertshader, *tmpfragshader);
    if (tmpshaderprogram.has_value()) {
        this->generalShader = tmpshaderprogram.value();
    }else{
    }
    delete tmpvertshader;
    delete tmpfragshader;
}
NAMESPACE_END