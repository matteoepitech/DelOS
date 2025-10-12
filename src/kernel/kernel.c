/*
** DELOS PROJECT, 2025
** src/kernel/kernel
** File description:
** Kernel main
*/

void kmain(void)
{
    *(char *) 0xb8000 = 'Z';
    while (1);
    return;
}
