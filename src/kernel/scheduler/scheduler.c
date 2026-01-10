/*
** DELOS PROJECT, 2026
** src/kernel/scheduler/scheduler
** File description:
** Scheduler source file main
*/

#include <kernel/scheduler/scheduler.h>
#include <kernel/memory/api/kmalloc.h>

/* @brief This variable is the head/tail of the task */
task_t *ktask_head = NULL;
task_t *ktask_tail = NULL;
/* @brief This variable contains the current task executed on the CPU */
task_t *kcurrent_task = NULL;

/**
 * @brief Initialize the scheduler stuff.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kscheduler_init(void)
{
    ktask_head = NULL;
    ktask_tail = NULL;
    kcurrent_task = NULL;
    return OK_TRUE;
}

/**
 * @brief Add a task in the scheduler.
 *
 * @param task   The task to add on the linked list used by the scheduler
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kscheduler_add_task(task_t *task)
{
    if (task == NULL) {
        return KO_FALSE;
    }
    if (ktask_tail == NULL) {
        ktask_head = task;
        ktask_tail = task;
    } else {
        ktask_tail->_next = task;
        ktask_tail = task;
    }
    return OK_TRUE;
}
