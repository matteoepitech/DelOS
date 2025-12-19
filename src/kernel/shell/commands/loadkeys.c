/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/loadkeys
** File description:
** loadkeys command source file
*/

#include <utils/kstdlib/kstring.h>
#include <kernel/misc/keyboard.h>
#include <kernel/shell/shell.h>
#include <utils/misc/print.h>
#include <defines.h>

/**
 * @brief Command for loadkeys.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_loadkeys(uint32_t argc, char *argv[])
{
    if (argc < 2) {
        KPRINTF_ERROR("usage: loadkeys <fr/us>");
        return OK_TRUE;
    }
    if (kstrcmp(argv[1], "fr") == 0) {
        keymap = KEYMAP_AZERTY;
        return KO_FALSE;
    } else if (kstrcmp(argv[1], "us") == 0) {
        keymap = KEYMAP_QWERTY;
        return KO_FALSE;
    } else {
        KPRINTF_ERROR("loadkeys: keymap \"%s\" not found", argv[1]);
        return OK_TRUE;
    }
    return KO_FALSE;
}
