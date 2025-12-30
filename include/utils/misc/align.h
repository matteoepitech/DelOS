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

    #ifndef IS_ALIGNED_TO
        #define IS_ALIGNED_TO(x, a) (x % a == 0)
    #endif /* ifndef IS_ALIGNED_TO */

#endif /* ifndef ALIGN_DOWN */
