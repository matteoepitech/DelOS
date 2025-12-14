# DelOS

![Status](https://img.shields.io/badge/Status-WIP-yellow)
![Made with](https://img.shields.io/badge/Made%20with-C%20%2B%20ASM-blueviolet)
[![MIT license](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)

DelOS is a tiny 32-bit educational x86 operating system designed for learning OS development fundamentals.

## Requirements

- `nasm` - Netwide Assembler
- `i386-elf-gcc` / `i386-elf-ld` (32-bit cross-compiler)
- `qemu-system-i386` - x86 emulator
- `make` - Build automation

## Installation

### Ubuntu/Debian
```sh
sudo apt install nasm qemu-system-x86 build-essential
```

For the `i386-elf` cross-compiler toolchain, you'll need to build it from source or use a pre-built package.

See [OSDev Wiki](https://wiki.osdev.org/GCC_Cross-Compiler) for detailed instructions.

### macOS
You are free to use a container / virtual machine for compiling the project. <3

## Quick Start

```sh
make       # Build the bootsector + OS image into build/delos.bin
make run   # Launch QEMU with the image
make clean # Clean build artifacts
```

## Notes & Disclaimers

> [!NOTE]
This is an educational operating system. Do not run on bare metal hardware you care about.

- Tested in QEMU only. Behavior on other emulators or real hardware may differ
- No warranty or guarantees of any kind
- Use at your own risk :)

## Contributing

Contributions are welcome! Whether you're fixing bugs, adding features, or improving documentation, your help is appreciated.

- See `CONTRIBUTING.md` for workflow, coding style, and contribution checklist
- See `TODO.md` for a list of tasks and ideas


## License

MIT License. See `LICENSE` for details.
