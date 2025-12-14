# DelOS

DelOS is a tiny 32-bit educational x86 operating system opened to contributions.

## Toolchain requirements
- `nasm`
- `i386-elf-gcc` / `i386-elf-ld` (freestanding, 32-bit)
- `qemu-system-i386`
- `make`

You can inspect detected sources/objects via `make info`.

## Quick start

```sh
make            # build bootsector + kernel -> build/delos.bin
make run        # launch QEMU (floppy raw image)
```

## Contributing
- Check `todo.md` for bite-sized tasks and ideas.
- Follow the existing code style (freestanding C, no dependencies).
- Prefer small, focused PRs (one task per PR).
- Add brief comments only where behavior is non-obvious.

## Notes & disclaimers
- This is an educational operating system, do not run on bare metal hardware you care about :)
- Tested in QEMU only; behavior on other emulators/hardware may differ.

## License
MIT License. See `LICENSE`.
