#pragma once

#include "bde/bde.hpp"

namespace bde::render {
    struct RenderContextState {
        glm::vec4 clearColor;
        double    clearDepth;
        int       clearStencil;
    };

    extern RenderContextState state;

    void setClearColor(const glm::vec4 &clearColor);

    void clearScreen();
    void clearScreen(const glm::vec4 &clearColor);
} // namespace bde::render
