/*
** DELOS PROJECT, 2026
** include/kernel/system/cred
** File description:
** System credentials header file
*/

#include <types.h>

#ifndef KERNEL_SYSTEM_CRED_H_
    #define KERNEL_SYSTEM_CRED_H_

/*
 * @brief Structure for credentials.
 *        - uid = the user ID
 *        - gid = the group ID
 */
typedef struct cred_s {
    uid_t _uid;
    gid_t _gid;
} cred_t;

#endif /* ifndef KERNEL_SYSTEM_CRED_H_ */
