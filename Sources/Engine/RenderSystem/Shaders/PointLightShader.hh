//
// Created by phage on 10/24/25.
//

#ifndef POINTLIGHTSHADER_HH
#define POINTLIGHTSHADER_HH

#include <Common.hh>
#include <Shader.hh>

NAMESPACE_BEGIN

#define POINTLIGHTVERTEXSHADER "lightVertexShader.vert"
#define POINTLIGHTFRAGMENTSHADER "lightFragmentShader.frag"

#define POINTLIGHT "Pointlight"

class PointLightShader : public Shader {
public:
    explicit PointLightShader(const fs::path& shaderdir);
    ~PointLightShader();

    string typeName() const override {return POINTLIGHT;};
};


NAMESPACE_END

#endif //POINTLIGHTSHADER_HH
