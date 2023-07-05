#include "../../inc/assembler/handler.hpp"
#include "../../misc/parser.tab.hh"

void Handler::debagovanje(std::string str)
{
  cout << str << endl;
}

void Handler::handle_identifier(std::string ident)
{
  std::cout << "Identifikator je: " << ident <<", sa duzinom od: " << ident.length() << "\n";
}

void Handler::handle_hex_literal(int lit)
{
  cout<< "Vrednost literala je: " << lit << " cija je heksadecimalna reprezentacija: " << hex << lit << "\n";
}

void Handler::global_directive(std::vector<std::string> symbol_name_list){
  // cout << "Sa global direktivom su definisani sledeci simboli: ";
  //   for(int i=0; i<symbol_name_list.size(); i++){
  //       cout << symbol_name_list[i];
  //       cout << " ";
  //   }
  //   cout << "\n";
  if(Assembler::secondPass) {
    as.globalDirectiveSecondPass(symbol_name_list);
  }
}

void Handler::extern_directive(std::vector<std::string> symbol_name_list)
{
  // cout << "Sa extern direktivom su definisani sledeci simboli: ";
  //   for(int i=0; i<symbol_name_list.size(); i++){
  //       cout << symbol_name_list[i];
  //       cout << " ";
  //   }
  //   cout << "\n";
  if(!Assembler::secondPass){
    as.externDirectiveFirstPass(symbol_name_list);
  }
  else {
    as.externDirectiveSecondPass(symbol_name_list);
  }
}

void Handler::section_directive(std::string section_name)
{
  // cout << "Sa section direktivom otvorena je sekcija pod nazivom: " << section_name << "\n";
  if(!Assembler::secondPass){
    as.sectionDirectiveFirstPass(section_name);
  }
  else {
    as.sectionDirectiveSecondPass(section_name);
  }
}

void Handler::word_directive(std::vector<std::string> symbol_name_list, std::vector<int> literal_value_list, std::vector<int> kind_list)
{
  // cout << "Sadrzaj koji ce biti popunjen sa word direktivom je sledeci: ";
  //   int m=0, n=0;
  //   for(int i=0; i<kind_list.size(); i++){
  //       if(kind_list[i]==0){
  //           cout << symbol_name_list[m];
  //           cout << " ";
  //           m++;
  //       }
  //       else{
  //           cout << literal_value_list[n];
  //           cout << " ";
  //           n++;
  //       }
  //   }
  //   cout << "\n";
  if(!Assembler::secondPass){
    as.wordDirectiveFirstPass(symbol_name_list, literal_value_list, kind_list);
  }
  else{
    as.wordDirectiveSecondPass(symbol_name_list, literal_value_list, kind_list);
  }
}

void Handler::skip_directive(int literal)
{
  // cout << "Sa skip direktivom preskoceno je: 0x" << hex << literal << " bajtova.\n";
  if(!Assembler::secondPass){
    as.skipDirectiveFirstPass(literal);
  }
  else{
    as.skipDirectiveSecondPass(literal);
  }
}

void Handler::end_directive()
{
  // cout << "Upotrebljena je direktiva .end\n";
  if(!Assembler::secondPass){
    as.endDirectiveFirstPass();
  }
  else{
    as.endDirectiveSecondPass();
  }
}

void Handler::halt_instruction_handler()
{
  // cout << "Pozvana je naredba HALT.\n";
  if(!Assembler::secondPass){
    as.allInstructionFirstPass();
  }
  else {
    as.haltInstructionSecondPass();
  }
}

void Handler::int_instruction_handler()
{
  // cout << "Pozvana je naredba INT.\n";
  if(!Assembler::secondPass){
    as.allInstructionFirstPass();
  }
  else {
    as.intInstructionSecondPass();
  }
}

void Handler::iret_instruction_handler()
{
  // cout << "Pozvana je naredba IRET.\n";
  if(!Assembler::secondPass){
    as.allInstructionFirstPass();
    as.iretInstructionFirstPass();
  }
  else {
    as.iretInstructionSecondPass();
  }
}

void Handler::call_command_handler(std::string operand, int symbol_or_literal)
{
    // int literal;
    // if(symbol_or_literal){
    //     literal=std::stoul(operand);
    // }
    // cout << "Pozvana je naredba call cija je odredisna adresa odredjena sa: " << operand << " i " << hex << literal <<"\n";
  if(!Assembler::secondPass){
    as.callCommandFirstPass(operand, symbol_or_literal);
    as.allInstructionFirstPass();
  }
  else {
    as.callCommandSecondPass(operand, symbol_or_literal);
  }
}

void Handler::jmp_command_handler(std::string operand, int symbol_or_literal)
{
  // int literal;
  //   if(symbol_or_literal){
  //       literal=std::stoul(operand);
  //   }
  //   cout << "Pozvana je naredba jmp cija je odredisna adresa odredjena sa: " << operand << " i " << hex << literal <<"\n";
  if(!Assembler::secondPass){
    as.jmpCommandFirstPass(operand, symbol_or_literal);
    as.allInstructionFirstPass();
  }
  else{
    as.jmpCommandSecondPass(operand, symbol_or_literal);
  }
}

void Handler::beq_command_handler(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal)
{
  // int literal;
  //   if(symbol_or_literal){
  //       literal=std::stoul(operand);
  //   }
  //   cout << "Pozvana je naredba BEQ ciji su registri: " << gpr1 << " i " << gpr2 << " i cija je odredisna adresa odredjena sa: " << operand << " i " << hex << literal <<"\n";
  if(!Assembler::secondPass){
    as.beqCommandFirstPass(gpr1, gpr2, operand, symbol_or_literal);
    as.allInstructionFirstPass();
  }
  else{
    as.beqCommandSecondPass(gpr1, gpr2, operand, symbol_or_literal);
  }
}

void Handler::bne_command_handler(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal)
{
  // int literal;
  //   if(symbol_or_literal){
  //       literal=std::stoul(operand);
  //   }
  //   cout << "Pozvana je naredba BNE ciji su registri: " << gpr1 << " i " << gpr2 << " i cija je odredisna adresa odredjena sa: " << operand << " i " << hex << literal <<"\n";
  if(!Assembler::secondPass){
    as.bneCommandFirstPass(gpr1, gpr2, operand, symbol_or_literal);
    as.allInstructionFirstPass();
  }
  else{
    as.bneCommandSecondPass(gpr1, gpr2, operand, symbol_or_literal);
  }
}

void Handler::bgt_command_handler(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal)
{
  // int literal;
  //   if(symbol_or_literal){
  //       literal=std::stoul(operand);
  //   }
  //   cout << "Pozvana je naredba BGT ciji su registri: " << gpr1 << " i " << gpr2 << " i cija je odredisna adresa odredjena sa: " << operand << " i " << hex << literal <<"\n";
  if(!Assembler::secondPass){
    as.bgtCommandFirstPass(gpr1, gpr2, operand, symbol_or_literal);
    as.allInstructionFirstPass();
  }
  else{
    as.bgtCommandSecondPass(gpr1, gpr2, operand, symbol_or_literal);
  }
}

void Handler::push_command_handler(std::string gpr1)
{
  // cout << "Pozvana je naredba PUSH ciji je registar: " << gpr1 <<"\n";
  if(!Assembler::secondPass){
    as.allInstructionFirstPass();
  }
  else{
    as.pushCommandSecondPass(gpr1);
  }
}

void Handler::pop_command_handler(std::string gpr1)
{
  // cout << "Pozvana je naredba POP ciji je registar: " << gpr1 <<"\n";
  if(!Assembler::secondPass){
    as.allInstructionFirstPass();
  }
  else{
    as.popCommandSecondPass(gpr1);
  }
}

void Handler::not_command_handler(std::string gpr1)
{
  // cout << "Pozvana je naredba NOT ciji je registar: " << gpr1 <<"\n";
  if(!Assembler::secondPass){
    as.allInstructionFirstPass();
  }
  else{
    as.notCommandSecondPass(gpr1);
  }
}

void Handler::xchg_command_handler(std::string gpr1, std::string gpr2)
{
  // cout << "Pozvana je naredba XCHG ciji su registri: " << gpr1 << " i " << gpr2 << "\n";
  if(!Assembler::secondPass){
    as.allInstructionFirstPass();
  }
  else{
    as.xchgCommandSecondPass(gpr1, gpr2);
  }
}

void Handler::add_command_handler(std::string gpr1, std::string gpr2)
{
  // cout << "Pozvana je naredba ADD ciji su registri: " << gpr1 << " i " << gpr2 << "\n";
  if(!Assembler::secondPass){
    as.allInstructionFirstPass();
  }
  else{
    as.addCommandSecondPass(gpr1, gpr2);
  }
}

void Handler::sub_command_handler(std::string gpr1, std::string gpr2)
{
  // cout << "Pozvana je naredba SUB ciji su registri: " << gpr1 << " i " << gpr2 << "\n";
  if(!Assembler::secondPass){
    as.allInstructionFirstPass();
  }
  else{
    as.subCommandSecondPass(gpr1, gpr2);
  }
}

void Handler::mul_command_handler(std::string gpr1, std::string gpr2)
{
  // cout << "Pozvana je naredba MUL ciji su registri: " << gpr1 << " i " << gpr2 << "\n";
  if(!Assembler::secondPass){
    as.allInstructionFirstPass();
  }
  else{
    as.mulCommandSecondPass(gpr1, gpr2);
  }
}

void Handler::div_command_handler(std::string gpr1, std::string gpr2)
{
  // cout << "Pozvana je naredba DIV ciji su registri: " << gpr1 << " i " << gpr2 << "\n";
  if(!Assembler::secondPass){
    as.allInstructionFirstPass();
  }
  else{
    as.divCommandSecondPass(gpr1, gpr2);
  }
}

void Handler::and_command_handler(std::string gpr1, std::string gpr2)
{
  // cout << "Pozvana je naredba AND ciji su registri: " << gpr1 << " i " << gpr2 << "\n";
  if(!Assembler::secondPass){
    as.allInstructionFirstPass();
  }
  else{
    as.andCommandSecondPass(gpr1, gpr2);
  }
}

void Handler::or_command_handler(std::string gpr1, std::string gpr2)
{
  // cout << "Pozvana je naredba OR ciji su registri: " << gpr1 << " i " << gpr2 << "\n";
  if(!Assembler::secondPass){
    as.allInstructionFirstPass();
  }
  else{
    as.orCommandSecondPass(gpr1, gpr2);
  }
}

void Handler::xor_command_handler(std::string gpr1, std::string gpr2)
{
  // cout << "Pozvana je naredba XOR ciji su registri: " << gpr1 << " i " << gpr2 << "\n";
  if(!Assembler::secondPass){
    as.allInstructionFirstPass();
  }
  else{
    as.xorCommandSecondPass(gpr1, gpr2);
  }
}

void Handler::shl_command_handler(std::string gpr1, std::string gpr2)
{
  // cout << "Pozvana je naredba SHL ciji su registri: " << gpr1 << " i " << gpr2 << "\n";
  if(!Assembler::secondPass){
    as.allInstructionFirstPass();
  }
  else{
    as.shlCommandSecondPass(gpr1, gpr2);
  }
}

void Handler::shr_command_handler(std::string gpr1, std::string gpr2)
{
  // cout << "Pozvana je naredba SHR ciji su registri: " << gpr1 << " i " << gpr2 << "\n";
  if(!Assembler::secondPass){
    as.allInstructionFirstPass();
  }
  else{
    as.shrCommandSecondPass(gpr1, gpr2);
  }
}

void Handler::csrrd_command_handler(std::string csr, std::string gpr1)
{
  // cout << "Pozvana je naredba CSRRD ciji su registri: " << csr << " i " << gpr1 << "\n";
  if(!Assembler::secondPass){
    as.allInstructionFirstPass();
  }
  else{
    as.csrrdCommandSecondPass(csr,gpr1);
  }
}

void Handler::csrwr_command_handler(std::string gpr1, std::string csr)
{
  // cout << "Pozvana je naredba CSRWR ciji su registri: " << gpr1 << " i " << csr << "\n";
  if(!Assembler::secondPass){
    as.allInstructionFirstPass();
  }
  else{
    as.csrwrCommandSecondPass(gpr1, csr);
  }
}

void Handler::ld_command_handler(std::string operand1, std::string operand2, int operand_data_way, std::string general_register)
{
    // cout << "Pozvana je naredba ld sa argumentima operand1:"<<operand1<<" ,operand2:"<<operand2<<" ,nacin dohvatanja podatka:"<<operand_data_way<<" ,registar:"<<general_register<<"\n";
  if(!Assembler::secondPass){
    as.ldCommandFirstPass(operand1, operand2, operand_data_way, general_register);
    as.allInstructionFirstPass();
  }
  else{
    as.ldCommandSecondPass(operand1, operand2, operand_data_way, general_register);
  }
}

void Handler::st_command_handler(std::string operand1, std::string operand2, int operand_data_way, std::string general_register)
{
  if(!Assembler::secondPass){
    as.stCommandFirstPass(operand1, operand2, operand_data_way, general_register);
    as.allInstructionFirstPass();
  }
  else{
    as.stCommandSecondPass(operand1, operand2, operand_data_way, general_register);
  }
}

void Handler::ret_instruction_handler()
{
  // cout << "Pozvana je naredba RET.\n";
  if(!Assembler::secondPass){
    as.allInstructionFirstPass();
  }
  else{
    as.retInstructionSecondPass();
  }
}

void Handler::label_handler(std::string symbol_label)
{
  // cout << "Definisan je symbol uz pomoc LABEL cije je ime: " << symbol_label << "\n";
  if(!Assembler::secondPass){
    as.labelFirstPass(symbol_label);
  }
  else{
    as.labelSecondPass(symbol_label);
  }
}
