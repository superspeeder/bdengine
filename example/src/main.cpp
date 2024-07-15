#include "main.hpp"

#include <cstdlib>
#include <iostream>

#include <bde/bde.hpp>
#include <bde/colors.hpp>
#include <bde/hal.hpp>
#include <bde/render.hpp>

using bde::global;

int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;

    bde::init();

    auto *window = new bde::Window(bde::Window::Description{
        .title     = "Window",
        .size      = {800, 600},
        .resizable = false,
    });
    {
        window->swapInterval(0);

        std::vector<int8_t> vertices = {
            0, 0, 0,
            127, 0, 0,
            0, 127, 0,
        };

        auto buffer      = bde::hal::Buffer::create_unique(vertices, bde::hal::BufferUsage::StaticDraw);
        auto vertexArray = bde::hal::VertexArray::create_unique();

        buffer->bind(bde::hal::BufferTarget::Array);
        vertexArray->vertexBuffer(buffer,
                                  {bde::hal::VertexAttribute{
                                      .dataType   = bde::hal::VertexDataType::Byte,
                                      .offset     = 0,
                                      .size       = 3,
                                      .normalized = true,
                                  }},
                                  3, 0);

        while (!window->shouldClose()) {
            window->pollEvents();

            bde::render::clearScreen(bde::colors::GREEN);

            vertexArray->bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);

            window->swap();
        }
    }
    delete window;


    bde::terminate();

    return EXIT_SUCCESS;
}
