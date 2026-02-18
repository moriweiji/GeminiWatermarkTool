# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

GeminiWatermarkTool removes Gemini visible watermarks from images using mathematically accurate reverse alpha blending. Available as both CLI and GUI (ImGui + SDL3).

## Build Commands

Prerequisites: CMake 3.21+, C++20 compiler, vcpkg, Ninja

```bash
# List available presets
cmake --list-presets

# macOS (Universal Binary with GUI)
cmake -B build-x64 -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_GUI=ON \
  -DVCPKG_MANIFEST_FEATURES=gui \
  -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake \
  -DVCPKG_TARGET_TRIPLET=x64-osx \
  -DCMAKE_OSX_ARCHITECTURES=x86_64
cmake --build build-x64

cmake -B build-arm64 -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_GUI=ON \
  -DVCPKG_MANIFEST_FEATURES=gui \
  -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake \
  -DVCPKG_TARGET_TRIPLET=arm64-osx \
  -DCMAKE_OSX_ARCHITECTURES=arm64
cmake --build build-arm64

# Create Universal Binary
lipo -create build-x64/GeminiWatermarkTool build-arm64/GeminiWatermarkTool -output GeminiWatermarkTool

# Windows (with D3D11 + OpenGL backends)
cmake --preset windows-x64-Release
cmake --build --preset windows-x64-Release

# Linux
cmake --preset linux-x64-Release
cmake --build --preset linux-x64-Release

# CLI-only build (no GUI)
cmake -B build -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_GUI=OFF \
  -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

## Architecture

### Core Engine (`src/core/`)
- `watermark_engine.hpp/cpp` - Main engine: alpha map management, add/remove watermark operations
- `watermark_detector.hpp/cpp` - Three-stage NCC detection algorithm (spatial, gradient, variance)
- `blend_modes.hpp/cpp` - Alpha blending math operations
- `types.hpp` - Shared type definitions

The engine uses embedded 48×48 and 96×96 alpha maps (in `assets/embedded_assets.hpp`) derived from reverse-engineering Gemini's watermark blending.

### Entry Point (`src/main.cpp`)
Routes to GUI or CLI based on arguments:
- No args or `--gui`: Launch GUI (if compiled with `BUILD_GUI=ON`)
- Any other args: CLI mode

### CLI (`src/cli/`)
Command-line interface with simple mode (drag & drop) and standard mode (`-i`/`-o`).

### GUI (`src/gui/`)
ImGui-based desktop application with multiple render backends:
- `backend/` - Render backend abstraction (OpenGL, D3D11, Vulkan)
- `app/` - Application state and controller
- `widgets/` - UI components (main window, image preview)
- `resources/style.hpp` - Theme constants

## Key Build Options

| Option | Description |
|--------|-------------|
| `BUILD_GUI` | Enable GUI (requires gui feature in vcpkg) |
| `ENABLE_D3D11` | D3D11 backend (Windows only, requires BUILD_GUI) |
| `ENABLE_VULKAN` | Vulkan backend (requires BUILD_GUI) |

Compile definitions: `GWT_HAS_GUI`, `GWT_HAS_D3D11`, `GWT_HAS_VULKAN`

## Watermark Detection Algorithm

Three-stage NCC (Normalized Cross-Correlation):
1. Spatial NCC (50% weight) - Correlates image region with alpha map
2. Gradient NCC (30% weight) - Sobel edge matching for star-shaped pattern
3. Variance Analysis (20% weight) - Texture dampening detection

Default threshold: 25% confidence

## Watermark Size Rules

| Image Size | Watermark | Position |
|------------|-----------|----------|
| W ≤ 1024 OR H ≤ 1024 | 48×48 | Bottom-right, 32px margin |
| W > 1024 AND H > 1024 | 96×96 | Bottom-right, 64px margin |
