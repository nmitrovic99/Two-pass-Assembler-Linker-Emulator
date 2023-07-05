#include "../../inc/linker/symbol.hpp"

Symbol::Symbol(int num, const std::string &name, std::string value, int size, int bind, int ndx, int objFile) 
    : num(num), name(name), value(value), size(size), bind(bind), ndx(ndx), objFile(objFile)
{

}
int Symbol::getNum() const
{
  return num;
}

std::string Symbol::getName() const
{
  return name;
}

std::string Symbol::getValue() const
{
  return value;
}

int Symbol::getSize() const
{
  return size;
}

int Symbol::getBind() const
{
  return bind;
}

int Symbol::getNdx() const
{
  return ndx;
}

void Symbol::setNum(int n)
{
  num = n;
}

void Symbol::setName(std::string n)
{
  name = n;
}

void Symbol::setValue(std::string v)
{
  value = v;
}

void Symbol::setSize(int s)
{
  size = s;
}

void Symbol::setBind(int b)
{
  bind=b;
}

void Symbol::setNdx(int n)
{
  ndx = n;
}

int Symbol::getObjFile() const
{
  return objFile;
}

void Symbol::setObjFile(int o)
{
  objFile=o;
}
