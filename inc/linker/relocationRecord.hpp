#ifndef RELOCATION_RECORD_HPP
#define RELOCATION_RECORD_HPP

#include <iostream>
#include <string>
#include <list>

using namespace std;


class RelocationRecord {
  public:
    RelocationRecord(std::string section, int offset, std::string type, int symbolId, int addend, int objFile);

    std::string getSection() const;
    int getOffset() const;
    std::string getType() const;  
    int getSymbolId() const;
    int getAddend() const;
    int getObjFile() const;
    void setObjFile(int o);

  private:
    std::string section;
    int offset;
    std::string type;
    int symbolId;
    int addend;
    int objFile;

};

#endif