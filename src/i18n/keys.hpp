/**
 * @file    keys.hpp
 * @brief   String key definitions for i18n
 * @author  AllenK (Kwyshell)
 * @license MIT
 *
 * @details
 * All translatable string keys are defined here as constexpr string_view.
 * This provides compile-time validation and IDE auto-completion.
 *
 * Naming convention:
 *   - menu.<menu>.<item>     : Menu items
 *   - toolbar.<action>       : Toolbar buttons
 *   - panel.<section>.<item> : Control panel
 *   - status.<state>         : Status bar messages
 *   - dialog.<name>.<item>   : Dialog content
 *   - preview.<item>         : Image preview area
 *   - shortcut.<action>      : Shortcut descriptions
 *   - cli.<context>          : CLI messages
 */

#pragma once

#include <string_view>

namespace gwt::i18n::keys {

// =============================================================================
// Menu - File
// =============================================================================
constexpr std::string_view MENU_FILE = "menu.file";
constexpr std::string_view MENU_FILE_OPEN = "menu.file.open";
constexpr std::string_view MENU_FILE_SAVE = "menu.file.save";
constexpr std::string_view MENU_FILE_SAVE_AS = "menu.file.save_as";
constexpr std::string_view MENU_FILE_CLOSE = "menu.file.close";
constexpr std::string_view MENU_FILE_EXIT = "menu.file.exit";

// =============================================================================
// Menu - Edit
// =============================================================================
constexpr std::string_view MENU_EDIT = "menu.edit";
constexpr std::string_view MENU_EDIT_PROCESS = "menu.edit.process";
constexpr std::string_view MENU_EDIT_REVERT = "menu.edit.revert";

// =============================================================================
// Menu - View
// =============================================================================
constexpr std::string_view MENU_VIEW = "menu.view";
constexpr std::string_view MENU_VIEW_COMPARE = "menu.view.compare";
constexpr std::string_view MENU_VIEW_ZOOM_IN = "menu.view.zoom_in";
constexpr std::string_view MENU_VIEW_ZOOM_OUT = "menu.view.zoom_out";
constexpr std::string_view MENU_VIEW_FIT = "menu.view.fit";
constexpr std::string_view MENU_VIEW_100 = "menu.view.100";

// =============================================================================
// Menu - Help
// =============================================================================
constexpr std::string_view MENU_HELP = "menu.help";
constexpr std::string_view MENU_HELP_DOCS = "menu.help.docs";
constexpr std::string_view MENU_HELP_ABOUT = "menu.help.about";
constexpr std::string_view MENU_HELP_LANGUAGE = "menu.help.language";

// =============================================================================
// Toolbar
// =============================================================================
constexpr std::string_view TOOLBAR_OPEN = "toolbar.open";
constexpr std::string_view TOOLBAR_SAVE = "toolbar.save";
constexpr std::string_view TOOLBAR_PROCESS = "toolbar.process";
constexpr std::string_view TOOLBAR_COMPARE = "toolbar.compare";

// =============================================================================
// Control Panel - Operation
// =============================================================================
constexpr std::string_view PANEL_OPERATION = "panel.operation";
constexpr std::string_view PANEL_OP_REMOVE = "panel.op.remove";
constexpr std::string_view PANEL_OP_ADD = "panel.op.add";

// =============================================================================
// Control Panel - Watermark Size
// =============================================================================
constexpr std::string_view PANEL_SIZE = "panel.size";
constexpr std::string_view PANEL_SIZE_AUTO = "panel.size.auto";
constexpr std::string_view PANEL_SIZE_SMALL = "panel.size.small";
constexpr std::string_view PANEL_SIZE_LARGE = "panel.size.large";
constexpr std::string_view PANEL_SIZE_CUSTOM = "panel.size.custom";

// =============================================================================
// Control Panel - Custom Watermark
// =============================================================================
constexpr std::string_view PANEL_REDETECT = "panel.redetect";
constexpr std::string_view PANEL_RESET = "panel.reset";
constexpr std::string_view PANEL_CONFIDENCE = "panel.confidence";  // "Confidence: {0:.0f}%"
constexpr std::string_view PANEL_FALLBACK = "panel.fallback";
constexpr std::string_view PANEL_DRAW_HINT = "panel.draw_hint";

// =============================================================================
// Control Panel - Detected Info
// =============================================================================
constexpr std::string_view PANEL_DETECTED = "panel.detected";
constexpr std::string_view PANEL_INFO_SIZE = "panel.info.size";
constexpr std::string_view PANEL_INFO_POS = "panel.info.pos";
constexpr std::string_view PANEL_INFO_REGION = "panel.info.region";

// =============================================================================
// Control Panel - Detection
// =============================================================================
constexpr std::string_view PANEL_DETECTION = "panel.detection";
constexpr std::string_view PANEL_AUTO_DETECT = "panel.auto_detect";
constexpr std::string_view PANEL_THRESHOLD_FMT = "panel.threshold_fmt";  // "Threshold: {0}%"
constexpr std::string_view PANEL_SKIP_BELOW = "panel.skip_below";  // "Skip images below {0}%"
constexpr std::string_view PANEL_PROCESS_ALL = "panel.process_all";
constexpr std::string_view PANEL_RECOMMENDED = "panel.recommended";

// =============================================================================
// Control Panel - Preview
// =============================================================================
constexpr std::string_view PANEL_PREVIEW = "panel.preview";
constexpr std::string_view PANEL_HIGHLIGHT = "panel.highlight";
constexpr std::string_view PANEL_SHOW_PROCESSED = "panel.show_processed";
constexpr std::string_view PANEL_ZOOM_FMT = "panel.zoom_fmt";  // "Zoom: {0:.0f}%"
constexpr std::string_view PANEL_ZOOM_FIT = "panel.zoom.fit";
constexpr std::string_view PANEL_ZOOM_100 = "panel.zoom.100";

// =============================================================================
// Control Panel - Batch
// =============================================================================
constexpr std::string_view PANEL_BATCH = "panel.batch";
constexpr std::string_view PANEL_BATCH_FILES = "panel.batch.files";  // "Files: {0}"
constexpr std::string_view PANEL_BATCH_RESULT = "panel.batch.result";  // "OK: {0}  Skipped: {1}  Failed: {2}"
constexpr std::string_view PANEL_EXIT_BATCH = "panel.exit_batch";
constexpr std::string_view PANEL_CANCEL_BATCH = "panel.cancel_batch";
constexpr std::string_view PANEL_PROCESS_BATCH = "panel.process_batch";
constexpr std::string_view PANEL_PROCESS_IMAGE = "panel.process_image";

// =============================================================================
// Shortcuts
// =============================================================================
constexpr std::string_view PANEL_SHORTCUTS = "panel.shortcuts";
constexpr std::string_view SHORTCUT_PROCESS = "shortcut.process";
constexpr std::string_view SHORTCUT_COMPARE = "shortcut.compare";
constexpr std::string_view SHORTCUT_REVERT = "shortcut.revert";
constexpr std::string_view SHORTCUT_HIDE_OVERLAY = "shortcut.hide_overlay";
constexpr std::string_view SHORTCUT_MOVE_REGION = "shortcut.move_region";
constexpr std::string_view SHORTCUT_PAN = "shortcut.pan";
constexpr std::string_view SHORTCUT_ZOOM = "shortcut.zoom";
constexpr std::string_view SHORTCUT_ZOOM_FIT = "shortcut.zoom_fit";
constexpr std::string_view SHORTCUT_ZOOM_CURSOR = "shortcut.zoom_cursor";

// =============================================================================
// Preview Area
// =============================================================================
constexpr std::string_view PREVIEW_PLACEHOLDER = "preview.placeholder";
constexpr std::string_view PREVIEW_MORE_FILES = "preview.more_files";  // "[+{0} more files...]"
constexpr std::string_view PREVIEW_RESULTS = "preview.results";
constexpr std::string_view PREVIEW_COMPLETE = "preview.complete";  // "Complete: {0} OK, {1} skipped, {2} failed (total: {3})"
constexpr std::string_view PREVIEW_WATERMARK = "preview.watermark";
constexpr std::string_view PREVIEW_REMOVED = "preview.removed";
constexpr std::string_view PREVIEW_CUSTOM = "preview.custom";
constexpr std::string_view PREVIEW_OVERLAY_HIDDEN = "preview.overlay_hidden";

// =============================================================================
// Status Messages
// =============================================================================
constexpr std::string_view STATUS_READY = "status.ready";
constexpr std::string_view STATUS_LOADED = "status.loaded";  // "Loaded: {0}x{1}"
constexpr std::string_view STATUS_PROCESSING = "status.processing";
constexpr std::string_view STATUS_REMOVED = "status.removed";
constexpr std::string_view STATUS_ADDED = "status.added";
constexpr std::string_view STATUS_REVERTED = "status.reverted";
constexpr std::string_view STATUS_SAVED = "status.saved";  // "Saved: {0}"
constexpr std::string_view STATUS_LOAD_FAILED = "status.load_failed";
constexpr std::string_view STATUS_SAVE_FAILED = "status.save_failed";
constexpr std::string_view STATUS_PROCESS_FAILED = "status.process_failed";
constexpr std::string_view STATUS_DETECTING = "status.detecting";
constexpr std::string_view STATUS_DETECTED = "status.detected";  // "Detected watermark ({0}% confidence)"
constexpr std::string_view STATUS_NOT_DETECTED = "status.not_detected";  // "No watermark detected ({0}%), using default"
constexpr std::string_view STATUS_DETECTION_FAILED = "status.detection_failed";
constexpr std::string_view STATUS_BATCH_READY = "status.batch_ready";  // "Batch: {0} files ready"
constexpr std::string_view STATUS_BATCH_PROGRESS = "status.batch_progress";  // "Batch: {0}/{1} (OK:{2} Skip:{3} Fail:{4})"
constexpr std::string_view STATUS_BATCH_CANCELLED = "status.batch_cancelled";  // "Batch cancelled ({0}/{1})"
constexpr std::string_view STATUS_BATCH_COMPLETE = "status.batch_complete";  // "Batch complete: {0} ok, {1} skipped, {2} failed"
constexpr std::string_view STATUS_ORIGINAL = "status.original";
constexpr std::string_view STATUS_PROCESSED = "status.processed";

// =============================================================================
// Dialog - About
// =============================================================================
constexpr std::string_view DIALOG_ABOUT_TITLE = "dialog.about.title";
constexpr std::string_view DIALOG_ABOUT_NAME = "dialog.about.name";
constexpr std::string_view DIALOG_ABOUT_VERSION = "dialog.about.version";  // "Version {0}"
constexpr std::string_view DIALOG_ABOUT_DESC = "dialog.about.desc";
constexpr std::string_view DIALOG_ABOUT_DESC2 = "dialog.about.desc2";
constexpr std::string_view DIALOG_ABOUT_AUTHOR = "dialog.about.author";
constexpr std::string_view DIALOG_ABOUT_LICENSE = "dialog.about.license";
constexpr std::string_view DIALOG_OK = "dialog.ok";

// =============================================================================
// Dialog - Batch Confirm
// =============================================================================
constexpr std::string_view DIALOG_BATCH_TITLE = "dialog.batch.title";
constexpr std::string_view DIALOG_BATCH_WARNING = "dialog.batch.warning";
constexpr std::string_view DIALOG_BATCH_FILES = "dialog.batch.files";  // "Files to process: {0}"
constexpr std::string_view DIALOG_BATCH_MODE = "dialog.batch.mode";  // "Mode: {0}"
constexpr std::string_view DIALOG_BATCH_SIZE = "dialog.batch.size";  // "Size: {0}"
constexpr std::string_view DIALOG_BATCH_CUSTOM_AUTO = "dialog.batch.custom_auto";
constexpr std::string_view DIALOG_BATCH_THRESHOLD = "dialog.batch.threshold";  // "Detection threshold: {0}%"
constexpr std::string_view DIALOG_BATCH_SKIP_INFO = "dialog.batch.skip_info";  // "Images below {0}% confidence will be skipped."
constexpr std::string_view DIALOG_BATCH_PROCESS_ALL = "dialog.batch.process_all";
constexpr std::string_view DIALOG_BATCH_NO_DETECT = "dialog.batch.no_detect";
constexpr std::string_view DIALOG_PROCESS = "dialog.process";
constexpr std::string_view DIALOG_CANCEL = "dialog.cancel";

// =============================================================================
// Size Mode Labels
// =============================================================================
constexpr std::string_view SIZE_AUTO = "size.auto";
constexpr std::string_view SIZE_SMALL = "size.small";
constexpr std::string_view SIZE_LARGE = "size.large";
constexpr std::string_view SIZE_CUSTOM = "size.custom";

// =============================================================================
// CLI Messages
// =============================================================================
constexpr std::string_view CLI_STANDALONE = "cli.standalone";
constexpr std::string_view CLI_AUTO_DETECTION = "cli.auto_detection";  // "Auto-detection enabled (threshold: {0}%)"
constexpr std::string_view CLI_SUMMARY = "cli.summary";
constexpr std::string_view CLI_PROCESSED = "cli.processed";  // "Processed: {0}"
constexpr std::string_view CLI_SKIPPED = "cli.skipped";  // ", Skipped: {0}"
constexpr std::string_view CLI_FAILED = "cli.failed";  // ", Failed: {0}"
constexpr std::string_view CLI_TOTAL = "cli.total";  // " (Total: {0})"
constexpr std::string_view CLI_OK = "cli.ok";
constexpr std::string_view CLI_SKIP = "cli.skip";
constexpr std::string_view CLI_FAIL = "cli.fail";
constexpr std::string_view CLI_ERROR = "cli.error";
constexpr std::string_view CLI_FATAL = "cli.fatal";
constexpr std::string_view CLI_CONFIDENCE = "cli.confidence";  // "({0}% confidence)"
constexpr std::string_view CLI_FILE_NOT_FOUND = "cli.file_not_found";  // "File not found: {0}"
constexpr std::string_view CLI_PATH_HINT = "cli.path_hint";
constexpr std::string_view CLI_DIR_NOT_SUPPORTED = "cli.dir_not_supported";  // "Directory not supported in simple mode: {0}"
constexpr std::string_view CLI_USE_DIR_HINT = "cli.use_dir_hint";
constexpr std::string_view CLI_INPUT_NOT_FOUND = "cli.input_not_found";  // "Input path not found: {0}"
constexpr std::string_view CLI_CJK_HINT = "cli.cjk_hint";
constexpr std::string_view CLI_GUI_HINT = "cli.gui_hint";
constexpr std::string_view CLI_FORCE_WARNING = "cli.force_warning";
constexpr std::string_view CLI_FORCING_SMALL = "cli.forcing_small";
constexpr std::string_view CLI_FORCING_LARGE = "cli.forcing_large";
constexpr std::string_view CLI_BOTH_SIZE_ERROR = "cli.both_size_error";

// =============================================================================
// Window Title
// =============================================================================
constexpr std::string_view WINDOW_TITLE = "window.title";

}  // namespace gwt::i18n::keys
