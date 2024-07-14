#pragma once

#include <array>
#include <cassert>
#include <cinttypes>
#include <concepts>
#include <cstdlib>
#include <stdexcept>
#include <type_traits>

#include <unistd.h>

#include <glad/gl.h>

#include <GLFW/glfw3.h>
#include <vector>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include "bde/math.hpp"

#define BDE_GENERATE_FLAGS(bits)                                                                                                                                                   \
    constexpr std::underlying_type_t<bits> operator|(const std::underlying_type_t<bits> &a, const bits &b) {                                                                       \
        return a | (std::underlying_type_t<bits>)b;                                                                                                                                \
    }                                                                                                                                                                              \
    constexpr std::underlying_type_t<bits> operator|(const bits &a, const std::underlying_type_t<bits> &b) {                                                                       \
        return (std::underlying_type_t<bits>)a | b;                                                                                                                                \
    }                                                                                                                                                                              \
    constexpr std::underlying_type_t<bits> operator|(const bits &a, const bits &b) {                                                                                               \
        return (std::underlying_type_t<bits>)a | (std::underlying_type_t<bits>)b;                                                                                                  \
    }                                                                                                                                                                              \
    constexpr std::underlying_type_t<bits> operator&(const std::underlying_type_t<bits> &a, const bits &b) {                                                                       \
        return a & (std::underlying_type_t<bits>)b;                                                                                                                                \
    }                                                                                                                                                                              \
    constexpr std::underlying_type_t<bits> operator&(const bits &a, const std::underlying_type_t<bits> &b) {                                                                       \
        return (std::underlying_type_t<bits>)a & b;                                                                                                                                \
    }                                                                                                                                                                              \
    constexpr std::underlying_type_t<bits> operator&(const bits &a, const bits &b) {                                                                                               \
        return (std::underlying_type_t<bits>)a & (std::underlying_type_t<bits>)b;                                                                                                  \
    }

namespace bde {

    struct LoggerSettings {
        bool write_to_stdout;
        bool create_file;
        bool include_in_combined;
    };

    struct Global {
        Global();
        ~Global();

        [[nodiscard]] std::shared_ptr<spdlog::logger> createGenericLogger(const std::string& name, const LoggerSettings& settings) const;

      private:
        std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> m_CombinedFileSink;
        std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> m_StdoutSink;
    };

    extern std::shared_ptr<spdlog::logger> logger;

    extern Global *global;

    class Window {
      public:
        struct Description {
            std::string title;
            glm::uvec2  size;
            glm::ivec2  pos       = {GLFW_ANY_POSITION, GLFW_ANY_POSITION};
            bool        resizable = false;
        };

        explicit Window(const Description &description);
        ~Window();

        void pollEvents();

        [[nodiscard]] inline bool shouldClose() const noexcept { return glfwWindowShouldClose(m_Window); };

        void swap();

        void swapInterval(int i);

      private:
        GLFWwindow *m_Window;
    };

    void init();
    void terminate();
} // namespace bde
