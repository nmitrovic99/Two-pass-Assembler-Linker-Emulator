#ifndef HANDLER_H_
#define HANDLER_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "assembler.hpp"

using namespace std;

    class Handler{

    public:
        void debagovanje(std::string str);
        void handle_identifier(std::string ident);
        void handle_hex_literal(int lit);
        void global_directive(std::vector<std::string> symbol_name_list);
        void extern_directive(std::vector<std::string> symbol_name_list);
        void section_directive(std::string section_name);
        void word_directive(std::vector<std::string> symbol_name_list, std::vector<int> literal_value_list, std::vector<int> kind_list);
        void skip_directive(int literal);
        void end_directive();
        void halt_instruction_handler();
        void int_instruction_handler();
        void iret_instruction_handler();
        void call_command_handler(std::string operand, int symbol_or_literal);
        void jmp_command_handler(std::string operand, int symbol_or_literal);
        void beq_command_handler(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal);
        void bne_command_handler(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal);
        void bgt_command_handler(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal);
        void push_command_handler(std::string gpr1);
        void pop_command_handler(std::string gpr1);
        void not_command_handler(std::string gpr1);
        void xchg_command_handler(std::string gpr1, std::string gpr2);
        void add_command_handler(std::string gpr1, std::string gpr2);
        void sub_command_handler(std::string gpr1, std::string gpr2);
        void mul_command_handler(std::string gpr1, std::string gpr2);
        void div_command_handler(std::string gpr1, std::string gpr2);
        void and_command_handler(std::string gpr1, std::string gpr2);
        void or_command_handler(std::string gpr1, std::string gpr2);
        void xor_command_handler(std::string gpr1, std::string gpr2);
        void shl_command_handler(std::string gpr1, std::string gpr2);
        void shr_command_handler(std::string gpr1, std::string gpr2);
        void csrrd_command_handler(std::string csr, std::string gpr1);
        void csrwr_command_handler(std::string gpr1, std::string csr);
        void ld_command_handler(std::string operand1, std::string operand2, int operand_data_way, std::string general_register);
        void st_command_handler(std::string operand1, std::string operand2, int operand_data_way, std::string general_register);
        void ret_instruction_handler();
        void label_handler(std::string symbol_label);

    private:
        Assembler as;

    };

        // void handle_identifier(std::string ident);
        // void handle_hex_literal(unsigned long int lit);
        // // void global_directive(std::vector<std::string> symbol_name_list);
        // void extern_directive(std::vector<std::string> symbol_name_list);
        // void section_directive(std::string section_name);
        // void word_directive(std::vector<std::string> symbol_name_list, std::vector<unsigned long int> literal_value_list, std::vector<int> kind_list);
        // void skip_directive(unsigned long int literal);
        // void end_directive();
        // void halt_instruction_handler();
        // void int_instruction_handler();
        // void iret_instruction_handler();
        // void call_command_handler(std::string operand, int symbol_or_literal);
        // void jmp_command_handler(std::string operand, int symbol_or_literal);
        // void beq_command_handler(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal);
        // void bne_command_handler(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal);
        // void bgt_command_handler(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal);
        // void push_command_handler(std::string gpr1);
        // void pop_command_handler(std::string gpr1);
        // void not_command_handler(std::string gpr1);
        // void xchg_command_handler(std::string gpr1, std::string gpr2);
        // void add_command_handler(std::string gpr1, std::string gpr2);
        // void sub_command_handler(std::string gpr1, std::string gpr2);
        // void mul_command_handler(std::string gpr1, std::string gpr2);
        // void div_command_handler(std::string gpr1, std::string gpr2);
        // void and_command_handler(std::string gpr1, std::string gpr2);
        // void or_command_handler(std::string gpr1, std::string gpr2);
        // void xor_command_handler(std::string gpr1, std::string gpr2);
        // void shl_command_handler(std::string gpr1, std::string gpr2);
        // void shr_command_handler(std::string gpr1, std::string gpr2);
        // void csrrd_command_handler(std::string csr, std::string gpr1);
        // void csrwr_command_handler(std::string gpr1, std::string csr);
        // void ld_command_handler(std::string operand1, std::string operand2, int operand_data_way, std::string general_register);
        // void ret_instruction_handler();
        // void label_handler(std::string symbol_label);

#endif