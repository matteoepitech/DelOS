/*
** DELOS PROJECT, 2025
** include/kernel/fs/tmpfs/tmpfs
** File description:
** TMPFS header file
*/

#include <kernel/fs/vfs/vfs.h>
#include <defines.h>
#include <types.h>

#ifndef KERNEL_FS_TMPFS_H_
    #define KERNEL_FS_TMPFS_H_

/*
 * @brief This enumeration contains all differents type of a file for the TMPFS.
 */
typedef enum {
    KTMPFS_FILE,
    KTMPFS_DIR,
} tmpfs_file_type_t;

/*
 * @brief Structure for a file entry in the tmpfs file system.
 *        - name     = the name of the entry (max len KTMPFS_NAME_MAX_LEN)
 *        - type     = the type of the entry
 *        - parent   = the parent of the entry (likely a dir)
 *        - data_ptr = the pointer to the raw data in memory (file type)
 *        - size     = the size of the raw data in memory (file type)
 *        - child    = the first child entry of a dir (dir type) then use the next to go through entire dir
 *        - next     = the next occurence in the entry (on a dir for example)
 */
typedef struct tmpfs_entry_s {
    char _name[KVFS_MAX_NAME_LEN];
    tmpfs_file_type_t _type;
    struct tmpfs_entry_s *_parent;
    union {
        struct {
            uint8_t *_data_ptr;
            size_t _size;
        } _file;
        struct {
            struct tmpfs_entry_s *_child;
        } _dir;
    };
    struct tmpfs_entry_s *_next;
} tmpfs_entry_t;

/* @brief Variable containing a static version of all operations of TMPFS fs */
extern struct vfs_ops_s ktmpfs_operations;

/**
 * @brief Create the vfs node and tmpfs entry for the root directory.
 *
 * @param loc       The location of the mount
 * @param device    The device pointer on how to access data (unused on tmpfs)
 *
 * @return The root directory of the tmpfs file system ("/").
 */
vfs_node_t *
ktmpfs_mount(const char *loc, UNUSED void *device);

/**
 * @brief Read data in the temporary virtual file system.
 *
 * @param node       The node of the file in the VFS
 * @param offset     The offset in the file
 * @param buffer     The buffer where to store the data read in (should be allocated to len size)
 * @param len        The number of byte to read
 *
 * @return The number of bytes read.
 */
size_t
ktmpfs_read(vfs_node_t *node, off_t offset, void *buffer, size_t len);

/**
 * @brief Write data in the temporary virtual file system.
 *
 * @param node       The node of the file in the VFS
 * @param offset     The offset in the file
 * @param buffer     The buffer where the data to write is in
 * @param len        The number of bytes to write
 *
 * @return The size of the number of bytes write in the file.
 */
size_t
ktmpfs_write(vfs_node_t *node, off_t offset, const void *buffer, size_t len);

/**
 * @brief Get another node from the VFS with a node and next level path.
 *
 * @param node           The node of the file in the VFS
 * @param next_level     The next level of the node (e.g. we are at "/" we want the file "abc", next_level = "abc")
 *
 * @return The new VFS node we get in the next level.
 */
vfs_node_t *
ktmpfs_lookup(vfs_node_t *node, const char *next_level);

/**
 * @brief Get the structure containing every callback for that filesystem.
 *
 * @return Pointer to the vfs_ops_t structure for the TMPFS fs.
 */
vfs_ops_t *
ktmpfs_get_operations(void);

/**
 * @brief Create a VFS node using an entry on that tmpfs.
 *
 * @param entry     The entry to get data from
 *
 * @return The VFS node pointer created or NULL otherwise.
 */
vfs_node_t *
ktmpfs_create_vfs_node(tmpfs_entry_t *entry);

/**
 * @brief Create an entry on the TMPFS fs using parent, name, type and return it.
 *
 * @param parent     The parent of the entry
 * @param name       The name of the entry
 * @param type       The type of the entry
 *
 * @return The entry created.
 */
tmpfs_entry_t *
ktmpfs_create_entry(tmpfs_entry_t *parent, const char *name, tmpfs_file_type_t type);

#endif /* ifndef KERNEL_FS_TMPFS_H_ */
