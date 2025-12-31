/*
** DELOS PROJECT, 2025
** include/utils/kstring
** File description:
** Kstring header file
*/

#include <types.h>

#ifndef UTILS_KSTDLIB_KSTRING_H_
    #define UTILS_KSTDLIB_KSTRING_H_

/**
 * @brief Get the length of a string.
 *
 * @param string        The string
 *
 * @return The length of it until a zero terminated byte.
 */
size_t
kstrlen(const char *string);

/**
 * @brief Get the difference between the first non equal character.
 *
 * @param string_a      The string A
 * @param string_b      The string B
 *
 * @return The difference between the first non equal character.
 */
int32_t
kstrcmp(const char *string_a, const char *string_b);

/**
 * @brief Get the difference between the first non equal character.
 *
 * @param string_a      The string A
 * @param string_b      The string B
 * @param n             The number max of characters to check
 *
 * @return The difference between the first non equal character.
 */
int32_t
kstrncmp(const char *string_a, const char *string_b, size_t n);

/**
 * @brief Concat the string b into the string a.
 *        This function assumes that you have enough allocated memory for the dest.
 *
 * @param string_a   The destination 
 * @param string_b   The source
 *
 * @return The destination
 */
char *
kstrcat(char *restrict string_a, const char *restrict string_b);

/**
 * @brief Copy a literal string into a pointer.
 *
 * @param dst        Where to copy
 * @param src        The string to copy
 *
 * @return The pointer to the destination.
 */
char *
kstrcpy(char *dst, const char *src);

/**
 * @brief Copy a literal string into a pointer.
 *
 * @param dst        Where to copy
 * @param src        The string to copy
 * @param n          The maximum of char to copy
 *
 * @return The pointer to the destination.
 */
char *
kstrncpy(char *dst, const char *src, size_t n);

#endif /* ifndef UTILS_KSTDLIB_KSTRING_H_ */
