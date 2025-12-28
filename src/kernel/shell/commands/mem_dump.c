/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/mem_dump
** File description:
** mem_dump command source file
*/

#include <utils/kstdlib/kstring.h>
#include <utils/kstdlib/kstdlib.h>
#include <utils/kstdlib/kctype.h>
#include <kernel/shell/shell.h>
#include <utils/misc/print.h>
#include <defines.h>

#ifndef MEM_DUMP_MSG
    #define MEM_DUMP_HELP_MSG "usage: mem_dump <addr> <len>"
    #define MEM_DUMP_ADDR_START_ERROR_MSG "mem_dump: the addr parameter need to start with 0x"
    #define MEM_DUMP_ADDR_PLACE_ERROR_MSG "mem_dump: the addr parameter need to be greater than 0"
    #define MEM_DUMP_ADDR_RANGE_ERROR_MSG "mem_dump: the addr parameter must fit in 32 bits"
    #define MEM_DUMP_LEN_ERROR_MSG "mem_dump: the len parameter need to be greater than 0"
#endif /* MEM_DUMP_MSG */

#ifndef MEM_DUMP_MISC
    #define MEM_DUMP_BYTES_PER_ROW 32
#endif /* MEM_DUMP_MISC */

/**
 * @brief Print the current byte into ascii value.
 *
 * @param byte   Print the current byte value if printable. A dot is printed if not.
 */
static void
mem_dump_print_byte(uint8_t byte)
{
    if (kisprint(byte)) {
        ktty_putc(byte, VGA_TEXT_DEFAULT_COLOR);
    } else {
        ktty_putc('.', VGA_TEXT_DEFAULT_COLOR);
    }
}

/**
 * @brief Print the memory for the shell mem_dump command.
 *
 * @param addr   The start address
 * @param len    The number of bytes to print
 */
static void
mem_dump_formatted(uint8_t *addr, uint32_t len)
{
    for (uint32_t current_len = 0; current_len < len; current_len++) {
        if (current_len % MEM_DUMP_BYTES_PER_ROW == 0) {
            if (current_len > 0) {
                ktty_putc('\n', VGA_TEXT_DEFAULT_COLOR);
            }
            KPRINTF_DATE();
            kprintf(VGA_TEXT_DATE_COLOR, "%08x   ", (uint32_t) addr);
        }
        mem_dump_print_byte(*addr);
        addr++;
    }
    ktty_putc('\n', VGA_TEXT_DEFAULT_COLOR);
}

/**
 * @brief Command for mem_dump.
 *
 * @param argc      The number of arguments
 * @param argv[]    The array of arguments
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_mem_dump(uint32_t argc, char *argv[])
{
    int32_t len = 0;
    uint32_t addr = 0;
    int64_t parsed_addr = 0;
    int32_t parse_ok = 0;

    if (argc < 3) {
        KPRINTF_ERROR("%s", MEM_DUMP_HELP_MSG);
        return OK_TRUE;
    }
    if (kstrncmp(argv[1], "0x", 2) != 0 && kstrncmp(argv[1], "0X", 2)) {
        KPRINTF_ERROR("%s", MEM_DUMP_ADDR_START_ERROR_MSG);
        return OK_TRUE;
    }
    len = katoi(argv[2]);
    if (len <= 0) {
        KPRINTF_ERROR("%s", MEM_DUMP_LEN_ERROR_MSG);
        return OK_TRUE;
    }
    parsed_addr = kstrtol(&argv[1][2], 16, &parse_ok);
    if (!parse_ok || parsed_addr < 0) {
        KPRINTF_ERROR("%s", MEM_DUMP_ADDR_PLACE_ERROR_MSG);
        return OK_TRUE;
    }
    if ((uint64_t) parsed_addr > 0xFFFFFFFFULL) {
        KPRINTF_ERROR("%s", MEM_DUMP_ADDR_RANGE_ERROR_MSG);
        return OK_TRUE;
    }
    addr = (uint32_t) parsed_addr;
    mem_dump_formatted((uint8_t *) addr, (uint32_t) len);
    return KO_FALSE;
}
