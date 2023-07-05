.global a c
.extern b
.section .text
jmp a
jmp e
jmp b
jmp d
d: .word d
#st %r1, b
ld c, %r1
#st %r1, e
.section .data
.skip 8
e: .word a
.word c
.word .bss
a: .word b
.section .bss
c: .skip 8
.end
