#ifndef SYSMACRO_OS_HPP
#define SYSMACRO_OS_HPP

#define OS_UNDEFINED   0
#define OS_WINDOWS     1
#define OS_LINUX       2
#define OS_MACOS       3
#define OS_ALOPEX      4

#if defined(CURRENT_OS) && !defined(REPLACE_CURRENT_OS)
    #error "CURRENT_OS is already defined. PLEASE SET REPLACE_CURRENT_OS to 1 to replace it."
#elif defined(CURRENT_OS) && defined(REPLACE_CURRENT_OS)
    #undef CURRENT_OS 
#endif

#if !defined(CURRENT_OS)

    #define CURRENT_OS OS_UNDEFINED

    #if defined(__ALOPEXOS__)
        #undef CURRENT_OS
        #define CURRENT_OS OS_ALOPEX
    #elif defined(_WIN32) || defined(_WIN64)
        #undef CURRENT_OS
        #define CURRENT_OS OS_WINDOWS
    #elif defined(__linux__)
        #undef CURRENT_OS
        #define CURRENT_OS OS_LINUX
    #elif defined(__APPLE__) && defined(__MACH__)
        #undef CURRENT_OS
        #define CURRENT_OS OS_MACOS
    #elif defined(__unix__) || defined(__posix__)
        #undef CURRENT_OS
        #define CURRENT_OS OS_LINUX
    #endif

#endif

#if CURRENT_OS == OS_UNDEFINED
    #error "Unsupported Operating System"
#endif

// Getter for the operating system name as a string. Use if string representation is needed or supported by the environment.
inline constexpr const char* get_os_name() {
    switch (CURRENT_OS) {
        case OS_WINDOWS: return "Windows";
        case OS_LINUX:   return "Linux";
        case OS_MACOS:   return "macOS";
        case OS_ALOPEX:  return "AlopexOS";
        default:         return "Unknown OS";
    }
}

#endif // SYSMACRO_OS_HPP