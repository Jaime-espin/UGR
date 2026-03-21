section .data
    msg db "Hola, mundo!", 0xA  ; Mensaje con salto de línea
    len equ $ - msg             ; Longitud del mensaje

section .text
    global _start

_start:
    mov eax, 4          ; syscall: sys_write
    mov ebx, 1          ; file descriptor: stdout
    mov ecx, msg        ; puntero al mensaje
    mov edx, len        ; longitud del mensaje
    int 0x80            ; llamada al sistema

    mov eax, 1          ; syscall: sys_exit
    xor ebx, ebx        ; código de salida 0
    int 0x80            ; llamada al sistema