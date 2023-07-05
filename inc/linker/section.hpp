#ifndef SECTION_HPP
#define SECTION_HPP

#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;


class Section {
  public:
    Section(std::string name, int size, std::vector<std::string> content, int objFile);

    std::string getName() const;
    int getSize() const;
    std::vector<std::string> getContent() const; 
    void setSize(int s);
    // void setContent(std::string con);
    int getObjFile() const;
    void setObjFile(int o);
    void setByteForContent(std::string byte, int offset);

  private:
    std::string name;
    int size;
    std::vector<std::string> content;
    int objFile;

};

#endif