# sysmacro

A lightweight, zero-dependency, header-only C++20 utility for ultra-fast compile-time operating system and architecture detection. Designed specifically for low-level systems programming, custom operating systems, and high-performance cross-platform toolchains.

## Features

- **Header-Only & Zero Dependencies**: Drop the files straight into your /include directory and immediately use them.
- **Zero-Cost Stringification**: Inline `constexpr` helpers that cost absolutely nothing if they aren't called.
- **Definition Collision Protection**: Built-in protection guards to prevent silent macro overrides unless explicitly requested via `REPLACE_CURRENT_OS` or `REPLACE_CURRENT_ARCH`.
- **IDE Friendly**: Keeps language servers like `clangd` perfectly happy across cross-compilation boundaries.

---

## Repository Structure

```
📁 sysmacro/
├── 📄 .clangd
├── 📄 .gitignore
├── 📄 CMakeLists.txt
├── 📄 LICENSE
├── 📄 README.md
├── 📁 include/
│   ├── 📄 sysmacro.hpp      <-- Umbrella master header
│   ├── 📄 sysmacro_os.hpp   <-- Isolated Operating System detection
│   └── 📄 sysmacro_arch.hpp <-- Isolated Architecture detection
└── 📁 tests/
    └── 📄 verify.cpp        <-- Standalone validation suite
```

---

## Configuration & Core Enums

### Operating Systems (sysmacro_os.hpp)
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

### Basic Inclusion
To include the complete suite, use the master umbrella header:

```cpp
#include <sysmacro.hpp>
#include <iostream>

int main() {
    std::cout << "Targeting OS: " << get_os_name() << "\n";
    std::cout << "Targeting Arch: " << get_arch_name() << "\n";
}
```

### Pre-existing Definition Guards
If `CURRENT_OS` or `CURRENT_ARCH` are already defined anywhere in your compilation unit before including these headers, a compilation #error will trigger to prevent unexpected behavior. 

If you intentionally want to override existing definitions, you must specify the override flags before inclusion:

#define REPLACE_CURRENT_OS 1
#define REPLACE_CURRENT_ARCH 1
#include <sysmacro.hpp>

---

## Integration via CMake

`sysmacro` can be dropped into your existing CMake pipeline gracefully. It automatically detects if it's being included by another project via add_subdirectory() or FetchContent, and safely exposes an INTERFACE target without exposing its internal verification tests.

# Include in your parent project CMakeLists.txt
add_subdirectory(third_party/sysmacro)

# Link against the header-only interface
target_link_libraries(your_project PRIVATE SysMacro)

---

## Performance & Bare-Metal Safety Notice

The helper stringifiers get_os_name() and get_arch_name() are qualified with inline constexpr. If they are never called in your code, the compiler completely strips the string tables out of your binary layout. 

> ⚠️ Warning for Bare-Metal Environment Creators: If these helpers are invoked within early kernel initialization sequences before physical memory page tables or virtual addressing are set up, accessing the returned data pointers may trip a CPU fault due to unmapped .rodata string segments. Use strictly where data segment pools are valid and supported.