/*
** DELOS PROJECT, 2026
** src/kernel/scheduler/scheduler
** File description:
** Scheduler source file main
*/

#include <kernel/scheduler/scheduler.h>
#include <kernel/memory/api/kmalloc.h>

/* @brief This variable is the head/tail of the schedulers nodes */
scheduler_node_t *kscheduler_node_head = NULL;
scheduler_node_t *kscheduler_node_tail = NULL;
/* @brief This variable contains the current task executed on the CPU */
scheduler_node_t *kcurrent_sched_node = NULL;

/**
 * @brief Initialize the scheduler stuff.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kscheduler_init(void)
{
    return OK_TRUE;
}

/**
 * @brief Add a task in the scheduler.
 *
 * @param task   The task to add on the scheduler nodes
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kscheduler_add_task(task_t *task)
{
    scheduler_node_t *node = NULL;

    if (task == NULL) {
        return KO_FALSE;
    }
    node = kmalloc(sizeof(scheduler_node_t));
    if (node == NULL) {
        return KO_FALSE;
    }
    node->_next = NULL;
    if (kscheduler_node_tail == NULL) {
        kscheduler_node_head = node;
        kscheduler_node_tail = node;
    } else {
        kscheduler_node_tail->_next = node;
        kscheduler_node_tail = node;
    }
    return OK_TRUE;
}
