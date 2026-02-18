/**
 * @file    i18n.hpp
 * @brief   Internationalization (i18n) support for Gemini Watermark Tool
 * @author  AllenK (Kwyshell)
 * @license MIT
 */

#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <filesystem>
#include <fmt/core.h>

namespace gwt::i18n {

// =============================================================================
// Supported Languages
// =============================================================================

enum class Language {
    English,       // en
    ChineseSimp,   // zh-CN
    ChineseTrad,   // zh-TW
    Japanese       // ja
};

// =============================================================================
// Core API
// =============================================================================

/**
 * Initialize i18n system
 * @param lang_dir Directory containing language JSON files
 * @param lang Initial language (default: English)
 * @return true if initialization successful
 */
bool init(const std::filesystem::path& lang_dir, Language lang = Language::English);

/**
 * Check if i18n system is initialized
 */
bool is_initialized();

/**
 * Get current language
 */
Language current_language();

/**
 * Set language (triggers reload of language file)
 * @param lang Target language
 * @return true if language switch successful
 */
bool set_language(Language lang);

/**
 * Get list of available languages with display names
 * @return Vector of (Language, display_name) pairs
 */
std::vector<std::pair<Language, std::string>> available_languages();

/**
 * Get language code string (e.g., "en", "zh-CN")
 */
const char* language_code(Language lang);

/**
 * Translate a string key
 * @param key String key (e.g., "menu.file.open")
 * @return Translated string, or key itself if not found
 */
const char* tr(std::string_view key);

/**
 * Translate and format a string with arguments
 * @param key String key
 * @param args Format arguments
 * @return Formatted translated string
 */
template<typename... Args>
std::string trf(std::string_view key, Args&&... args) {
    try {
        return fmt::format(fmt::runtime(tr(key)), std::forward<Args>(args)...);
    } catch (const fmt::format_error&) {
        // 格式化失败时返回原始翻译
        return std::string(tr(key));
    }
}

// =============================================================================
// Convenience Macros
// =============================================================================

// 用于 ImGui 等需要 const char* 的场景
#define TR(key) ::gwt::i18n::tr(key)

// 用于格式化字符串，返回 std::string
#define TRF(key, ...) ::gwt::i18n::trf(key, __VA_ARGS__)

}  // namespace gwt::i18n
