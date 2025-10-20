//
// Created by phage on 10/20/25.
//

#ifndef GLOBALCONTEXT_HH
#define GLOBALCONTEXT_HH

#include <Common.hh>

NAMESPACE_BEGIN
    class RenderContext;

class AppContext {
public:
    AppContext();

    unique_ptr<RenderContext> aRenderContext;
    bool aIsRunning ;
    bool aIsInited ;
    bool aShouldQuit;
    bool aEditorMode ;
    bool aShowEditor ;

    void switchEditorMode();

};
NAMESPACE_END
#endif //GLOBALCONTEXT_HH
