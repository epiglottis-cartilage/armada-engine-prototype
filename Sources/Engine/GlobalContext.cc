//
// Created by phage on 10/20/25.
//

#include <GlobalContext.hh>
#include <RenderSystem.hh>
#include <SDL2/SDL.h>

NAMESPACE_BEGIN

AppContext::AppContext() :
    aIsRunning(false), //use this if possible......
    aIsInited(false),
    aShouldQuit(false),
    aEditorMode(false),
    aShowEditor(true)
{
    aRenderContext = make_unique<RenderContext>();
}

void AppContext::switchEditorMode()
{
    SDL_SetRelativeMouseMode(aEditorMode ? SDL_FALSE : SDL_TRUE);
    SDL_ShowCursor(aEditorMode ? SDL_ENABLE : SDL_DISABLE);
}


NAMESPACE_END