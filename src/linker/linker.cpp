#include "../../inc/linker/linker.hpp"

std::list<Symbol> Linker::symbolTable;

std::list<Section> Linker::sectionList;

std::list<RelocationRecord> Linker::relocationRecordList;

std::list<Plan> Linker::mappingPlanList;

std::list<Symbol> Linker::linkerSymbolTable;

Linker::Linker()
{

}

void Linker::addToSymbolTable(Symbol symbol)
{
  symbolTable.push_back(symbol);
}

void Linker::writeSymbolTable()
{
    cout << "Symbol Table" << endl;
    cout << std::setw(15) << "Num" << std::setw(15) << "Value" << std::setw(15) << "Size" << std::setw(15) << "Bind"
    << std::setw(15) << "Ndx" << std::setw(15) << "Name" << std::setw(15) << "ObjFile" << std::endl;
    for (const auto& symbol : symbolTable) {
      cout << std::setw(15) << symbol.getNum() << std::setw(15) << symbol.getValue() << std::setw(15) << symbol.getSize() << 
      std::setw(15) << (symbol.getBind()==0?"local":"global") << std::setw(15) << symbol.getNdx() 
      << std::setw(15) << symbol.getName() << std::setw(15) << symbol.getObjFile() << std::endl;
    }
}

std::string Linker::getSymNameForSymIdAndObjFile(int symbolId, int objFile)
{
    for(const auto& sym : symbolTable) {
      if(sym.getNum()==symbolId && sym.getObjFile()==objFile){
        return sym.getName();
      }
    }
    return "";
}

bool Linker::symbolIsSection(int symbolId, int objFile)
{
    std::string symbolName=getSymNameForSymIdAndObjFile(symbolId, objFile);
    for(const auto& sect:sectionList){
      if(sect.getName()==symbolName){
        return true;
      }
    }
    return false;
}

void Linker::addToSectionList(Section section)
{
  sectionList.push_back(section);
}

void Linker::writeSectionList()
{
  
    for (const auto& section : sectionList) {
      cout << "Section: " << section.getName() <<  "(" << section.getSize() << ")" << "ObjFile: " << section.getObjFile() << std::endl;
      int m=0, n=0, s=0;
      while(m<section.getContent().size()){
        cout<<section.getContent().at(m);
        m++;
        // if(m<section.getContent().size()){
        //   outputFile<<section.getContent().at(m);
        //   m++;
        // }
        if(m<section.getContent().size()){
          cout<<" ";
        }
        n=n+2;
        // s=s+2;
        // if(s==8){
        //   outputFile<<" ";
        //   s=0;
        // }
        if(n==16){
          cout<<"\n";
          n=0;
        }
      }
      if(n!=0){
        cout<<endl;
      }
    }
}

void Linker::setContentFromRelocationRecord(std::string section_name, int objFile, std::string content, int offset)
{
  for(auto& sect:sectionList){
    if(sect.getName()==section_name && sect.getObjFile()==objFile){
      int offs=offset;
      for(int i=0; i<7; i+=2){
        std::string byte=content.substr(i,2);
        sect.setByteForContent(byte, offs);
        offs++;
      }
    }
  }
}

std::vector<std::string> Linker::getContentForSection(std::string section, int indexOfObjFile)
{
  std::vector<std::string> vect;
  for(const auto& sect:sectionList){
    if(sect.getName()==section && sect.getObjFile()==indexOfObjFile){
      return sect.getContent();
    }
  }
  return vect;
}

void Linker::addToRelocationRecordList(RelocationRecord relocationRecord)
{
  relocationRecordList.push_back(relocationRecord);
}

void Linker::writeRelocationRecordList()
{
    cout << "Relocation Record List" << endl;
    cout << std::setw(15) << "Section" << std::setw(15) << "Offset" << std::setw(15) << "Type"
        << std::setw(15) << "SymbolId"  << std::setw(15) << "Addend" << std::setw(15) << "ObjFile" << std::endl;
    for (const auto& record : relocationRecordList) {
      // std::ostringstream symbol;
      // symbol << record.getSymbolId() << " (" << getNameForSymbol(record.getSymbolId()) << ")";
      cout << std::setw(15) << record.getSection() << std::setw(15) << record.getOffset() << std::setw(15) << record.getType() 
      << std::setw(15) << record.getSymbolId() << std::setw(15) << record.getAddend() << std::setw(15) << record.getObjFile() << std::endl;
    }
}

void Linker::addToMappingPlanList(Plan mappingPlan)
{
  mappingPlanList.push_back(mappingPlan);
}

void Linker::writeMappingPlanList()
{
    cout << "Mapping Plan List" << endl;
    cout << std::setw(15) << "Section" << std::setw(15) << "Size" << std::setw(15) << "StardAddr"
        << std::setw(15) << "IndexOfObjFile" << std::endl;
    for (const auto& plan : mappingPlanList) {
      // std::ostringstream symbol;
      // symbol << record.getSymbolId() << " (" << getNameForSymbol(record.getSymbolId()) << ")";
      cout << std::setw(15) << plan.getSection() << std::setw(15) << plan.getSize() << std::setw(15) << plan.getStartAddr() 
      << std::setw(15) << plan.getIndexOfObjFile() << std::endl;
    }
}

bool Linker::existInMappingPlanList(std::string section, int objFile)
{
    for(const auto& plan : mappingPlanList) {
      if(plan.getSection()==section && plan.getIndexOfObjFile()==objFile){
        return true;
      }
    }
    return false;
}

bool Linker::isFreeSpaceForPutSection(std::string addr, int sectionSize)
{
    unsigned int adr=convertHexStringToInt(addr);
    for(const auto& plan : mappingPlanList) {
      unsigned int startAddr=convertHexStringToInt(plan.getStartAddr());
      if((adr > startAddr && adr < (startAddr+plan.getSize())) || ((adr+sectionSize) > startAddr && (adr+sectionSize) < (startAddr+plan.getSize()))
      || (adr < startAddr && (adr+sectionSize) > (startAddr+plan.getSize()))){
        return false;
      }
    }
    return true;
}

int Linker::findFirstFreeSpaceForSection(std::string addr, int sectionSize)
{
  //problem mogu da prave samo ove sekcije cija se adresa zadaje sa place, tako da mogu samo za njih da proveravam
  unsigned int adr=convertHexStringToInt(addr);
  for(const auto& plan : mappingPlanList) {
    unsigned int startAddr=convertHexStringToInt(plan.getStartAddr());

  }
  return -1;
}

int Linker::getSectionSizeInMappingPlan(std::string section)
{
  int size=0;
  for(const auto& plan : mappingPlanList) {
    if(plan.getSection()==section){
      size+=plan.getSize();
    }
  }
  return size;
}

std::string Linker::getStartAddrForSection(std::string section, int objFile)
{
  for(const auto& plan : mappingPlanList){
    if(plan.getSection()==section && plan.getIndexOfObjFile()==objFile){
      return plan.getStartAddr();
    }
  }
  return "";
}

void Linker::addToLinkerSymbolTable(Symbol symbol)
{
  linkerSymbolTable.push_back(symbol);
}

void Linker::writeLinkerSymbolTable()
{
  cout << "Symbol Table" << endl;
    cout << std::setw(15) << "Num" << std::setw(15) << "Value" << std::setw(15) << "Size" << std::setw(15) << "Bind"
    << std::setw(15) << "Ndx" << std::setw(15) << "Name" << std::endl;
    for (const auto& symbol : linkerSymbolTable) {
      cout << std::setw(15) << symbol.getNum() << std::setw(15) << symbol.getValue() << std::setw(15) << symbol.getSize() << 
      std::setw(15) << (symbol.getBind()==0?"local":"global") << std::setw(15) << symbol.getNdx() 
      << std::setw(15) << symbol.getName() << std::endl;
    }
}

int Linker::getNdxForSectionInLinkerSymbolTable(int ndxInOldSymTable, int objFile)
{
    std::string sectionName;
    for(const auto& symbol : symbolTable) {
      if(symbol.getNdx()==ndxInOldSymTable && symbol.getObjFile()==objFile){
        sectionName=symbol.getName();
        break;
      }
    }
    for(const auto& symbol : linkerSymbolTable) {
      if(symbol.getName()==sectionName){
        return symbol.getNum();
      }
    }
    return -1;
}

std::string Linker::getSymAddrFromPlanAndSymTable(std::string symName, int ndxInOldSymTable, int objFile)
{
    std::string sectionName;
    unsigned int symbolOffset=0;
    for(const auto& symbol : symbolTable) {
      if(symbol.getNdx()==ndxInOldSymTable && symbol.getObjFile()==objFile){
        sectionName=symbol.getName();
        // symbolOffset=convertHexStringToInt(symbol.getValue());
        break;
      }
    }
    for(const auto& symbol : symbolTable) {
      if(symbol.getName()==symName && symbol.getObjFile()==objFile){
        symbolOffset=convertHexStringToInt(symbol.getValue());
        break;
      }
    }
    unsigned int startAddr=0;
    for(const auto& plan : mappingPlanList) {
      if(plan.getSection()==sectionName && plan.getIndexOfObjFile()==objFile){
        startAddr=convertHexStringToInt(plan.getStartAddr());
        break;
      }
    }
    return convertIntToHexStringWidth8(symbolOffset+startAddr);
}

std::string Linker::getAddrFromLinkerSymbolTable(std::string symName)
{
    for(const auto& sym:linkerSymbolTable){
      if(sym.getName()==symName){
        return sym.getValue();
      }
    }
    return "";
}

void Linker::sortMappingPlanList()
{
  for(auto it1=mappingPlanList.begin(); it1!=mappingPlanList.end(); ++it1){
    for(auto it2=std::next(it1); it2!=mappingPlanList.end(); ++it2){
      if(convertHexStringToInt(it1->getStartAddr())>convertHexStringToInt(it2->getStartAddr())){
        std::swap(*it1, *it2);
      }
    }
  }
}

void Linker::readObjectFiles(std::vector<std::string> inputFiles)
{
  int objFileIndex=0;
  for(std::string file:inputFiles){
    int numOfSymbols=0;
    int numOfSections=0;
    int numOfRelocationRecords=0;
    std::ifstream inputFile(file);
    if(!inputFile){
      cout << "GRESKA: Greska prilikom otvaranja ulaznog fajla: " << file << endl;
      return;
    }
    std::string line;
    std::getline(inputFile, line);       //ovo je za Symbol Table
    std::getline(inputFile, line);       //header tabele
    bool symTab=true;
    while(symTab){
      std::getline(inputFile, line);
      if(line.empty()){
        symTab=false;
        numOfSymbolsPerObjectFile.push_back(numOfSymbols);
      }
      else{
        std::string num, value, size, bind, ndx, name;
        std::istringstream tokens(line);
        tokens >> std::setw(20) >> num >> std::setw(20) >> value >> std::setw(20) >> size >> std::setw(20) >> bind >> 
        std::setw(20) >> ndx >> std::setw(20) >> name;
        // cout << "Num:" << num << "Value:" << value << "Size:" << size << "Bind:" << bind << "Ndx:" << ndx << "Name:" << name <<  endl;
        Symbol sym(convertStringToInt(num),name, value, convertStringToInt(size), bind=="local"?0:1, convertStringToInt(ndx), objFileIndex);
        addToSymbolTable(sym);
        numOfSymbols++;
      }
    }
    bool sectionList=true;
    std::string name, size;
    std::vector<std::string> content;
    while(sectionList){
      std::getline(inputFile, line);
      if(line.empty()){
        sectionList=false;
        if(content.size()!=0){
          Section sect(name, convertStringToInt(size), content, objFileIndex);
          addToSectionList(sect);
          numOfSections++;
          content.clear();
        }
        numOfSectionsPerObjectFile.push_back(numOfSections);
      }
      else{
        
        if(line.compare(0, 7, "Section")==0){
          if(content.size()!=0){
            Section sect(name, convertStringToInt(size), content, objFileIndex);
            addToSectionList(sect);
            numOfSections++;
            content.clear();
          }
          int startInd=line.find(':');
          startInd=startInd+2;      //jer je pocetak imena sekcije 2 karaktera posle :
          name=line.substr(startInd);
          name=name.substr(0,name.find('('));
          // cout << name << endl;
          size=line.substr(line.find('(')+1);
          size=size.substr(0, size.find(')'));
          // cout << size << endl;
          
        }
        else{
          std::string bajt;
          std::istringstream iss(line);
          while(std::getline(iss, bajt, ' ')){          //split
            content.push_back(bajt);
          }
        }
      }
    }
    bool relocationRecordList=true;
    std::getline(inputFile, line);       //ovo je za Relocation Record List
    std::getline(inputFile, line);       //header tabele
    while(relocationRecordList){
      std::getline(inputFile, line);
      if(line.empty() || inputFile.eof()){
        relocationRecordList=false;
        numOfRelocationRecordsPerObjectFile.push_back(numOfRelocationRecords);
      }
      else{
        std::string section, offset, type, symbolId, symbolName, addend;
        std::istringstream tokens(line);
        tokens >> std::setw(20) >> section >> std::setw(20) >> offset >> std::setw(20) >> type >> std::setw(20) >> symbolId >> 
        std::setw(20) >> symbolName >> std::setw(20) >> addend;
        // cout << "section:" << section << "offset:" << offset << "type:" << type << "symbolId:" << symbolId << "addend:" << addend << endl;
        // Symbol sym(convertStringToInt(num),name, value, convertStringToInt(size), bind=="local"?0:1, convertStringToInt(ndx));
        // addToSymbolTable(sym);
        RelocationRecord reloc(section, convertStringToInt(offset), type, convertStringToInt(symbolId), convertStringToInt(addend), objFileIndex);
        addToRelocationRecordList(reloc);
        numOfSymbols++;
      }
    }
    objFileIndex++;
  }
}

void Linker::makeMappingPlan(std::vector<std::string> placeOptionStrings)
{
  int addr=0;
  // int indexOfObjFile=0;
  int i=0;
  if(placeOptionStrings.size()>0){
    std::vector<Section> sections;
    for(int i=0; i<placeOptionStrings.size(); i++) {
      std::string sect=placeOptionStrings[i].substr(placeOptionStrings[i].find('=')+1);
      sect=sect.substr(0,sect.find('@'));
      std::string place=placeOptionStrings[i].substr(placeOptionStrings[i].find('@')+3);
      //kopiramo sekcije cije je ime sect u privremeni vector sections
      int sectionSize;
      for(const auto& section : sectionList){
        if(section.getName()==sect){
          sectionSize+=section.getSize();
          Section sectionCopy(section);
          sections.push_back(sectionCopy);
        }
      }
      if(!isFreeSpaceForPutSection(place, sectionSize)){
        throw std::runtime_error("Dolazi do preklapanja sekcija usled koriscenja place opcija!");
        // return;
      }
      else{
        // cout << " je na " << std::hex << place << endl;
        unsigned int placeInt=convertHexStringToInt(place);
        // cout << std::hex << placeInt << endl;
        for(int i=0; i<sections.size(); i++){
          Plan plan(sections[i].getName(), sections[i].getSize(), convertIntToHexStringWidth8(placeInt), sections[i].getObjFile());
          addToMappingPlanList(plan);
          placeInt+=sections[i].getSize();
        }
      }
      sections.clear();
    }
  }
  for (const auto& section : sectionList) {
    if(!existInMappingPlanList(section.getName(),section.getObjFile())){
      int sectionSize;
      std::vector<Section> sections;
      for(const auto& sect : sectionList){
        if(section.getName()==sect.getName()){
          sectionSize+=sect.getSize();
          Section sectionCopy(sect);
          sections.push_back(sectionCopy);
        }
      }
      //posto problem sa preklapanjem mogu da prave samo ove sekcije sto su navedene sa place provericu samo preklapanje sa njima
      int j=0;
      while(j<placeOptionStrings.size()) {
        std::string sect=placeOptionStrings[j].substr(placeOptionStrings[j].find('=')+1);
        sect=sect.substr(0,sect.find('@'));
        std::string place=placeOptionStrings[j].substr(placeOptionStrings[j].find('@')+3);
        int sectionPlaceSize=getSectionSizeInMappingPlan(sect);
        unsigned int placeInt = convertHexStringToInt(place);
        // cout << addr << endl;
        // cout << sectionSize << endl;
        // cout << placeInt << endl;
        // cout << sectionPlaceSize << endl;
        if(((addr+sectionSize) > placeInt && (addr+sectionSize) < (placeInt+sectionPlaceSize)) || addr==placeInt 
            || (addr < placeInt && (addr+sectionSize) > (placeInt+sectionPlaceSize)))
        {
          addr=placeInt+sectionPlaceSize;
        }
        j++;
        // else{
        //   // break;
        //   j=placeOptionStrings.size();
        // }
      }
      Plan plan(section.getName(), section.getSize(), convertIntToHexStringWidth8(addr), section.getObjFile());
      addToMappingPlanList(plan);
      addr+=section.getSize();
      std::list<Section>::iterator it=sectionList.begin();
      std::advance(it, i+1);
      while(it!=sectionList.end()){
        if(it->getName()==section.getName()){
          Plan plan(it->getName(), it->getSize(), convertIntToHexStringWidth8(addr), it->getObjFile());
          addToMappingPlanList(plan);
          addr+=it->getSize();
        }
        ++it;
      }
    sections.clear();
    }
    // for(std::list<Plan>::iterator it=mappingPlanList.begin(); it!=mappingPlanList.end(); ++it){
    //   if(it->getSection()==section.getName()){
        
    //   }
    // }
    i++;
  }
}

void Linker::makeLinkerSymbolTable()
{
  int symbolNum=1;
  std::vector<std::string> definedSymbols;
  std::vector<std::string> undefinedSymbols;
  //da proverim da li ima vise globalnih definisanih simbola
  for(const auto& sym : symbolTable){
    if(sym.getBind()==1 && sym.getNdx()!=0){
      for(const auto& defSym : definedSymbols){
        if(defSym==sym.getName()){
          throw std::runtime_error("Postoje dva ista globalno definisana simbola!");
          // return;
        }
      }
      definedSymbols.push_back(sym.getName());
    }
  }
  definedSymbols.clear();
  //da stavim prvo sekcije
  std::string sect;
  int sectSize=0;
  std::string sectValue;
  for(const auto& plan:mappingPlanList){
    if(sect==""){
      sect=plan.getSection();
      sectSize=plan.getSize();
      sectValue=plan.getStartAddr();
    }
    else if(plan.getSection()==sect){
      sectSize+=plan.getSize();
    }
    else{
      //vise nam ne treba broj objektnog fajla
      Symbol sym(symbolNum, sect, sectValue, sectSize, 0, symbolNum, -1);
      addToLinkerSymbolTable(sym);
      symbolNum++;
      sect=plan.getSection();
      sectSize=plan.getSize();
      sectValue=plan.getStartAddr();
    }
  }
  //za poslednju sekciju koja nije obradjena u foru:
  Symbol sym(symbolNum, sect, sectValue, sectSize, 0, symbolNum, -1);
  addToLinkerSymbolTable(sym);
  symbolNum++;
  //sad da ubacim simbole
  for(const auto& sym : symbolTable){
    if(sym.getBind()==1 && sym.getNdx()!=0){
      Symbol symbol(symbolNum, sym.getName(), getSymAddrFromPlanAndSymTable(sym.getName(), sym.getNdx(), sym.getObjFile()),
      0, 1, getNdxForSectionInLinkerSymbolTable(sym.getNdx(), sym.getObjFile()), -1);
      addToLinkerSymbolTable(symbol);
      symbolNum++;
      definedSymbols.push_back(sym.getName());
      int ind=-1;
      for(int i=0; i<undefinedSymbols.size(); i++){
        if(undefinedSymbols[i]==sym.getName()){
          ind=i;
          break;
        }
      }
      if(ind!=-1){
        undefinedSymbols.erase(undefinedSymbols.begin()+ind);
      }
    }
    //ako je extern simbol
    else if(sym.getBind()==1 && sym.getNdx()==0){
      bool found=false;
      for(const auto& elem:definedSymbols){
        if(elem==sym.getName()){
          found=true;
          break;
        }
      }
      if(!found){
        bool existInUndefinedList=false;
        for(const auto& elem:undefinedSymbols){
          if(elem==sym.getName()){
            existInUndefinedList=true;
            break;
          }
        }
        if(!existInUndefinedList){
          undefinedSymbols.push_back(sym.getName());
        }
      }
    }
  }
  if(undefinedSymbols.size()>0){
    throw std::runtime_error("Postoji simbol koji je extern, a nigde nije definisan!");
    // return;
  }
}

void Linker::resolveRelocationRecords()
{
  for(const auto& record:relocationRecordList){
    std::string symbolName=getSymNameForSymIdAndObjFile(record.getSymbolId(), record.getObjFile());
    unsigned int valueForWrite=0;
    if(symbolIsSection(record.getSymbolId(), record.getObjFile())){
      //ako je simbolId u relokacionom zapisu sekcija
      std::string startAddr=getStartAddrForSection(symbolName, record.getObjFile());
      valueForWrite=convertHexStringToInt(startAddr)+record.getAddend();
    }
    else{
      std::string address=getAddrFromLinkerSymbolTable(symbolName);
      valueForWrite=convertHexStringToInt(address)+record.getAddend();
    }
    std::string stringValueForWrite=convertIntToHexStringWidth8(valueForWrite);
    std::string valueInLittleEndian=stringToLittleEndian(stringValueForWrite);
    setContentFromRelocationRecord(record.getSection(), record.getObjFile(), valueInLittleEndian, record.getOffset());
  }
}

void Linker::writeExecutableCodeToHexFile(const std::string& outputFileName)
{
  std::ofstream outputFile(outputFileName);
  if(outputFile.is_open()){
    unsigned int startAddr=0;
    for(const auto& plan:mappingPlanList){
      //da bih uporedjivao da li se trenutna sekcija nastavlja na prethodnu
      unsigned int oldStartAddr=startAddr;
      //startAddr ce da se povecava kad budem smestao sadrzaj sekcije i ako je stigao do adrese do koje je prethodna sekcija stigla ne radi se nista ovo dole nego se samo nastavlja
      if(startAddr!=convertHexStringToInt(plan.getStartAddr())){
        if(startAddr%8!=0){
          outputFile<<endl;
        }
        startAddr=convertHexStringToInt(plan.getStartAddr());
        int lineNum=startAddr;
        //ako pocetna adresa nije deljiva sa 8 smanjujem dok ne bude deljiva da bih mogao da ispisem u onom formatu koji su trazili
        if(lineNum%8!=0){
          while(lineNum%8!=0){
            lineNum--;
          }
          outputFile << convertIntToHexStringWidth8(lineNum) << ":";
        }
        if(startAddr%8!=0 ){
          //ako pocetna adresa sadrzaja koji treba da ispisemo nije deljiva sa 8 onda moram da popunjavam nulama(ili razmacima) dok se ne dodje do te adrese
          int j=0;
          while((startAddr+j)%8!=0){
            // cout << "   ";
            // for(int k=0; k<3; k++){          ovo je za razmake
            //   outputFile << " ";
            // }
            outputFile << " ";
            outputFile << "00";
            j++;
          }
          if(oldStartAddr%8!=0){
            outputFile << endl;
          }
        }
      }
      std::vector<std::string> sectionContent=getContentForSection(plan.getSection(), plan.getIndexOfObjFile());
      for(int i=0; i<sectionContent.size(); i++){
        if(startAddr%8==0){
          outputFile << convertIntToHexStringWidth8(startAddr) << ":";
        }
        outputFile << " " << sectionContent[i];
        startAddr++;
        if(startAddr%8==0){
          outputFile << endl;
        }
      }
    }
    if(startAddr%8!=0){
      outputFile << endl;
    }
    outputFile.close();
  }
  else{
    cout << "GRESKA: Neuspesno otvaranje fajla " + outputFileName + "!" << endl;
  }
  
}

unsigned int Linker::convertHexStringToInt(std::string hexValue)
{
    unsigned int value;
    std::stringstream ss;
    ss << std::hex << hexValue;
    ss >> value;
    return value;
}

int Linker::convertStringToInt(std::string stringValue)
{
  int num=std::stoi(stringValue);
  return num;
}

std::string Linker::convertIntToHexStringWidth8(int intValue)
{
  std::stringstream hexLiteral;
  hexLiteral << std::hex << intValue;
  std::string hexString = hexLiteral.str();
  while(hexString.length()<8){
    hexString="0"+hexString;
  }
  return hexString;
}

std::string Linker::stringToLittleEndian(std::string literal)
{
  std::string littleEndianString="";
  std::string byte="";
  for(int i=0; i<(literal.size()/2); i++){
    byte+=literal.at(i*2);
    byte+=literal.at(i*2+1);
    littleEndianString=byte+littleEndianString;
    byte="";
  }
  return littleEndianString;
}