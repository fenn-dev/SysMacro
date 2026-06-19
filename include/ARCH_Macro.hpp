#ifndef SYSMACRO_ARCH_HPP
#define SYSMACRO_ARCH_HPP

#define ARCH_UNDEFINED 0
#define ARCH_X86 1
#define ARCH_X64 2
#define ARCH_ARM32 3
#define ARCH_ARM64 4
#define ARCH_RISCV32 5
#define ARCH_RISCV64 6
#define ARCH_MIPS32 7
#define ARCH_MIPS64 8
#define ARCH_PPC32 9
#define ARCH_PPC64 10
#define ARCH_SPARC32 11
#define ARCH_SPARC64 12
#define ARCH_IA64 13
#define ARCH_S390X 14
#define ARCH_WASM32 15
#define ARCH_WASM64 16

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
    #elif defined(__riscv_xlen) && __riscv_xlen == 64
        #undef CURRENT_ARCH
        #define CURRENT_ARCH ARCH_RISCV64
    #elif defined(__riscv_xlen) && __riscv_xlen == 32
        #undef CURRENT_ARCH
        #define CURRENT_ARCH ARCH_RISCV32
    #elif defined(__mips64) || defined(__mips64_)
        #undef CURRENT_ARCH
        #define CURRENT_ARCH ARCH_MIPS64
    #elif defined(__mips__) || defined(__mips32__)
        #undef CURRENT_ARCH
        #define CURRENT_ARCH ARCH_MIPS32
    #elif defined(__powerpc64__) || defined(__ppc64__)
        #undef CURRENT_ARCH
        #define CURRENT_ARCH ARCH_PPC64
    #elif defined(__powerpc__) || defined(__ppc__)
        #undef CURRENT_ARCH
        #define CURRENT_ARCH ARCH_PPC32
    #elif defined(__sparc64__)
        #undef CURRENT_ARCH
        #define CURRENT_ARCH ARCH_SPARC64
    #elif defined(__sparc__)
        #undef CURRENT_ARCH
        #define CURRENT_ARCH ARCH_SPARC32
    #elif defined(__ia64__)
        #undef CURRENT_ARCH
        #define CURRENT_ARCH ARCH_IA64
    #elif defined(__s390x__)
        #undef CURRENT_ARCH
        #define CURRENT_ARCH ARCH_S390X
    #elif defined(__wasm__)
        #undef CURRENT_ARCH
        #define CURRENT_ARCH ARCH_WASM32
    #elif defined(__wasm64__)
        #undef CURRENT_ARCH
        #define CURRENT_ARCH ARCH_WASM64
    #endif
#endif

#if CURRENT_ARCH == ARCH_UNDEFINED
    #error "Unsupported Architecture"
#endif

// Getter for the architecture name as a string. Use if string representation is needed or supported by the environment.
inline constexpr const char* get_arch_name() {
    switch (CURRENT_ARCH) {
    case ARCH_X86:     return "x86";
    case ARCH_X64:     return "x86_64";
    case ARCH_ARM32:   return "ARM32";
    case ARCH_ARM64:   return "ARM64";
    case ARCH_RISCV32: return "RISC-V 32";
    case ARCH_RISCV64: return "RISC-V 64";
    case ARCH_MIPS32:  return "MIPS 32";
    case ARCH_MIPS64:  return "MIPS 64";
    case ARCH_PPC32:   return "PowerPC 32";
    case ARCH_PPC64:   return "PowerPC 64";
    case ARCH_SPARC32: return "SPARC 32";
    case ARCH_SPARC64: return "SPARC 64";
    case ARCH_IA64:    return "Itanium (IA-64)";
    case ARCH_S390X:   return "IBM System/390";
    case ARCH_WASM32:  return "WebAssembly 32";
    case ARCH_WASM64:  return "WebAssembly 64";
    default:           return "Unknown Architecture";
    }
}

#define IMPL_X86(code)
#define IMPL_X64(code)
#define IMPL_ARM64(code)
#define IMPL_ARM32(code)
#define IMPL_RISCV32(code)
#define IMPL_RISCV64(code)
#define IMPL_MIPS32(code)
#define IMPL_MIPS64(code)
#define IMPL_PPC32(code)
#define IMPL_PPC64(code)
#define IMPL_SPARC32(code)
#define IMPL_SPARC64(code)
#define IMPL_IA64(code)
#define IMPL_S390X(code)
#define IMPL_WASM32(code)
#define IMPL_WASM64(code)
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
#elif CURRENT_ARCH == ARCH_ARM32
    #undef IMPL_ARM32
    #define IMPL_ARM32(code) code
#elif CURRENT_ARCH == ARCH_RISCV32
    #undef IMPL_RISCV32
    #define IMPL_RISCV32(code) code
#elif CURRENT_ARCH == ARCH_RISCV64
    #undef IMPL_RISCV64
    #define IMPL_RISCV64(code) code
#elif CURRENT_ARCH == ARCH_MIPS32
    #undef IMPL_MIPS32
    #define IMPL_MIPS32(code) code
#elif CURRENT_ARCH == ARCH_MIPS64
    #undef IMPL_MIPS64
    #define IMPL_MIPS64(code) code
#elif CURRENT_ARCH == ARCH_PPC32
    #undef IMPL_PPC32
    #define IMPL_PPC32(code) code
#elif CURRENT_ARCH == ARCH_PPC64
    #undef IMPL_PPC64
    #define IMPL_PPC64(code) code
#elif CURRENT_ARCH == ARCH_SPARC32
    #undef IMPL_SPARC32
    #define IMPL_SPARC32(code) code
#elif CURRENT_ARCH == ARCH_SPARC64
    #undef IMPL_SPARC64
    #define IMPL_SPARC64(code) code
#elif CURRENT_ARCH == ARCH_IA64
    #undef IMPL_IA64
    #define IMPL_IA64(code) code
#elif CURRENT_ARCH == ARCH_S390X
    #undef IMPL_S390X
    #define IMPL_S390X(code) code
#elif CURRENT_ARCH == ARCH_WASM32
    #undef IMPL_WASM32
    #define IMPL_WASM32(code) code
#elif CURRENT_ARCH == ARCH_WASM64
    #undef IMPL_WASM64
    #define IMPL_WASM64(code) code
#else
    #undef IMPL_UNKNOWN_ARCH
    #define IMPL_UNKNOWN_ARCH(code) code
#endif

#define IMPL_X86_64(code) IMPL_X64(code)

#endif // SYSMACRO_ARCH_HPP