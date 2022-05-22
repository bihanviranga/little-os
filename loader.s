global loader ; the entry symbol for ELF

MAGIC_NUMBER  equ 0x1BADB002    ; magic number constant
FLAGS         equ 0x0           ; multiboot flags
CHECKSUM      equ -MAGIC_NUMBER ; calculate the checsum
                                ; magic number + checksum + flags should equal 0
KERNEL_STACK_SIZE equ 4096      ; size of stack in bytes

extern kmain

section .text:    ; text (code) section
align 4           ; align code to 4 bytes
  dd MAGIC_NUMBER ; (D)efine (D)oubleword (allocate 4 bytes)
  dd FLAGS
  dd CHECKSUM

loader:                                     ; loader label which is the entry point
  mov esp, kernel_stack + KERNEL_STACK_SIZE ; point esp to the start of the stack
                                            ; (at the end of the reserved memory)
  mov eax, 0xCAFEBABE                       ; store the number in the register

  call kmain

.loop:
  jmp .loop ; infinite loop

section .bss:
align 4                   ; align to 4 bytes
kernel_stack:             ; label pointing to the beginning of memory
  resb KERNEL_STACK_SIZE  ; reserve for kernel stack
