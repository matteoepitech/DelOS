# TODO DelOS

## Memory stuff
- [x] Fix `kearly_malloc_init` start/end check (NULL vs non-NULL typo) and enforce a hard panic if the early allocator is called after it is disabled; add a simple "bytes used/remaining" counter for debugging.
- [ ] Map the whole kernel image + early heap + stack based on `__kernel_physical_end` (not a fixed 4 MiB window); keep identity mappings for required low-memory regions (BIOS data/e820/VRAM/low MMIO) until safe to drop; ensure higher-half access to e820/early data.
- [ ] PMM: add a range-reservation helper (initrd/MMIO/APIC/VGA/firmware tables); return NULL instead of panicking when no contiguous run exists; validate `page_count <= kpmm_free_pages_amount`; detect double free and expose a `kpmm_mark_used_range` API.
- [ ] PMM: add an aligned/2^n allocation helper and optionally "alloc without zeroing"; expose stats (total/free/highest page).
- [ ] Page-fault path: install #PF/#GP/#DF handlers that log CR2/error code + PDE/PTE snapshot, then panic cleanly; add a fallback IDT/GDT for double faults.
- [x] Heap: enforce `kernel_heap_limit`, bail cleanly if `create_heap_header` fails, validate pointers in `kfree` (heap range + double-free).
- [ ] Heap: add block split/merge
- [ ] Heap: add aligned alloc and optional `krealloc`.
- [ ] Heap hardening: add simple canaries/poison for freed blocks and expose heap stats (bytes used/free, fragments) to shell.
- [x] Memory library: fix `kmemcpy` pointer arithmetic on `void *`; add 32-bit optimized `kmemset`, `memcmp`, `strnlen`, `strncpy`; add self-tests for `memcpy`/`memmove`/`memset`.
- [ ] Map MMIO windows (VGA text, serial, LAPIC/IOAPIC, PIT/RTC) explicitly in higher-half with correct cache flags; keep identity for required ports until PIC reprogram done.
- [ ] Add a simple "leak" tracker for PMM/VMM allocations in debug builds (tag caller + size, print on shutdown/panic).

## VFS / tmpfs / initrd
- [ ] Define VFS objects (superblock, inode, dentry, file) with operation tables and refcounts; add a mountable root.
- [ ] Implement tmpfs/ramfs (files + directories, dynamic sizes, per-file page list) and use it as the root fs.
- [ ] Initrd loader: pick a format (cpio/newc), parse headers, align sections, reserve the physical range in PMM, and either expose it read-only or unpack into tmpfs.
- [ ] Device abstraction: block/char device layer; implement a RAM disk backend and hook it into VFS.
- [ ] Path resolution: handle ".", "..", absolute vs relative; implement a dentry/inode cache with simple LRU and negative entries.
- [ ] File API: open/close/read/write/seek/stat/readdir; error codes consistent; support symlinks or plan for it.
- [ ] File descriptors: per-task FD table, `dup`/`dup2`/`close-on-exec` flags; integrate with future syscalls.
- [ ] Add buffer/page cache for VFS objects (lookup + dirty tracking + eviction) and a writeback policy stub.
- [ ] Shell commands for VFS: `ls`, `cat`, `stat`, `mount`, `umount`, maybe `tree`/`hexdump` for debugging.
- [ ] Add VFS consistency checks (inode refcount leaks, orphan dentries) and a debug dump command.

## User mode / processes
- [ ] Per-process address spaces: user bit set on mappings, shared kernel space, user stacks with guard pages; helpers to clone/fork CR3.
- [ ] Context switch: minimal scheduler driven by PIT tick; save/restore regs/FPU stub; set up TSS for ring3 stacks.
- [ ] ELF loader: validate header/PHDR count, map PT_LOAD with correct flags, zero BSS, set up user stack with argc/argv/envp and aux values; reject malformed binaries.
- [ ] Syscalls: add int 0x80 (or sysenter) entry, syscall dispatch table, base syscalls (`write`, `read`, `open`, `close`, `lseek`, `exit`, `brk`/`mmap` stubs).
- [ ] User copy helpers: `copy_from_user`/`copy_to_user` with range checks against user VMAs; panic/log on violation.
- [ ] Launch a fake init user process from initrd/tmpfs to validate the ring3 path; add a stub libc (minimal start code) if needed.
- [ ] Signals/fault delivery skeleton (SIGSEGV on bad user access) to debug userland crashes.

## Observability / tests
- [ ] Expose PMM/VMM/heap stats via shell commands (total/free pages, allocated PT count, heap fragments).
- [ ] Add shell debug commands: `dump-pagetable <vaddr>`, `dump-tlb`, `fault-test` (#PF/#DF), `alloc-stress` for kmalloc/PMM.
- [ ] Add QEMU automation to run memory unit tests (`memcpy`/`memmove`/`memset`, kmalloc alloc/free, VMM map/unmap) and CI hook.
- [ ] Add panic enhancements: dump registers + CR2 + last faulting instruction; mirror panic to serial if available.
- [ ] Add poisoning/guard patterns for freed PMM pages in debug builds; optional page-fill on allocation for deterministic tests.

## Boot / interrupts
- [ ] Install default handlers for exceptions 0–31 and a dedicated double-fault handler with backup IDT/GDT/stack.
- [ ] Handle int 0x13 errors gracefully during boot load (retry/report).
- [ ] Replace magic numbers in boot (KERNEL_LOCATION, PIC offsets, etc.) with named defines.
- [ ] Add NMI mask/unmask helpers and spurious IRQ handler; consider lazy PIC mask/unmask helpers to remove duplicated `outb`s.
- [ ] Embed e820 validation in boot (reject overlapping/unsorted entries) and log usable ranges early.
- [ ] Add an early serial logger path in boot to help debug pre-VGA issues.
