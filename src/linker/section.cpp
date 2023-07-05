#include "../../inc/linker/section.hpp"

Section::Section(std::string name, int size, std::vector<std::string> content, int objFile)
  : name(name), size(size), content(content), objFile(objFile)
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

std::vector<std::string> Section::getContent() const
{
  return content;
}

void Section::setSize(int s)
{
  size = s;
}

int Section::getObjFile() const
{
  return objFile;
}

void Section::setObjFile(int o)
{
  objFile=o;
}

void Section::setByteForContent(std::string byte, int offset)
{
  content[offset]=byte;
}

// void Section::setContent(std::string con)
// {
//   content=con;
// }
