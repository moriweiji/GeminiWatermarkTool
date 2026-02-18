/**
 * @file    i18n.cpp
 * @brief   i18n implementation - JSON loading and string lookup
 * @author  AllenK (Kwyshell)
 * @license MIT
 */

#include "i18n.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <unordered_map>
#include <spdlog/spdlog.h>

namespace gwt::i18n {

namespace {

// =============================================================================
// Internal State
// =============================================================================

struct I18nState {
    bool initialized = false;
    Language current = Language::English;
    std::filesystem::path lang_dir;
    std::unordered_map<std::string, std::string> strings;
    std::unordered_map<std::string, std::string> fallback;  // English fallback

    // 用于返回 const char* 的持久化存储
    std::string last_lookup_result;
};

I18nState& state() {
    static I18nState s;
    return s;
}

// =============================================================================
// Helper Functions
// =============================================================================

std::string lang_to_filename(Language lang) {
    switch (lang) {
        case Language::English:     return "en.json";
        case Language::ChineseSimp: return "zh-CN.json";
        case Language::ChineseTrad: return "zh-TW.json";
        case Language::Japanese:    return "ja.json";
    }
    return "en.json";
}

/**
 * Flatten nested JSON to dot-notation keys
 * e.g., {"menu": {"file": "File"}} -> {"menu.file": "File"}
 */
void flatten_json(const nlohmann::json& j, const std::string& prefix,
                  std::unordered_map<std::string, std::string>& out) {
    for (auto& [key, value] : j.items()) {
        // 跳过 meta 节点
        if (prefix.empty() && key == "meta") {
            continue;
        }

        std::string full_key = prefix.empty() ? key : prefix + "." + key;

        if (value.is_object()) {
            flatten_json(value, full_key, out);
        } else if (value.is_string()) {
            out[full_key] = value.get<std::string>();
        }
    }
}

bool load_language_file(const std::filesystem::path& path,
                        std::unordered_map<std::string, std::string>& out) {
    if (!std::filesystem::exists(path)) {
        spdlog::warn("[i18n] Language file not found: {}", path.string());
        return false;
    }

    try {
        std::ifstream file(path);
        if (!file.is_open()) {
            spdlog::error("[i18n] Failed to open: {}", path.string());
            return false;
        }

        nlohmann::json j = nlohmann::json::parse(file);
        out.clear();
        flatten_json(j, "", out);

        spdlog::debug("[i18n] Loaded {} strings from {}", out.size(), path.string());
        return true;

    } catch (const nlohmann::json::parse_error& e) {
        spdlog::error("[i18n] JSON parse error in {}: {}", path.string(), e.what());
        return false;
    } catch (const std::exception& e) {
        spdlog::error("[i18n] Failed to load {}: {}", path.string(), e.what());
        return false;
    }
}

}  // anonymous namespace

// =============================================================================
// Public API Implementation
// =============================================================================

bool init(const std::filesystem::path& lang_dir, Language lang) {
    auto& s = state();
    s.lang_dir = lang_dir;
    s.initialized = false;

    // 始终加载英文作为 fallback
    auto en_path = lang_dir / "en.json";
    if (!load_language_file(en_path, s.fallback)) {
        spdlog::error("[i18n] Failed to load English fallback from {}", en_path.string());
        return false;
    }

    s.initialized = true;

    // 加载目标语言
    if (lang == Language::English) {
        s.strings = s.fallback;
        s.current = lang;
        spdlog::info("[i18n] Initialized with English");
        return true;
    }

    return set_language(lang);
}

bool is_initialized() {
    return state().initialized;
}

Language current_language() {
    return state().current;
}

bool set_language(Language lang) {
    auto& s = state();

    if (!s.initialized) {
        spdlog::warn("[i18n] Not initialized, cannot switch language");
        return false;
    }

    if (lang == Language::English) {
        s.strings = s.fallback;
        s.current = lang;
        spdlog::info("[i18n] Switched to English");
        return true;
    }

    auto path = s.lang_dir / lang_to_filename(lang);

    if (load_language_file(path, s.strings)) {
        s.current = lang;
        spdlog::info("[i18n] Switched to {}", lang_to_filename(lang));
        return true;
    }

    // 加载失败，回退到英文
    spdlog::warn("[i18n] Failed to load {}, falling back to English", lang_to_filename(lang));
    s.strings = s.fallback;
    s.current = Language::English;
    return false;
}

std::vector<std::pair<Language, std::string>> available_languages() {
    return {
        {Language::English,     "English"},
        {Language::ChineseSimp, "简体中文"},
        {Language::ChineseTrad, "繁體中文"},
        {Language::Japanese,    "日本語"}
    };
}

const char* language_code(Language lang) {
    switch (lang) {
        case Language::English:     return "en";
        case Language::ChineseSimp: return "zh-CN";
        case Language::ChineseTrad: return "zh-TW";
        case Language::Japanese:    return "ja";
    }
    return "en";
}

const char* tr(std::string_view key) {
    auto& s = state();
    std::string k(key);

    // 尝试当前语言
    auto it = s.strings.find(k);
    if (it != s.strings.end()) {
        return it->second.c_str();
    }

    // 回退到英文
    it = s.fallback.find(k);
    if (it != s.fallback.end()) {
        return it->second.c_str();
    }

    // 最后返回 key 本身（帮助识别缺失的翻译）
    spdlog::debug("[i18n] Missing translation: {}", key);

    // 存储到持久化字符串以返回有效的 const char*
    s.last_lookup_result = k;
    return s.last_lookup_result.c_str();
}

}  // namespace gwt::i18n
