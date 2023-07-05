#include "../../inc/assembler/section.hpp"

Section::Section(std::string name, int size, std::string content)
  : name(name), size(size), content(content), sizeSecondPass(0)
{
}

std::string Section::getName() const
{
  return name;
}

int Section::getSize() const
{
  return size;
}

int Section::getSizeSecondPass() const
{
  return sizeSecondPass;
}

std::string Section::getContent() const
{
  return content;
}

void Section::setSize(int s)
{
  size = s;
}

void Section::setSizeSecondPass(int s)
{
  sizeSecondPass = s;
}

void Section::setContent(std::string con)
{
  content=con;
}
