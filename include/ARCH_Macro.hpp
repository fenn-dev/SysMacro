#ifndef SYSMACRO_ARCH_HPP
#define SYSMACRO_ARCH_HPP

#define ARCH_UNDEFINED 0
#define ARCH_X86       1
#define ARCH_X64       2
#define ARCH_ARM64     3

#if defined(CURRENT_ARCH) && !defined(REPLACE_CURRENT_ARCH)
    #error "CURRENT_ARCH is already defined. PLEASE SET REPLACE_CURRENT_ARCH to 1 to replace it."
#elif defined(CURRENT_ARCH) && defined(REPLACE_CURRENT_ARCH)
    #undef CURRENT_ARCH
#endif

#if !defined(CURRENT_ARCH)

    #define CURRENT_ARCH ARCH_UNDEFINED

    #if defined(__x86_64__) || defined(_WIN64)
        #undef CURRENT_ARCH
        #define CURRENT_ARCH ARCH_X64
    #elif defined(__aarch64__) || defined(__arm64__)
        #undef CURRENT_ARCH
        #define CURRENT_ARCH ARCH_ARM64
    #elif defined(_M_IX86) || defined(__i386__)
        #undef CURRENT_ARCH
        #define CURRENT_ARCH ARCH_X86
    #endif

#endif

#if CURRENT_ARCH == ARCH_UNDEFINED
    #error "Unsupported Architecture"
#endif

// Getter for the architecture name as a string. Use if string representation is needed or supported by the environment.
inline constexpr const char* get_arch_name() {
    switch (CURRENT_ARCH) {
        case ARCH_X86:   return "x86";
        case ARCH_X64:   return "x86_64";
        case ARCH_ARM64: return "ARM64";
        default:         return "Unknown Architecture";
    }
}

#define IMPL_X86(code)
#define IMPL_X64(code)
#define IMPL_ARM64(code)
#define IMPL_UNKNOWN_ARCH(code)
#if CURRENT_ARCH == ARCH_X86
    #undef IMPL_X86
    #define IMPL_X86(code) code
#elif CURRENT_ARCH == ARCH_X64
    #undef IMPL_X64
    #define IMPL_X64(code) code
#elif CURRENT_ARCH == ARCH_ARM64
    #undef IMPL_ARM64
    #define IMPL_ARM64(code) code
#else
    #undef IMPL_UNKNOWN_ARCH
    #define IMPL_UNKNOWN_ARCH(code) code
#endif

#define IMPL_X86_64(code) IMPL_X64(code)

#endif // SYSMACRO_ARCH_HPP