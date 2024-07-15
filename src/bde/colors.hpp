#pragma once

#include <glm/glm.hpp>

namespace bde::colors {
    constinit glm::vec4 BLACK       = {0.0f, 0.0f, 0.0f, 1.0f};
    constinit glm::vec4 WHITE       = {1.0f, 1.0f, 1.0f, 1.0f};
    constinit glm::vec4 RED         = {1.0f, 0.0f, 0.0f, 1.0f};
    constinit glm::vec4 GREEN       = {0.0f, 1.0f, 0.0f, 1.0f};
    constinit glm::vec4 BLUE        = {0.0f, 0.0f, 1.0f, 1.0f};
    constinit glm::vec4 YELLOW      = {1.0f, 1.0f, 0.0f, 1.0f};
    constinit glm::vec4 CYAN        = {0.0f, 1.0f, 1.0f, 1.0f};
    constinit glm::vec4 MAGENTA     = {1.0f, 0.0f, 1.0f, 1.0f};
    constinit glm::vec4 TRANSPARENT = {0.0f, 0.0f, 0.0f, 0.0f};
} // namespace bde::colors
