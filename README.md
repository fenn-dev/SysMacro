# sysmacro

A lightweight, zero-dependency, header-only C++20 utility for ultra-fast compile-time operating system and architecture detection. Designed specifically for low-level systems programming, custom operating systems, and high-performance cross-platform toolchains.

## Features

* Header-Only & Zero Dependencies: Drop the files into your include directory and go.
* Zero-Cost Abstraction: All detection logic is `constexpr`. If a stringifier is never called, the compiler strips the string tables entirely.
* Deterministic Configuration: Built-in collision protection prevents accidental macro overrides.
* Platform-Aware Macros: Includes specialized `IMPL_` macros to cleanly encapsulate platform or architecture-specific implementation blocks.
* IDE-Friendly: Compatible with modern language servers (e.g., `clangd`) for seamless cross-compilation support.

---

## Repository Structure

```text
📁 sysmacro/
├── 📁 include/
│   ├── 📄 sysmacro.hpp        <-- Umbrella master header
│   ├── 📄 sysmacro_os.hpp     <-- OS detection & platform macros
│   └── 📄 sysmacro_arch.hpp   <-- Arch detection & arch macros
└── 📁 tests/
└── 📄 verify.cpp          <-- Standalone validation suite
```

---

## Configuration & Enums

### Operating Systems (`sysmacro_os.hpp`)
| Macro Identifier | Value | Target Platform |
| :--- | :--- | :--- |
| OS_UNDEFINED | 0 | Fallback / Unknown Target |
| OS_WINDOWS | 1 | Microsoft Windows (32-bit / 64-bit) |
| OS_LINUX | 2 | Linux / POSIX Generic Fallbacks |
| OS_MACOS | 3 | Apple macOS |
| OS_ALOPEX | 4 | AlopexOS Natively |

### Architectures (sysmacro_arch.hpp)
| Macro Identifier | Value | Word Size / Details |
| :--- | :--- | :--- |
| ARCH_UNDEFINED | 0 | Fallback / Unknown Target |
| ARCH_X86 | 1 | 32-bit x86 (_M_IX86, __i386__) |
| ARCH_X64 | 2 | 64-bit x86_64 (__x86_64__, _WIN64) |
| ARCH_ARM64 | 3 | 64-bit ARM (__aarch64__, __arm64__) |

---

## Usage Guide

### Implementation Macros (The DSL Pattern)
`sysmacro` provides `IMPL_` macros that automatically expand to your code *only* if the condition matches the build target. This keeps your logic clean and prevents `#ifdef` soup.

```cpp
#include <sysmacro.hpp>

// This code only exists if compiled for Windows
IMPL_WINDOWS(
    void initialize_platform() { /* Windows-specific setup */ }
)

// This code only exists if compiled for x64
IMPL_X64(
    void optimized_math() { /* ASM or intrinsic implementation */ }
)
```

### Pre-existing Definition Guards
To prevent accidental symbol collisions, `sysmacro` triggers a compilation error if `CURRENT_OS` or `CURRENT_ARCH` is pre-defined. To explicitly override these:

```cpp
#define REPLACE_CURRENT_OS 1
#define REPLACE_CURRENT_ARCH 1
#include <sysmacro.hpp>
```

---

## Performance & Bare-Metal Safety Notice

The `get_os_name()` and `get_arch_name()` helpers are `inline constexpr`. If unused, the compiler effectively deletes them from your binary.

---

```cpp
#include <sysmacro.hpp>
#include <iostream>

int main() {
    std::cout << "Targeting OS: " << get_os_name() << "\n";
    std::cout << "Targeting Arch: " << get_arch_name() << "\n";
}
```

---

## Integration via CMake

`sysmacro` is designed to be added via `add_subdirectory`.

---

> ⚠️ Bare-Metal Warning: If these helpers are invoked during early kernel boot (before MMU/paging/data segment relocation), accessing the string return values may trigger a page fault or General Protection Fault because the `.rodata` section may not yet be mapped. Use these only after your data segment is initialized and available.