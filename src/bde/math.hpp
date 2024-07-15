#pragma once

#include <glm/glm.hpp>

namespace bde::math {
    constexpr float lerp(const float &a, const float &b, const float &t) {
        return a + (b - a) * t;
    }

    constexpr glm::vec3 lerp(const glm::vec3 &a, const glm::vec3 &b, const float &t) {
        return glm::vec3{
            lerp(a.r, b.r, t),
            lerp(a.g, b.g, t),
            lerp(a.b, b.b, t),
        };
    }

    constexpr glm::vec4 lerp(const glm::vec4 &a, const glm::vec4 &b, const float &t) {
        return glm::vec4{
            lerp(a.r, b.r, t),
            lerp(a.g, b.g, t),
            lerp(a.b, b.b, t),
            lerp(a.a, b.a, t),
        };
    }
} // namespace bde::math
