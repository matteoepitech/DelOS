/*
** DELOS PROJECT, 2025
** include/utils/asm/hlt
** File description:
** HLT header file
*/

#include <utils/misc/print.h>
#include <kernel/tty/tty.h>

#ifndef UTILS_ASM_HLT_H_
    #define UTILS_ASM_HLT_H_

    #ifndef KHLT_DO
        #define KHLT_DO() make_hlt()
    #endif /* ifndef KHLT_DO */
    
    #ifndef KHLT_HARD_DO
        #define KHLT_HARD_DO() make_hlt_hard()
    #endif /* ifndef KHLT_HARD_DO */
    
    #ifndef KHLT_HARD_DO_NO_MSG
        #define KHLT_HARD_DO_NO_MSG() make_hlt_hard_no_msg()
    #endif /* ifndef KHLT_HARD_DO_NO_MSG */

/**
 * @brief Stop the execution of the CPU.
 *        hlt will stop the CPU exection until something happens (irq hardware)
 */
static inline void
make_hlt(void)
{
    // AT&T syntax used by GCC
    __asm__ volatile ("hlt" ::);
}

/**
 * @brief Stop the execution of the CPU but in the HARD way.
 *        cli will stop the CPU to receive any irq hardware
 *        hlt will stop the CPU exection
 *
 *        Basically you shouldn't use this function.
 */
static inline void
make_hlt_hard(void)
{
    // AT&T syntax used by GCC
    KPRINTF_WARN("** A hard halt has been triggered **\n");
    __asm__ volatile ("cli" ::);
    __asm__ volatile ("hlt" ::);
}

/**
 * @brief Stop the execution of the CPU but in the HARD way.
 *        cli will stop the CPU to receive any irq hardware
 *        hlt will stop the CPU exection
 *
 *        Version without message
 *
 *        Basically you shouldn't use this function.
 */
static inline void
make_hlt_hard_no_msg(void)
{
    // AT&T syntax used by GCC
    __asm__ volatile ("cli" ::);
    __asm__ volatile ("hlt" ::);
}

#endif /* ifndef UTILS_ASM_HLT_H */
