/*
** DELOS PROJECT, 2025
** src/kernel/kernel
** File description:
** Kernel main
*/

#include <stdint.h>

void kmain(void)
{
    for (int i = 0; i < 26; i++) {
        *(unsigned char *) ((uintptr_t) 0xb8000 + i * 2) = 'A' + i;
    }
    while (1);
    return;
}
