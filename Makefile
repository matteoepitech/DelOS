##
## DELOS PROJECT, 2025
## Makefile
## File description:
## MAKEFILE DELOS
##

BOOT_DIR	:= boot
SRC_DIR		:= src
BUILD_DIR	:= build

BOOT_FILE	:= $(BOOT_DIR)/bootsector.s
ENTRY_FILE	:= $(BOOT_DIR)/kernel_entry.s
ZERO_FILE 	:= $(BOOT_DIR)/padding_zeroes.s
KERNEL_C	:= $(SRC_DIR)/kernel/kernel.c

OS_BIN		:= $(BUILD_DIR)/delos.bin

NASM		:= nasm
CC		:= i386-elf-gcc
LD		:= i386-elf-ld
QEMU		:= qemu-system-i386

CFLAGS		:= -ffreestanding -m32 -g -c -Wall -Wextra
LDFLAGS		:= -Ttext 0x10000 --oformat binary

# all RULE : do the whole process
all: prepare $(OS_BIN)

# prepare RULE : prepare the build directory
prepare:
	@mkdir -p $(BUILD_DIR)

# $(BUILD_DIR)/boot_sector.bin RULE : create the boot sector for the bin
$(BUILD_DIR)/boot_sector.bin: $(BOOT_FILE)
	@echo "Assembling bootloader..."
	@$(NASM) -I $(BOOT_DIR) -f bin $< -o $@

# $(BUILD_DIR)/kernel_entry.o RULE : create the kernel entry
$(BUILD_DIR)/kernel_entry.o: $(ENTRY_FILE)
	@echo "Assembling kernel entry..."
	@$(NASM) -f elf32 $< -o $@

# $(BUILD_DIR)/padding_zeroes.bin RULE : create the padding for the bin
$(BUILD_DIR)/padding_zeroes.bin: $(ZERO_FILE)
	@echo "Creating padding..."
	@$(NASM) -f bin $< -o $@

# $(BUILD_DIR)/kernel.o RULE : create the kernel source code
$(BUILD_DIR)/kernel.o: $(KERNEL_C)
	@echo "Compiling kernel..."
	@$(CC) $(CFLAGS) $< -o $@

# $(BUILD_DIR)/full_kernel.bin RULE : link the kernel source code with the kernel entry
$(BUILD_DIR)/full_kernel.bin: $(BUILD_DIR)/kernel_entry.o $(BUILD_DIR)/kernel.o
	@echo "Linking kernel..."
	@$(LD) $(LDFLAGS) -o $@ $^

# $(OS_BIN) RULE : create the final $(OS_BIN) file
$(OS_BIN): $(BUILD_DIR)/boot_sector.bin $(BUILD_DIR)/full_kernel.bin $(BUILD_DIR)/padding_zeroes.bin
	@echo "Creating OS image..."
	@cat $^ > $@
	@echo "Build complete: $@"

# run RULE : run the OS
run: $(OS_BIN)
	@echo "Starting $(OS_BIN)..."
	@$(QEMU) -drive format=raw,file=$<,index=0,if=floppy -m 128M

# clean RULE : clean everything in $(BUILD_DIR) directory
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)

# re RULE : redo the whole build + clean
re: clean all

# info RULE : show build information
info:
	@echo "=== DELOS BUILD INFO ==="
	@echo "Bootloader: $(BOOT_FILE)"
	@echo "Kernel Entry: $(ENTRY_FILE)"
	@echo "Kernel C: $(KERNEL_C)"
	@echo "Output: $(OS_BIN)"
	@echo "CC: $(CC)"
	@echo "LD: $(LD)"
	@echo "QEMU: $(QEMU)"

.PHONY: all clean run re prepare info
