/*
** DELOS PROJECT, 2026
** include/kernel/scheduler/scheduler
** File description:
** Scheduler header file
*/

#include <defines.h>
#include <types.h>

#ifndef KERNEL_SCHEDULER_H_
    #define KERNEL_SCHEDULER_H_

/**
 * @brief Initialize the scheduler stuff.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kscheduler_init(void);

#endif /* ifndef KERNEL_SCHEDULER_H_ */
