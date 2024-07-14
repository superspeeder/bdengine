#include "main.hpp"

#include <cstdlib>
#include <iostream>

#include <bde/bde.hpp>

using bde::global;

int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;

    bde::init();

    auto* window = new bde::Window(bde::Window::Description{
        .title = "Window",
        .size = {800, 600},
        .resizable = false,
    });

    window->swapInterval(0);



    while (!window->shouldClose()) {
        window->pollEvents();

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        window->swap();
    }

    delete window;


    bde::terminate();

    return EXIT_SUCCESS;
}
