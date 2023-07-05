#ifndef MAPPING_PLAN_HPP
#define MAPPING_PLAN_HPP

#include <iostream>
#include <string>
#include <list>

using namespace std;


class Plan {
  public:

    Plan(const std::string& section, int size, std::string startAddr, int indexOfObjFile);

    std::string getSection() const;
    int getSize() const;
    std::string getStartAddr() const;
    int getIndexOfObjFile() const;
    void setSection(std::string s);
    void setSize(int s);
    void setStartAddr(std::string a);
    void setIndexOfObjFile(int i);
    


  private:
    std::string section;
    int size;
    std::string startAddr;
    int indexOfObjFile;

};

#endif