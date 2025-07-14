#include "spCust.hh"


spCust::spCust(std::string sourceGeneralVertexPath, std::string sourceGeneralFragmentPath) {
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