#include "Shader.hh"

NAMESPACE_BEGIN

ShaderFinal::ShaderFinal(std::string sourceGeneralVertexPath, std::string sourceGeneralFragmentPath) {
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

ShaderFinal::ShaderFinal(std::filesystem::path sourceGeneralVertexPath, std::filesystem::path sourceGeneralFragmentPath) {

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