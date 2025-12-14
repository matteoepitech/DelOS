# Contributing to DelOS

Thanks for your interest in DelOS! This is a small educational x86 kernel; please keep changes focused and easy to review.

## Prerequisites
- Toolchain: `nasm`, `i386-elf-gcc`, `i386-elf-ld`
- Emulator: `qemu-system-i386`
- Build: `make`

## Workflow
1. Fork the repo and create a topic branch (e.g. `fix/idt-bounds`, `feat/kprintf`).
2. Pick a bite-sized task from `todo.md` or propose one.
3. Keep PRs small and scoped to one task.
4. Add concise comments only when behavior is non-obvious.
5. Prefer ASCII and keep headers consistent with existing code.

## Building & testing
- Build: `make`
- Run in QEMU: `make run`
- Clean: `make clean`
- For doc-only changes, mention “doc-only” in the PR notes.

## Coding style
- Freestanding C (no libc), minimal dependencies.
- Avoid arithmetic on `void *` (cast to byte pointers).
- Use guards/NULL checks where applicable.
- Keep macros safe (`do { } while (0)` when needed).
- Keep formatting consistent (tabs/spaces as in existing files).

## PR checklist
- [ ] Scope is limited to one task/bug/feature.
- [ ] Build completes (`make`).
- [ ] Ran `make run` if the change affects runtime behavior (or explain why not).
- [ ] Added/updated comments only where behavior is non-obvious.
- [ ] Referenced files/paths in the description when relevant.

## Communication
If unsure about approach or scope, open an issue/PR draft describing the plan before heavy coding.
