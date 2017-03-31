[BITS 32]

global load_cr3

load_cr3:
    mov edx, 0x600000 ;[ebp  + 8]

    mov cr3, edx

    ret