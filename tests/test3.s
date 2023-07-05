.section .text
.global startTest

startTest:
    ld $7, %r1         
    ld $1, %r2 
    ld $1, %r3         

calculate_factorial:
    beq %r1, %r3, end_calculation        

    mul %r1, %r2      
    sub %r3, %r1     

    jmp calculate_factorial

end_calculation:

    ld %r2, %r7

.end
