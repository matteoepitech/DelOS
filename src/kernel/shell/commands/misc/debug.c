/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/misc/debug
** File description:
** debug command source file
*/

#include <kernel/memory/early_allocator/early_alloc.h>
#include <kernel/fs/vfs/vfs_registry.h>
#include <kernel/fs/fd/fd_operations.h>
#include <kernel/memory/api/kmalloc.h>
#include <kernel/fs/vfs/vfs_open.h>
#include <kernel/fs/tmpfs/tmpfs.h>
#include <utils/kstdlib/kstring.h>
#include <kernel/memory/vmm/vmm.h>
#include <kernel/memory/pmm/pmm.h>
#include <kernel/shell/shell.h>
#include <utils/misc/print.h>
#include <kernel/sys/syscall.h>
#include <kernel/fs/fd/fd.h>
#include <defines.h>

/**
 * @brief Command for debug.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_debug(UNUSED uint32_t argc, UNUSED char *argv[])
{
    // ------- SETUP -------
    char buffer_read[10] = {0};
    char buffer[10] = "Salut la!";
    vfs_stat_t stat_buffer = {0};
    fd_t file = ksys_open("./my_file", KVFS_O_CREAT | KVFS_O_RDWR, 0644);
    if (file >= 0) {
        kfd_write(file, buffer, sizeof(buffer));
        kfd_get(file)->_offset = 0;
        kfd_read(file, buffer_read, 10);
        KPRINTF_DEBUG("%s", buffer_read);
        ksys_fstat(file, &stat_buffer);
        KPRINTF_DEBUG("%d", stat_buffer._size);
        ksys_close(file);
    }
    // ----- END SETUP -----
    return KO_FALSE;
}
