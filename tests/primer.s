#identiiti
#0xf032a
.section .text
push %r2
int
.global labela3
.extern extern111 extern222
ret
labela2:
ret
.global labela1
.word labela1 labela4 0x15 0xfff labela2 0x0
#.skip 50
iret
halt
call labela1
jmp extern222
beq %r1, %r2, extern111
bgt %r1, %r2, labela3
bne %r5, %r11, labela1
call labela3
call extern111
call labela5
labela1: #pop %r1
push %r9
xchg %r7, %r1
add %r3, %r5
sub %r12, %r7
mul %r1, %r11
div %r11, %r12
.section sekcija1
and %r2, %r1
labela3:
or %r2, %r1
labela5:
xor %r2, %r1
shl %r6, %r8
.section .text
shr %r10, %r15
labela4: 
not %r14
.section sekcija2
csrwr %r1, %handler
csrrd %cause, %r1
ld $0xf32, %r2
ld $0xff22, %r12
ld 0xff34, %r11
ld [%r7+0x32c], %r10
ld labela3, %r5
#               sub
.end
