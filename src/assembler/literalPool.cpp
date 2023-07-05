#include "../../inc/assembler/literalPool.hpp"

LiteralPool::LiteralPool(std::string value, std::string address, std::string section, int type)
    : value(value), address(address), section(section), type(type)
{
}

std::string LiteralPool::getValue() const
{
  return value;
}

std::string LiteralPool::getAddress() const
{
  return address;
}

std::string LiteralPool::getSection() const
{
  return section;
}

int LiteralPool::getType() const
{
  return type;
}

void LiteralPool::setAddress(std::string adr)
{
  address=adr;
}
