/*
** DELOS PROJECT, 2025
** src/kernel/arch/i386/gdt
** File description:
** GDT source file
*/

#include <kernel/arch/i386/gdt.h>

/* @brief Variables for the new Global Descriptor Table */
static gdt_entry_t gdt_entries[3] __attribute__((aligned(8))) = {0};
static gdt_ptr_t gdt_ptr = {0};

/**
 * @brief Populate an entry inside the GDT with base/limit/access values.
 *
 * @param index   The index inside the GDT array
 * @param base    The base address of the segment
 * @param limit   The size limit of the segment
 * @param access  The access flags (privilege/type)
 * @param gran    The granularity flags (page/byte + limit high bits)
 */
static void
kgdt_set_entry(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt_entries[index]._base_low = (base & 0xFFFF);
    gdt_entries[index]._base_middle = (base >> 16) & 0xFF;
    gdt_entries[index]._base_high = (base >> 24) & 0xFF;
    gdt_entries[index]._limit_low = (limit & 0xFFFF);
    gdt_entries[index]._granularity = (limit >> 16) & 0x0F;
    gdt_entries[index]._granularity |= (gran & 0xF0);
    gdt_entries[index]._access = access;
}

/**
 * @brief Rebuild a minimal GDT in high memory and reload segments.
 *        This keeps the GDT mapped after identity mapping is removed.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kgdt_init(void)
{
    gdt_ptr._limit = sizeof(gdt_entries) - 1;
    gdt_ptr._base = (uint32_t) &gdt_entries;
    kgdt_set_entry(0, 0, 0, 0, 0);
    kgdt_set_entry(1, 0, 0xFFFFF, 0x9A, 0xCF); // code segment
    kgdt_set_entry(2, 0, 0xFFFFF, 0x92, 0xCF); // data segment
    KGDT_RELOAD_PTR(&gdt_ptr);
    return OK_TRUE;
}
