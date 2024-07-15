#pragma once

namespace bde::render {
    class Renderable {
      public:
        virtual ~Renderable() = default;

        virtual void render(/* TODO: figure out what will need to be passed into here */) = 0;
    };
}