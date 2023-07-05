#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <iostream>
#include <string>
#include <list>

using namespace std;


class Symbol {
  public:

    Symbol(int num, const std::string& name, int value, int size, int bind, int Ndx);

    int getNum() const;
    std::string getName() const;
    int getValue() const;
    int getSize() const;
    int getBind() const;
    int getNdx() const;
    void setSize(int s);
    void setBind(int b);
    


  private:
    int num;
    std::string name;
    int value;
    int size;
    int bind;
    int ndx;

};

#endif