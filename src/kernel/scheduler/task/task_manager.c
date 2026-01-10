/*
** DELOS PROJECT, 2026
** src/kernel/scheduler/task/task_manager
** File description:
** Task manager source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <kernel/scheduler/task.h>

/**
 * @brief Create a new task and return it.
 *
 * @param void (*entry)(void)    A function pointer to the handler of the task
 *
 * @return The new task created.
 */
task_t *
ktask_create(void (*entry)(void))
{
    task_t *task = NULL;

    if (entry == NULL) {
        return NULL;
    }
    task = kmalloc(sizeof(task_t));
    if (task == NULL) {
        return NULL;
    }
    task->_entry = entry;
    task->_state = KTASK_IDLE;
    return task;
}
