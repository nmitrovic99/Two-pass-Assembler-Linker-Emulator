.extern my_counter
.global handler
.global term_out
.global term_in
.global ascii_code
.section my_code_handler
handler:
 push %r1
 push %r2
term_out:
 csrrd %cause, %r1
 ld $2, %r2
 beq %r1, %r2, my_isr_timer
term_in:
 ld $3, %r2
ascii_code:
 beq %r1, %r2, my_isr_terminal
# obrada prekida od tajmera
my_isr_timer:
 ld $ascii_code , %r1
 st %r1, term_out
 jmp finish
# obrada prekida od terminala
my_isr_terminal:
 ld term_in, %r1
 st %r1, term_out
 ld my_counter, %r1
 ld $1, %r2
 add %r2, %r1
 st %r1, my_counter
finish:
 pop %r2
 pop %r1
 iret
.end
