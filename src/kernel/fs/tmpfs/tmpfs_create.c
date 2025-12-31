/*
** DELOS PROJECT, 2025
** src/kernel/fs/tmpfs/tmpfs_create
** File description:
** TMPFS create source file
*/

#include <kernel/fs/vfs/vfs_registry.h>
#include <kernel/memory/api/kmalloc.h>
#include <utils/kstdlib/kstring.h>
#include <kernel/fs/tmpfs/tmpfs.h>
#include <kernel/fs/vfs/vfs.h>

/**
 * @brief Create a file in a parent entry on the TMPFS.
 *
 * @param parent     The parent of the file (likely a dir)
 * @param name       The name of the file we want to create
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
ktmpfs_create(vfs_node_t *parent, const char *name)
{
    if (parent == NULL || name == NULL) {
        return KO_FALSE;
    }
    if (ktmpfs_create_entry(parent->_private, name, KTMPFS_FILE) == NULL) {
        return KO_FALSE;
    }
    return OK_TRUE;
}
