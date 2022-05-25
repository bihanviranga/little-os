little-os

Requires:

* nasm
* bochs
* genisoimage (in Arch this is in the `cdrkit` package)
* gcc

Running:

Compile, generate the ISO, and run with bochs:
`make run`

Compile and generate the ISO:
`make os.iso`

Compile the kernel:
`make kernel.elf`

There's also a `make clean` to delete compiled files.
