/*
** DELOS PROJECT, 2025
** include/utils/kstdarg
** File description:
** Kstdarg header file
*/

#ifndef UTILS_KSTDLIB_KSTDARG_H_
    #define UTILS_KSTDLIB_KSTDARG_H_

// TODO: Add a kstdarg depending on the architecture.
// WARN: This is actually only working with an i386 architecture (x86)
// WARN: This is actually only working without optimisations or weird stuff (-O0)

/*
 * @brief The primary type of the variadic list but for kernel implementation.
 */
typedef char* kva_list;

    #ifndef KVA_START
        #define KVA_START(param) ((kva_list) (&param + 1))
    #endif /* ifndef KVA_START */

    #ifndef KVA_ARG
        #define KVA_ARG(va, type) (*(type *)((va += sizeof(type)) - sizeof(type)))
    #endif /* ifndef KVA_ARG */

#endif /* ifndef UTILS_KSTDLIB_KSTDARG_H_ */
