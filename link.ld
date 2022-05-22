ENTRY(loader)             /* name of the entry point label */

SECTIONS {
  . = 0x00100000;         /* load the code at 1 MB mark */

  .text ALIGN (0x1000):   /* align at 4 KB */
  {
    *(.text)              /* all the text sections from all files */
  }

  .rodata ALIGN (0x1000):
  {
    *(.rodata*)           /* read-only sections from all files */
  }

  .data ALIGN (0x1000):
  {
    *(.data)              /* data sections from all files */
  }

  .bss ALIGN (0x1000):
  {
    *(COMMON)             /* COMMON sections from all files */
    *(.bss)               /* bss sections from all files */
  }
}
