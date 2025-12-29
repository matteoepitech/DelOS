/*
** DELOS PROJECT, 2025
** src/utils/kstdlib/stdlib/katoi
** File description:
** katoi source file
*/

#include <utils/kstdlib/kstring.h>
#include <utils/kstdlib/kctype.h>
#include <defines.h>

/**
 * @brief Get an integer from a buffer.
 *
 * @param buffer     The buffer to get the integer from
 *
 * @return The result on base 10 of the current buffer
 */
int32_t
katoi(const char *buffer)
{
    int32_t minus_count = 0;
    int32_t result = 0;

    while (!kisdigit(*buffer)) {
        if (*buffer == '-') {
            minus_count++;
        }
        buffer++;
    }
    for (; *buffer; buffer++) {
        if (kisdigit(*buffer) == KO_FALSE) {
            break;
        }
        result = (result * 10) + (*buffer - '0');
    }
    return result * (minus_count % 2 == 0 ? 1 : -1);
}
