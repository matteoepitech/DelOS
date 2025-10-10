##
## DELOS PROJECT, 2025
## Makefile
## File description:
## MAKEFILE DELOS
##

BOOT_DIR	=	boot
BOOT_FILE_NAME	=	boot.s
BIN_BOOT_NAME	=	os.bin

all: $(BIN_BOOT_NAME)

# Make the raw binary bootable file
$(BIN_BOOT_NAME):
	nasm -f bin $(BOOT_DIR)/$(BOOT_FILE_NAME) -o $(BIN_BOOT_NAME)

run:
	@echo "Starting $(BIN_BOOT_NAME)..."
	@qemu-system-i386 -drive format=raw,file=$(BIN_BOOT_NAME)

clean:
	rm -f $(BIN_BOOT_NAME)

re: clean all
