section .text
bits 64
default rel
global sdotproduct

sdotproduct:
    ; n@rcx (size of vector), vec1@rdx (vector1), vec2@r8 (vector2), result@r9 (result vector)
    MOVSD XMM1, [rdx]      ; Load element from vector1 into xmm0
    MULSD XMM1, [r8]       ; Multiply xmm0 by element from vector2
    MOVSD [r9], XMM1       ; Store result in result vector

    ; Increment pointers
    ADD rdx, 8
    ADD r8, 8
    ADD r9, 8

    DEC rcx                ; Decrement counter
    JNZ sdotproduct        ; Repeat until rcx is zero

done:
    ret