
#if defined(_WIN32)
    #define ZY_WINDOWS
#elif defined(_WIN64)
    #define ZY_WINDOWS // Windows
#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define ZY_WINDOWS // Windows (Cygwin POSIX under Microsoft Window)
#elif defined(__ANDROID__)
    #define ZY_ANDROID // Android (implies Linux, so it must come first)
#elif defined(__linux__)
    #define ZY_LINUX "linux" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
    #include <sys/param.h>
    #if defined(BSD)
        #define ZY_BSD // FreeBSD, NetBSD, OpenBSD, DragonFly BSD
    #endif
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #define ZY_IOS // Apple iOS
    #elif TARGET_OS_IPHONE == 1
        #define ZY_IOS // Apple iOS
    #elif TARGET_OS_MAC == 1
        #define ZY_OSX // Apple OSX
    #endif
#elif defined(__sun) && defined(__SVR4)
    #define ZY_SOLARIS // Oracle Solaris, Open Indiana
#else
    #define ZY_NOPLATFORM
#endif