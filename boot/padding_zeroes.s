; this is used to make the file bigger so the emulated virtual memory is not very small. Since we are loading a random amount of disk sector since
; we don't know the size of the kernel. This prevent DISK_ERROR when using an emulated hardware like qemu does.
section .padding
times 10240 db 0
