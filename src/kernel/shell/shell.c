/*
** DELOS PROJECT, 2025
** src/kernel/shell/shell
** File description:
** Shell source file
*/

#include <kernel/shell/parser/autocomplete.h>
#include <kernel/shell/parser/arguments.h>
#include <utils/kstdlib/kstring.h>
#include <kernel/misc/keyboard.h>
#include <kernel/shell/shell.h>
#include <utils/misc/print.h>
#include <kernel/tty/tty.h>
#include <defines.h>

/**
 * @brief All shell commands.
 */
const shell_command_t shell_commands[] = {
    {"help", &kshell_help},
    {"reboot", &kshell_reboot},
    {"clear", &kshell_clear},
    {"uptime", &kshell_uptime},
    {"timer", &kshell_timer},
    {"shutdown", &kshell_shutdown},
    {"panictest", &kshell_panic_test},
    {"repeat", &kshell_repeat},
    {"loadkeys", &kshell_loadkeys},
    {"debug", &kshell_debug},
    {NULL, NULL}
};

/**
 * @brief Setup a command using the buffer and run the command.
 *
 * @param buffer                The buffer of the user prompt
 *
 * @return The final exit code of the operation.
 */
static uint8_t
setup_run_shell_command(char *buffer)
{
    char *argv[SHELL_ARGV_MAX_COUNT] = {0};
    uint32_t argc = 0;

    if (buffer == NULL || !*buffer) {
        return KO_FALSE;
    }
    argc = kshell_parse_get_argc(buffer);
    kshell_parse_formatting_buffer(buffer);
    kshell_parse_get_argv(buffer, argv);
    return kshell_execute_command(argc, argv);
}

/**
 * @brief Print the shell prompt. THAT IT.
 */
static
void print_shell_prompt(void)
{
    KPRINTF_DATE();
    ktty_puts(KERNEL_SHELL_PROMPT_BASE" ", VGA_TEXT_DEFAULT_COLOR);
}

/**
 * @brief Execute the command
 *
 * @param argc               The ARGC
 * @param char *argv[16]     The ARGV
 *
 * @return The final exit code of the operation.
 */
uint8_t
kshell_execute_command(uint32_t argc, char *argv[SHELL_ARGV_MAX_COUNT])
{
    if (argv == NULL || argv[0] == NULL) {
        return KO_FALSE;
    }
    for (uint32_t i = 0; shell_commands[i].command != NULL; i++) {
        if (kstrcmp(argv[0], shell_commands[i].command) != 0)
            continue;
        return shell_commands[i].func(argc, argv);
    }
    KPRINTF_WARN("Command not found: %s", argv[0]);
    return OK_TRUE;
}

/**
 * @brief Start the shell and waiting for user prompt.
 *        This shell is the main process of the kernel and took the while.
 *
 * @return OK_TRUE if worked KO_FALSE otherwise.
 */
bool32_t
kshell_start(void)
{
    char buffer[KERNEL_SHELL_BUFFER_SIZE];
    uint32_t index = 0;

    KPRINTF_OK("Shell has been started.");
    print_shell_prompt();
    while (OK_TRUE) {
        uint8_t c = kkeyboard_getchar();

        switch (c) {
            case '\n':
                buffer[index] = '\0';
                ktty_puts("\n", VGA_TEXT_DEFAULT_COLOR);
                setup_run_shell_command(buffer);
                print_shell_prompt();
                index = 0;
                break;

            case '\b':
                if (index > 0) {
                    ktty_putc('\b', VGA_TEXT_DEFAULT_COLOR);
                    index--;
                }
                break;

            case '\t':
                kshell_parse_autocomplete(buffer, &index);
                break;

            default:
                if (index < KERNEL_SHELL_BUFFER_SIZE - 1) {
                    buffer[index] = c;
                    ktty_putc(c, VGA_TEXT_DEFAULT_COLOR);
                    index++;
                }
                break;
        }
    }
    return OK_TRUE;
}
