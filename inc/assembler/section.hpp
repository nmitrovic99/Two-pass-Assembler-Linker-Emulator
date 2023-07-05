#ifndef SECTION_HPP
#define SECTION_HPP

#include <iostream>
#include <string>
#include <list>

using namespace std;


class Section {
  public:
    Section(std::string name, int size, std::string content);

    std::string getName() const;
    int getSize() const;
    int getSizeSecondPass() const;
    std::string getContent() const; 
    void setSize(int s); 
    void setSizeSecondPass(int s);
    void setContent(std::string con);

  private:
    std::string name;
    int size;
    int sizeSecondPass;
    std::string content;

};

#endif