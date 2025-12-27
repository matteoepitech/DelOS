# TODO DelOS

## Critical fixes
- [x] Zero the entire IDT with `kmemset(idt, 0, sizeof(idt))` (src/kernel/arch/i386/interruption/idt.c).
- [x] Add index bounds checks in `kidt_set_entry`, `kisr_register_handler`, `kisr_handler` to stay within `IDT_SIZE` (src/kernel/arch/i386/interruption/idt.c, src/kernel/arch/i386/interruption/isr_handler.c).
- [ ] Add default handlers for CPU exceptions 0–31 (#GP, #PF, #DF, etc.) and register them in the IDT (src/kernel/arch/i386/interruption/idt.c, src/kernel/arch/i386/interruption/isr/*).
- [x] Replace the infinite busy loop in `kmain` with an idle `hlt` loop or idle task (src/kernel/kernel.c).
- [x] Guard `kpit_timer_init` against `frequency == 0` / too high; clamp divisor to 16 bits (src/kernel/arch/i386/interruption/pit.c).
- [ ] Add null-pointer checks before dereferencing in shell/TTY/panic paths (grep for `NULL` comparisons) (multiple files).
- [x] Ensure `kvga_putc_at` silently drops out-of-bounds writes; add tests/logging guard (src/drivers/video/vga.c).
- [x] Add sanity checks for PIT divisor overflows and log the actual divisor (src/kernel/arch/i386/interruption/pit.c).
- [ ] Make `kreboot` timeout and fail gracefully if controller never clears bit 1 (src/kernel/misc/reboot.c).
- [ ] Accessing the address 0xC0300000 need to page fault? Since the kernel is not pagging this address right now.

## Shell / input / TTY
- [x] Implement basic argv/argc parsing (split on space/tab) and return an error code when a command is unknown (src/kernel/shell/shell.c).
- [ ] Implement basic argv/argc parsing for handle quotes (src/kernel/shell/shell.c).
- [x] Print "command not found" on unknown commands; stop after executing one matched command (src/kernel/shell/shell.c).
- [x] Add `clear`, `uptime`/`timer`, and `panic-test` commands (src/kernel/shell/commands/).
- [x] Handle Shift (src/kernel/arch/i386/interruption/irq/irq_keyboard_press.c, include/kernel/misc/keyboard.h).
- [x] Handle CapsLock (src/kernel/arch/i386/interruption/irq/irq_keyboard_press.c, include/kernel/misc/keyboard.h).
- [x] Add switch layout keyboard configuration command (src/kernel/shell/commands/*.c)
- [x] Make `kkeyboard_getchar` CPU-friendly (e.g., `hlt` in loop with interrupts enabled) (src/kernel/misc/keyboard.c).
- [x] Align `ktty_puts_at` signature (char * vs int8_t *) between header and implementation; preserve passed color on newline handling (src/kernel/tty/tty.c, include/kernel/tty/tty.h).
- [x] Fix scroll/backspace to stay in bounds and properly erase previous char (src/kernel/tty/tty.c).
- [x] Add tab completion stub (just bell or no-op) and key handling structure for future features (src/kernel/shell/shell.c).
- [x] Add configurable prompt string and color (store in a global) (src/kernel/shell/shell.c).
- [x] Add `repeat <n> <cmd>` command to loop a command for stress testing (src/kernel/shell/commands/repeat.c).

## Boot / interrupts
- [x] Compute kernel sector count dynamically instead of hardcoded `0x14` + padding (boot/bootsector.s, boot/padding_zeroes.s, Makefile).
- [ ] Check `int 0x13` return status and print a readable disk error before continuing (boot/bootsector.s).
- [x] Enable A20 line before jumping to protected mode (boot/bootsector.s).
- [ ] Replace magic numbers (KERNEL_LOCATION, KERNEL_BASE_POINTER, PIC offsets) with documented defines (boot/bootsector.s, boot/extra/gdt.s, include/kernel/arch/i386/interruption/pic.h).
- [ ] Add a double-fault handler and a fallback IDT/GDT to avoid triple faults (src/kernel/arch/i386/interruption/idt.c, src/kernel/arch/i386/interruption/isr/*).
- [ ] Add NMI (Non Maskable Interrupt) disable/enable helpers and ensure NMI masking where needed (new helper + boot/bootsector.s).
- [ ] Add spurious IRQ handler and mask if repeatedly triggered (src/kernel/arch/i386/interruption/idt.c, irq handler).
- [ ] Add lazy PIC masking/unmasking helper to avoid magic `outb` duplication (src/kernel/arch/i386/interruption/pic.c).
- [ ] Provide an `isr_dump_regs` helper reusable by all handlers (src/kernel/arch/i386/interruption/isr_handler.c).
- [ ] Add `sti`/`cli` wrappers with debug logging toggles for tracing (include/kernel/arch/i386/interruption/interruption.h).

## Kernel library
- [ ] Finish 4-byte aligned `kmemset` optimization (TODO present) (src/utils/kstdlib/memory/memset.c).
- [ ] Make `kmemcpy` avoid arithmetic on `void *` (cast to uint8_t *) (src/utils/kstdlib/memory/memcpy.c).
- [ ] Add simple in-kernel tests (qemu) for `kstrlen`/`kstrcmp`/`memcpy`/`memmove`/`memset` (src/utils/kstdlib/*).
- [ ] Expand types (`uintptr_t`, `uint64_t`, `ssize_t`) and avoid redefining `NULL`/booleans if already provided (include/types.h, include/defines.h).
- [ ] Add endian helpers: `htons`/`ntohs`/`htonl`/`ntohl` (include/utils/kstdlib/byteswap.h).
- [ ] Add `memcmp` implementation (src/utils/kstdlib/memory/memcmp.c).
- [ ] Add `strncpy`/`strnlen` minimal variants (src/utils/kstdlib/string/).
- [ ] Add lightweight random stub (e.g., LCG) for tests (src/utils/kstdlib/rand.c).
- [ ] Add `min/max/clamp` macros in a common header (include/defines.h or new math util).
- [ ] Add safe `ARRAY_SIZE` macro for static arrays (include/defines.h).

## New features (bite-sized)
- [x] Add a `heap` allocator placeholder: a bump allocator with a simple API no-op to unblock future features (new file `src/kernel/mem/heap.c`, header under `include/kernel/mem/heap.h`).
- [ ] Implement a simple serial driver (COM1) for logging: init, putc, puts (src/drivers/serial/serial.c, include/drivers/serial/serial.h).
- [x] Add a kernel printf-lite (`kprintf`) supporting %s/%d/%x/%c routed to TTY (src/utils/kstdlib/kprintf.c, header in include/utils/kstdlib/kprintf.h).
- [ ] Introduce a basic timer-based scheduler stub: task struct + ready queue placeholder, tick hook increments a per-task runtime counter (src/kernel/sched/*).
- [x] Add a page frame allocator stub (bitmap over a fixed region) with `pfa_alloc`/`pfa_free` prototypes, even if not fully wired (src/kernel/mem/pfa.c, include/kernel/mem/pfa.h).
- [ ] Create a minimal ELF loader stub that validates ELF header and logs the entry point (src/kernel/loader/elf.c, include/kernel/loader/elf.h).
- [ ] Add a `version` command that prints git commit (if embedded) or a hardcoded version string plus build date (src/kernel/shell/commands/version.c).
- [ ] Add a `banner` command that reprints the welcome banner without reboot (src/kernel/shell/commands/banner.c).
- [ ] Add a `help -v` / `help --verbose` option to show command descriptions (extend shell command metadata with a short help string) (src/kernel/shell/shell.c and command files).
- [ ] Add a `history` buffer for the shell (up/down arrows optional later): store last N commands and a `history` command to print them (src/kernel/shell/shell.c).
- [ ] Expose uptime in seconds via a `sysinfo` struct and a `sysinfo` command (src/kernel/shell/commands/sysinfo.c).
- [ ] Add a `beep` command using PIT/PC speaker (new helper in drivers if needed).
- [ ] Add screen color theme switching: define color schemes and a `theme <name>` command (src/kernel/tty/*, shell commands).
- [ ] Add a tiny assertion macro `KASSERT(cond, msg)` that triggers `kpanic` with file/line (include/defines.h or new assert header).
- [ ] Add unit-test-like harness: a `test` command that runs small internal checks (memcpy/memmove/strlen) and reports pass/fail counts (src/kernel/shell/commands/test.c).
- [ ] Add `time` command that measures execution time of another command using ticks (src/kernel/shell/commands/time.c).
- [ ] Add `sleep <ms>` using PIT ticks (src/kernel/shell/commands/sleep.c).
- [ ] Add `colors` command to list available VGA color codes (src/kernel/shell/commands/colors.c).
- [ ] Add `cursor on/off` command to toggle cursor visibility (src/kernel/shell/commands/cursor.c).
- [ ] Add `cls <color>` to clear screen with a given color (src/kernel/shell/commands/cls.c).
- [ ] Add `kbd-layout` command to switch layout at runtime (src/kernel/shell/commands/kbd_layout.c).
- [ ] Add `memset-demo` command to fill a screen region with a character for debug (src/kernel/shell/commands/memset_demo.c).
- [ ] Add `rand` command to print a random number (src/kernel/shell/commands/rand.c).
- [ ] Add `env`-like command to print build info (toolchain, flags) embedded at build time (src/kernel/shell/commands/buildinfo.c).
- [ ] Add `stack-check` command to walk the current stack frame and print return addresses (requires frame pointer) (src/kernel/shell/commands/stack_check.c).
- [ ] Add `regs` command to snapshot general-purpose registers via inline asm (best-effort) (src/kernel/shell/commands/regs.c).
- [ ] Add `scroll-test` command to write multiple lines and verify scroll visually (src/kernel/shell/commands/scroll_test.c).
- [ ] Add `keyboard-test` command that echoes scancodes and ASCII (src/kernel/shell/commands/keyboard_test.c).
- [ ] Add `pagewalk` stub command reserved for future paging introspection (src/kernel/shell/commands/pagewalk.c).
- [ ] Add `trace on/off` flag to log all shell input/output for debugging (src/kernel/shell/shell.c).
- [ ] Add serial console mirror option (duplicate TTY output to serial) (shell or TTY config).
- [ ] Add a `logo` command with ASCII art stored in a const table (src/kernel/shell/commands/logo.c).
- [x] Add `dump-mem <addr> <len>` command (hex/ASCII) guarded for safe ranges (src/kernel/shell/commands/dump_mem.c).
- [ ] Add `fill-mem <addr> <len> <byte>` command with range checks (src/kernel/shell/commands/fill_mem.c).
- [ ] Add `cmp-mem <addr1> <addr2> <len>` command for quick memory comparisons (src/kernel/shell/commands/cmp_mem.c).

## Debug / observability
- [ ] Extend `kpanic`/`KPANIC` to dump registers, int number, and context (src/kernel/misc/panic.c, src/kernel/arch/i386/interruption/isr_handler.c).
- [x] Add a small logging helper (levels, colors) instead of raw `KDEBUG_TTY` (include/kernel/tty/tty.h).
- [ ] Add shell test commands: `int3`, divide-by-zero, and `dump-idt` (src/kernel/shell/commands/).
- [ ] Add `trace interrupts on/off` to log int numbers in `kisr_handler` (src/kernel/arch/i386/interruption/isr_handler.c).
- [ ] Add a configurable debug level flag (bitmask) settable via a shell command (config header + shell command).
- [ ] Add a crash counter and last-crash reason stored in a small struct (src/kernel/misc/panic.c).
- [ ] Add a watchdog command that triggers a timeout and reports via panic/log (shell command).
- [ ] Mirror panic output to serial if available (panic.c + serial driver).

## Tooling / CI / docs
- [ ] Add a Makefile target to check toolchain deps (`nasm`, `i386-elf-gcc/ld`, `qemu`) and fail clearly if missing (Makefile).
- [ ] Provide headless qemu run target + simple autotest script (capture serial/TTY) (Makefile + scripts).
- [ ] Extend `.gitignore` for qemu logs, core dumps, future artifacts (.gitignore).
- [x] Add a CONTRIBUTING.md with coding style, branch naming, PR checklist.
- [ ] Add issue/PR templates with sections for testing and screenshots/logs.
- [ ] Add a `make docs` target that prints available targets and main commands.
- [ ] Add a script to embed git commit hash and build time into a header (e.g., generated `include/version.h`).
- [ ] Add CI matrix for multiple toolchain versions (if CI is hooked later).
