/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/dump_mem
** File description:
** dump_mem command source file
*/

#include <utils/kstdlib/kstring.h>
#include <utils/kstdlib/kstdlib.h>
#include <utils/kstdlib/kctype.h>
#include <kernel/shell/shell.h>
#include <utils/misc/print.h>
#include <defines.h>

#ifndef DUMP_MEM_MSG
    #define DUMP_MEM_HELP_MSG "usage: dumpmem <addr> <len>"
    #define DUMP_MEM_ADDR_START_ERROR_MSG "dumpmem: the addr parameter need to start with 0x"
    #define DUMP_MEM_ADDR_PLACE_ERROR_MSG "dumpmem: the addr parameter need to be greater than 0"
    #define DUMP_MEM_LEN_ERROR_MSG "dumpmem: the len parameter need to be greater than 0"
#endif /* ifndef DUMP_MEM_MSG */

#ifndef DUMP_MEM_MISC
    #define DUMP_MEM_BYTES_PER_ROW 32
#endif /* ifndef DUMP_MEM_MISC */

/**
 * @brief Print the current byte into ascii value.
 *
 * @param byte   Print the current byte value if printable. A dot is print if not.
 */
static void
print_byte(uint8_t byte)
{
    if (kisprint(byte)) {
        ktty_putc(byte, VGA_TEXT_DEFAULT_COLOR);
    } else {
        ktty_putc('.', VGA_TEXT_DEFAULT_COLOR);
    }
}

/**
 * @brief Print the memory for the shell dump_mem command.
 *
 * @param addr   The start of the printing
 * @param len    The number of bytes to print
 */
static void
dump_mem_formatted(uint8_t *addr, uint32_t len)
{
    for (uint32_t current_len = 0; current_len < len; current_len++) {
        if (current_len % DUMP_MEM_BYTES_PER_ROW == 0) {
            if (current_len > 0) {
                ktty_putc('\n', VGA_TEXT_DEFAULT_COLOR);
            }
            KPRINTF_DATE();
            kprintf(VGA_TEXT_DATE_COLOR, "%08x   ", addr);
        }
        print_byte(*addr);
        addr++;
    }
    ktty_putc('\n', VGA_TEXT_DEFAULT_COLOR);
}

/**
 * @brief Command for dump_mem.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_dump_mem(uint32_t argc, char *argv[])
{
    int32_t len = 0;
    int32_t addr = 0;
    int32_t parse_ok = 0;

    if (argc < 3) {
        KPRINTF_ERROR("%s", DUMP_MEM_HELP_MSG);
        return OK_TRUE;
    }
    if (kstrncmp(argv[1], "0x", 2) != 0 && kstrncmp(argv[1], "0X", 2)) {
        KPRINTF_ERROR("%s", DUMP_MEM_ADDR_START_ERROR_MSG);
        return OK_TRUE;
    }
    len = katoi(argv[2]);
    if (len <= 0) {
        KPRINTF_ERROR("%s", DUMP_MEM_LEN_ERROR_MSG);
        return OK_TRUE;
    }
    addr = kstrtol(&argv[1][2], 16, &parse_ok);
    if (addr < 0 && parse_ok) {
        KPRINTF_ERROR("%s", DUMP_MEM_ADDR_PLACE_ERROR_MSG);
        return OK_TRUE;
    }
    dump_mem_formatted((uint8_t *) addr, (uint32_t) len);
    return KO_FALSE;
}
