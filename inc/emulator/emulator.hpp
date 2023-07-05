#ifndef EMULATOR_HPP
#define EMULATOR_HPP

#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <cstdint>

using namespace std;

#define PAGE_SIZE 4096
#define MEMORY_FILE "memory_file.hex"
#define OUTPUT_FILE "output_file.txt"
#define REGISTER_PC 15
#define REGISTER_SP 14
#define PROGRAM_START_ADDRESS 0x40000000
#define NUM_OF_PAGES_IN_PROGRAM 4
#define REGISTER_STATUS 0
#define REGISTER_HANDLE 1
#define REGISTER_CAUSE 2

typedef struct  {
  std::vector<unsigned char> content;
  std::string key;
}Page;

class Emulator {
  public:
    Emulator();
    void readHexFile(std::string hexFile);
    void removePageToMemoryFile(std::string pageNum);
    void addPageFromMemoryFile(std::string pageNum);
    void displayPages();
    unsigned int fetch4BytesFromPage(unsigned int addrFromMemory);
    unsigned char fetch1ByteFromPc();
    unsigned int fetch4BytesFromPc();
    void writeGeneralRegisters();
    void providePageExistInListAndUpdateMRUList(std::string pageNum);
    void emulationProcess();
    void put4BytesToMemoryInLittleEndian(unsigned int address, unsigned int value);
    void push4BytesToStack(unsigned int value);
    unsigned int pop4BytesFromStack();

    std::string bytesToHexString(const std::vector<unsigned char>& bytes);
  private:
    std::vector<unsigned int> generalRegisters;
    std::vector<unsigned int> statusRegisters;
    std::list<Page> pageList;
    std::list<std::string> mostRecentlyUsePage;
    std::unordered_map<std::string, std::list<Page>::iterator> pageMap;
    std::unordered_map<std::string, std::streampos> pageInMemoryFile;
    // void writePageToMemoryFile(std::vector<unsigned char> page, std::string pageNum);

    // std::string stringToLittleEndian(std::string literal);
    // std::string convertIntToHexString(int intValue);
    std::string convertUnsignedIntToHexStringWidth8(unsigned int intValue);
    std::string convertIntToHexStringWidth3(int intValue);
    unsigned int convertHexStringToUnsignedInt(std::string hexValue);
    // int convertStringToInt(std::string stringValue);
    unsigned char convertHexStringValueToCharByte(std::string stringValue);
    std::string convertUnsignedCharToString(unsigned char charValue);
    int convertStringWidth3ToSignedInt(std::string hexString);
    
};



#endif