/*
** DELOS PROJECT, 2025
** src/kernel/fs/vfs/vfs_open
** File description:
** VFS open source file
*/

#include <kernel/fs/vfs/vfs_open.h>
#include <utils/kstdlib/kstring.h>
#include <kernel/fs/tmpfs/tmpfs.h>
#include <utils/misc/print.h>
#include <defines.h>
#include <types.h>

/**
 * @brief Open a file and go through its entire path to get the node associated to the end level.
 *        This version is returning NULL if the file doesn't exist.
 *        Use the API function kvfs_open() instead which can handle flags.
 *
 * @param path   The complete path to a node (e.g. "/abc/dir/a.txt")
 *
 * @return The VFS node of the path result. (Can be anything: file, dir, link, ...)
 */
vfs_node_t *
kvfs_lookup_open(const char *path)
{
    if (path == NULL) {
        return NULL;
    }
    if (path[0] == '/') {
        return kvfs_resolve_from(NULL, path);
    } else {
        return kvfs_resolve_from(kvfs_cwd, path);
    }
}

/**
 * @brief Open a file and go through its entire path to get the node associated to the end level.
 *
 * @param path   The complete path to a node (e.g. "/abc/dir/a.txt")
 * @param flags  The flags O_CREAT | O_RDONLY ...
 * @param mode   The mode (used when creating the file only)
 *
 * @return The VFS node of the path result. (Can be anything: file, dir, link, ...)
 */
vfs_node_t *
kvfs_open(const char *path, int32_t flags, mode_t mode)
{
    int32_t accmode = flags & KVFS_O_ACCMODE;
    char file_name[KVFS_MAX_NAME_LEN] = {0};
    vfs_stat_t stat_buffer = {0};
    const cred_t cred = {0, 0};
    vfs_node_t *parent = NULL;
    vfs_node_t *node = NULL;

    if (path == NULL) {
        return NULL;
    }
    parent = kvfs_resolve_parent_from(path[0] == '/' ? NULL : kvfs_cwd, path, file_name);
    if (parent == NULL) {
        return NULL;
    }
    if (kvfs_get_stat(parent, &stat_buffer) == KO_FALSE) {
        kvfs_close(parent);
        return NULL;
    }
    if (flags & KVFS_O_CREAT) {
        if (kvfs_stat_can_write(&stat_buffer, &cred) == KO_FALSE || kvfs_stat_can_exec(&stat_buffer, &cred) == KO_FALSE) {
            kvfs_close(parent);
            return NULL;
        }
        node = kvfs_lookup(parent, file_name);
        if (node != NULL) {
            kvfs_close(node);
            if (flags & KVFS_O_EXCL) {
                kvfs_close(parent);
                return NULL;
            }
        } else {
            if (flags & KVFS_O_DIRECTORY) {
                if (kvfs_mkdir(parent, file_name, mode) == KO_FALSE) {
                    kvfs_close(parent);
                    return NULL;
                }
            } else if (kvfs_create(parent, file_name, mode) == KO_FALSE) {
                kvfs_close(parent);
                return NULL;
            }
        }
    }
    node = kvfs_lookup(parent, file_name);
    if (node == NULL) {
        kvfs_close(parent);
        return NULL;
    }
    if (kvfs_get_stat(node, &stat_buffer) == KO_FALSE) {
        kvfs_close(node);
        return NULL;
    }
    if (accmode == KVFS_O_RDONLY) {
        if (kvfs_stat_can_read(&stat_buffer, &cred) == KO_FALSE) {
            kvfs_close(node);
            kvfs_close(parent);
            return NULL;
        }
    } else if (accmode == KVFS_O_WRONLY) {
        if (kvfs_stat_can_write(&stat_buffer, &cred) == KO_FALSE) {
            kvfs_close(node);
            kvfs_close(parent);
            return NULL;
        }
    } else if (accmode == KVFS_O_RDWR) {
        if (kvfs_stat_can_read(&stat_buffer, &cred) == KO_FALSE || kvfs_stat_can_write(&stat_buffer, &cred) == KO_FALSE) {
            kvfs_close(node);
            kvfs_close(parent);
            return NULL;
        }
    }
    if ((flags & KVFS_O_TRUNC) && accmode != KVFS_O_RDONLY) {
        //kvfs_truncate(node, 0);
        //TODO: truncate operation
    }
    if (parent != kvfs_cwd) {
        kvfs_close(parent);
    }
    return node;
}
