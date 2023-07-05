#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

#include "symbol.hpp"
#include "section.hpp"
#include "relocationRecord.hpp"
#include "literalPool.hpp"

using namespace std;


class Assembler {
  public:
    Assembler();
    static bool secondPass;
    static int proba;

    static std::list<Symbol> symbolTable;
    void addToSymbolTable(Symbol symbol);
    void writeSymbolTable(const std::string& outputFileName);
    int getNdxInSymbolTable(std::string section_name);
    void setSizeForSymbol(std::string symbol_name, int size);
    int getSizeForSymbol(std::string symbol_name);
    int getNumForSymbol(std::string symbol_name);
    int getValueForSymbol(std::string symbol_name);
    std::string getNameForSymbol(int symbolId);
    void setBindForSymbol(std::string symbol_name, int bind);
    bool symbolExistInTable(std::string symbol_name);

    static std::list<Section> sectionList;
    void addToSectionList(Section section);
    void writeSectionList(const std::string& outputFileName);
    void setSizeForSection(std::string section_name, int size);
    int getSizeForSection(std::string section_name);
    void setSizeSecondPassForSection(std::string section_name, int size);
    int getSizeSecondPassForSection(std::string section_name);
    void setContentForSection(std::string section_name, std::string content);
    void addContentForSection(std::string section_name, std::string content);

    static std::list<RelocationRecord> relocationRecordList;
    void addToRelocationRecordList(RelocationRecord relocationRecord);
    void writeRelocationRecordList(const std::string& outputFileName);
    void insertToRelocationTableForR32(std::string symbol);

    static std::list<LiteralPool> literalPoolList;
    void addToLiteralPoolList(LiteralPool literalPool);
    void writeLiteralPoolList();
    void fillLiteralPool();
    std::string getAddressForLiteral(std::string lit, std::string sect);
    void fillSectionWithContentFromLiteralPool();
    bool existValueAndSectionInLiteralPool(std::string value, std::string section);

    // void setSecondPass();
    // bool getSecondPass();
    
    void sectionDirectiveFirstPass(std::string section_name);
    void sectionDirectiveSecondPass(std::string section_name);
    void wordDirectiveFirstPass(std::vector<std::string> symbol_name_list, std::vector<int> literal_list, std::vector<int> kind_list);
    void wordDirectiveSecondPass(std::vector<std::string> symbol_name_list, std::vector<int> literal_list, std::vector<int> kind_list);
    void externDirectiveFirstPass(std::vector<std::string> symbol_name_list);
    void externDirectiveSecondPass(std::vector<std::string> symbol_name_list);
    void skipDirectiveFirstPass(int literal);
    void skipDirectiveSecondPass(int literal);
    void globalDirectiveSecondPass(std::vector<std::string> symbol_name_list);
    void endDirectiveFirstPass();
    void endDirectiveSecondPass();
    void labelFirstPass(std::string symbol_label);
    void labelSecondPass(std::string symbol_label);
    void allInstructionFirstPass();
    void haltInstructionSecondPass();
    void intInstructionSecondPass();
    void iretInstructionSecondPass();
    void retInstructionSecondPass();
    void callCommandSecondPass(std::string operand, int symbol_or_literal);
    void jmpCommandSecondPass(std::string operand, int symbol_or_literal);
    void beqCommandSecondPass(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal);
    void bneCommandSecondPass(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal);
    void bgtCommandSecondPass(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal);
    void xchgCommandSecondPass(std::string gpr1, std::string gpr2);
    void addCommandSecondPass(std::string gpr1, std::string gpr2);
    void subCommandSecondPass(std::string gpr1, std::string gpr2);
    void mulCommandSecondPass(std::string gpr1, std::string gpr2);
    void divCommandSecondPass(std::string gpr1, std::string gpr2);
    void notCommandSecondPass(std::string gpr1);
    void andCommandSecondPass(std::string gpr1, std::string gpr2);
    void orCommandSecondPass(std::string gpr1, std::string gpr2);
    void xorCommandSecondPass(std::string gpr1, std::string gpr2);
    void shlCommandSecondPass(std::string gpr1, std::string gpr2);
    void shrCommandSecondPass(std::string gpr1, std::string gpr2);
    void pushCommandSecondPass(std::string gpr1);
    void popCommandSecondPass(std::string gpr1);
    void ldCommandSecondPass(std::string operand1, std::string operand2, int operand_data_way, std::string general_register);
    void stCommandSecondPass(std::string operand1, std::string operand2, int operand_data_way, std::string general_register);
    void csrrdCommandSecondPass(std::string csr, std::string gpr1);
    void csrwrCommandSecondPass(std::string gpr1, std::string csr);
    void ldCommandFirstPass(std::string operand1, std::string operand2, int operand_data_way, std::string general_register);
    void stCommandFirstPass(std::string operand1, std::string operand2, int operand_data_way, std::string general_register);
    void callCommandFirstPass(std::string operand, int symbol_or_literal);
    void jmpCommandFirstPass(std::string operand, int symbol_or_literal);
    void beqCommandFirstPass(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal);
    void bneCommandFirstPass(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal);
    void bgtCommandFirstPass(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal);
    void iretInstructionFirstPass();

  private:
    int locationCounter;
    int numOfSymbols;
    string currentSection;
    void wordDirectiveSymbol(std::string symbol);
    void wordDirectiveLiteral(int literal);
    std::string stringToLittleEndian(std::string literal);
    std::string convertIntToHexString(int intValue);
    std::string convertIntToHexStringWidth8(int intValue);
    std::string convertIntToHexStringWidth3(int intValue);
    int convertHexStringToInt(std::string hexValue);
    std::string offsetForJumpInstructions(std::string operand, int symbol_or_literal);
    int getNumberForRegister(std::string reg);
    int getNumberForCsrRegister(std::string reg);
    std::string offsetForDataInstructionsForSymbol(std::string operand);
    

};



#endif