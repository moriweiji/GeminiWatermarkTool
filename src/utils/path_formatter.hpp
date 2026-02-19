/**
 * @file    path_formatter.hpp
 * @brief   Custom fmt formatter for std::filesystem::path with UTF-8 support
 * @author  AllenK (Kwyshell)
 * @date    2026.01.26
 * @license MIT
 *
 * @details
 * Solves Windows UTF-8 encoding issues when logging filesystem paths.
 *
 * Problem:
 *   - Windows: path.string() returns ANSI (local codepage, e.g., CP932, CP936, CP949, CP950)
 *   - spdlog/fmt expects UTF-8
 *   - ImGui::Text expects UTF-8
 *
 * Solution:
 *   - Use path.u8string() which always returns UTF-8
 *   - C++20: u8string() returns std::u8string (char8_t) - needs reinterpret_cast
 *   - C++17: u8string() returns std::string (char) - works directly
 *
 * Usage:
 *   #include "path_formatter.hpp"
 *   spdlog::info("Processing: {}", some_path);  // Just works with fmt!
 *   ImGui::Text("File: %s", gwt::to_utf8(some_path).c_str());  // For ImGui
 */

#pragma once

#include <filesystem>
#include <string>
#include <string_view>
#include <fmt/format.h>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

namespace gwt {

/**
 * Convert filesystem path to UTF-8 encoded std::string
 *
 * This handles the C++20 char8_t issue where u8string() returns std::u8string
 * instead of std::string.
 *
 * @param path  The filesystem path to convert
 * @return      UTF-8 encoded string
 */
inline std::string to_utf8(const std::filesystem::path& path) {
    auto u8str = path.u8string();
    return std::string(
        reinterpret_cast<const char*>(u8str.data()),
        u8str.size()
    );
}

/**
 * Convert path filename to UTF-8 encoded std::string
 * Convenience function for common use case
 */
inline std::string filename_utf8(const std::filesystem::path& path) {
    return to_utf8(path.filename());
}

/**
 * Convert UTF-8 string to filesystem path
 *
 * SDL always returns UTF-8 on all platforms (including drop events).
 * On Windows without UTF-8 beta enabled, std::filesystem::path(const char*)
 * interprets the string as ANSI (system code page), causing corruption
 * for non-ASCII characters (CJK, etc.).
 *
 * This function correctly handles UTF-8 → wstring → path on Windows.
 *
 * @param utf8_str  UTF-8 encoded string (e.g., from SDL drop event)
 * @return          Properly constructed filesystem path
 */
inline std::filesystem::path path_from_utf8(const char* utf8_str) {
#ifdef _WIN32
    if (!utf8_str || !*utf8_str) return {};

    // Calculate required buffer size
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8_str, -1, nullptr, 0);
    if (len <= 0) return std::filesystem::path(utf8_str);  // fallback

    // Convert UTF-8 to wide string
    std::wstring wstr(len - 1, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, utf8_str, -1, wstr.data(), len);

    return std::filesystem::path(wstr);
#else
    // Linux/macOS are UTF-8 native
    return std::filesystem::path(utf8_str);
#endif
}

// Overload for std::string
inline std::filesystem::path path_from_utf8(const std::string& utf8_str) {
    return path_from_utf8(utf8_str.c_str());
}

}  // namespace gwt

// =============================================================================
// OpenCV UTF-8 path support for Windows
// =============================================================================

#include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>
#include <fstream>

namespace gwt {

/**
 * Read image from path with UTF-8 support on Windows
 *
 * OpenCV's imread() on Windows uses ANSI encoding, which fails for
 * non-ASCII paths (CJK characters, etc.). This function reads the file
 * as binary and uses imdecode() to properly handle UTF-8 paths.
 *
 * @param path   Filesystem path to the image
 * @param flags  OpenCV imread flags (default: IMREAD_COLOR)
 * @return       Loaded cv::Mat, or empty Mat on failure
 */
inline cv::Mat imread_utf8(const std::filesystem::path& path, int flags = cv::IMREAD_COLOR) {
    spdlog::debug("[imread_utf8] Reading: {}", path);

#ifdef _WIN32
    // On Windows, read file as binary and decode
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        spdlog::error("[imread_utf8] Failed to open file: {}", path);
        return cv::Mat();
    }

    auto size = file.tellg();
    if (size <= 0) {
        spdlog::error("[imread_utf8] Invalid file size: {}", static_cast<long long>(size));
        return cv::Mat();
    }

    file.seekg(0, std::ios::beg);

    std::vector<uchar> buffer(static_cast<size_t>(size));
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        spdlog::error("[imread_utf8] Failed to read file data");
        return cv::Mat();
    }
    file.close();

    spdlog::debug("[imread_utf8] Read {} bytes, decoding...", buffer.size());

    cv::Mat result = cv::imdecode(buffer, flags);
    if (result.empty()) {
        spdlog::error("[imread_utf8] imdecode failed for: {}", path);
    } else {
        spdlog::debug("[imread_utf8] Decoded image: {}x{}", result.cols, result.rows);
    }
    return result;
#else
    // Linux/macOS: imread works with UTF-8 natively
    cv::Mat result = cv::imread(path.string(), flags);
    if (result.empty()) {
        spdlog::error("[imread_utf8] imread failed for: {}", path);
    }
    return result;
#endif
}

/**
 * Write image to path with UTF-8 support on Windows
 *
 * @param path   Filesystem path to save the image
 * @param img    Image to save
 * @param params Optional encoding parameters
 * @return       true on success, false on failure
 */
inline bool imwrite_utf8(const std::filesystem::path& path,
                         const cv::Mat& img,
                         const std::vector<int>& params = {}) {
    spdlog::debug("[imwrite_utf8] Writing: {} ({}x{})", path, img.cols, img.rows);

#ifdef _WIN32
    // Encode image to memory buffer
    std::string ext = path.extension().string();
    std::vector<uchar> buffer;
    if (!cv::imencode(ext, img, buffer, params)) {
        spdlog::error("[imwrite_utf8] imencode failed for: {}", path);
        return false;
    }

    // Write buffer to file using wide path
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) {
        spdlog::error("[imwrite_utf8] Failed to create file: {}", path);
        return false;
    }

    file.write(reinterpret_cast<const char*>(buffer.data()),
               static_cast<std::streamsize>(buffer.size()));
    bool success = file.good();
    file.close();

    if (success) {
        spdlog::debug("[imwrite_utf8] Wrote {} bytes", buffer.size());
    } else {
        spdlog::error("[imwrite_utf8] Write failed for: {}", path);
    }
    return success;
#else
    bool success = cv::imwrite(path.string(), img, params);
    if (!success) {
        spdlog::error("[imwrite_utf8] imwrite failed for: {}", path);
    }
    return success;
#endif
}

}  // namespace gwt

// =============================================================================
// fmt formatter specialization for std::filesystem::path
// =============================================================================

template <>
struct fmt::formatter<std::filesystem::path> : fmt::formatter<std::string_view> {
    auto format(const std::filesystem::path& p, format_context& ctx) const {
        auto u8 = p.u8string();
        std::string_view sv{
            reinterpret_cast<const char*>(u8.data()),
            u8.size()
        };
        return fmt::formatter<std::string_view>::format(sv, ctx);
    }
};
