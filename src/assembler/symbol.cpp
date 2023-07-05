#include "../../inc/assembler/symbol.hpp"

Symbol::Symbol(int num, const std::string &name, int value, int size, int bind, int ndx) 
    : num(num), name(name), value(value), size(size), bind(bind), ndx(ndx)
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

int Symbol::getValue() const
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

void Symbol::setSize(int s)
{
  size = s;
}

void Symbol::setBind(int b)
{
  bind=b;
}
