%{
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "lex.yy.h"
#include "../inc/assembler/handler.hpp"

extern int yylineno;
void yyerror(const char *);
Handler h;
std::string symbol_name;
std::string symbol_value;
std::vector<std::string> symbol_name_list;
int literal;
int literal_value;
std::vector<int> literal_list;
std::vector<int> kind_list;
int symbol_or_literal;
int symbol_or_literal_value;
std::string gpr1, gpr2;
std::string csr;
int operand_data_way;
%}

%union {
    char *strval;
    int hexval;
}

%token <strval> IDENTIFIER
%token <hexval> HEX_LITERAL

%start program

%token INSTRUCTION
%token DIRECTIVE
%token END_OF_LINE

%token MOV CMP

%token GLOBAL EXTERN SECTION WORD SKIP END STATUS HANDLER CAUSE HALT INT
%token IRET CALL RET JMP BEQ BNE BGT PUSH POP XCHG 
%token ADD SUB MUL DIV NOT AND OR XOR SHL SHR LD ST CSRRD CSRWR
%token R0 R1 R2 R3 R4 R5 R6 R7 R8 R9 R10 R11 R12 R13 R14 R15 PC SP 
%token COLON OFFSET COMMA LEFT_SQUARE RIGHT_SQUARE PLUS POINT

%%

program: assembler_program
    ;

assembler_program: one_assembler_line
    | assembler_program one_assembler_line
    ;

one_assembler_line: directive
    | instruction 
    | label END_OF_LINE 
    | label_directive 
    | label_instruction 
    | END_OF_LINE 
    ;

label_directive: label directive
    ;

label_instruction: label instruction
    ;

/*
directive: DIRECTIVE END_OF_LINE
    ;
    */

directive: global_directive END_OF_LINE
    |
    extern_directive END_OF_LINE
    |
    section_directive END_OF_LINE
    |
    word_directive END_OF_LINE
    |
    skip_directive END_OF_LINE
    |
    end_directive END_OF_LINE
    ;

global_directive: GLOBAL symbol_list { 
        h.global_directive(symbol_name_list);
        symbol_name_list.clear();
    }
    ;

extern_directive: EXTERN symbol_list { 
        h.extern_directive(symbol_name_list);
        symbol_name_list.clear();
    }
    ;

section_directive: SECTION symbol {
        h.section_directive(symbol_name);
    }
    | SECTION POINT symbol {
        h.section_directive("."+symbol_name);
    }
    ;

word_directive: WORD symbol_or_literal_list {
        h.word_directive(symbol_name_list, literal_list, kind_list);
        symbol_name_list.clear();
        literal_list.clear();
        kind_list.clear();
    }
    ;

skip_directive: SKIP literal {
        h.skip_directive(literal);
    }   
    ;

end_directive: END {
        h.end_directive();
        //YYACCEPT;
    }
    ;

/*
instruction: INSTRUCTION END_OF_LINE
    ;
    */

instruction: halt_instruction END_OF_LINE
           | int_instruction END_OF_LINE
           | iret_instruction END_OF_LINE
           | call_command END_OF_LINE
           | jmp_command END_OF_LINE
           | beq_command END_OF_LINE
           | bne_command END_OF_LINE
           | bgt_command END_OF_LINE
           | push_command END_OF_LINE
           | pop_command END_OF_LINE
           | xchg_command END_OF_LINE
           | add_command END_OF_LINE
           | sub_command END_OF_LINE
           | mul_command END_OF_LINE
           | div_command END_OF_LINE
           | and_command END_OF_LINE
           | or_command END_OF_LINE
           | xor_command END_OF_LINE
           | shl_command END_OF_LINE
           | shr_command END_OF_LINE
           | not_command END_OF_LINE
           | csrrd_command END_OF_LINE
           | csrwr_command END_OF_LINE
           | ld_command END_OF_LINE
           | st_command END_OF_LINE
           | ret_instruction END_OF_LINE 
           ;

halt_instruction: HALT { h.halt_instruction_handler(); }
    ;

int_instruction: INT { h.int_instruction_handler(); }
    ;

iret_instruction: IRET { h.iret_instruction_handler(); }
    ;

call_command: CALL operand_destination_adress {
        if(symbol_or_literal==0){
            h.call_command_handler(symbol_name, symbol_or_literal);
        }
        else{
            std::stringstream ss;
            ss << std::hex << literal;
            h.call_command_handler(ss.str(), symbol_or_literal);
            gpr1=""; gpr2="";
            //h.call_command_handler(std::to_string(literal), symbol_or_literal);
        }
        
    }
    ;

jmp_command: JMP operand_destination_adress {
        if(symbol_or_literal==0){
            h.jmp_command_handler(symbol_name, symbol_or_literal);
        }
        else{
            std::stringstream ss;
            ss << std::hex << literal;
            h.jmp_command_handler(ss.str(), symbol_or_literal);
            gpr1=""; gpr2="";
            //h.jmp_command_handler(std::to_string(literal), symbol_or_literal);
        }
        
    }
    ;

beq_command: BEQ general_registers COMMA general_registers COMMA operand_destination_adress {
        if(symbol_or_literal==0){
            h.beq_command_handler(gpr1, gpr2, symbol_name, symbol_or_literal);
        }
        else{
            std::stringstream ss;
            ss << std::hex << literal;
            h.beq_command_handler(gpr1, gpr2, ss.str(), symbol_or_literal);
            gpr1=""; gpr2="";
            //h.beq_command_handler(gpr1, gpr2, std::to_string(literal), symbol_or_literal);
        }
        gpr1="";
        gpr2="";
    }
    ;

bne_command: BNE general_registers COMMA general_registers COMMA operand_destination_adress {
        if(symbol_or_literal==0){
            h.bne_command_handler(gpr1, gpr2, symbol_name, symbol_or_literal);
        }
        else{
            std::stringstream ss;
            ss << std::hex << literal;
            h.bne_command_handler(gpr1, gpr2, ss.str(), symbol_or_literal);
            gpr1=""; gpr2="";
            //h.bne_command_handler(gpr1, gpr2, std::to_string(literal), symbol_or_literal);
        }
        gpr1="";
        gpr2="";
    }
    ;

bgt_command: BGT general_registers COMMA general_registers COMMA operand_destination_adress {
        if(symbol_or_literal==0){
            h.bgt_command_handler(gpr1, gpr2, symbol_name, symbol_or_literal);
        }
        else{
            std::stringstream ss;
            ss << std::hex << literal;
            h.bgt_command_handler(gpr1, gpr2, ss.str(), symbol_or_literal);
            gpr1=""; gpr2="";
            //h.bgt_command_handler(gpr1, gpr2, std::to_string(literal), symbol_or_literal);
        }
        gpr1="";
        gpr2="";
    }
    ;

push_command: PUSH general_registers {
        h.push_command_handler(gpr1);
        gpr1="";
    }
    ;

pop_command: POP general_registers {
        h.pop_command_handler(gpr1);
        gpr1="";
    }
    | POP control_and_status_registers {
        h.pop_command_handler(csr);
        csr="";
    }
    ;

not_command: NOT general_registers {
        h.not_command_handler(gpr1);
        gpr1="";
    }
    ;

xchg_command: XCHG general_registers COMMA general_registers {
        h.xchg_command_handler(gpr1, gpr2);
        gpr1="";
        gpr2="";
    }
    ;  

add_command: ADD general_registers COMMA general_registers {
        h.add_command_handler(gpr1, gpr2);
        gpr1="";
        gpr2="";
    }
    ; 

sub_command: SUB general_registers COMMA general_registers {
        h.sub_command_handler(gpr1, gpr2);
        gpr1="";
        gpr2="";
    }
    ; 

mul_command: MUL general_registers COMMA general_registers {
        h.mul_command_handler(gpr1, gpr2);
        gpr1="";
        gpr2="";
    }
    ; 

div_command: DIV general_registers COMMA general_registers {
        h.div_command_handler(gpr1, gpr2);
        gpr1="";
        gpr2="";
    }
    ; 

and_command: AND general_registers COMMA general_registers {
        h.and_command_handler(gpr1, gpr2);
        gpr1="";
        gpr2="";
    }
    ; 

or_command: OR general_registers COMMA general_registers {
        h.or_command_handler(gpr1, gpr2);
        gpr1="";
        gpr2="";
    }
    ; 

xor_command: XOR general_registers COMMA general_registers {
        h.xor_command_handler(gpr1, gpr2);
        gpr1="";
        gpr2="";
    }
    ; 

shl_command: SHL general_registers COMMA general_registers {
        h.shl_command_handler(gpr1, gpr2);
        gpr1="";
        gpr2="";
    }
    ; 

shr_command: SHR general_registers COMMA general_registers {
        h.shr_command_handler(gpr1, gpr2);
        gpr1="";
        gpr2="";
    }
    ;   

csrrd_command: CSRRD control_and_status_registers COMMA general_registers {
        h.csrrd_command_handler(csr, gpr1);
        gpr1="";
    }
    ;

csrwr_command: CSRWR general_registers COMMA control_and_status_registers {
        h.csrwr_command_handler(gpr1, csr);
        gpr1="";
    }
    ;

ld_command: LD operand_data COMMA general_registers {
        if(operand_data_way==0) {
            h.ld_command_handler(symbol_name, "", operand_data_way, gpr1);
            gpr1=""; gpr2="";
        }
        else if(operand_data_way==1) {
            std::stringstream ss;
            ss << std::hex << literal;
            h.ld_command_handler(ss.str(), "", operand_data_way, gpr1);
            gpr1=""; gpr2="";
            //h.ld_command_handler(std::to_string(literal), "", operand_data_way, gpr1);
        }
        else if(operand_data_way==2) {
            h.ld_command_handler(symbol_name, "", operand_data_way, gpr1);
            gpr1=""; gpr2="";
        }
        else if(operand_data_way==3) {
            std::stringstream ss;
            ss << std::hex << literal;
            h.ld_command_handler(ss.str(), "", operand_data_way, gpr1);
            gpr1=""; gpr2="";
            //h.ld_command_handler(std::to_string(literal), "", operand_data_way, gpr1);
        }
        else if(operand_data_way==4) {
            h.ld_command_handler(gpr1, "", operand_data_way, gpr2);
            gpr1=""; gpr2="";
        }
        else if(operand_data_way==5) {
            h.ld_command_handler(gpr1, "", operand_data_way, gpr2);
            gpr1=""; gpr2="";
        }
        else if(operand_data_way==6) {
            std::stringstream ss;
            ss << std::hex << literal;
            h.ld_command_handler(gpr1, ss.str(), operand_data_way, gpr2);
            gpr1=""; gpr2="";
            //h.ld_command_handler(gpr1, std::to_string(literal), operand_data_way, gpr2);
        }
        else if(operand_data_way==7) {
            h.ld_command_handler(gpr1, symbol_name, operand_data_way, gpr2);
            gpr1=""; gpr2="";
        }
    }

st_command: ST general_registers COMMA operand_data {
        if(operand_data_way==0) {
            h.st_command_handler(symbol_name, "", operand_data_way, gpr1);
            gpr1=""; gpr2="";
        }
        else if(operand_data_way==1) {
            std::stringstream ss;
            ss << std::hex << literal;
            h.st_command_handler(ss.str(), "", operand_data_way, gpr1);
            gpr1=""; gpr2="";
            //h.st_command_handler(std::to_string(literal), "", operand_data_way, gpr1);
        }
        else if(operand_data_way==2) {
            h.st_command_handler(symbol_name, "", operand_data_way, gpr1);
            gpr1=""; gpr2="";
        }
        else if(operand_data_way==3) {
            std::stringstream ss;
            ss << std::hex << literal;
            h.st_command_handler(ss.str(), "", operand_data_way, gpr1);
            gpr1=""; gpr2="";
            //h.st_command_handler(std::to_string(literal), "", operand_data_way, gpr1);
        }
        else if(operand_data_way==4) {
            h.st_command_handler(gpr2, "", operand_data_way, gpr1);
            gpr1=""; gpr2="";
        }
        else if(operand_data_way==5) {
            h.st_command_handler(gpr2, "", operand_data_way, gpr1);
            gpr1=""; gpr2="";
        }
        else if(operand_data_way==6) {
            std::stringstream ss;
            ss << std::hex << literal;
            h.st_command_handler(gpr2, ss.str(), operand_data_way, gpr1);
            gpr1=""; gpr2="";
        }
        else if(operand_data_way==7) {
            h.st_command_handler(gpr2, symbol_name, operand_data_way, gpr1);
            gpr1=""; gpr2="";
        }
}

ret_instruction: RET { h.ret_instruction_handler(); }
    ;

symbol_or_literal_list: symbol_or_literal
    | symbol_or_literal_list COMMA symbol_or_literal
    ;

symbol_list: symbol
    {
        //symbol_name_list=$1;
        symbol_name_list.push_back(symbol_name);
    }
    | symbol_list COMMA symbol
    {
        //symbol_name_list=$1;
        symbol_name_list.push_back(symbol_name);
    }
    ;

/*
symbol_list:
    {
        //symbol_name_list=$1;
        //symbol_name_list.push_back(symbol_name);
        symbol_name_list.clear();
    }
    | symbol_list symbol
    {
        //symbol_name_list=$1;
        symbol_name_list.push_back(symbol_name);
    }
    ;
    */

symbol_or_literal: symbol { 
        symbol_name_list.push_back(symbol_name); 
        kind_list.push_back(0);
    }
    | POINT symbol { 
        symbol_name_list.push_back("."+symbol_name); 
        kind_list.push_back(0);
    }
    | literal { 
        literal_list.push_back(literal);
        kind_list.push_back(1); 
    }
    ;

operand_destination_adress: symbol {
        symbol_or_literal=0;
    }
    | literal {
        symbol_or_literal=1;
    }
    ;

operand_data: OFFSET symbol {
        operand_data_way=0;
    }
    | OFFSET literal {
        operand_data_way=1;
    }
    | symbol {
        operand_data_way=2;
    }
    | literal {
        operand_data_way=3;
    }
    | general_registers {
        operand_data_way=4;
    }
    | LEFT_SQUARE general_registers RIGHT_SQUARE {
        operand_data_way=5;
    }
    | LEFT_SQUARE general_registers PLUS literal RIGHT_SQUARE {
        operand_data_way=6;
    }
    | LEFT_SQUARE general_registers PLUS symbol RIGHT_SQUARE {
        operand_data_way=7;
    }
    ;

general_registers: R0 { if(gpr1=="") gpr1="r0"; else gpr2="r0"; }
    | R1 { if(gpr1=="") gpr1="r1"; else gpr2="r1"; }
    | R2 { if(gpr1=="") gpr1="r2"; else gpr2="r2"; }
    | R3 { if(gpr1=="") gpr1="r3"; else gpr2="r3"; }
    | R4 { if(gpr1=="") gpr1="r4"; else gpr2="r4"; }
    | R5 { if(gpr1=="") gpr1="r5"; else gpr2="r5"; }
    | R6 { if(gpr1=="") gpr1="r6"; else gpr2="r6"; }
    | R7 { if(gpr1=="") gpr1="r7"; else gpr2="r7"; }
    | R8 { if(gpr1=="") gpr1="r8"; else gpr2="r8"; }
    | R9 { if(gpr1=="") gpr1="r9"; else gpr2="r9"; }
    | R10 { if(gpr1=="") gpr1="r10"; else gpr2="r10"; }
    | R11 { if(gpr1=="") gpr1="r11"; else gpr2="r11"; }
    | R12 { if(gpr1=="") gpr1="r12"; else gpr2="r12"; }
    | R13 { if(gpr1=="") gpr1="r13"; else gpr2="r13"; }
    | R14 { if(gpr1=="") gpr1="r14"; else gpr2="r14"; }
    | R15 { if(gpr1=="") gpr1="r15"; else gpr2="r15"; }
    | SP { if(gpr1=="") gpr1="sp"; else gpr2="sp"; }
    | PC { if(gpr1=="") gpr1="pc"; else gpr2="pc"; }
    ;

control_and_status_registers: STATUS { csr="status"; }
    | HANDLER { csr="handler"; }
    | CAUSE { csr="cause"; }
    ;

label: symbol COLON { h.label_handler(symbol_name); }

symbol: IDENTIFIER {  symbol_name = yytext; }
        ;

literal: HEX_LITERAL { literal = $1; }

%%

void yyerror(const char *s) {
    std::cerr << "Parser error: " << s << " on line " << yylineno << std::endl;
}