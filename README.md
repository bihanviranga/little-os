# Mini OS

Instructions:

* Compile the code:
`nasm -f elf32 loader.s`

* Link the executable
`ld -T link.ld -melf_i386 loader.o -o kernel.elf`

* Copy the `kernel.elf` file to `iso/boot`
`cp kernel.elf iso/boot/kernel.elf`

* Generate the ISO
```bash
chmod u+x generate_iso.sh
./generate_iso
```

* Run with bochs
`bochs -f bochsrc -q`
