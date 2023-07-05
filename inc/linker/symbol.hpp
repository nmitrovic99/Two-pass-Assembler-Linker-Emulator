#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <iostream>
#include <string>
#include <list>

using namespace std;


class Symbol {
  public:

    Symbol(int num, const std::string& name, std::string value, int size, int bind, int Ndx, int objFile);

    int getNum() const;
    std::string getName() const;
    std::string getValue() const;
    int getSize() const;
    int getBind() const;
    int getNdx() const;
    void setNum(int n);
    void setName(std::string n);
    void setValue(std::string v);
    void setSize(int s);
    void setBind(int b);
    void setNdx(int n);
    int getObjFile() const;
    void setObjFile(int o);

  private:
    int num;
    std::string name;
    std::string value;
    int size;
    int bind;
    int ndx;
    int objFile;

};

#endif