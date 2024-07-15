#pragma once

#include <concepts>
#include <type_traits>
#include <typeinfo>

#include <filesystem>
#include <memory>
#include <variant>

namespace bde::utils {
    template <typename T, typename T1>
    concept tptr = std::same_as<std::remove_cvref_t<std::remove_pointer_t<T>>, T1> || (requires(T v) {
                       { v.operator*() } -> std::same_as<T1 &>;
                       { v.operator->() } -> std::same_as<T1 *>;
                   });

    static_assert(tptr<const int *, int>);
    static_assert(tptr<std::shared_ptr<const char *>, const char *>);

    struct file_handle {
        std::filesystem::path path;
    };

    struct string_source {
        std::variant<std::string, const std::string_view> text;
    };

    using source_definition = std::variant<string_source, file_handle>;

    std::string load_string(const source_definition &def);
    std::string read_file(const std::filesystem::path& path);
    inline std::string read_file(const file_handle& fh) { return read_file(fh.path); };
} // namespace bde::utils
