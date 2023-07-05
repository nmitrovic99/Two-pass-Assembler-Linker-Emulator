#identiiti
#0xf032a
.section .text
.global labela3
.extern extern111 extern222
labela2:
.global labela1 labela0
#.word labela1 labela4 0x15 0xfff labela2 0x0
#.skip 50
call labela0
call 0x110110
ld $0xf32, %r2
st %r3, labela0
ld $0xff22, %r12
labela0:
.section sekcija1
labela3:
ld 0xff34, %r11
st %r8, [%r13]
labela1:
ld [%r7+0x32c2], %r10
ld [%r7+labela4], %r14
labela5:
ld labela3, %r5
.section .text
labela4:
ld $labela0, %r6
ld $0xff22, %r9
ld [%r2], %r10
.section sekcija2
ld 0xabc, %r3
st %r9, [%r1+0x33333]
ld %r6, %r8

#               sub
.end
