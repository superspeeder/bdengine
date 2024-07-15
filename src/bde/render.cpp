#include "render.hpp"

namespace bde::render {
    RenderContextState state{
        .clearColor   = {0.0f, 0.0f, 0.0f, 1.0f},
        .clearDepth   = 0.0,
        .clearStencil = 0,
    };

    void setClearColor(const glm::vec4 &clearColor) {
        state.clearColor = clearColor;
    }

    void clearScreen() {
        glClearColor(state.clearColor.r, state.clearColor.g, state.clearColor.b, state.clearColor.a);
        glClearStencil(state.clearStencil);
        glClearDepth(state.clearDepth);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    void clearScreen(const glm::vec4 &clearColor) {
        setClearColor(clearColor);
        clearScreen();
    }
} // namespace bde::render
