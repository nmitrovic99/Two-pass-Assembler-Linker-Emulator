#ifndef LINKER_HPP
#define LINKER_HPP

#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <stdexcept>

#include "symbol.hpp"
#include "section.hpp"
#include "relocationRecord.hpp"
#include "mappingPlan.hpp"

using namespace std;


class Linker {
  public:
    Linker();
    static std::list<Symbol> symbolTable;
    void addToSymbolTable(Symbol symbol);
    void writeSymbolTable();
    std::string getSymNameForSymIdAndObjFile(int symbolId, int objFile);
    bool symbolIsSection(int symbolId, int objFile);
    // int getNdxInSymbolTable(std::string section_name);
    // void setSizeForSymbol(std::string symbol_name, int size);
    // int getSizeForSymbol(std::string symbol_name);
    // int getNumForSymbol(std::string symbol_name);
    // int getValueForSymbol(std::string symbol_name);
    // std::string getNameForSymbol(int symbolId);
    // void setBindForSymbol(std::string symbol_name, int bind);
    // bool symbolExistInTable(std::string symbol_name);

    static std::list<Section> sectionList;
    void addToSectionList(Section section);
    void writeSectionList();
    void setContentFromRelocationRecord(std::string section_name, int objFile, std::string content, int offset);
    std::vector<std::string> getContentForSection(std::string section, int indexOfObjFile);
    // void setSizeForSection(std::string section_name, int size);
    // int getSizeForSection(std::string section_name);
    // void setSizeSecondPassForSection(std::string section_name, int size);
    // int getSizeSecondPassForSection(std::string section_name);
    // void setContentForSection(std::string section_name, std::string content);
    // void addContentForSection(std::string section_name, std::string content);

    static std::list<RelocationRecord> relocationRecordList;
    void addToRelocationRecordList(RelocationRecord relocationRecord);
    void writeRelocationRecordList();
    // void insertToRelocationTableForR32(std::string symbol);

    static std::list<Plan> mappingPlanList;
    void addToMappingPlanList(Plan mappingPlan);
    void writeMappingPlanList();
    bool existInMappingPlanList(std::string section, int objFile);
    //da li ima slobodnog mesta da se stavi sekcija na tu adresu
    bool isFreeSpaceForPutSection(std::string addr, int sectionSize);
    int findFirstFreeSpaceForSection(std::string addr, int sectionSize);
    int getSectionSizeInMappingPlan(std::string section);
    std::string getStartAddrForSection(std::string section, int objFile);

    static std::list<Symbol> linkerSymbolTable;
    void addToLinkerSymbolTable(Symbol symbol);
    void writeLinkerSymbolTable();
    int getNdxForSectionInLinkerSymbolTable(int ndxInOldSymTable, int objFile);
    std::string getSymAddrFromPlanAndSymTable(std::string symName, int ndxInOldSymTable, int objFile);
    std::string getAddrFromLinkerSymbolTable(std::string symName);
    void sortMappingPlanList();

    void readObjectFiles(std::vector<std::string> inputFiles);
    void makeMappingPlan(std::vector<std::string> placeOptionStrings);
    void makeLinkerSymbolTable();
    void resolveRelocationRecords();
    void writeExecutableCodeToHexFile(const std::string& outputFileName);

  private:
    std::vector<int> numOfSymbolsPerObjectFile;
    std::vector<int> numOfSectionsPerObjectFile;
    std::vector<int> numOfRelocationRecordsPerObjectFile;
    std::string stringToLittleEndian(std::string literal);
    // std::string convertIntToHexString(int intValue);
    std::string convertIntToHexStringWidth8(int intValue);
    // std::string convertIntToHexStringWidth3(int intValue);
    unsigned int convertHexStringToInt(std::string hexValue);
    int convertStringToInt(std::string stringValue);

};



#endif