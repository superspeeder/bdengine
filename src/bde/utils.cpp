#include "bde/utils.hpp"

#include <fstream>

namespace bde::utils {
    std::string load_string(const std::variant<string_source, file_handle> &def) {
        switch (def.index()) {
        case 0: {
            auto ss = std::get<0>(def);
            switch (ss.text.index()) {
            case 0: {
                return std::get<0>(ss.text);
            }
            case 1:
                return std::string(std::get<1>(ss.text));
            }
        }
        case 1: {
            return read_file(std::get<1>(def));
        }
        }

        throw std::runtime_error("Bad variant value");
    }

    std::string utils::read_file(const std::filesystem::path &path) {
        std::ifstream f(path, std::ios::in | std::ios::ate);
        auto end = f.tellg();
        f.seekg(0);
        std::string text;
        text.resize(end);
        f.read(text.data(), end);
        return text;
    }
} // namespace bde::utils
