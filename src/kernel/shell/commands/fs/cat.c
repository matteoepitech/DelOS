/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/fs/cat
** File description:
** cat command source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <kernel/fs/vfs/vfs_stat.h>
#include <kernel/shell/shell.h>
#include <kernel/fs/vfs/vfs.h>
#include <utils/misc/print.h>
#include <defines.h>

/**
 * @brief Command for cat.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_cat(uint32_t argc, char *argv[])
{
    vfs_stat_t stat_buffer = {0};
    vfs_node_t *file = NULL;
    char *buffer = NULL;
    size_t len = 0;

    if (argc < 2) {
        KPRINTF_ERROR("usage: cat <path>");
        return OK_TRUE;
    }
    file = kvfs_lookup_open(argv[1]);
    if (file == NULL) {
        KPRINTF_ERROR("cat: no such file or directory");
        return OK_TRUE;
    }
    if (kvfs_stat_from_node(file, &stat_buffer) == KO_FALSE) {
        kvfs_close(file);
        return OK_TRUE;
    }
    if (KVFS_STAT_ISREG(stat_buffer._mode) == KO_FALSE) {
        KPRINTF_ERROR("cat: not a file to read");
        return OK_TRUE;
    }
    len = stat_buffer._size;
    if (len == 0) {
        return KO_FALSE;
    }
    buffer = kmalloc(len);
    if (buffer == NULL) {
        KPRINTF_ERROR("cat: failed to read, no more memory space available");
        return OK_TRUE;
    }
    file->_ops->_read(file, 0, buffer, len);
    KPRINTF_OK("%s", argv[1]);
    ktty_puts(buffer, VGA_TEXT_DEFAULT_COLOR);
    ktty_putc('\n', VGA_TEXT_DEFAULT_COLOR);
    return KO_FALSE;
}
