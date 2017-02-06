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

    mov eax, 0x01

    cpuid
    mov [esi], ecx
    add esi, 4
    mov [esi], edx

    inc esi
    mov ecx, 0
    mov [esi], ecx

    mov esi, [ebp + 12]
    mov eax, 0x80000002
    jmp get_brand


get_brand:
    
    cpuid
    mov [esi], eax
    add esi, 4
    mov [esi], ebx
    add esi, 4
    mov [esi], ecx
    add esi, 4
    mov [esi], edx
    add esi, 4
    inc eax
    cmp eax, 0x80000004
    je get_brand

    xor ecx, ecx
    mov [esi], ecx
    jmp done

done:
    ret