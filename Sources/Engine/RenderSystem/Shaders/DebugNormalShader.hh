//
// Created by phage on 11/3/25.
//

#ifndef DEBUGNORMALSHADER_HH
#define DEBUGNORMALSHADER_HH

#include <Common.hh>
#include <Shader.hh>

NAMESPACE_BEGIN

#define DEBUGNORMALSHADERTYPE "DebugNormal"
#define Debug_Shader_Name "normaldebug.geom"
#define Shining_Color_Fragshader_Name "sheencolorFragmentShader.frag"

class DebugNormalShader : public Shader {
public:
    explicit DebugNormalShader(const fs::path &path);

    string typeName() const override;

};

NAMESPACE_END

#endif //DEBUGNORMALSHADER_HH
