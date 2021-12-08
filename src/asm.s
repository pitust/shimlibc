global setjmp
global longjmp

setjmp:
    mov [0 + rdi], rbx
    mov [8 + rdi], rbp
    mov [16 + rdi], r12
    mov [24 + rdi], r13
    mov [32 + rdi], r14
    mov [40 + rdi], r15
    lea rax, [8 + rsp]
    mov [48 + rdi], rax
    mov rax, [rsp]
    mov [56 + rdi], rax
    mov rax, 0
    ret

longjmp:
    mov rax, rsi
    mov rbp, [8 + rdi]
    mov rsp, [48 + rdi]
    push QWORD [56 + rdi]
    mov rbx, [0 + rdi]
    mov r12, [16 + rdi]
    mov r13, [24 + rdi]
    mov r14, [32 + rdi]
    mov r15, [40 + rdi]
    ret
