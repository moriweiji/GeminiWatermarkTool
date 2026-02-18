/**
 * @file    i18n_test.cpp
 * @brief   Unit tests for i18n module
 * @author  AllenK (Kwyshell)
 * @license MIT
 */

#include <gtest/gtest.h>
#include "i18n/i18n.hpp"
#include "i18n/keys.hpp"
#include <filesystem>

namespace gwt::i18n {

class I18nTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Find lang directory relative to test executable
        lang_dir_ = std::filesystem::current_path() / "lang";
        if (!std::filesystem::exists(lang_dir_)) {
            // Try parent directory (for different build configurations)
            lang_dir_ = std::filesystem::current_path().parent_path() / "lang";
        }
    }

    std::filesystem::path lang_dir_;
};

// =============================================================================
// Initialization Tests
// =============================================================================

TEST_F(I18nTest, InitWithValidPath) {
    ASSERT_TRUE(std::filesystem::exists(lang_dir_))
        << "Language directory not found: " << lang_dir_;
    EXPECT_TRUE(init(lang_dir_, Language::English));
    EXPECT_TRUE(is_initialized());
}

TEST_F(I18nTest, InitWithInvalidPath) {
    EXPECT_FALSE(init("/nonexistent/path", Language::English));
}

TEST_F(I18nTest, InitDefaultsToEnglish) {
    ASSERT_TRUE(init(lang_dir_, Language::English));
    EXPECT_EQ(current_language(), Language::English);
}

// =============================================================================
// Translation Tests
// =============================================================================

TEST_F(I18nTest, TranslateKnownKey) {
    ASSERT_TRUE(init(lang_dir_, Language::English));

    // Test menu keys
    EXPECT_STREQ(tr("menu.file"), "File");
    EXPECT_STREQ(tr("menu.file.open"), "Open...");
    EXPECT_STREQ(tr("menu.edit"), "Edit");
}

TEST_F(I18nTest, TranslateNestedKey) {
    ASSERT_TRUE(init(lang_dir_, Language::English));

    // Test deeply nested keys
    EXPECT_STREQ(tr("dialog.about.title"), "About");
    EXPECT_STREQ(tr("panel.size.auto"), "Auto Detect");
}

TEST_F(I18nTest, FallbackForMissingKey) {
    ASSERT_TRUE(init(lang_dir_, Language::English));

    // Unknown key should return the key itself
    const char* result = tr("unknown.nonexistent.key");
    EXPECT_STREQ(result, "unknown.nonexistent.key");
}

TEST_F(I18nTest, TranslateUsingKeyConstants) {
    ASSERT_TRUE(init(lang_dir_, Language::English));

    // Test using keys.hpp constants
    EXPECT_STREQ(tr(keys::MENU_FILE), "File");
    EXPECT_STREQ(tr(keys::TOOLBAR_OPEN), "Open");
    EXPECT_STREQ(tr(keys::STATUS_READY), "Ready");
}

// =============================================================================
// Format String Tests
// =============================================================================

TEST_F(I18nTest, FormatStringWithArgs) {
    ASSERT_TRUE(init(lang_dir_, Language::English));

    // Test format strings
    auto result = trf("status.loaded", 1920, 1080);
    EXPECT_EQ(result, "Loaded: 1920x1080");
}

TEST_F(I18nTest, FormatStringWithSingleArg) {
    ASSERT_TRUE(init(lang_dir_, Language::English));

    auto result = trf("status.saved", "/path/to/file.png");
    EXPECT_EQ(result, "Saved: /path/to/file.png");
}

TEST_F(I18nTest, FormatStringWithMultipleArgs) {
    ASSERT_TRUE(init(lang_dir_, Language::English));

    auto result = trf("preview.complete", 10, 2, 1, 13);
    EXPECT_EQ(result, "Complete: 10 OK, 2 skipped, 1 failed (total: 13)");
}

// =============================================================================
// Language Switching Tests
// =============================================================================

TEST_F(I18nTest, SwitchToChineseSimplified) {
    ASSERT_TRUE(init(lang_dir_, Language::English));

    // Switch to Chinese
    EXPECT_TRUE(set_language(Language::ChineseSimp));
    EXPECT_EQ(current_language(), Language::ChineseSimp);

    // Verify Chinese translation
    EXPECT_STREQ(tr("menu.file"), "文件");
    EXPECT_STREQ(tr("toolbar.open"), "打开");
}

TEST_F(I18nTest, SwitchBackToEnglish) {
    ASSERT_TRUE(init(lang_dir_, Language::ChineseSimp));

    // Switch back to English
    EXPECT_TRUE(set_language(Language::English));
    EXPECT_EQ(current_language(), Language::English);

    // Verify English translation
    EXPECT_STREQ(tr("menu.file"), "File");
}

TEST_F(I18nTest, FallbackToEnglishForMissingLanguage) {
    ASSERT_TRUE(init(lang_dir_, Language::English));

    // Try to switch to Japanese (file doesn't exist)
    bool result = set_language(Language::Japanese);

    // Should fall back to English
    EXPECT_FALSE(result);
    EXPECT_EQ(current_language(), Language::English);
}

// =============================================================================
// Available Languages Tests
// =============================================================================

TEST_F(I18nTest, AvailableLanguagesNotEmpty) {
    auto langs = available_languages();
    EXPECT_FALSE(langs.empty());
    EXPECT_GE(langs.size(), 2u);  // At least English and Chinese
}

TEST_F(I18nTest, AvailableLanguagesContainsEnglish) {
    auto langs = available_languages();
    bool found = false;
    for (const auto& [lang, name] : langs) {
        if (lang == Language::English) {
            found = true;
            EXPECT_EQ(name, "English");
            break;
        }
    }
    EXPECT_TRUE(found);
}

// =============================================================================
// Language Code Tests
// =============================================================================

TEST_F(I18nTest, LanguageCodeCorrect) {
    EXPECT_STREQ(language_code(Language::English), "en");
    EXPECT_STREQ(language_code(Language::ChineseSimp), "zh-CN");
    EXPECT_STREQ(language_code(Language::ChineseTrad), "zh-TW");
    EXPECT_STREQ(language_code(Language::Japanese), "ja");
}

// =============================================================================
// Edge Cases
// =============================================================================

TEST_F(I18nTest, EmptyKeyReturnsEmpty) {
    ASSERT_TRUE(init(lang_dir_, Language::English));

    const char* result = tr("");
    EXPECT_STREQ(result, "");
}

TEST_F(I18nTest, TranslateBeforeInit) {
    // tr() should handle uninitialized state gracefully
    // (returns key itself since no translations loaded)
    const char* result = tr("menu.file");
    // Either returns key or empty, but shouldn't crash
    EXPECT_NE(result, nullptr);
}

}  // namespace gwt::i18n
