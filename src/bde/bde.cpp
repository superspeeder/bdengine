#include "bde/bde.hpp"

#include <memory>

namespace bde {
    Global *global;
    std::shared_ptr<spdlog::logger> logger;
    std::shared_ptr<spdlog::logger> gl_logger;

    void GLAPIENTRY
    debugCallback( GLenum source,
                    GLenum type,
                    GLuint id,
                    GLenum severity,
                    GLsizei length,
                    const GLchar* message,
                    const void* userParam )
    {
        std::string source_str;
        std::string type_str;
        switch (source) {
        case GL_DEBUG_SOURCE_APPLICATION:
            source_str = "application";
            break;
        case GL_DEBUG_SOURCE_API:
            source_str = "Application";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            source_str = "System";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            source_str = "Shader Compiler";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            source_str = "Third Party";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            source_str = "Other";
            break;
        }

        switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            type_str = "Error";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            type_str = "Deprecated Behavior";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            type_str = "Undefined Behavior";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            type_str = "Portability";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            type_str = "Performance";
            break;
        case GL_DEBUG_TYPE_MARKER:
            type_str = "Marker";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            type_str = "Push Group";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            type_str = "Pop Group";
            break;
        case GL_DEBUG_TYPE_OTHER:
            type_str = "Other";
            break;
        }

        switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            gl_logger->error("({}|{}) [{}] {}", source_str, type_str, id, message);
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            gl_logger->warn("({}|{}) [{}] {}", source_str, type_str, id, message);
            break;
        case GL_DEBUG_SEVERITY_LOW:
            gl_logger->info("({}|{}) [{}] {}", source_str, type_str, id, message);
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            gl_logger->debug("({}|{}) [{}] {}", source_str, type_str, id, message);
            break;
        }
    }

    Global::Global() {
        glfwInit();

        m_CombinedFileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/combined.log", SIZE_MAX, 30, true);

        logger = createGenericLogger("bde", LoggerSettings{
                                                  .write_to_stdout = true,
                                                  .create_file = true,
                                                  .include_in_combined = true,
                                              });

        gl_logger = createGenericLogger("glerror", LoggerSettings{
                                                       .write_to_stdout = true,
                                                       .create_file = true,
                                                       .include_in_combined = true,
                                                   });

        m_StdoutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    }

    Global::~Global() {
        glfwTerminate();
    }

    std::shared_ptr<spdlog::logger> Global::createGenericLogger(const std::string& name, const LoggerSettings &settings) const {
        std::vector<spdlog::sink_ptr> sinks;
        if (settings.create_file)
            sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/" + name + ".log", SIZE_MAX, 30, true));
        if (settings.write_to_stdout)
            sinks.push_back(m_StdoutSink);
        if (settings.include_in_combined)
            sinks.push_back(m_CombinedFileSink);

        if (sinks.empty()) throw std::runtime_error("Cannot create logger with no outputs");

        return std::make_shared<spdlog::logger>(name, sinks.begin(), sinks.end());
    }

    void init() {
        global = new Global();
    }

    void terminate() {
        delete global;
        global = nullptr;
    }

    Window::Window(const Window::Description &description) {
        glfwDefaultWindowHints();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#ifndef NDEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
        glfwWindowHint(GLFW_RESIZABLE, description.resizable);
        glfwWindowHint(GLFW_POSITION_X, description.pos.x);
        glfwWindowHint(GLFW_POSITION_Y, description.pos.y);
        m_Window = glfwCreateWindow((int)description.size.x, (int)description.size.y, description.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        gladLoadGL(glfwGetProcAddress);

        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true);
            glDebugMessageCallback(debugCallback, nullptr);
        }
    }

    Window::~Window() {
        glfwDestroyWindow(m_Window);
    }


    void Window::pollEvents() {
        glfwPollEvents();
        int w,h;
        glfwGetFramebufferSize(m_Window, &w, &h);
        glViewport(0, 0, w, h);
    }

    void Window::swap() {
        glfwSwapBuffers(m_Window);
    }

    void Window::swapInterval(int i) {
        glfwSwapInterval(i);
    }
} // namespace bde
