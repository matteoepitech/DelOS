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

/*
 * @brief Structure for a scheduler node.
 *        - task = the task
 *        - next = the next scheduler node
 */
typedef struct scheduler_node_s {
    task_t *_task;
    struct scheduler_node_s *_next;
} scheduler_node_t;

/* @brief This variable is the head/tail of the schedulers nodes */
extern scheduler_node_t *kscheduler_node_head;
extern scheduler_node_t *kscheduler_node_tail;
/* @brief This variable contains the current task executed on the CPU */
extern scheduler_node_t *kcurrent_sched_node;

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
