[BITS 32]

global load_cr3

load_cr3:
    mov eax, [ebp + 8]

    mov cr3, eax

    ret