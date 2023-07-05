#include "../../inc/assembler/assembler.hpp"

bool Assembler::secondPass = false;

std::list<Symbol> Assembler::symbolTable={Symbol(0, "UND", 0, 0, 0, 0)};

std::list<Section> Assembler::sectionList;

std::list<RelocationRecord> Assembler::relocationRecordList;

std::list<LiteralPool> Assembler::literalPoolList;

Assembler::Assembler()
{
  currentSection="";
  numOfSymbols=1;
  locationCounter=0;
  // Symbol undefinedSection(numOfSymbols, "UND", 0, 0, 0, 0);
  // numOfSymbols++;
  // symbolTable.push_back();
  // addToSymbolTable(undefinedSection);
}

void Assembler::addToSymbolTable(Symbol symbol)
{
  symbolTable.push_back(symbol);
}

void Assembler::writeSymbolTable(const std::string& outputFileName)
{
  std::ofstream outputFile(outputFileName);
  if(outputFile.is_open()){
    outputFile << "Symbol Table" << endl;
    outputFile << std::setw(20) << "Num" << std::setw(20) << "Value" << std::setw(20) << "Size" << std::setw(20) << "Bind"
    << std::setw(20) << "Ndx" << std::setw(20) << "Name" << std::endl;
    for (const auto& symbol : symbolTable) {
      outputFile << std::setw(20) << symbol.getNum() << std::setw(20) << convertIntToHexStringWidth8(symbol.getValue()) << std::setw(20) << symbol.getSize() << 
      std::setw(20) << (symbol.getBind()==0?"local":"global") << std::setw(20) << symbol.getNdx() << std::setw(20) << symbol.getName() << std::endl;
    }
    outputFile.close();
  }
  else{
    cout << "GRESKA: Neuspesno otvaranje fajla " + outputFileName + "!" << endl;
  }
  
}

int Assembler::getNdxInSymbolTable(std::string section_name)
{
  for(const auto& symbol:symbolTable) {
    if(symbol.getName()==section_name) {
      return symbol.getNdx();
    }
  }
  return -1;
}

void Assembler::setSizeForSymbol(std::string symbol_name, int size)
{
  for(auto& symbol:symbolTable) {
    if(symbol.getName()==symbol_name) {
      symbol.setSize(size);
    }
  }
}

int Assembler::getSizeForSymbol(std::string symbol_name)
{
  for(const auto& symbol:symbolTable) {
    if(symbol.getName()==symbol_name) {
      return symbol.getSize();
    }
  }
  return -1;
}

int Assembler::getNumForSymbol(std::string symbol_name)
{
  for(const auto& symbol:symbolTable) {
    if(symbol.getName()==symbol_name) {
      return symbol.getNum();
    }
  }
  return -1;
}

int Assembler::getValueForSymbol(std::string symbol_name)
{
  for(const auto& symbol:symbolTable) {
    if(symbol.getName()==symbol_name) {
      return symbol.getValue();
    }
  }
  return -1;
}

std::string Assembler::getNameForSymbol(int symbolId)
{
  for(const auto& symbol:symbolTable) {
    if(symbol.getNum()==symbolId) {
      return symbol.getName();
    }
  }
  return "";
}

void Assembler::setBindForSymbol(std::string symbol_name, int bind)
{
  for(auto& symbol:symbolTable) {
    if(symbol.getName()==symbol_name) {
      symbol.setBind(bind);
    }
  }
}

bool Assembler::symbolExistInTable(std::string symbol_name)
{
  for(auto& symbol:symbolTable) {
    if(symbol.getName()==symbol_name) {
      return true;
    }
  }
  return false;
}

void Assembler::addToSectionList(Section section)
{
  sectionList.push_back(section);
}

void Assembler::writeSectionList(const std::string& outputFileName)
{
  std::ofstream outputFile(outputFileName, std::ios::app);
  if(outputFile.is_open()){
    outputFile << endl;
    for (const auto& section : sectionList) {
      outputFile << "Section: " << section.getName() <<  "(" << section.getSize() << ")" << std::endl;
      int m=0, n=0, s=0;
      while(m<section.getContent().size()){
        outputFile<<section.getContent().at(m);
        m++;
        if(m<section.getContent().size()){
          outputFile<<section.getContent().at(m);
          m++;
        }
        outputFile<<" ";
        n=n+2;
        // s=s+2;
        // if(s==8){
        //   outputFile<<" ";
        //   s=0;
        // }
        if(n==16){
          outputFile<<"\n";
          n=0;
        }
      }
      if(n!=0){
        outputFile<<endl;
      }
    }
    outputFile.close();
  }
  else{
    cout << "GRESKA: Neuspesno otvaranje fajla " + outputFileName + "!" << endl;
  }
    // std::cout<<section.getContent()<<std::endl;
}

void Assembler::setSizeForSection(std::string section_name, int size)
{
  for(auto& section:sectionList) {
    if(section.getName()==section_name) {
      section.setSize(size);
    }
  }
}

void Assembler::setSizeSecondPassForSection(std::string section_name, int size)
{
  for(auto& section:sectionList) {
    if(section.getName()==section_name) {
      section.setSizeSecondPass(size);
    }
  }
}

int Assembler::getSizeForSection(std::string section_name)
{
  for(const auto& section:sectionList) {
    if(section.getName()==section_name) {
      return section.getSize();
    }
  }
  return -1;
}

int Assembler::getSizeSecondPassForSection(std::string section_name)
{
  for(const auto& section:sectionList) {
    if(section.getName()==section_name) {
      return section.getSizeSecondPass();
    }
  }
  return -1;
}

void Assembler::setContentForSection(std::string section_name, std::string content)
{
  Section* sec;
  for(auto& section:sectionList) {
    if(section.getName()==section_name) {
      sec=&section;
    }
  }
  std::string contentToAdd=sec->getContent()+content;
  sec->setContent(contentToAdd);
}

void Assembler::addToRelocationRecordList(RelocationRecord relocationRecord)
{
  relocationRecordList.push_back(relocationRecord);
}

void Assembler::writeRelocationRecordList(const std::string& outputFileName)
{
  std::ofstream outputFile(outputFileName, std::ios::app);
  if(outputFile.is_open()){
    outputFile << endl;
    outputFile << "Relocation Record List" << endl;
    outputFile << std::setw(20) << "Section" << std::setw(20) << "Offset" << std::setw(20) << "Type"
        << std::setw(20) << "SymbolId"  << std::setw(20) << "Addend" << std::endl;
    for (const auto& record : relocationRecordList) {
      std::ostringstream symbol;
      symbol << record.getSymbolId() << " (" << getNameForSymbol(record.getSymbolId()) << ")";
      outputFile << std::setw(20) << record.getSection() << std::setw(20) << record.getOffset() << std::setw(20) << record.getType() 
      << std::setw(20) << symbol.str() << std::setw(20) << record.getAddend() << std::endl;
    }
  }
  else{
    cout << "GRESKA: Neuspesno otvaranje fajla " + outputFileName + "!" << endl;
    return;
  }
  
}

void Assembler::insertToRelocationTableForR32(std::string symbol)
{
  Symbol* sym;
  for(auto& symb:symbolTable) {
    if(symb.getName()==symbol) {
      sym=&symb;
    }
  }
  if(sym==NULL){
    cout << "Koristi se simbol koji nije uvezen ili koji nije definisan!!!" << endl;
  }
  if(sym->getBind()==0){
    RelocationRecord reloc(currentSection, locationCounter, "R_32", sym->getNdx(), getValueForSymbol(symbol));
    addToRelocationRecordList(reloc);
  }
  else{
    RelocationRecord reloc(currentSection, locationCounter, "R_32", sym->getNum(), 0);
    addToRelocationRecordList(reloc);
  }
}

void Assembler::addToLiteralPoolList(LiteralPool literalPool)
{
  literalPoolList.push_back(literalPool);
}

void Assembler::writeLiteralPoolList()
{
  cout << "Literal Pool" << endl;
  cout << "Value\tAddress\tSection\tType" << std::endl;
  for (const auto& literal : literalPoolList) {
    std::cout << literal.getValue() << "\t" << literal.getAddress() << "\t" << literal.getSection() << "\t" << literal.getType() << std::endl;
  }
}

void Assembler::fillLiteralPool()
{
  for (auto& literal : literalPoolList) {
    int currentSize=getSizeForSymbol(literal.getSection());
    literal.setAddress(convertIntToHexStringWidth8(currentSize));
    setSizeForSymbol(literal.getSection(),currentSize+4);
    setSizeForSection(literal.getSection(),currentSize+4);
  }
}

std::string Assembler::getAddressForLiteral(std::string lit, std::string sect)
{
  for (const auto& literal : literalPoolList) {
    if(literal.getValue()==lit && literal.getSection()==sect){
      return literal.getAddress();
    }
  }
  return "0";
}

void Assembler::fillSectionWithContentFromLiteralPool()
{
  for (const auto& literal : literalPoolList) {
    std::string content="";
    if(literal.getType()==1){
      content=literal.getValue();
      while(content.length()<8){
        content="0"+content;
      }
      setContentForSection(literal.getSection(), stringToLittleEndian(content));
    }
    else {
      content="00000000";
      setContentForSection(literal.getSection(), content);
      Symbol* sym;
      for(auto& symb:symbolTable) {
        if(symb.getName()==literal.getValue()) {
          sym=&symb;
        }
      }
      if(sym==NULL){
        cout << "Koristi se simbol koji nije uvezen ili koji nije definisan!!!" << endl;
      }
      if(sym->getBind()==0){
        RelocationRecord reloc(literal.getSection(), convertHexStringToInt(literal.getAddress()), "R_32", sym->getNdx(), getValueForSymbol(sym->getName()));
        addToRelocationRecordList(reloc);
      }
      else{
        RelocationRecord reloc(literal.getSection(), convertHexStringToInt(literal.getAddress()), "R_32", sym->getNum(), 0);
        addToRelocationRecordList(reloc);
      }
      // RelocationRecord reloc(literal.getSection(), convertHexStringToInt(literal.getAddress()), "R_32", getNumForSymbol(literal.getValue()), 0);
      // addToRelocationRecordList(reloc);
    }
  }
}
bool Assembler::existValueAndSectionInLiteralPool(std::string value, std::string section)
{
  for (const auto& literal : literalPoolList) {
    if(literal.getValue()==value && literal.getSection()==section){
      return true;
    }
  }
  return false;
}
// void Assembler::setSecondPass()
// {
//   secondPass=true;
// }

// bool Assembler::getSecondPass()
// {
//   return secondPass;
// }

void Assembler::sectionDirectiveFirstPass(std::string section_name)
{
  if(currentSection!=""){
    setSizeForSymbol(currentSection, locationCounter);
    setSizeForSection(currentSection, locationCounter);
  }
  if(getNdxInSymbolTable(section_name)!=-1){
    locationCounter=getSizeForSymbol(section_name);
  }
  else{
    Symbol sect(numOfSymbols, section_name, 0, 0, 0, numOfSymbols);
    addToSymbolTable(sect);
    numOfSymbols++;
    locationCounter=0;
    Section section(section_name, 0, "");
    addToSectionList(section);
  }
  currentSection=section_name;
}

void Assembler::sectionDirectiveSecondPass(std::string section_name)
{
  if(currentSection!=""){
    setSizeSecondPassForSection(currentSection, locationCounter);
  }
  if(getSizeSecondPassForSection(section_name)!=-1){
    locationCounter=getSizeSecondPassForSection(section_name);
  }else{
    locationCounter=0;
  }
  currentSection=section_name;
  
}

void Assembler::wordDirectiveFirstPass(std::vector<std::string> symbol_name_list, std::vector<int> literal_list, std::vector<int> kind_list)
{
  int listSize=4*kind_list.size();
  // cout << "ListSize je " << listSize << endl;
  locationCounter+=listSize;
}

void Assembler::wordDirectiveSecondPass(std::vector<std::string> symbol_name_list, std::vector<int> literal_list, std::vector<int> kind_list)
{
  int m=0, n=0;
  for(int i=0; i<kind_list.size(); i++){
    if(kind_list[i]==0) {
      wordDirectiveSymbol(symbol_name_list[m]);
      m++;
    }
    else{
      wordDirectiveLiteral(literal_list[n]);
      n++;
    }
    locationCounter+=4;
  }
}

void Assembler::externDirectiveFirstPass(std::vector<std::string> symbol_name_list)
{
  for(int i=0; i<symbol_name_list.size(); i++){
    Symbol sym(numOfSymbols, symbol_name_list[i], 0, 0, 1, 0);
    addToSymbolTable(sym);
    numOfSymbols++;
  }
}

void Assembler::externDirectiveSecondPass(std::vector<std::string> symbol_name_list)
{
}

void Assembler::skipDirectiveFirstPass(int literal)
{
  locationCounter+=literal;
}

void Assembler::skipDirectiveSecondPass(int literal)
{
  locationCounter+=literal;
  std::string skipContent="";
  for(int i=0; i<literal; i++) {
    skipContent+="00";
  }
  setContentForSection(currentSection, skipContent);
}

void Assembler::globalDirectiveSecondPass(std::vector<std::string> symbol_name_list)
{
  for(int i=0; i<symbol_name_list.size(); i++) {
    if(!symbolExistInTable(symbol_name_list[i])){
      cout<< "SIMBOL MORA BITI DEFINISAN DA BI BIO PROGLASEN KAO GLOBALAN! " << endl;
    }
    else{
      setBindForSymbol(symbol_name_list[i], 1);
    }
  }
}

void Assembler::endDirectiveFirstPass()
{
  setSizeForSymbol(currentSection, locationCounter);
  setSizeForSection(currentSection, locationCounter);
  currentSection="";
  locationCounter=0;
}

void Assembler::endDirectiveSecondPass()
{
}

void Assembler::labelFirstPass(std::string symbol_label)
{
  Symbol label(numOfSymbols, symbol_label, locationCounter, 0, 0, getNdxInSymbolTable(currentSection));
  addToSymbolTable(label);
  numOfSymbols++;
}

void Assembler::labelSecondPass(std::string symbol_label)
{
}

void Assembler::allInstructionFirstPass()
{
  locationCounter+=4;
}

void Assembler::haltInstructionSecondPass()
{
  std::string instructionFormat="00000000";
  locationCounter+=4;
  setContentForSection(currentSection, instructionFormat);
}

void Assembler::intInstructionSecondPass()
{
  std::string instructionFormat="10000000";
  locationCounter+=4;
  setContentForSection(currentSection, instructionFormat);
}

void Assembler::iretInstructionSecondPass()
{
  // popCommandSecondPass("pc");
  // popCommandSecondPass("status");
  std::string instructionFormat="";
  std::string opcode;
  std::string modificator;
  std::string aaaa, bbbb, cccc;
  std::string displacement;
  //u status stavljamo mem[sp+4]
  opcode="9";
  modificator="6";
  aaaa="0";   //status registar
  bbbb="e";   //sp registar
  cccc="0";   //ne treba mi
  displacement="004";
  instructionFormat=opcode+modificator+aaaa+bbbb+cccc+displacement;
  locationCounter+=4;
  setContentForSection(currentSection, instructionFormat);
  //skidamo pc sa steka
  opcode="9";
  modificator="3";
  aaaa="f";   //pc registar
  bbbb="e";   //sp registar
  cccc="0";   //ne treba
  displacement="008";   //da se stek vrati za 8B gore jer smo skinuli i status i pc sa steka
  instructionFormat=opcode+modificator+aaaa+bbbb+cccc+displacement;
  locationCounter+=4;
  setContentForSection(currentSection, instructionFormat);
}

void Assembler::retInstructionSecondPass()
{
  popCommandSecondPass("pc");
}

void Assembler::callCommandSecondPass(std::string operand, int symbol_or_literal)
{
  std::string instructionFormat="";
  std::string opcode;
  std::string modificator;
  std::string aaaa;
  std::string bbbb;
  std::string cccc;
  std::string displacement;
  if(symbol_or_literal==1){
    if(operand.length()<=3){
      opcode="2";
      modificator="0";
      aaaa="0";
      bbbb="0";
      cccc="0";
      displacement=operand;
      while(displacement.length()<3){
        displacement="0"+displacement;
      }
      instructionFormat=opcode+modificator+aaaa+bbbb+cccc+displacement;
      // locationCounter+=4;
      setContentForSection(currentSection, instructionFormat);
    }
    else{
      //jer koristim r1 kao privremeni registar
      // pushCommandSecondPass("r1");
      //da u r1 ucitam vrednost literala iz bazena literala
      // ldCommandSecondPass(operand, "", 1, "r1");
      opcode="2";
      modificator="1";
      aaaa=convertIntToHexString(15);         //jer je pc 15. registar
      bbbb="0";
      cccc="0";
      int address=std::stoi(getAddressForLiteral(operand, currentSection), NULL, 16);
      int displ=address-locationCounter-4;
      displacement=convertIntToHexStringWidth3(displ);
      // displacement="000";
      instructionFormat=opcode+modificator+aaaa+bbbb+cccc+displacement;
      // locationCounter+=4;
      setContentForSection(currentSection, instructionFormat);
      // popCommandSecondPass("r1");
    }
  }
  else{
    //jer koristim r1 kao privremeni registar
      // pushCommandSecondPass("r1");
      //da u r1 ucitam vrednost literala iz bazena literala
      // ldCommandSecondPass(operand, "", 0, "r1");
      opcode="2";
      modificator="1";
      aaaa=convertIntToHexString(15);         //jer je pc 15. registar
      bbbb="0";
      cccc="0";
      // displacement="000";
      int address=std::stoi(getAddressForLiteral(operand, currentSection), NULL, 16);
      int displ=address-locationCounter-4;
      displacement=convertIntToHexStringWidth3(displ);
      instructionFormat=opcode+modificator+aaaa+bbbb+cccc+displacement;
      // locationCounter+=4;
      setContentForSection(currentSection, instructionFormat);
      // popCommandSecondPass("r1");
  }
  locationCounter+=4;
}

void Assembler::jmpCommandSecondPass(std::string operand, int symbol_or_literal)
{
  std::string instructionFormat="";
  std::string opcode;
  std::string modificator;
  std::string aaaa;
  std::string bbbb;
  std::string cccc;
  std::string displacement;
  if(symbol_or_literal==1){
    if(operand.length()<=3){
      opcode="3";
      modificator="0";
      aaaa="0";
      bbbb="0";
      cccc="0";
      displacement=operand;
      while(displacement.length()<3){
        displacement="0"+displacement;
      }
      instructionFormat=opcode+modificator+aaaa+bbbb+cccc+displacement;
      // locationCounter+=4;
      setContentForSection(currentSection, instructionFormat);
    }
    else{
      //jer koristim r1 kao privremeni registar
      // pushCommandSecondPass("r1");
      //da u r1 ucitam vrednost literala iz bazena literala
      // ldCommandSecondPass(operand, "", 1, "r1");
      opcode="3";
      modificator="8";
      aaaa=convertIntToHexString(15);         //jer je pc 15. registar
      bbbb="0";
      cccc="0";
      int address=std::stoi(getAddressForLiteral(operand, currentSection), NULL, 16);
      int displ=address-locationCounter-4;
      displacement=convertIntToHexStringWidth3(displ);
      instructionFormat=opcode+modificator+aaaa+bbbb+cccc+displacement;
      // locationCounter+=4;
      setContentForSection(currentSection, instructionFormat);
      // popCommandSecondPass("r1");
    }
  }
  else{
    //jer koristim r1 kao privremeni registar
      // pushCommandSecondPass("r1");
      //da u r1 ucitam vrednost literala iz bazena literala
      // ldCommandSecondPass(operand, "", 0, "r1");
      opcode="3";
      modificator="8";
      aaaa=convertIntToHexString(15);         //jer je pc 15. registar
      bbbb="0";
      cccc="0";
      int address=std::stoi(getAddressForLiteral(operand, currentSection), NULL, 16);
      int displ=address-locationCounter-4;
      displacement=convertIntToHexStringWidth3(displ);
      instructionFormat=opcode+modificator+aaaa+bbbb+cccc+displacement;
      // locationCounter+=4;
      setContentForSection(currentSection, instructionFormat);
      // popCommandSecondPass("r1");
  }
  locationCounter+=4;
}

void Assembler::beqCommandSecondPass(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal)
{
  std::string instructionFormat="";
  std::string opcode;
  std::string modificator;
  std::string aaaa;
  std::string bbbb;
  std::string cccc;
  std::string displacement;
  if(symbol_or_literal==1){
    if(operand.length()<=3){
      opcode="3";
      modificator="1";
      aaaa="0";
      bbbb=convertIntToHexString(getNumberForRegister(gpr1));
      cccc=convertIntToHexString(getNumberForRegister(gpr2));
      displacement=operand;
      while(displacement.length()<3){
        displacement="0"+displacement;
      }
      instructionFormat=opcode+modificator+aaaa+bbbb+cccc+displacement;
      // locationCounter+=4;
      setContentForSection(currentSection, instructionFormat);
    }
    else{
      //jer koristim r1 kao privremeni registar
      // pushCommandSecondPass("r1");
      //da u r1 ucitam vrednost literala iz bazena literala
      // ldCommandSecondPass(operand, "", 1, "r1");
      opcode="3";
      modificator="9";
      aaaa=convertIntToHexString(15);         //jer je pc 15. registar
      bbbb=convertIntToHexString(getNumberForRegister(gpr1));
      cccc=convertIntToHexString(getNumberForRegister(gpr2));
      int address=std::stoi(getAddressForLiteral(operand, currentSection), NULL, 16);
      int displ=address-locationCounter-4;
      displacement=convertIntToHexStringWidth3(displ);
      instructionFormat=opcode+modificator+aaaa+bbbb+cccc+displacement;
      // locationCounter+=4;
      setContentForSection(currentSection, instructionFormat);
      popCommandSecondPass("r1");
    }
  }
  else{
    //jer koristim r1 kao privremeni registar
      // pushCommandSecondPass("r1");
      //da u r1 ucitam vrednost literala iz bazena literala
      // ldCommandSecondPass(operand, "", 0, "r1");
      opcode="3";
      modificator="9";
      aaaa=convertIntToHexString(15);         //jer je pc 15. registar
      bbbb=convertIntToHexString(getNumberForRegister(gpr1));
      cccc=convertIntToHexString(getNumberForRegister(gpr2));
      int address=std::stoi(getAddressForLiteral(operand, currentSection), NULL, 16);
      int displ=address-locationCounter-4;
      displacement=convertIntToHexStringWidth3(displ);
      instructionFormat=opcode+modificator+aaaa+bbbb+cccc+displacement;
      // locationCounter+=4;
      setContentForSection(currentSection, instructionFormat);
      // popCommandSecondPass("r1");
  }
  locationCounter+=4;
}

void Assembler::bneCommandSecondPass(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal)
{
  std::string instructionFormat="";
  std::string opcode;
  std::string modificator;
  std::string aaaa;
  std::string bbbb;
  std::string cccc;
  std::string displacement;
  if(symbol_or_literal==1){
    if(operand.length()<=3){
      opcode="3";
      modificator="2";
      aaaa="0";
      bbbb=convertIntToHexString(getNumberForRegister(gpr1));
      cccc=convertIntToHexString(getNumberForRegister(gpr2));
      displacement=operand;
      while(displacement.length()<3){
        displacement="0"+displacement;
      }
      instructionFormat=opcode+modificator+aaaa+bbbb+cccc+displacement;
      // locationCounter+=4;
      setContentForSection(currentSection, instructionFormat);
    }
    else{
      //jer koristim r1 kao privremeni registar
      // pushCommandSecondPass("r1");
      //da u r1 ucitam vrednost literala iz bazena literala
      // ldCommandSecondPass(operand, "", 1, "r1");
      opcode="3";
      modificator="a";
      aaaa=convertIntToHexString(15);         //jer je pc 15. registar
      bbbb=convertIntToHexString(getNumberForRegister(gpr1));
      cccc=convertIntToHexString(getNumberForRegister(gpr2));
      int address=std::stoi(getAddressForLiteral(operand, currentSection), NULL, 16);
      int displ=address-locationCounter-4;
      displacement=convertIntToHexStringWidth3(displ);
      instructionFormat=opcode+modificator+aaaa+bbbb+cccc+displacement;
      // locationCounter+=4;
      setContentForSection(currentSection, instructionFormat);
      popCommandSecondPass("r1");
    }
  }
  else{
    //jer koristim r1 kao privremeni registar
      // pushCommandSecondPass("r1");
      //da u r1 ucitam vrednost literala iz bazena literala
      // ldCommandSecondPass(operand, "", 0, "r1");
      opcode="3";
      modificator="a";
      aaaa=convertIntToHexString(15);         //jer je pc 15. registar
      bbbb=convertIntToHexString(getNumberForRegister(gpr1));
      cccc=convertIntToHexString(getNumberForRegister(gpr2));
      int address=std::stoi(getAddressForLiteral(operand, currentSection), NULL, 16);
      int displ=address-locationCounter-4;
      displacement=convertIntToHexStringWidth3(displ);
      instructionFormat=opcode+modificator+aaaa+bbbb+cccc+displacement;
      // locationCounter+=4;
      setContentForSection(currentSection, instructionFormat);
      // popCommandSecondPass("r1");
  }
  locationCounter+=4;
}

void Assembler::bgtCommandSecondPass(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal)
{
  std::string instructionFormat="";
  std::string opcode;
  std::string modificator;
  std::string aaaa;
  std::string bbbb;
  std::string cccc;
  std::string displacement;
  if(symbol_or_literal==1){
    if(operand.length()<=3){
      opcode="3";
      modificator="3";
      aaaa="0";
      bbbb=convertIntToHexString(getNumberForRegister(gpr1));
      cccc=convertIntToHexString(getNumberForRegister(gpr2));
      displacement=operand;
      while(displacement.length()<3){
        displacement="0"+displacement;
      }
      instructionFormat=opcode+modificator+aaaa+bbbb+cccc+displacement;
      // locationCounter+=4;
      setContentForSection(currentSection, instructionFormat);
    }
    else{
      //jer koristim r1 kao privremeni registar
      // pushCommandSecondPass("r1");
      //da u r1 ucitam vrednost literala iz bazena literala
      // ldCommandSecondPass(operand, "", 1, "r1");
      opcode="3";
      modificator="b";
      aaaa=convertIntToHexString(15);         //jer je pc 15. registar
      bbbb=convertIntToHexString(getNumberForRegister(gpr1));
      cccc=convertIntToHexString(getNumberForRegister(gpr2));
      int address=std::stoi(getAddressForLiteral(operand, currentSection), NULL, 16);
      int displ=address-locationCounter-4;
      displacement=convertIntToHexStringWidth3(displ);
      instructionFormat=opcode+modificator+aaaa+bbbb+cccc+displacement;
      // locationCounter+=4;
      setContentForSection(currentSection, instructionFormat);
      popCommandSecondPass("r1");
    }
  }
  else{
    //jer koristim r1 kao privremeni registar
      // pushCommandSecondPass("r1");
      //da u r1 ucitam vrednost literala iz bazena literala
      // ldCommandSecondPass(operand, "", 0, "r1");
      opcode="3";
      modificator="b";
      aaaa=convertIntToHexString(15);         //jer je pc 15. registar
      bbbb=convertIntToHexString(getNumberForRegister(gpr1));
      cccc=convertIntToHexString(getNumberForRegister(gpr2));
      int address=std::stoi(getAddressForLiteral(operand, currentSection), NULL, 16);
      int displ=address-locationCounter-4;
      displacement=convertIntToHexStringWidth3(displ);
      instructionFormat=opcode+modificator+aaaa+bbbb+cccc+displacement;
      // locationCounter+=4;
      setContentForSection(currentSection, instructionFormat);
      // popCommandSecondPass("r1");
  }
  locationCounter+=4;
}

void Assembler::xchgCommandSecondPass(std::string gpr1, std::string gpr2)
{
  std::string instructionFormat="";
  std::string opcode="4";
  std::string modificator="0";
  std::string aaaa="0";         //OVO PROVERI DA LI TREBA DA BUDE 0 ILI MOZDA SE ODNOSI NA PC REGISTAR
  std::string bbbb=convertIntToHexString(getNumberForRegister(gpr1));
  std::string cccc=convertIntToHexString(getNumberForRegister(gpr2));
  // Symbol* sym;
  std::string instructionDisplacement="000";
  instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
  
  locationCounter+=4;
  setContentForSection(currentSection, instructionFormat);
}

void Assembler::addCommandSecondPass(std::string gpr1, std::string gpr2)
{
  std::string instructionFormat="";
  std::string opcode="5";
  std::string modificator="0";
  std::string aaaa=convertIntToHexString(getNumberForRegister(gpr2));
  std::string bbbb=convertIntToHexString(getNumberForRegister(gpr2));
  std::string cccc=convertIntToHexString(getNumberForRegister(gpr1));
  // Symbol* sym;
  std::string instructionDisplacement="000";
  instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
  
  locationCounter+=4;
  setContentForSection(currentSection, instructionFormat);
}

void Assembler::subCommandSecondPass(std::string gpr1, std::string gpr2)
{
  std::string instructionFormat="";
  std::string opcode="5";
  std::string modificator="1";
  std::string aaaa=convertIntToHexString(getNumberForRegister(gpr2));
  std::string bbbb=convertIntToHexString(getNumberForRegister(gpr2));
  std::string cccc=convertIntToHexString(getNumberForRegister(gpr1));
  // Symbol* sym;
  std::string instructionDisplacement="000";
  instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
  
  locationCounter+=4;
  setContentForSection(currentSection, instructionFormat);
}

void Assembler::mulCommandSecondPass(std::string gpr1, std::string gpr2)
{
  std::string instructionFormat="";
  std::string opcode="5";
  std::string modificator="2";
  std::string aaaa=convertIntToHexString(getNumberForRegister(gpr2));
  std::string bbbb=convertIntToHexString(getNumberForRegister(gpr2));
  std::string cccc=convertIntToHexString(getNumberForRegister(gpr1));
  // Symbol* sym;
  std::string instructionDisplacement="000";
  instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
  
  locationCounter+=4;
  setContentForSection(currentSection, instructionFormat);
}

void Assembler::divCommandSecondPass(std::string gpr1, std::string gpr2)
{
  std::string instructionFormat="";
  std::string opcode="5";
  std::string modificator="3";
  std::string aaaa=convertIntToHexString(getNumberForRegister(gpr2));
  std::string bbbb=convertIntToHexString(getNumberForRegister(gpr2));
  std::string cccc=convertIntToHexString(getNumberForRegister(gpr1));
  // Symbol* sym;
  std::string instructionDisplacement="000";
  instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
  
  locationCounter+=4;
  setContentForSection(currentSection, instructionFormat);
}

void Assembler::notCommandSecondPass(std::string gpr1)
{
  std::string instructionFormat="";
  std::string opcode="6";
  std::string modificator="0";
  std::string aaaa=convertIntToHexString(getNumberForRegister(gpr1));
  std::string bbbb=convertIntToHexString(getNumberForRegister(gpr1));
  std::string cccc="0";
  // Symbol* sym;
  std::string instructionDisplacement="000";
  instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
  
  locationCounter+=4;
  setContentForSection(currentSection, instructionFormat);
}

void Assembler::andCommandSecondPass(std::string gpr1, std::string gpr2)
{
  std::string instructionFormat="";
  std::string opcode="6";
  std::string modificator="1";
  std::string aaaa=convertIntToHexString(getNumberForRegister(gpr2));
  std::string bbbb=convertIntToHexString(getNumberForRegister(gpr2));
  std::string cccc=convertIntToHexString(getNumberForRegister(gpr1));;
  // Symbol* sym;
  std::string instructionDisplacement="000";
  instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
  
  locationCounter+=4;
  setContentForSection(currentSection, instructionFormat);
}

void Assembler::orCommandSecondPass(std::string gpr1, std::string gpr2)
{
  std::string instructionFormat="";
  std::string opcode="6";
  std::string modificator="2";
  std::string aaaa=convertIntToHexString(getNumberForRegister(gpr2));
  std::string bbbb=convertIntToHexString(getNumberForRegister(gpr2));
  std::string cccc=convertIntToHexString(getNumberForRegister(gpr1));;
  // Symbol* sym;
  std::string instructionDisplacement="000";
  instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
  
  locationCounter+=4;
  setContentForSection(currentSection, instructionFormat);
}

void Assembler::xorCommandSecondPass(std::string gpr1, std::string gpr2)
{
  std::string instructionFormat="";
  std::string opcode="6";
  std::string modificator="3";
  std::string aaaa=convertIntToHexString(getNumberForRegister(gpr2));
  std::string bbbb=convertIntToHexString(getNumberForRegister(gpr2));
  std::string cccc=convertIntToHexString(getNumberForRegister(gpr1));;
  // Symbol* sym;
  std::string instructionDisplacement="000";
  instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
  
  locationCounter+=4;
  setContentForSection(currentSection, instructionFormat);
}


void Assembler::shlCommandSecondPass(std::string gpr1, std::string gpr2)
{
  std::string instructionFormat="";
  std::string opcode="7";
  std::string modificator="0";
  std::string aaaa=convertIntToHexString(getNumberForRegister(gpr2));
  std::string bbbb=convertIntToHexString(getNumberForRegister(gpr2));
  std::string cccc=convertIntToHexString(getNumberForRegister(gpr1));;
  // Symbol* sym;
  std::string instructionDisplacement="000";
  instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
  
  locationCounter+=4;
  setContentForSection(currentSection, instructionFormat);
}

void Assembler::shrCommandSecondPass(std::string gpr1, std::string gpr2)
{
  std::string instructionFormat="";
  std::string opcode="7";
  std::string modificator="1";
  std::string aaaa=convertIntToHexString(getNumberForRegister(gpr2));
  std::string bbbb=convertIntToHexString(getNumberForRegister(gpr2));
  std::string cccc=convertIntToHexString(getNumberForRegister(gpr1));;
  // Symbol* sym;
  std::string instructionDisplacement="000";
  instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
  
  locationCounter+=4;
  setContentForSection(currentSection, instructionFormat);
}

void Assembler::pushCommandSecondPass(std::string gpr1)
{
  //ovde se koristi operacioni kod za instrukciju smestanja podatka sa modificator=1
  std::string instructionFormat="";
  std::string opcode="8";
  std::string modificator="1";
  std::string aaaa=convertIntToHexString(14);
  std::string bbbb="0";
  std::string cccc=convertIntToHexString(getNumberForRegister(gpr1));
  // Symbol* sym;
  std::string instructionDisplacement=convertIntToHexString(-4);
  while(instructionDisplacement.length()<3){
    instructionDisplacement="0"+instructionDisplacement;
  }
  instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
  
  locationCounter+=4;
  setContentForSection(currentSection, instructionFormat);
}

void Assembler::popCommandSecondPass(std::string gpr1)
{
  //ovde se koristi operacioni kod za instrukciju ucitavanja podatka sa modificator=3
  std::string instructionFormat="";
  if(gpr1=="status" || gpr1=="handler" || gpr1=="cause"){
    std::string opcode="9";
    std::string modificator="7";
    std::string aaaa=convertIntToHexString(getNumberForCsrRegister(gpr1));
    std::string bbbb=convertIntToHexString(14);
    std::string cccc="0";
    // Symbol* sym;
    std::string instructionDisplacement=convertIntToHexString(4);
    while(instructionDisplacement.length()<3){
      instructionDisplacement="0"+instructionDisplacement;
    }
    instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
  }
  else{
    std::string opcode="9";
    std::string modificator="3";
    std::string aaaa=convertIntToHexString(getNumberForRegister(gpr1));
    std::string bbbb=convertIntToHexString(14);
    std::string cccc="0";
    // Symbol* sym;
    std::string instructionDisplacement=convertIntToHexString(4);
    while(instructionDisplacement.length()<3){
      instructionDisplacement="0"+instructionDisplacement;
    }
    instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
  }
  locationCounter+=4;
  setContentForSection(currentSection, instructionFormat);
}

void Assembler::ldCommandSecondPass(std::string operand1, std::string operand2, int operand_data_way, std::string general_register)
{
  std::string instructionFormat="";
  std::string modificator;
  std::string aaaa, bbbb, cccc, instructionDisplacement;
  std::string opcode="9";
  //ovo je ako je operand offset simbola
  if(operand_data_way==0){
    modificator="2";
    aaaa=convertIntToHexString(getNumberForRegister(general_register));
    bbbb=convertIntToHexString(15);     //jer je pc 15. registar
    cccc="0";
    int address=std::stoi(getAddressForLiteral(operand1, currentSection), NULL, 16);
    int displ=address-locationCounter-4;
    instructionDisplacement=convertIntToHexStringWidth3(displ);
  }
  //ako je operand offset literal
  else if(operand_data_way==1){
    //ako je duzina literala manja od 12b onda moze da stane u displacement i mozemo da koristimo ovu operaciju sa modifikator=1
    if(operand1.length()<=3){
      modificator="1";
      aaaa=convertIntToHexString(getNumberForRegister(general_register));
      bbbb="0";     
      cccc="0";
      instructionDisplacement=operand1;
      while(instructionDisplacement.length()<3){
        instructionDisplacement="0"+instructionDisplacement;
      }
    }
    //ako je duzina literala veca od 12b onda stavljamo displacement u odnosu na bazen literala tako da dohvatimo tu vrednost iz bazena literala
    else{
      modificator="2";
      aaaa=convertIntToHexString(getNumberForRegister(general_register));
      bbbb=convertIntToHexString(15);     //jer je pc 15. registar
      cccc="0";
      int address=std::stoi(getAddressForLiteral(operand1, currentSection), NULL, 16);
      int displ=address-locationCounter-4;
      instructionDisplacement=convertIntToHexStringWidth3(displ);
    }
  }
  //ako je ooperand literal, znaci vrednost iz memorije na adresi odredjenom sa literal
  else if(operand_data_way==3){
    if(operand1.length()<=3){
      modificator="2";
      aaaa=convertIntToHexString(getNumberForRegister(general_register));
      bbbb="0";     
      cccc="0";
      instructionDisplacement=operand1;
      while(instructionDisplacement.length()<3){
        instructionDisplacement="0"+instructionDisplacement;
      }
    }
    else{
      //posto imam mem[literal], ja prvo moram da dohvatim literal iz memorije, pa tek onda mem[literal], pa su onda to dve instrukcije
      modificator="2";
      aaaa=convertIntToHexString(getNumberForRegister(general_register));
      bbbb=convertIntToHexString(15);     //jer je pc 15. registar
      cccc="0";
      int address=std::stoi(getAddressForLiteral(operand1, currentSection), NULL, 16);
      int displ=address-locationCounter-4;
      instructionDisplacement=convertIntToHexStringWidth3(displ);
      instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
      locationCounter+=4;
      setContentForSection(currentSection, instructionFormat);
      //-----ovaj gornji deo je da bih dohvatio literal iz memorije, tj iz bazena literala i literal ce mi se nalaziti u general_register registru
      //ovaj donji deo je za mem[literal] koji mi je u general_register
      modificator="2";
      aaaa=convertIntToHexString(getNumberForRegister(general_register));
      bbbb=convertIntToHexString(getNumberForRegister(general_register));
      cccc="0";
      instructionDisplacement="000";
    }
  }
  //ako je operand simbol, znaci vrednost iz memorije na adresi odredjenom sa simbol
  else if(operand_data_way==2){
    //posto imam mem[literal], ja prvo moram da dohvatim literal iz memorije, pa tek onda mem[literal], pa su onda to dve instrukcije
    //ovo je kao da ovde stoji literal, isto se radi, jer ce relokacioni zapis da obezbedi da tu stoji prava vrednost
    modificator="2";
    aaaa=convertIntToHexString(getNumberForRegister(general_register));
    bbbb=convertIntToHexString(15);     //jer je pc 15. registar
    cccc="0";
    int address=std::stoi(getAddressForLiteral(operand1, currentSection), NULL, 16);
    int displ=address-locationCounter-4;
    instructionDisplacement=convertIntToHexStringWidth3(displ);
    instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
    locationCounter+=4;
    setContentForSection(currentSection, instructionFormat);
    //-----ovaj gornji deo je da bih dohvatio literal iz memorije, tj iz bazena literala i literal ce mi se nalaziti u general_register registru
    //ovaj donji deo je za mem[symbol] koji mi je u general_register
    modificator="2";
    aaaa=convertIntToHexString(getNumberForRegister(general_register));
    bbbb=convertIntToHexString(getNumberForRegister(general_register));
    cccc="0";
    instructionDisplacement="000";
  }
  //ako je operand registar, znaci vrednost iz registra
  else if(operand_data_way==4){
    //posto moram da koristim gprA<=gpr[B]+D stavicu da mi gpr[B] bude ovaj operand, a za D cu da stavim nulu
    modificator="1";
    aaaa=convertIntToHexString(getNumberForRegister(general_register));
    bbbb=convertIntToHexString(getNumberForRegister(operand1));
    cccc="0";
    instructionDisplacement="000";
  }
  //ako je operand registar ali vrednost u memoriji na koju ukazuje vrednost u registru
  else if(operand_data_way==5){
    modificator="2";
    aaaa=convertIntToHexString(getNumberForRegister(general_register));
    bbbb=convertIntToHexString(getNumberForRegister(operand1));
    cccc="0";
    instructionDisplacement="000";
  }
  //ako je operand na adresi reg+literal
  else if(operand_data_way==6) {
    if(operand2.length()<=3){
      modificator="2";
      aaaa=convertIntToHexString(getNumberForRegister(general_register));
      bbbb=convertIntToHexString(getNumberForRegister(operand1));     
      cccc="0";
      instructionDisplacement=operand2;
      while(instructionDisplacement.length()<3){
        instructionDisplacement="0"+instructionDisplacement;
      }
    }
    //ako je duzina literala veca od 12b onda stavljamo displacement u odnosu na bazen literala tako da dohvatimo tu vrednost iz bazena literala
    // else{
    //   modificator="2";
    //   aaaa=convertIntToHexString(getNumberForRegister(general_register));
    //   bbbb=convertIntToHexString(15);     //jer je pc 15. registar
    //   cccc="0";
    //   int address=std::stoi(getAddressForLiteral(operand2), NULL, 16);
    //   int displ=address-locationCounter-4;
    //   instructionDisplacement=convertIntToHexStringWidth3(displ);
    //   instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
    //   locationCounter+=4;
    //   setContentForSection(currentSection, instructionFormat);
    //   //-----ovaj gornji deo je da bih dohvatio literal iz memorije, tj iz bazena literala i literal ce mi se nalaziti u general_register registru
    //   //ovaj donji deo je za mem[literal] koji mi je u general_register
    //   modificator="2";
    //   aaaa=convertIntToHexString(getNumberForRegister(general_register));
    //   bbbb=convertIntToHexString(getNumberForRegister(operand1));
    //   cccc=convertIntToHexString(getNumberForRegister(general_register));
    //   instructionDisplacement="000";
    // }
  }
  //ako je operand na adresi reg+symbol
  else if(operand_data_way==7) {
    //KONACNA VREDNOST SIMBOLA NECE BITI POZNATA ZA VREME ASEMBLIRANJA OSIM ZA DIREKTIVU .EQU KOJU NISAM URADIO
      // modificator="2";
      // aaaa=convertIntToHexString(getNumberForRegister(general_register));
      // bbbb=convertIntToHexString(15);     //jer je pc 15. registar
      // cccc="0";
      // int address=std::stoi(getAddressForLiteral(operand2), NULL, 16);
      // int displ=address-locationCounter-4;
      // instructionDisplacement=convertIntToHexStringWidth3(displ);
      // instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
      // locationCounter+=4;
      // setContentForSection(currentSection, instructionFormat);
      // //-----ovaj gornji deo je da bih dohvatio literal iz memorije, tj iz bazena literala i literal ce mi se nalaziti u general_register registru
      // //ovaj donji deo je za mem[literal] koji mi je u general_register
      // modificator="2";
      // aaaa=convertIntToHexString(getNumberForRegister(general_register));
      // bbbb=convertIntToHexString(getNumberForRegister(operand1));
      // cccc=convertIntToHexString(getNumberForRegister(general_register));
      // instructionDisplacement="000";
  }
  instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
  
  locationCounter+=4;
  setContentForSection(currentSection, instructionFormat);
  
}

void Assembler::stCommandSecondPass(std::string operand1, std::string operand2, int operand_data_way, std::string general_register)
{
  std::string instructionFormat="";
  std::string modificator;
  std::string aaaa, bbbb, cccc, instructionDisplacement;
  std::string opcode;
  //ovo je ako je operand offset simbola
  if(operand_data_way==0){
    cout<<"GRESKA: VREDNOST SIMBOLA NE SME DA BUDE ODREDISTE ST INSTRUKCIJE!"<<endl;
    return;
  }
  //ako je operand offset literal
  else if(operand_data_way==1){
    cout<<"GRESKA: VREDNOST LITERALA NE SME DA BUDE ODREDISTE ST INSTRUKCIJE!"<<endl;
    return;
  }
  //ako je ooperand symbol, znaci vrednost iz memorije na adresi odredjenom sa literal
  else if(operand_data_way==2){
    opcode="8";
    modificator="2";
    aaaa="0";
    bbbb=convertIntToHexString(15);     //jer je pc 15. registar
    cccc=convertIntToHexString(getNumberForRegister(general_register));
    int address=std::stoi(getAddressForLiteral(operand1, currentSection), NULL, 16);
    int displ=address-locationCounter-4;
    instructionDisplacement=convertIntToHexStringWidth3(displ);
    instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
    setContentForSection(currentSection, instructionFormat);
    // popCommandSecondPass(reg);
  }
  //ako je operand literal, znaci vrednost iz memorije na adresi odredjenom sa simbol
  else if(operand_data_way==3){
    if(operand1.length()<=3){
      opcode="8";
      modificator="0";
      aaaa="0";
      bbbb="0";     
      cccc=convertIntToHexString(getNumberForRegister(general_register));
      instructionDisplacement=operand1;
      while(instructionDisplacement.length()<3){
        instructionDisplacement="0"+instructionDisplacement;
      }
    }
    else{
      opcode="8";
      modificator="2";
      aaaa="0";
      bbbb=convertIntToHexString(15);     //jer je pc 15. registar
      cccc=convertIntToHexString(getNumberForRegister(general_register));
      int address=std::stoi(getAddressForLiteral(operand1, currentSection), NULL, 16);
      int displ=address-locationCounter-4;
      instructionDisplacement=convertIntToHexStringWidth3(displ);
      instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
      setContentForSection(currentSection, instructionFormat);
    }
  }
  //ako je operand registar, znaci vrednost iz registra
  else if(operand_data_way==4){
    cout<<"GRESKA: VREDNOST REGISTRA NE SME DA BUDE ODREDISTE ST INSTRUKCIJE!"<<endl;
    return;
  }
  //ako je operand registar ali vrednost u memoriji na koju ukazuje vrednost u registru
  else if(operand_data_way==5){
    opcode="8";
    modificator="0";
    aaaa=convertIntToHexString(getNumberForRegister(operand1));
    bbbb="0";
    cccc=convertIntToHexString(getNumberForRegister(general_register));
    instructionDisplacement="000";
    instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
    setContentForSection(currentSection, instructionFormat);
  }
  //ako je operand na adresi reg+literal
  else if(operand_data_way==6) {
    if(operand2.length()<=3){
      opcode="8";
      modificator="0";
      aaaa=convertIntToHexString(getNumberForRegister(operand1)); 
      bbbb="0";     
      cccc=convertIntToHexString(getNumberForRegister(general_register));
      instructionDisplacement=operand2;
      while(instructionDisplacement.length()<3){
        instructionDisplacement="0"+instructionDisplacement;
      }
      instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
      setContentForSection(currentSection, instructionFormat);
    }
  }
  //ako je operand na adresi reg+symbol
  else if(operand_data_way==7) {
  }
  locationCounter+=4;
}

void Assembler::csrrdCommandSecondPass(std::string csr, std::string gpr1)
{
  std::string instructionFormat="";
  std::string opcode="9";
  std::string modificator="0";
  std::string aaaa=convertIntToHexString(getNumberForRegister(gpr1));
  std::string bbbb=convertIntToHexString(getNumberForCsrRegister(csr));
  std::string cccc="0";
  // Symbol* sym;
  std::string instructionDisplacement="000";
  instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
  
  locationCounter+=4;
  setContentForSection(currentSection, instructionFormat);
}

void Assembler::csrwrCommandSecondPass(std::string gpr1, std::string csr)
{
  std::string instructionFormat="";
  std::string opcode="9";
  std::string modificator="4";
  std::string aaaa=convertIntToHexString(getNumberForCsrRegister(csr));
  std::string bbbb=convertIntToHexString(getNumberForRegister(gpr1));
  std::string cccc="0";
  // Symbol* sym;
  std::string instructionDisplacement="000";
  instructionFormat=opcode+modificator+aaaa+bbbb+cccc+instructionDisplacement;
  
  locationCounter+=4;
  setContentForSection(currentSection, instructionFormat);
}

void Assembler::callCommandFirstPass(std::string operand, int symbol_or_literal)
{
  if(symbol_or_literal==1){
    if(operand.length()>3){
      if(!existValueAndSectionInLiteralPool(operand, currentSection)){
        LiteralPool literal(operand, "", currentSection, 1);
        addToLiteralPoolList(literal);
      //dodajem ovde +12 jer ce mi ova instrukcija biti iz dve instrukcije, vidi u ldCommandSecondPass
      }
      // locationCounter+=12;
    }
  }
  else{
    if(!existValueAndSectionInLiteralPool(operand, currentSection)){
      LiteralPool literal(operand, "", currentSection, 0);
      addToLiteralPoolList(literal);
      //dodajem ovde +12 jer ce mi ova instrukcija biti iz dve instrukcije, vidi u ldCommandSecondPass
    }
    // locationCounter+=12;
  }
}

void Assembler::jmpCommandFirstPass(std::string operand, int symbol_or_literal)
{
  if(symbol_or_literal==1){
    if(operand.length()>3){
      if(!existValueAndSectionInLiteralPool(operand, currentSection)){
        LiteralPool literal(operand, "", currentSection, 1);
        addToLiteralPoolList(literal);
        //dodajem ovde +12 jer ce mi ova instrukcija biti iz dve instrukcije, vidi u ldCommandSecondPass
      }
      // locationCounter+=12;
    }
  }
  else{
    if(!existValueAndSectionInLiteralPool(operand, currentSection)){
      LiteralPool literal(operand, "", currentSection, 0);
      addToLiteralPoolList(literal);
      //dodajem ovde +12 jer ce mi ova instrukcija biti iz dve instrukcije, vidi u ldCommandSecondPass
    }
    // locationCounter+=12;
  }
  // cout << "Operand je: " << operand << endl;
}

void Assembler::beqCommandFirstPass(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal)
{
  if(symbol_or_literal==1){
    if(operand.length()>3){
      if(!existValueAndSectionInLiteralPool(operand, currentSection)){
      LiteralPool literal(operand, "", currentSection, 1);
      addToLiteralPoolList(literal);
      //dodajem ovde +12 jer ce mi ova instrukcija biti iz dve instrukcije, vidi u ldCommandSecondPass
      }
      // locationCounter+=12;
    }
  }
  else{
    if(!existValueAndSectionInLiteralPool(operand, currentSection)){
      LiteralPool literal(operand, "", currentSection, 0);
      addToLiteralPoolList(literal);
      //dodajem ovde +12 jer ce mi ova instrukcija biti iz dve instrukcije, vidi u ldCommandSecondPass
    }
    // locationCounter+=12;
  }
}

void Assembler::bneCommandFirstPass(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal)
{
  if(symbol_or_literal==1){
    if(operand.length()>3){
      if(!existValueAndSectionInLiteralPool(operand, currentSection)){
      LiteralPool literal(operand, "", currentSection, 1);
      addToLiteralPoolList(literal);
      //dodajem ovde +12 jer ce mi ova instrukcija biti iz dve instrukcije, vidi u ldCommandSecondPass
      }
      // locationCounter+=12;
    }
  }
  else{
    if(!existValueAndSectionInLiteralPool(operand, currentSection)){
      LiteralPool literal(operand, "", currentSection, 0);
      addToLiteralPoolList(literal);
      //dodajem ovde +12 jer ce mi ova instrukcija biti iz dve instrukcije, vidi u ldCommandSecondPass
    }
    // locationCounter+=12;
  }
}

void Assembler::bgtCommandFirstPass(std::string gpr1, std::string gpr2, std::string operand, int symbol_or_literal)
{
  if(symbol_or_literal==1){
    if(operand.length()>3){
      if(!existValueAndSectionInLiteralPool(operand, currentSection)){
      LiteralPool literal(operand, "", currentSection, 1);
      addToLiteralPoolList(literal);
      //dodajem ovde +12 jer ce mi ova instrukcija biti iz dve instrukcije, vidi u ldCommandSecondPass
      }
      // locationCounter+=12;
    }
  }
  else{
    if(!existValueAndSectionInLiteralPool(operand, currentSection)){
      LiteralPool literal(operand, "", currentSection, 0);
      addToLiteralPoolList(literal);
      //dodajem ovde +12 jer ce mi ova instrukcija biti iz dve instrukcije, vidi u ldCommandSecondPass
    }
    // locationCounter+=12;
  }
}

void Assembler::iretInstructionFirstPass()
{
  //jer  se ova instrukcija sastoji iz dva pop-a
  locationCounter+=4;
}

void Assembler::ldCommandFirstPass(std::string operand1, std::string operand2, int operand_data_way, std::string general_register)
{
  if(operand_data_way==0){
    if(!existValueAndSectionInLiteralPool(operand1, currentSection)){
      LiteralPool literal(operand1, "", currentSection, 0);
      addToLiteralPoolList(literal);
    }
  }
  else if(operand_data_way==1) {
    if(operand1.length()>3){
      if(!existValueAndSectionInLiteralPool(operand1, currentSection)){
        LiteralPool literal(operand1, "", currentSection, 1);
        addToLiteralPoolList(literal);
      }
    }
  }
  else if(operand_data_way==2){
    if(!existValueAndSectionInLiteralPool(operand1, currentSection)){
      LiteralPool literal(operand1, "", currentSection, 0);
      addToLiteralPoolList(literal);
      //dodajem ovde +4 jer ce mi ova instrukcija biti iz dve instrukcije, vidi u ldCommandSecondPass
    }
    locationCounter+=4;
  }
  else if(operand_data_way==3){
    if(operand1.length()>3){
      if(!existValueAndSectionInLiteralPool(operand1, currentSection)){
        LiteralPool literal(operand1, "", currentSection, 1);
        addToLiteralPoolList(literal);
        //dodajem ovde +4 jer ce mi ova instrukcija biti iz dve instrukcije, vidi u ldCommandSecondPass
      }
      locationCounter+=4;
    }
  }
  else if(operand_data_way==6){
    if(operand2.length()>3) {
      // if(!existValueAndSectionInLiteralPool(operand2, currentSection)){
      //   LiteralPool literal(operand2, "", currentSection, 1);
      //   addToLiteralPoolList(literal);
      // }
      // locationCounter+=4;
      cout << "GRESKA U PROCESU ASEMBLIRANJA: VREDNOST LITERALA NIJE MOGUCE ZAPISATI NA SIRINI OD 12 BITA." << endl;
      return;
    }
    
  }
  else if(operand_data_way==7){
    // if(!existValueAndSectionInLiteralPool(operand2, currentSection)){
    //   LiteralPool literal(operand2, "", currentSection, 0);
    //   addToLiteralPoolList(literal);
    // }
    // locationCounter+=4;
    cout << "GRESKA U PROCESU ASEMBLIRANJA: KONACNA VREDNOST SIMBOLA NIJE POZNATA U VREME ASEMBLIRANJA." << endl;
    return;
  }

}

void Assembler::stCommandFirstPass(std::string operand1, std::string operand2, int operand_data_way, std::string general_register)
{
  // if(operand_data_way==0){
  //   if(!existValueAndSectionInLiteralPool(operand1, currentSection)){
  //     LiteralPool literal(operand1, "", currentSection, 0);
  //     addToLiteralPoolList(literal);
  //   }
  // }
  if(operand_data_way==2){
    if(!existValueAndSectionInLiteralPool(operand1, currentSection)){
      LiteralPool literal(operand1, "", currentSection, 0);
      addToLiteralPoolList(literal);
      //dodajem ovde +4 jer ce mi ova instrukcija biti iz dve instrukcije, vidi u ldCommandSecondPass
    }
    // locationCounter+=12;
  }
  else if(operand_data_way==3){
    if(operand1.length()>3){
      if(!existValueAndSectionInLiteralPool(operand1, currentSection)){
        LiteralPool literal(operand1, "", currentSection, 1);
        addToLiteralPoolList(literal);
        //dodajem ovde +4 jer ce mi ova instrukcija biti iz dve instrukcije, vidi u ldCommandSecondPass
        // locationCounter+=4;
      }
    }
  }
  // else if(operand_data_way==1) {
  //   if(!existValueAndSectionInLiteralPool(operand1, currentSection)){
  //     if(operand1.length()>3){
  //       LiteralPool literal(operand1, "", currentSection, 1);
  //       addToLiteralPoolList(literal);
  //     }
  //   }
  // }
  else if(operand_data_way==6){
    // if(operand2.length()>3) {
    //   if(!existValueAndSectionInLiteralPool(operand2, currentSection)){
    //     LiteralPool literal(operand2, "", currentSection, 1);
    //     addToLiteralPoolList(literal);
    //   }
    //   locationCounter+=12;
    // }
    if(operand2.length()>3) {
      cout << "GRESKA U PROCESU ASEMBLIRANJA: VREDNOST LITERALA NIJE MOGUCE ZAPISATI NA SIRINI OD 12 BITA." << endl;
      return;
    }
  }
  else if(operand_data_way==7){
    // if(!existValueAndSectionInLiteralPool(operand2, currentSection)){
    //   LiteralPool literal(operand2, "", currentSection, 0);
    //   addToLiteralPoolList(literal);
    // }
    // locationCounter+=12;
    cout << "GRESKA U PROCESU ASEMBLIRANJA: KONACNA VREDNOST SIMBOLA NIJE POZNATA U VREME ASEMBLIRANJA." << endl;
    return;
  }
}

void Assembler::wordDirectiveSymbol(std::string symbol)
{
  // int symbolNum = getNumForSymbol(symbol);
  // if(symbolNum==-1){
  //   cout << "Koristi se simbol koji nije uvezen ili koji nije definisan!!!" << endl;
  // }
  // insertToRelocationTableForR32(symbol);
  Symbol* sym;
  for(auto& symb:symbolTable) {
    if(symb.getName()==symbol) {
      sym=&symb;
    }
  }
  if(sym==NULL){
    cout << "Koristi se simbol koji nije uvezen ili koji nije definisan!!!" << endl;
  }
  if(sym->getBind()==0){
    RelocationRecord reloc(currentSection, locationCounter, "R_32", sym->getNdx(), getValueForSymbol(symbol));
    addToRelocationRecordList(reloc);
  }
  else{
    RelocationRecord reloc(currentSection, locationCounter, "R_32", sym->getNum(), 0);
    addToRelocationRecordList(reloc);
  }
  // RelocationRecord reloc(currentSection, locationCounter, "R_32", symbolNum, getValueForSymbol(symbol));
  // addToRelocationRecordList(reloc);
  setContentForSection(currentSection, "00000000");
}

void Assembler::wordDirectiveLiteral(int literal)
{
  std::stringstream hexLiteral;
  hexLiteral << std::hex << literal;
  std::string hexString = hexLiteral.str();
  if(hexString.size()>8){
    cout<<"Literalna vrednost je van opsega!"<<endl;
  }
  while(hexString.size()<8){
    hexString="0"+hexString;
  }
  hexString=stringToLittleEndian(hexString);
  setContentForSection(currentSection, hexString);
}

std::string Assembler::stringToLittleEndian(std::string literal)
{
  std::string littleEndianString="";
  std::string byte="";
  for(int i=0; i<(literal.size()/2); i++){
    byte+=literal.at(i*2);
    byte+=literal.at(i*2+1);
    // cout<<byte<<endl;
    littleEndianString=byte+littleEndianString;
    byte="";
  }
  return littleEndianString;
}

std::string Assembler::convertIntToHexString(int intValue)
{
  std::stringstream hexLiteral;
  hexLiteral << std::hex << intValue;
  std::string hexString = hexLiteral.str();
  if(hexString.length()>3){
    return hexString.substr(hexString.length() - 3);
  }
  return hexString;
}

std::string Assembler::convertIntToHexStringWidth8(int intValue)
{
  std::stringstream hexLiteral;
  hexLiteral << std::hex << intValue;
  std::string hexString = hexLiteral.str();
  while(hexString.length()<8){
    hexString="0"+hexString;
  }
  return hexString;
}

std::string Assembler::convertIntToHexStringWidth3(int intValue)
{
  std::stringstream hexLiteral;
  hexLiteral << std::hex << intValue;
  std::string hexString = hexLiteral.str();
  while(hexString.length()<3){
    hexString="0"+hexString;
  }
  if(hexString.length()>3 && hexString[0]=='f'){
    return hexString.substr(hexString.length()-3);
  }
  else if(hexString.length()>3){
    cout << "GRESKA: NEDOZVOLJENA VELICINA DISPLACEMENT, BACI IZUZETAK!" << endl;
    return "";
  }
  return hexString;
}

int Assembler::convertHexStringToInt(std::string hexValue)
{
    int value;
    std::stringstream ss;
    ss << std::hex << hexValue;
    ss >> value;
    return value;
}
std::string Assembler::offsetForJumpInstructions(std::string operand, int symbol_or_literal)
{
  // std::string instructionFormat="";
  Symbol* sym;
  if(symbol_or_literal==1){
    //ako je operand literal samo se postavlja pc na tu vrednost literala
    if(operand.size()>3){
      cout<<"VREDNOST OPERANDA NE SME BITI VECA OD 12 BITA JER JE TOLIKI DISPLACEMENT"<<endl;
      return "";
    }
    // instructionFormat="20000";
    return operand;
  }
  else{
    
    for(auto& symbol:symbolTable) {
      if(symbol.getName()==operand) {
        sym=&symbol;
      }
    }
    //ako je operand simbol ali ga nema u tabeli simbola
    if(sym==NULL) {
      cout<<"KORISTI SE SIMBOL KOJI NIGDE NIJE DEFINISAN NITI UVEZEN!"<<endl;
      return "";
      // Symbol s(numOfSymbols, operand, 0, 0, 1, 0);
      // numOfSymbols++;
      // addToSymbolTable(s);
      // RelocationRecord r(currentSection, locationCounter+2, "R_PC_16", getNumForSymbol(operand), -4);
      // addToRelocationRecordList(r);
      // instructionFormat="20000000";
    }
    else{
      //ako operand pripada istoj sekciji kao sto je ova onda odmah znamo pomeraj
      if(sym->getNdx()==getNdxInSymbolTable(currentSection)){
        //ovde od vrednosti simbola u tabeli simbola oduzimamo locationCounter uvecan za 4 jer hocemo offset sledece instrukcije
        int offset=getValueForSymbol(operand)-(locationCounter+4);
        std::string offsetString=convertIntToHexString(offset);
        if(offsetString.size()>3){
          cout<<"PREVELIKI OFFSET ZA CALL INSTRUKCIJU"<<endl;
          return "";
        }
        while(offsetString.size()<3){
          offsetString="0"+offsetString;
        }
        // instructionFormat="20000"+offsetString;
        return offsetString;
      }
      //ako je simbol extern
      else if(sym->getNdx()==0) {
        RelocationRecord r(currentSection, locationCounter+2, "R_PC_32", getNumForSymbol(operand), -4);
        addToRelocationRecordList(r);
        // instructionFormat="20000000";
        return "000";
      }
      else if(sym->getBind()==0) {
        std::string sectionName=getNameForSymbol(sym->getNdx());
        RelocationRecord r(currentSection, locationCounter+2, "R_PC_32", getNumForSymbol(sectionName), getValueForSymbol(sym->getName())-4);
        addToRelocationRecordList(r);
        // instructionFormat="20000000";
        return "000";
      }
      else if(sym->getBind()==1) {
        RelocationRecord r(currentSection, locationCounter+2, "R_PC_32", getNumForSymbol(operand), -4);
        addToRelocationRecordList(r);
        // instructionFormat="20000000";
        return "000";
      }
    }
  }
  return "";
}

int Assembler::getNumberForRegister(std::string reg)
{
  if(reg=="r0"){ return 0; }
  if(reg=="r1"){ return 1; }
  if(reg=="r2"){ return 2; }
  if(reg=="r3"){ return 3; }
  if(reg=="r4"){ return 4; }
  if(reg=="r5"){ return 5; }
  if(reg=="r6"){ return 6; }
  if(reg=="r7"){ return 7; }
  if(reg=="r8"){ return 8; }
  if(reg=="r9"){ return 9; }
  if(reg=="r10"){ return 10; }
  if(reg=="r11"){ return 11; }
  if(reg=="r12"){ return 12; }
  if(reg=="r13"){ return 13; }
  if(reg=="r14"){ return 14; }
  if(reg=="r15"){ return 15; }
  if(reg=="sp"){ return 14; }
  if(reg=="pc"){ return 15; }
  return - 1;
}

int Assembler::getNumberForCsrRegister(std::string reg)
{
  if(reg=="status"){ return 0; }
  if(reg=="handler"){ return 1; }
  if(reg=="cause"){ return 2; }
  return -1;
}
std::string Assembler::offsetForDataInstructionsForSymbol(std::string operand)
{             
    Symbol* sym;
    for(auto& symbol:symbolTable) {
      if(symbol.getName()==operand) {
        sym=&symbol;
      }
    }
    //ako je operand simbol ali ga nema u tabeli simbola
    if(sym==NULL) {
      cout<<"KORISTI SE SIMBOL KOJI NIGDE NIJE DEFINISAN NITI UVEZEN!"<<endl;
      return "";
      // Symbol s(numOfSymbols, operand, 0, 0, 1, 0);
      // numOfSymbols++;
      // addToSymbolTable(s);
      // RelocationRecord r(currentSection, locationCounter+2, "R_PC_16", getNumForSymbol(operand), -4);
      // addToRelocationRecordList(r);
      // instructionFormat="20000000";
    }
    else{
      //ako operand pripada istoj sekciji kao sto je ova onda odmah znamo pomeraj
      if(sym->getNdx()==getNdxInSymbolTable(currentSection)){
        //ovde od vrednosti simbola u tabeli simbola oduzimamo locationCounter uvecan za 4 jer hocemo offset sledece instrukcije
        int offset=getValueForSymbol(operand)-(locationCounter+4);
        std::string offsetString=convertIntToHexString(offset);
        if(offsetString.size()>3){
          cout<<"PREVELIKI OFFSET ZA LD INSTRUKCIJU"<<endl;
          return "";
        }
        while(offsetString.size()<3){
          offsetString="0"+offsetString;
        }
        // instructionFormat="20000"+offsetString;
        return offsetString;
      }
      //ako je simbol extern
      else if(sym->getNdx()==0) {
        RelocationRecord r(currentSection, locationCounter+2, "R_PC_32", getNumForSymbol(operand), -4);
        addToRelocationRecordList(r);
        // instructionFormat="20000000";
        return "000";
      }
      //ako je simbol lokalan onda radimo relokaciju u odnosu na sekciju kojoj pripada
      else if(sym->getBind()==0) {
        std::string sectionName=getNameForSymbol(sym->getNdx());
        RelocationRecord r(currentSection, locationCounter+2, "R_PC_32", getNumForSymbol(sectionName), getValueForSymbol(sym->getName())-4);
        addToRelocationRecordList(r);
        // instructionFormat="20000000";
        return "000";
      }
      //ako je simbol globalan onda radimo relokaciju u odnosu na taj simbol
      else if(sym->getBind()==1) {
        RelocationRecord r(currentSection, locationCounter+2, "R_PC_32", getNumForSymbol(operand), -4);
        addToRelocationRecordList(r);
        // instructionFormat="20000000";
        return "000";
      }
    }
    return "";
}
