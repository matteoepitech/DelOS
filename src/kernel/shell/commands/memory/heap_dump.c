/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/memory/heap_dump
** File description:
** heap_dump command source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <kernel/shell/shell.h>
#include <utils/misc/print.h>
#include <defines.h>

/**
 * @brief Get the amount of headers available.
 *        Warning 1 header doesn't mean 1 allocation.
 *        We can have header freed but waiting for allocation.
 *        We can have header containing multiples pages as well of physical space.
 *
 * @param only_free     Only take in count the free headers (waiting for allocation)
 *
 * @return The amount of headers already allocated on the heap.
 */
static uint32_t
get_amount_heap_header(bool32_t only_free)
{
    kmalloc_header_t *h = kernel_heap_lh;
    uint32_t amount = 0;

    while (h != NULL) {
        if (only_free == OK_TRUE && h->_free == OK_TRUE) {
            amount++;
        } else if (only_free == KO_FALSE) {
            amount++;
        }
        h = h->_next;
    }
    return amount;
}

/**
 * @brief Command for heap_dump.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_heap_dump(UNUSED uint32_t argc, UNUSED char *argv[])
{
    uint32_t free = get_amount_heap_header(OK_TRUE);
    uint32_t used = get_amount_heap_header(KO_FALSE) - free;
    kmalloc_header_t *hdr = kernel_heap_lh;

    KPRINTF_INFO("heapdump: dump informations (kmalloc):");
    KPRINTF_INFO("  base : %x", (uint32_t) kernel_heap_base);
    KPRINTF_INFO("  brk  : %x", (uint32_t) kernel_heap_brk);
    KPRINTF_INFO("  limit: %x", (uint32_t) kernel_heap_limit);
    KPRINTF_INFO("  size : %d bytes", kernel_heap_limit - kernel_heap_base);
    KPRINTF_INFO("  hdrs : %d used / %d free", used, free);
    KPRINTF_INFO("heapdump: headers details:");
    for (uint32_t i = 1; hdr != NULL; hdr = hdr->_next) {
        KPRINTFN_INFO("  #%03d  ", i);
        if (hdr->_free) {
            kprintf(VGA_TEXT_SUCCESS_COLOR, "FREE");
        } else {
            kprintf(VGA_TEXT_ERROR_COLOR, "USED");
        }
        kprintf(VGA_TEXT_DEFAULT_COLOR, "  size=%dB  hdr=%x\n", hdr->_size, (uint32_t) hdr);
        i++;
    }
    return OK_TRUE;
}
