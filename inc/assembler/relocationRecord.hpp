#ifndef RELOCATION_RECORD_HPP
#define RELOCATION_RECORD_HPP

#include <iostream>
#include <string>
#include <list>

using namespace std;


class RelocationRecord {
  public:
    RelocationRecord(std::string section, int offset, std::string type, int symbolId, int addend);

    std::string getSection() const;
    int getOffset() const;
    std::string getType() const;  
    int getSymbolId() const;
    int getAddend() const;

  private:
    std::string section;
    int offset;
    std::string type;
    int symbolId;
    int addend;

};

#endif