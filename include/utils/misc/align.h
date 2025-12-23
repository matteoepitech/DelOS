/*
** DELOS PROJECT, 2025
** include/utils/misc/align
** File description:
** Alignement header file
*/

#ifndef UTILS_MISC_ALIGN_H_
    #define UTILS_MISC_ALIGN_H_

    #ifndef ALIGN_UP
        #define ALIGN_UP(x, a)   (((x) + ((a) - 1)) & ~((a) - 1))
    #endif /* ifndef ALIGN_UP */

    #ifndef ALIGN_DOWN
        #define ALIGN_DOWN(x, a) ((x) & ~((a) - 1))
    #endif /* ifndef ALIGN_DOWN */

#endif /* ifndef ALIGN_DOWN */
