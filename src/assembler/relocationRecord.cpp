#include "../../inc/assembler/relocationRecord.hpp"

RelocationRecord::RelocationRecord(std::string section, int offset, std::string type, int symbolId, int addend)
    : section(section), offset(offset), type(type), symbolId(symbolId), addend(addend)
{
  
}

std::string RelocationRecord::getSection() const
{
  return section;
}

int RelocationRecord::getOffset() const
{
  return offset;
}

std::string RelocationRecord::getType() const
{
  return type;
}

int RelocationRecord::getSymbolId() const
{
  return symbolId;
}

int RelocationRecord::getAddend() const
{
  return addend;
}
