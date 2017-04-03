[BITS 32]

global identify_cpu

identify_cpu:
    mov esi, [ebp + 8]  ;offset to the function argument
    mov eax, 0x00

    cpuid

    mov [esi], ebx
    add esi, 4
    mov [esi], edx
    add esi, 4
    mov [esi], ecx
    add esi, 4

    inc esi
    mov eax, 0x00
    mov [esi], eax
    add esi, 4
    
    cpuid           ;dont mov eax into anywhere, since eax is the return value

    ret

get_hileaf:
  mov eax, 0x00

  cpuid

  ret

get_brand:


done:
    ret
