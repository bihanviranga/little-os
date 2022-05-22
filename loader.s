global loader ; the entry symbol for ELF

MAGIC_NUMBER  equ 0x1BADB002    ; magic number constant
FLAGS         equ 0x0           ; multiboot flags
CHECKSUM      equ -MAGIC_NUMBER ; calculate the checsum
                                ; magic number + checksum + flags should equal 0

section .text:    ; text (code) section
align 4           ; align code to 4 bytes
  dd MAGIC_NUMBER ; (D)efine (D)oubleword (allocate 4 bytes)
  dd FLAGS
  dd CHECKSUM

loader:               ; loader label which is the entry point
  mov eax, 0xCAFEBABE ; store the number in the register
.loop:
  jmp .loop           ; infinite loop
