/*
** DELOS PROJECT, 2025
** include/kernel/misc/print
** File description:
** Kernel logging and formatted output utilities
*/

#include "kernel/arch/i386/interruption/pit.h"
#include "utils/kstdlib/kstdio.h"
#include "drivers/video/vga.h"
#include "kernel/tty/tty.h"

#ifndef UTILS_MISC_PRINT_H_
    #define UTILS_MISC_PRINT_H_

    /*
    * These macros are internal helpers used by KPRINTF_*.
    * They are not part of the public API and must not be called directly.
    */

    #define _KPRINTF_LABEL_OPEN()   ktty_putc('[', VGA_TEXT_DEFAULT_COLOR)
    #define _KPRINTF_LABEL_CLOSE()  ktty_putc(']', VGA_TEXT_DEFAULT_COLOR)
    #define _KPRINTF_LABEL_SPACES() ktty_puts(" ", VGA_TEXT_DEFAULT_COLOR)

    #define _KPRINTF_LABEL_INFO()                   \
        do {                                        \
            _KPRINTF_LABEL_OPEN();                  \
            _KPRINTF_LABEL_SPACES();                \
            ktty_puts("INFO", VGA_TEXT_INFO_COLOR); \
            _KPRINTF_LABEL_SPACES();                \
            _KPRINTF_LABEL_CLOSE();                 \
            ktty_putc(' ', VGA_TEXT_DEFAULT_COLOR); \
        } while (0)

    #define _KPRINTF_LABEL_WARN()                   \
        do {                                        \
            _KPRINTF_LABEL_OPEN();                  \
            _KPRINTF_LABEL_SPACES();                \
            ktty_puts("WARN", VGA_TEXT_WARN_COLOR); \
            _KPRINTF_LABEL_SPACES();                \
            _KPRINTF_LABEL_CLOSE();                 \
            ktty_putc(' ', VGA_TEXT_DEFAULT_COLOR); \
        } while (0)

    #define _KPRINTF_LABEL_DEBUG()                   \
        do {                                         \
            _KPRINTF_LABEL_OPEN();                   \
            _KPRINTF_LABEL_SPACES();                 \
            ktty_puts("DEBUG", VGA_TEXT_DEBUG_COLOR);\
            _KPRINTF_LABEL_SPACES();                 \
            _KPRINTF_LABEL_CLOSE();                  \
            ktty_putc(' ', VGA_TEXT_DEFAULT_COLOR);  \
        } while (0)

    #define _KPRINTF_LABEL_OK()                     \
        do {                                        \
            _KPRINTF_LABEL_OPEN();                  \
            _KPRINTF_LABEL_SPACES();                \
            ktty_puts("OK", VGA_TEXT_SUCCESS_COLOR);\
            _KPRINTF_LABEL_SPACES();                \
            _KPRINTF_LABEL_CLOSE();                 \
            ktty_putc(' ', VGA_TEXT_DEFAULT_COLOR); \
        } while (0)

    #define _KPRINTF_LABEL_ERROR()                    \
        do {                                          \
            _KPRINTF_LABEL_OPEN();                    \
            _KPRINTF_LABEL_SPACES();                  \
            ktty_puts("ERROR", VGA_TEXT_ERROR_COLOR); \
            _KPRINTF_LABEL_SPACES();                  \
            _KPRINTF_LABEL_CLOSE();                   \
            ktty_putc(' ', VGA_TEXT_DEFAULT_COLOR);   \
        } while (0)

    /**
     * @brief Print kernel timestamp in the format [SSSSS.cc]
     *
     * SSSSS = seconds since boot
     * cc    = centiseconds (based on PIT frequency)
     *
     * This macro is intentionally exposed so it can be reused
     * independently of log levels if needed.
     */
    #ifndef KPRINTF_DATE
        #define KPRINTF_DATE() \
            kprintf(VGA_TEXT_DATE_COLOR, "[%05d.%02d] ", seconds_count, ticks_count % PIT_TARGET_FREQUENCY)
    #endif

    /**
     * @brief Print INFO level kernel log message
     *
     * Used for general informational messages that do not
     * represent an error condition.
     */
    #ifndef KPRINTF_INFO
        #define KPRINTF_INFO(format, ...)               \
            do {                                        \
                KPRINTF_DATE();                         \
                _KPRINTF_LABEL_INFO();                  \
                kprintf(VGA_TEXT_DEFAULT_COLOR, format, ##__VA_ARGS__); \
                ktty_putc('\n', VGA_TEXT_DEFAULT_COLOR);\
            } while (0)
    #endif

    /**
     * @brief Print WARN level kernel log message
     *
     * Used for recoverable or suspicious situations.
     */
    #ifndef KPRINTF_WARN
        #define KPRINTF_WARN(format, ...)               \
            do {                                        \
                KPRINTF_DATE();                         \
                _KPRINTF_LABEL_WARN();                  \
                kprintf(VGA_TEXT_DEFAULT_COLOR, format, ##__VA_ARGS__); \
                ktty_putc('\n', VGA_TEXT_DEFAULT_COLOR);\
            } while (0)
    #endif

    /**
     * @brief Print DEBUG level kernel log message
     *
     * Used for verbose/diagnostic messages during development.
     */
    #ifndef KPRINTF_DEBUG
        #define KPRINTF_DEBUG(format, ...)              \
            do {                                        \
                KPRINTF_DATE();                         \
                _KPRINTF_LABEL_DEBUG();                 \
                kprintf(VGA_TEXT_DEFAULT_COLOR, format, ##__VA_ARGS__); \
                ktty_putc('\n', VGA_TEXT_DEFAULT_COLOR);\
            } while (0)
    #endif

    /**
     * @brief Print OK level kernel log message
     *
     * Used to explicitly confirm successful operations.
     */
    #ifndef KPRINTF_OK
        #define KPRINTF_OK(format, ...)                 \
            do {                                        \
                KPRINTF_DATE();                         \
                _KPRINTF_LABEL_OK();                    \
                kprintf(VGA_TEXT_DEFAULT_COLOR, format, ##__VA_ARGS__); \
                ktty_putc('\n', VGA_TEXT_DEFAULT_COLOR);\
            } while (0)
    #endif

    /**
     * @brief Print ERROR level kernel log message
     *
     * Used for serious but controlled kernel errors where
     * the system can continue running.
     */
    #ifndef KPRINTF_ERROR
        #define KPRINTF_ERROR(format, ...)              \
            do {                                        \
                KPRINTF_DATE();                         \
                _KPRINTF_LABEL_ERROR();                 \
                kprintf(VGA_TEXT_ERROR_COLOR, format, ##__VA_ARGS__); \
                ktty_putc('\n', VGA_TEXT_ERROR_COLOR);  \
            } while (0)
    #endif

#endif /* UTILS_MISC_PRINT_H_ */
