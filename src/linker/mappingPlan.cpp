#include "../../inc/linker/mappingPlan.hpp"

Plan::Plan(const std::string &section, int size, std::string startAddr, int indexOfObjFile)
  : section(section), size(size), startAddr(startAddr), indexOfObjFile(indexOfObjFile)
{
}

std::string Plan::getSection() const
{
  return section;
}

int Plan::getSize() const
{
  return size;
}

std::string Plan::getStartAddr() const
{
  return startAddr;
}

int Plan::getIndexOfObjFile() const
{
  return indexOfObjFile;
}

void Plan::setSection(std::string s)
{
  section=s;
}

void Plan::setSize(int s)
{
  size=s;
}

void Plan::setStartAddr(std::string a)
{
  startAddr=a;
}

void Plan::setIndexOfObjFile(int i)
{
  indexOfObjFile=i;
}
