#ifndef LITERAL_POOL_HPP
#define LITERAL_POOL_HPP

#include <iostream>
#include <string>
#include <list>

using namespace std;


class LiteralPool {
  public:
    LiteralPool(std::string value, std::string address, std::string section, int type);

    std::string getValue() const;
    std::string getAddress() const;
    std::string getSection() const; 
    int getType() const;
    void setAddress(std::string adr);

  private:
    std::string value;
    std::string address;
    std::string section;
    int type;         //0 za symbol, 1 za literal

};

#endif