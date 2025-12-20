/*
** DELOS PROJECT, 2025
** src/utils/kstdlib/ctype/kisprint
** File description:
** kisprint source file
*/

#include <utils/kstdlib/kctype.h>
#include <defines.h>

/**
 * @brief Say if a character (byte or more) is actually printable.
 *
 * @param character  The character to check if printable
 *
 * @return OK_TRUE if printable, KO_FALSE otherwise.
 */
bool32_t
kisprint(int32_t character)
{
    if (character >= 0x20 && character <= 0x7E) {
        return OK_TRUE;
    }
    return KO_FALSE;
}
