%{
#include "parser.tab.hh"
%}

%option noyywrap
%option yylineno

%%
[ \t]+    /* ignorisi space i tabulaciju */
#(.)*               /* ignorisi jednolinijske komentare */
\n                            { return END_OF_LINE; }

\.global                        { return GLOBAL; }
\.extern                        { return EXTERN; }
\.section                       { return SECTION; }
\.word                          { return WORD; }
\.skip                          { return SKIP; }
\.end                           { return END; }
\%status                          { return STATUS; }
\%handler                         { return HANDLER; }
\%cause                           { return CAUSE; }
halt                            { return HALT; }
int                             { return INT; }
iret                            { return IRET; }
call                            { return CALL; }
ret                             { return RET; }
jmp                             { return JMP; }
beq                             { return BEQ; }
bne                             { return BNE; }
bgt                             { return BGT; }
push                            { return PUSH; }
pop                             { return POP; }
xchg                            { return XCHG; }
add                             { return ADD; }
sub                             { return SUB; }
mul                             { return MUL; }
div                             { return DIV; }
not                             { return NOT; }
and                             { return AND; }
or                              { return OR; }
xor                             { return XOR; }
shl                             { return SHL; }
shr                             { return SHR; }
ld                              { return LD; }
st                              { return ST; }
csrrd                           { return CSRRD; }
csrwr                           { return CSRWR; }
\%r0                              { return R0; }
\%r1                              { return R1; }
\%r2                              { return R2; }
\%r3                              { return R3; }
\%r4                              { return R4; }
\%r5                              { return R5; }
\%r6                              { return R6; }
\%r7                              { return R7; }
\%r8                              { return R8; }
\%r9                              { return R9; }
\%r10                             { return R10; }
\%r11                             { return R11; }
\%r12                             { return R12; }
\%r13                             { return R13; }
\%r14                             { return R14; }
\%r15                             { return R15; }
\%pc                              { return PC; }
\%sp                              { return SP; }
[a-zA-Z_][a-zA-Z0-9_]*          { yylval.strval = strdup(yytext); return IDENTIFIER; }
0x[0-9A-Fa-f]+                  { yylval.hexval = strtol(yytext+2, NULL, 16); return HEX_LITERAL; }
[0-9]+                  { yylval.hexval = strtol(yytext, NULL, 10); return HEX_LITERAL; }
\$                               { return OFFSET; }
\+                               { return PLUS; }
\[                               { return LEFT_SQUARE; }
\]                               { return RIGHT_SQUARE; }
:                               { return COLON; }
,                               { return COMMA; }
\.                              { return POINT; }
.                               { return MOV; }

%%



//$0x[0-9A-Fa-f]+                 { return OFFSET_HEX_LITERAL; }
//$[a-zA-Z_][a-zA-Z0-9_]*         { return OFFSET_SIMBOL; }
/* .|\n                            { return *yytext; }    */
//mov                             { return MOV; }
//add                             { return ADD; }
//sub                             { return SUB; }
//jmp                             { return JMP; }
//cmp                             { return CMP; }
// #(.)*\n               /* ignorisi jednolinijske komentare */