/*
** DELOS PROJECT, 2026
** include/kernel/scheduler/scheduler
** File description:
** Scheduler header file
*/

#include <kernel/scheduler/task.h>
#include <defines.h>
#include <types.h>

#ifndef KERNEL_SCHEDULER_H_
    #define KERNEL_SCHEDULER_H_

/* @brief This variable is the head/tail of the task */
extern task_t *ktask_head;
extern task_t *ktask_tail;
/* @brief This variable contains the current task executed on the CPU */
extern task_t *kcurrent_task;

/**
 * @brief Initialize the scheduler stuff.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kscheduler_init(void);

/**
 * @brief Add a task in the scheduler.
 *
 * @param task   The task to add on the scheduler nodes
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kscheduler_add_task(task_t *task);

#endif /* ifndef KERNEL_SCHEDULER_H_ */
