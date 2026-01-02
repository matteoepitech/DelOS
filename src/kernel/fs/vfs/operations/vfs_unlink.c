/*
** DELOS PROJECT, 2026
** src/kernel/fs/vfs/operations/vfs_unlink
** File description:
** VFS unlink source file
*/

#include <kernel/fs/vfs/vfs.h>
#include <utils/misc/print.h>
#include <defines.h>
#include <types.h>
    
/**
 * @brief Unlink a file (remove it's entry but not his data of course)
 *
 * @param path   The path to the file to unlink
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvfs_unlink(const char *path)
{
    vfs_node_t *node = NULL;

    if (path == NULL) {
        return KO_FALSE;
    }
    node = kvfs_open(path);
    if (node == NULL) {
        KPRINTF_ERROR("vfs: no such file or directory to unlink");
        return KO_FALSE;
    }
    if (node->_type == KVFS_DIR || node->_type == KVFS_DEVICE) {
        KPRINTF_ERROR("vfs: cannot unlink this type of file");
        return KO_FALSE;
    }
    if (node->_ops->_unlink(node) == KO_FALSE) {
        KPRINTF_ERROR("vfs: error while unlinking the file in fs operation");
        return KO_FALSE;
    }
    kvfs_close(node);
    return OK_TRUE;
}
