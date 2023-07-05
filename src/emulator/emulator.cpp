#include "../../inc/emulator/emulator.hpp"

Emulator::Emulator() {
  generalRegisters=std::vector<unsigned int>(16, 0x00000000);
  //program treba da pocne da izvrsadva instrukcije od adrese 0x40000000
  generalRegisters[REGISTER_PC]=PROGRAM_START_ADDRESS;
  generalRegisters[REGISTER_SP]=0xfffffefe;
  statusRegisters=std::vector<unsigned int>(3, 0x00000000);
  //da se izbrise sav sadrzaj iz fajla ako on postoji
  std::ofstream memory_file(MEMORY_FILE, std::ios::trunc);
  memory_file.close();
}

void Emulator::readHexFile(std::string hexFile){
  std::ifstream inputFile(hexFile);
  if(!inputFile){
    cout << "GRESKA: Greska prilikom otvaranja ulaznog fajla: " << hexFile << endl;
    return;
  }
  std::string line;
  std::getline(inputFile, line);
  std::string address;
  std::string pageNum;
  std::string contentLine;
  std::vector<unsigned char> pageContent;
  while(!line.empty()) {
    address = line.substr(0, line.find(':'));
    contentLine=line.substr(line.find(':')+2);
    //ako treba neka druga stranica da se ucita
    if(pageNum!=address.substr(0,5) && pageNum!=""){
      //ovu tekucu stranicu ubaci u listu stranica
      //proveri da li ima mesta da se ubaci u listu, ako nema izbaci neku stranicu
      if(pageList.size()<NUM_OF_PAGES_IN_PROGRAM){
        //ubaci tu stranicu koja je do sad popunjavana u listu stranica
        Page page;
        page.content=pageContent;
        pageContent.clear();
        page.key=pageNum;
        pageList.push_back(page);
        pageMap[page.key] = std::prev(pageList.end());      //da pokazuje na poslednji dodati element
        mostRecentlyUsePage.push_back(pageNum);
      }
      else{
        //stavim u memorijski fajl prvi element iz liste 
        removePageToMemoryFile(mostRecentlyUsePage.front());
        mostRecentlyUsePage.pop_front();
        //sada ima prostora u pageList i mogu da ubacim ovaj novi element
        Page page;
        page.content=pageContent;
        pageContent.clear();
        page.key=pageNum;
        pageList.push_back(page);
        pageMap[page.key] = std::prev(pageList.end());
        mostRecentlyUsePage.push_back(pageNum);
      }
      //mora da se rezervise novi vektor za novu stranicu
      pageNum=address.substr(0,5);
      pageContent=std::vector<unsigned char>(PAGE_SIZE, 0x00);
      std::string bajt;
      std::istringstream iss(contentLine);
      int index=convertHexStringToUnsignedInt(address.substr(5));
      while(std::getline(iss, bajt, ' ')){          //split
        pageContent[index]=convertHexStringValueToCharByte(bajt);
        index++;
      }
    }
    else if(pageNum!=""){
      std::string bajt;
      std::istringstream iss(contentLine);
      int index=convertHexStringToUnsignedInt(address.substr(5));
      while(std::getline(iss, bajt, ' ')){          //split
        pageContent[index]=convertHexStringValueToCharByte(bajt);
        index++;
      }
    }
    else{
      pageNum = address.substr(0,5);
      pageContent=std::vector<unsigned char>(PAGE_SIZE, 0x00);
      std::string bajt;
      std::istringstream iss(contentLine);
      int index=convertHexStringToUnsignedInt(address.substr(5));
      while(std::getline(iss, bajt, ' ')){          //split
        pageContent[index]=convertHexStringValueToCharByte(bajt);
        index++;
      }
    }
    std::getline(inputFile, line);
    if(line.empty()){
      if(pageList.size()<NUM_OF_PAGES_IN_PROGRAM){
        //ubaci tu stranicu koja je do sad popunjavana u listu stranica
        Page page;
        page.content=pageContent;
        pageContent.clear();
        page.key=pageNum;
        pageList.push_back(page);
        pageMap[page.key] = std::prev(pageList.end());      //da pokazuje na poslednji dodati element
        mostRecentlyUsePage.push_back(pageNum);
      }
      else{
        //stavim u memorijski fajl prvi element iz liste 
        removePageToMemoryFile(mostRecentlyUsePage.front());
        mostRecentlyUsePage.pop_front();
        //sada ima prostora u pageList i mogu da ubacim ovaj novi element
        Page page;
        page.content=pageContent;
        pageContent.clear();
        page.key=pageNum;
        pageList.push_back(page);
        pageMap[page.key] = std::prev(pageList.end());
        mostRecentlyUsePage.push_back(pageNum);
      }
    }
  }
}

void Emulator::removePageToMemoryFile(std::string pageNum){
  auto iterator = pageMap.find(pageNum);
  auto iter = pageInMemoryFile.find(pageNum);
  if(iter!=pageInMemoryFile.end()){
    //ako ova stranica vec postoji u fajlu gde je memorija samo prepisujem preko tog sadrzaja
    std::fstream memory_file(MEMORY_FILE, std::ios::in | std::ios::out);
    if(memory_file.is_open()){
      memory_file.seekp(pageInMemoryFile[pageNum],std::ios::beg);
      int i=0;
      while(i<iterator->second->content.size()){
        if(i%8==0){
          if(i!=0){
            memory_file << endl;
          }
          memory_file << pageNum << convertIntToHexStringWidth3(i) << ":";
          
        }
        memory_file << " ";
        memory_file << convertUnsignedCharToString(iterator->second->content[i]);
        i++;
      }
      if(i%8==0){
        memory_file << endl;
      }
    }
    memory_file.close();
  }
  else{
    //dodajemo novu stranicu u fajl za memoriju
    std::ofstream memory_file(MEMORY_FILE, std::ios::app);
    if(!memory_file.is_open()){
      cout << "Nije moguce otvoriti izlazni fajl za memoriju!" << endl;
      return;
    }
    std::streampos pos = memory_file.tellp();
    pageInMemoryFile[pageNum]=pos;
    int i=0;
    while(i<iterator->second->content.size()){
      if(i%8==0){
        if(i!=0){
          memory_file << endl;
        }
        memory_file << pageNum << convertIntToHexStringWidth3(i) << ":";
      }
      memory_file << " ";
      memory_file << convertUnsignedCharToString(iterator->second->content[i]);
      i++;
    }
    if(i%8==0){
      memory_file << endl;
    }
    memory_file.close();
  }
  pageList.erase(iterator->second);
  pageMap.erase(iterator);
}

void Emulator::addPageFromMemoryFile(std::string pageNum)
{
  std::ifstream memory_file(MEMORY_FILE, std::ios::in);
  if(!memory_file){
    cout << "GRESKA: Greska prilikom otvaranja ulaznog fajla: " << MEMORY_FILE << endl;
    return;
  }
  // cout << pageInMemoryFile[pageNum] << endl;
  memory_file.seekg(pageInMemoryFile[pageNum],std::ios::beg);
  std::vector<unsigned char> pageContent(PAGE_SIZE);
  //4096 je velicina stranice, a u svakom redu ima po 8 bajta
  std::string line;
  std::string contentLine;
  int i=0;
  while(i<PAGE_SIZE){
    std::getline(memory_file, line);
    contentLine=line.substr(line.find(':')+2);
    std::string bajt;
    std::istringstream iss(contentLine);
    // int index=convertHexStringToUnsignedInt(address.substr(5));
    while(std::getline(iss, bajt, ' ')){          //split
      pageContent[i]=convertHexStringValueToCharByte(bajt);
      i++;
    }  
  }
  Page page;
  page.content=pageContent;
  pageContent.clear();
  page.key=pageNum;
  pageList.push_back(page);
  pageMap[page.key] = std::prev(pageList.end());      //da pokazuje na poslednji dodati element
  mostRecentlyUsePage.push_back(pageNum);
}

void Emulator::displayPages()
{
  std::cout << "Sadržaj liste:" << std::endl;
  for (const auto &page : pageList)
  {
    std::cout << "Ključ: " << page.key << ", Sadržaj: " << bytesToHexString(page.content) << std::endl;
  }
}

unsigned int Emulator::fetch4BytesFromPage(unsigned int addrFromMemory)
{
  std::stringstream ss;
  ss << std::setw(8) << std::setfill('0') << std::hex << addrFromMemory;
  std::string address=ss.str();
  std::string pageNum=address.substr(0,5);
  std::string offs=address.substr(5);
  unsigned int offset=convertHexStringToUnsignedInt(offs);
  providePageExistInListAndUpdateMRUList(pageNum);
  auto pageIterator = pageMap.find(pageNum);
  unsigned char* addr = &pageIterator->second->content[offset];
  unsigned int retValue=0;
  for(int i=0; i<=3; i++){
    retValue |= static_cast<unsigned int>(*addr << i*8);
    addr++;
  }
  return retValue;
}

unsigned char Emulator::fetch1ByteFromPc()
{
  std::stringstream ss;
  ss << std::setw(8) << std::setfill('0') << std::hex << generalRegisters[REGISTER_PC];
  std::string hexAddressPc=ss.str();
  std::string pageNum=hexAddressPc.substr(0,5);
  std::string offs=hexAddressPc.substr(5);
  unsigned int offset=convertHexStringToUnsignedInt(offs);
  providePageExistInListAndUpdateMRUList(pageNum);
  auto pageIterator = pageMap.find(pageNum);
  unsigned char oneByte = pageIterator->second->content[offset];
  generalRegisters[REGISTER_PC]+=1;
  return oneByte;
}

unsigned int Emulator::fetch4BytesFromPc()
{
  std::stringstream ss;
  ss << std::setw(8) << std::setfill('0') << std::hex << generalRegisters[REGISTER_PC];
  std::string hexAddressPc=ss.str();
  std::string pageNum=hexAddressPc.substr(0,5);
  std::string offs=hexAddressPc.substr(5);
  unsigned int offset=convertHexStringToUnsignedInt(offs);
  providePageExistInListAndUpdateMRUList(pageNum);
  auto pageIterator = pageMap.find(pageNum);
  unsigned int fourBytes = (static_cast<unsigned int>(pageIterator->second->content[offset] << 24) |
                            static_cast<unsigned int>(pageIterator->second->content[offset+1] << 16) |
                            static_cast<unsigned int>(pageIterator->second->content[offset+2] << 8) |
                            static_cast<unsigned int>(pageIterator->second->content[offset+3]));
  generalRegisters[REGISTER_PC]+=4;
  return fourBytes;
}

void Emulator::writeGeneralRegisters()
{
  cout << "Emulated processor state:" << endl;
  for(int i=0; i<16; i++){
    std::ostringstream oss;
    oss << std::hex << std::setfill('0') << std::setw(8) << generalRegisters[i];
    cout << "r" << std::dec << i << "=0x" << oss.str();
    if((i+1)%4==0){
      cout << endl;
    }
    else{
      cout << "\t";
    }
  }
}

void Emulator::providePageExistInListAndUpdateMRUList(std::string pageNum)
{
  if(pageMap.find(pageNum)!=pageMap.end()){
    //stranica se nalazi u pageList
    if(mostRecentlyUsePage.back()!=pageNum){
      //da pomerim na kraj ove liste stranicu koja ce sad da se koristi
      mostRecentlyUsePage.remove(pageNum);
      mostRecentlyUsePage.push_back(pageNum);
    }
  }
  else{
    auto pageExistInMemFile = pageInMemoryFile.find(pageNum);
    if(pageExistInMemFile != pageInMemoryFile.end()){
      //stranica se nalazi u mem_file i treba da se ucita
      if(pageList.size() < NUM_OF_PAGES_IN_PROGRAM){
        addPageFromMemoryFile(pageNum);
      }
      else{
        removePageToMemoryFile(mostRecentlyUsePage.front());
        mostRecentlyUsePage.pop_front();
        addPageFromMemoryFile(pageNum);
      }
    }
    else{
      //stranica se ne nalazi u memoriji pa alociramo novu stranicu u kojoj ce biti sve nule
      if(pageList.size() < NUM_OF_PAGES_IN_PROGRAM){
        std::vector<unsigned char> pageContent=std::vector<unsigned char>(PAGE_SIZE, 0x00);
        Page page;
        page.content=pageContent;
        pageContent.clear();
        page.key=pageNum;
        pageList.push_back(page);
        pageMap[page.key] = std::prev(pageList.end());      //da pokazuje na poslednji dodati element
        mostRecentlyUsePage.push_back(pageNum);
      }
      else{
        removePageToMemoryFile(mostRecentlyUsePage.front());
        mostRecentlyUsePage.pop_front();
        std::vector<unsigned char> pageContent=std::vector<unsigned char>(PAGE_SIZE, 0x00);
        Page page;
        page.content=pageContent;
        pageContent.clear();
        page.key=pageNum;
        pageList.push_back(page);
        pageMap[page.key] = std::prev(pageList.end());      //da pokazuje na poslednji dodati element
        mostRecentlyUsePage.push_back(pageNum);
      }
    }
    
    
  }
}

void Emulator::emulationProcess()
{
  std::ofstream output_file(OUTPUT_FILE);
  bool emulation=true;
  std::string instruction;
  while(emulation){
    instruction = convertUnsignedIntToHexStringWidth8(fetch4BytesFromPc());
    unsigned char opcodeMod=convertHexStringValueToCharByte(instruction.substr(0,2));
    int regA = std::stoi(instruction.substr(2,1), nullptr, 16);
    int regB = std::stoi(instruction.substr(3,1), nullptr, 16);
    int regC = std::stoi(instruction.substr(4,1), nullptr, 16);
    int displ = convertStringWidth3ToSignedInt(instruction.substr(5));
    output_file << "Instrukcija: " << instruction << " opcode: " << convertUnsignedCharToString(opcodeMod) << " regA: " << regA << " regB: " << regB << " regC: " << regC << " displ: "  << std::dec << displ << endl;
    switch (opcodeMod)
    {
    case (0x00):
      {
        cout << "Emulated processor executed halt instruction" << endl;
        output_file << "Na redu je HALT instrukcija" << endl;
        emulation=false;
      }
      break;
    case (0x10):
      {
        output_file << "Na redu je instrukcija SOFTVERSKOG PREKIDA" << endl;
        push4BytesToStack(statusRegisters[REGISTER_STATUS]);
        push4BytesToStack(generalRegisters[REGISTER_PC]);
        statusRegisters[REGISTER_CAUSE] = 4;
        statusRegisters[REGISTER_STATUS] = statusRegisters[REGISTER_STATUS] & (~0x1);
        generalRegisters[REGISTER_PC] = statusRegisters[REGISTER_HANDLE];
      }
      break;
    case (0x20):
      {
        output_file << "Na redu je instrukcija CALL sa modifikatorom 0" << endl;
        push4BytesToStack(generalRegisters[REGISTER_PC]);
        generalRegisters[REGISTER_PC]=generalRegisters[regA]+generalRegisters[regB]+displ;
        output_file << "Call instrukcijom se skace na adresu: " << convertUnsignedIntToHexStringWidth8(generalRegisters[REGISTER_PC]) << endl;
      }
      break;
    case (0x21):
      {
        output_file << "Na redu je instrukcija CALL sa modifikatorom 1" << endl;
        push4BytesToStack(generalRegisters[REGISTER_PC]);
        unsigned int addr=generalRegisters[regA]+generalRegisters[regB]+displ;
        output_file << "Adresa sa koje se uzima adresa za CALL: " << convertUnsignedIntToHexStringWidth8(addr) << endl;
        unsigned int wordFromAddr = fetch4BytesFromPage(addr);
        generalRegisters[REGISTER_PC]=wordFromAddr;
        output_file << "Call instrukcijom se skace na adresu: " << convertUnsignedIntToHexStringWidth8(generalRegisters[REGISTER_PC]) << endl;
      }
      break;
    case (0x30):
      {
        output_file << "Na redu je instrukcija JMP sa modifikatorom 0" << endl;
        generalRegisters[REGISTER_PC]=generalRegisters[regA]+displ;
        output_file << "JMP instrukcijom se skace na adresu: " << convertUnsignedIntToHexStringWidth8(generalRegisters[REGISTER_PC]) << endl;
      }
      break;
    case (0x31):
      {
        output_file << "Na redu je instrukcija BEQ sa modifikatorom 1" << endl;
        if(generalRegisters[regB]==generalRegisters[regC]){
          generalRegisters[REGISTER_PC]=generalRegisters[regA]+displ;
          output_file << "BEQ instrukcijom se skace na adresu: " << convertUnsignedIntToHexStringWidth8(generalRegisters[REGISTER_PC]) << endl;
        }
        output_file << "Nije ispunjen uslov za BEQ instrukciju pa se nastavlja dalje!" << endl;
      }
      break;
    case (0x32):
      {
        output_file << "Na redu je instrukcija BNE sa modifikatorom 2" << endl;
        if(generalRegisters[regB]!=generalRegisters[regC]){
          generalRegisters[REGISTER_PC]=generalRegisters[regA]+displ;
          output_file << "BNE instrukcijom se skace na adresu: " << convertUnsignedIntToHexStringWidth8(generalRegisters[REGISTER_PC]) << endl;
        }
        output_file << "Nije ispunjen uslov za BNE instrukciju pa se nastavlja dalje!" << endl;
      }
      break;
    case (0x33):
      {
        output_file << "Na redu je instrukcija BGT sa modifikatorom 3" << endl;
        int registerB = static_cast<int>(generalRegisters[regB]);
        int registerC = static_cast<int>(generalRegisters[regC]);
        if(registerB > registerC){
          generalRegisters[REGISTER_PC]=generalRegisters[regA]+displ;
          output_file << "BGT instrukcijom se skace na adresu: " << convertUnsignedIntToHexStringWidth8(generalRegisters[REGISTER_PC]) << endl;
        }
        output_file << "Nije ispunjen uslov za BGT instrukciju pa se nastavlja dalje!" << endl;
      }
      break;
    case (0x38):
      {
        output_file << "Na redu je instrukcija JMP sa modifikatorom 8" << endl;
        unsigned int addr=generalRegisters[regA]+displ;
        output_file << "Adresa sa koje se uzima adresa za JMP: " << convertUnsignedIntToHexStringWidth8(addr) << endl;
        unsigned int wordFromAddr = fetch4BytesFromPage(addr);
        generalRegisters[REGISTER_PC]=wordFromAddr;
        output_file << "JMP instrukcijom se skace na adresu: " << convertUnsignedIntToHexStringWidth8(generalRegisters[REGISTER_PC]) << endl;
      }
      break;
    case (0x39):
      {
        output_file << "Na redu je instrukcija BEQ sa modifikatorom 9" << endl;
        if(generalRegisters[regB]==generalRegisters[regC]){
          unsigned int addr=generalRegisters[regA]+displ;
          output_file << "Adresa sa koje se uzima adresa za BEQ: " << convertUnsignedIntToHexStringWidth8(addr) << endl;
          unsigned int wordFromAddr = fetch4BytesFromPage(addr);
          generalRegisters[REGISTER_PC]=wordFromAddr;
          output_file << "BEQ instrukcijom se skace na adresu: " << convertUnsignedIntToHexStringWidth8(generalRegisters[REGISTER_PC]) << endl;
        }
        output_file << "Nije ispunjen uslov za BEQ instrukciju pa se nastavlja dalje!" << endl;
      }
      break;
    case (0x3a):
      {
        output_file << "Na redu je instrukcija BNE sa modifikatorom A" << endl;
        if(generalRegisters[regB]!=generalRegisters[regC]){
          unsigned int addr=generalRegisters[regA]+displ;
          output_file << "Adresa sa koje se uzima adresa za BNE: " << convertUnsignedIntToHexStringWidth8(addr) << endl;
          unsigned int wordFromAddr = fetch4BytesFromPage(addr);
          generalRegisters[REGISTER_PC]=wordFromAddr;
          output_file << "BNE instrukcijom se skace na adresu: " << convertUnsignedIntToHexStringWidth8(generalRegisters[REGISTER_PC]) << endl;
        }
        output_file << "Nije ispunjen uslov za BNE instrukciju pa se nastavlja dalje!" << endl;
      }
      break;
    case (0x3b):
      {
        output_file << "Na redu je instrukcija BGT sa modifikatorom B" << endl;
        int registerB = static_cast<int>(generalRegisters[regB]);
        int registerC = static_cast<int>(generalRegisters[regC]);
        if(registerB > registerC){
          unsigned int addr=generalRegisters[regA]+displ;
          output_file << "Adresa sa koje se uzima adresa za BGT: " << convertUnsignedIntToHexStringWidth8(addr) << endl;
          unsigned int wordFromAddr = fetch4BytesFromPage(addr);
          generalRegisters[REGISTER_PC]=wordFromAddr;
          output_file << "BGT instrukcijom se skace na adresu: " << convertUnsignedIntToHexStringWidth8(generalRegisters[REGISTER_PC]) << endl;
        }
        output_file << "Nije ispunjen uslov za BGT instrukciju pa se nastavlja dalje!" << endl;
      }
      break;
    case (0x40):
      {
        //treba da atomicno zamenjuje vrednosti dva registra bez mogucnosti da zamena bude prekinuta usled asinhronog zahteva za prekid ali ja nisam radio sa terminalom i tajmerom pa ne moze da dodje do asinhronog zahteva za prekid
        output_file << "Na redu je instrukcija XCHG sa modifikatorom B" << endl;
        unsigned int temp = generalRegisters[regB];
        generalRegisters[regB] = generalRegisters[regC];
        generalRegisters[regC] = temp;
      }
      break;
    case (0x50):
      {
        output_file << "Na redu je instrukcija ADD" << endl;
        output_file << "Zbir " << std::hex << generalRegisters[regB] << " i " << generalRegisters[regC] << " je: ";
        generalRegisters[regA]=generalRegisters[regB]+generalRegisters[regC];
        output_file << generalRegisters[regA] << endl;
      }
      break;
    case (0x51):
      {
        output_file << "Na redu je instrukcija SUB" << endl;
        output_file << "Razlika " << std::hex << generalRegisters[regB] << " i " << generalRegisters[regC] << " je: ";
        generalRegisters[regA]=generalRegisters[regB]-generalRegisters[regC];
        output_file << generalRegisters[regA] << endl;
      }
      break;
    case (0x52):
      {
        output_file << "Na redu je instrukcija MUL" << endl;
        output_file << "Proizvod " << std::hex << generalRegisters[regB] << " i " << generalRegisters[regC] << " je: ";
        generalRegisters[regA]=generalRegisters[regB]*generalRegisters[regC];
        output_file << generalRegisters[regA] << endl;
      }
      break;
    case (0x53):
      {
        output_file << "Na redu je instrukcija DIV sa modifikatorom B" << endl;
        output_file << "Kolicnik " << std::hex << generalRegisters[regB] << " i " << generalRegisters[regC] << " je: ";
        generalRegisters[regA]=generalRegisters[regB]/generalRegisters[regC];
        output_file << generalRegisters[regA] << endl;
      }
      break;
    case (0x60):
      {
        output_file << "Na redu je instrukcija NOT sa modifikatorom B" << endl;
        output_file << "NOT operacija vrednosti " << std::hex << generalRegisters[regB] << " je: ";
        generalRegisters[regA] = ~generalRegisters[regB];
        output_file << generalRegisters[regA] << endl; 
      }
      break;
    case (0x61):
      {
        output_file << "Na redu je instrukcija AND sa modifikatorom B" << endl;
        output_file << "AND operacija vrednosti " << std::hex << generalRegisters[regB] << " i " << generalRegisters[regC] << " je: ";
        generalRegisters[regA] = generalRegisters[regB] & generalRegisters[regC];
        output_file << generalRegisters[regA] << endl;
      }
      break;
    case (0x62):
      {
        output_file << "Na redu je instrukcija OR sa modifikatorom B" << endl;
        output_file << "OR operacija vrednosti " << std::hex << generalRegisters[regB] << " i " << generalRegisters[regC] << " je: ";
        generalRegisters[regA] = generalRegisters[regB] | generalRegisters[regC];
        output_file << generalRegisters[regA] << endl;
      }
      break;
    case (0x63):
      {
        output_file << "Na redu je instrukcija XOR sa modifikatorom B" << endl;
        output_file << "XOR operacija vrednosti " << std::hex << generalRegisters[regB] << " i " << generalRegisters[regC] << " je: ";
        generalRegisters[regA] = generalRegisters[regB] ^ generalRegisters[regC];
        output_file << generalRegisters[regA] << endl;
      }
      break;
    case (0x70):
      {
        output_file << "Na redu je instrukcija SHL " << endl;
        output_file << "SHL operacija vrednosti " << std::hex << generalRegisters[regB] << " i " << generalRegisters[regC] << " je: ";
        generalRegisters[regA] = generalRegisters[regB] << generalRegisters[regC];
        output_file << generalRegisters[regA] << endl;
      }
      break;
    case (0x71):
      {
        output_file << "Na redu je instrukcija SHR " << endl;
        output_file << "SHR operacija vrednosti " << std::hex << generalRegisters[regB] << " i " << generalRegisters[regC] << " je: ";
        generalRegisters[regA] = generalRegisters[regB] >> generalRegisters[regC];
        output_file << generalRegisters[regA] << endl;
      }
      break;
    case (0x80):
      {
        output_file << "Na redu je instrukcija ST sa modifikatorom 0" << endl;
        unsigned int address=generalRegisters[regA]+generalRegisters[regB]+displ;
        put4BytesToMemoryInLittleEndian(address, generalRegisters[regC]);
        output_file << "Vrednost koja se upisuje u ST instrukciji na adresu: " << std::hex << address << " je: " << std::hex << generalRegisters[regC] << endl;
        output_file << "Dohvacen podatak iz memorije je: " << std::hex << fetch4BytesFromPage(address) << endl;
      }
      break;
    case (0x81):
      {
        output_file << "Na redu je instrukcija ST sa modifikatorom 1 (push instr)" << endl;
        generalRegisters[regA] = generalRegisters[regA] + displ;
        output_file << "SP sada pokazuje na adresu: " << std::hex << generalRegisters[regA] << endl;
        put4BytesToMemoryInLittleEndian(generalRegisters[regA], generalRegisters[regC]);
        output_file << "Vrednost koja se upisuje tamo gde pokazuje SP je: " << std::hex << generalRegisters[regC] << endl;
        output_file << "Dohvacen podatak iz memorije je: " << std::hex << fetch4BytesFromPage(generalRegisters[regA]) << endl;
      }
      break;
    case (0x82):
      {
        output_file << "Na redu je instrukcija ST sa modifikatorom 2" << endl;
        unsigned int addressForFetchAddress=generalRegisters[regA]+generalRegisters[regB]+displ;
        unsigned int address = fetch4BytesFromPage(addressForFetchAddress);
        put4BytesToMemoryInLittleEndian(address, generalRegisters[regC]);
        output_file << "Vrednost koja se upisuje u ST instrukciji na adresu: " << std::hex << address << " je: " << std::hex << generalRegisters[regC] << endl;
        output_file << "Dohvacen podatak iz memorije je: " << std::hex << fetch4BytesFromPage(address) << endl;
      }
      break;
    case (0x90):
      {
        output_file << "Na redu je instrukcija LD sa modifikatorom 0" << endl;
        generalRegisters[regA] = statusRegisters[regB];
        output_file << "U general registar " << regA << " je upisana vrednost: " << std::hex << statusRegisters[regB] << " iz statusnog registra " << regB << endl; 
      }
      break;
    case (0x91):
      {
        output_file << "Na redu je instrukcija LD sa modifikatorom 1" << endl;
        generalRegisters[regA] = generalRegisters[regB] + displ;
        output_file << "U registar " << regA << " se upisuje zbir: " << std::hex << generalRegisters[regB] << "+" << displ << "=" << generalRegisters[regA] << endl;
      }
      break;
    case (0x92):
      {
        output_file << "Na redu je instrukcija LD sa modifikatorom 2" << endl;
        unsigned int address = generalRegisters[regB] + generalRegisters[regC] + displ;
        output_file << "Adresa sa koje se uzima podatak je: " << std::hex << address << "=" << generalRegisters[regB] << "+" << generalRegisters[regC] << "+" << displ << endl;
        generalRegisters[regA] = fetch4BytesFromPage(address);
        output_file << "U registar " << regA << " se upisuje vrednost: " << generalRegisters[regA] << endl;
      }
      break;
    case (0x93):
      {
        output_file << "Na redu je instrukcija LD sa modifikatorom 3 (push instr)" << endl;
        generalRegisters[regA] = fetch4BytesFromPage(generalRegisters[regB]);
        output_file << "Sa adrese " << std::hex << generalRegisters[regB] << "se uzima vrednost: " << generalRegisters[regA] << endl;
        generalRegisters[regB] = generalRegisters[regB] + displ;
        output_file << "Sada je vrednost sp registra: " << std::hex << generalRegisters[regB] << endl;
      }
      break;
    case (0x94):
      {
        output_file << "Na redu je instrukcija LD sa modifikatorom 4" << endl;
        statusRegisters[regA] = generalRegisters[regB];
        output_file << "U status registar " << regA << " je upisana vrednost: " << std::hex << generalRegisters[regB] << " iz general registra " << regB << endl; 
      }
      break;
    case (0x95):
      {
        output_file << "Na redu je instrukcija LD sa modifikatorom 5" << endl;
        statusRegisters[regA] = statusRegisters[regB] | displ;
        output_file << "U registar " << regA << " se upisuje OR: " << std::hex << generalRegisters[regB] << "+" << displ << "=" << generalRegisters[regA] << endl;
      }
      break;
    case (0x96):
      {
        output_file << "Na redu je instrukcija LD sa modifikatorom 6" << endl;
        unsigned int address = generalRegisters[regB] + generalRegisters[regC] + displ;
        output_file << "Adresa sa koje se uzima podatak je: " << std::hex << address << "=" << generalRegisters[regB] << "+" << generalRegisters[regC] << "+" << displ << endl;
        statusRegisters[regA] = fetch4BytesFromPage(address);
        output_file << "U statusni registar " << regA << " se upisuje vrednost: " << statusRegisters[regA] << endl;
      }
      break;
    case (0x97):
      {
        output_file << "Na redu je instrukcija LD sa modifikatorom 7" << endl;
        statusRegisters[regA] = fetch4BytesFromPage(generalRegisters[regB]);
        output_file << "Sa adrese " << std::hex << generalRegisters[regB] << "se uzima vrednost: " << statusRegisters[regA] << endl;
        generalRegisters[regB] = generalRegisters[regB] + displ;
        output_file << "Sada je vrednost sp registra: " << std::hex << generalRegisters[regB] << endl;
      }
      break;

    default:
      {
        cout << "Pozvana instrukcija sa pogresnim operacionim kodom i ide se u prekidnu rutinu!" << endl;
         
      }
      break;
    }
    output_file << std::hex << generalRegisters[REGISTER_PC] << endl;
  }
}

void Emulator::put4BytesToMemoryInLittleEndian(unsigned int address, unsigned int value)
{
  std::stringstream ss;
  ss << std::setw(8) << std::setfill('0') << std::hex << address;
  std::string hexAddress=ss.str();
  std::string pageNum=hexAddress.substr(0,5);
  std::string offs=hexAddress.substr(5);
  unsigned int offset=convertHexStringToUnsignedInt(offs);
  providePageExistInListAndUpdateMRUList(pageNum);
  auto pageIterator = pageMap.find(pageNum);
  unsigned char* addrPointer = &pageIterator->second->content[offset];
  for(int i=0; i<=3; i++){
    *addrPointer=static_cast<unsigned char>((value >> 8*i) & 0xFF);
    addrPointer++;
  }
}

void Emulator::push4BytesToStack(unsigned int value)
{
  std::stringstream ss;
  ss << std::setw(8) << std::setfill('0') << std::hex << generalRegisters[REGISTER_SP];
  std::string hexAddressSP=ss.str();
  std::string pageNum=hexAddressSP.substr(0,5);
  std::string offs=hexAddressSP.substr(5);
  unsigned int offset=convertHexStringToUnsignedInt(offs);
  providePageExistInListAndUpdateMRUList(pageNum);
  auto pageIterator = pageMap.find(pageNum);
  unsigned char* stackPointer = &pageIterator->second->content[offset];
  for(int i=3; i>=0; i--){
    stackPointer--;
    *stackPointer=static_cast<unsigned char>((value >> 8*i) & 0xFF);
  }
  generalRegisters[REGISTER_SP]-=4;
}

unsigned int Emulator::pop4BytesFromStack()
{
  std::stringstream ss;
  ss << std::setw(8) << std::setfill('0') << std::hex << generalRegisters[REGISTER_SP];
  std::string hexAddressSP=ss.str();
  std::string pageNum=hexAddressSP.substr(0,5);
  std::string offs=hexAddressSP.substr(5);
  unsigned int offset=convertHexStringToUnsignedInt(offs);
  providePageExistInListAndUpdateMRUList(pageNum);
  auto pageIterator = pageMap.find(pageNum);
  unsigned char* stackPointer = &pageIterator->second->content[offset];
  unsigned int retValue=0;
  for(int i=0; i<=3; i++){
    retValue |= static_cast<unsigned int>(*stackPointer << i*8);
    stackPointer++;
  }
  generalRegisters[REGISTER_SP]+=4;
  return retValue;
}

unsigned int Emulator::convertHexStringToUnsignedInt(std::string hexValue)
{
  unsigned int value;
  std::istringstream iss(hexValue);
  iss >> std::hex >> value;
  return value;
}

unsigned char Emulator::convertHexStringValueToCharByte(std::string stringValue){
    std::stringstream ss;
    ss << std::hex << stringValue;
    int intValue;
    ss >> intValue;

    unsigned char byte = static_cast<unsigned char>(intValue);
    return byte;
}

std::string Emulator::convertUnsignedCharToString(unsigned char charValue){
    std::ostringstream oss;
    oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(charValue);
    return oss.str();
}

int Emulator::convertStringWidth3ToSignedInt(std::string hexString)
{
    std::string displacement = hexString;
    if(displacement.at(0)=='8' || displacement.at(0)=='9' || displacement.at(0)=='a' || displacement.at(0)=='b' || displacement.at(0)=='c' || displacement.at(0)=='d' ||displacement.at(0)=='e' ||displacement.at(0)=='f'){
      while(displacement.size()<8){
        displacement="f"+displacement;
      }
    }
    unsigned int value;
    std::stringstream ss;
    ss << std::hex << displacement;
    ss >> value;
    int signedValue = static_cast<int>(value);
    return signedValue;
}

std::string Emulator::convertUnsignedIntToHexStringWidth8(unsigned int intValue)
{
    std::ostringstream oss;
    oss << std::hex << std::setw(8) << std::setfill('0') << intValue;
    return oss.str();
}

std::string Emulator::convertIntToHexStringWidth3(int intValue)
{
    std::ostringstream oss;
    oss << std::hex << std::setw(3) << std::setfill('0') << intValue;
    return oss.str();
}

std::string Emulator::bytesToHexString(const std::vector<unsigned char> &bytes) {
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0');
    for (const auto& byte : bytes) {
        oss << std::setw(2) << static_cast<int>(byte);
    }
    return oss.str();
}