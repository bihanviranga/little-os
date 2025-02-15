global outb ; make the label outb visible outside this file
global inb  ; same for inb

; outb - send a byte to an I/O port
; stack:  [esp + 8] the data byte
;         [esp + 4] the I/O port
;         [esp    ] return address
outb:
  mov al, [esp + 8] ; move the data to be sent into AL
  mov dx, [esp + 4] ; move the address of the I/O port into DX
  out dx, al        ; send the data to the I/O port
  ret               ; return to caller


; inb - returns a byte from the given I/O port
; stack:  [esp + 4] the I/O port
;         [esp    ] return address
inb:
  mov dx, [esp + 4] ; move the address of the I/O port to DX
  in al, dx         ; return a byte from the port and store it in AL
  ret               ; return to caller
