#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <stdexcept>

#include "../../inc/linker/linker.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  try{
    Linker ld;

    bool hexOption=false;
    bool outputOption=false;
    bool placeOption=false;
    bool inputFileArgExist=false;
    std::vector<std::string> arguments;
    std::vector<std::string> placeOptionStrings;
    std::vector<std::string> inputFileNames;
    std::string outputFileName;
    if(argc<2){
      cout << "GRESKA: Neodgovarajuci broj argumenata!" << endl;
      return -1;
    }
    for(int i=0; i<argc; i++){
      arguments.push_back(argv[i]);
    }
    int i=1;
    while(i<argc){
      if(arguments[i]=="-o"){
        outputOption=true;
        outputFileName=arguments[i+1];
        i++;
      }
      else if(arguments[i]=="-hex"){
        hexOption=true;
      }
      else if(arguments[i].compare(0,6,"-place")==0){
        placeOption=true;
        placeOptionStrings.push_back(arguments[i]);
      }
      else{
        inputFileArgExist=true;
        inputFileNames.push_back(arguments[i]);
      }
      i++;
    }
    if(!hexOption) {
      // cout << "Ne postoji hex opcija i ne treba da bude generisan izlaz!" << endl;
      throw std::runtime_error("Ne postoji hex opcija i ne treba da bude generisan izlaz!");
    }
    if(!inputFileArgExist){
      // cout << "GRESKA: Ne postoji nijedan ulazni fajl!" << endl;
      throw std::runtime_error("GRESKA: Ne postoji nijedan ulazni fajl!");
    }
    // else{
    //   for(std::string elem:inputFileNames){
    //     cout << elem << endl;
    //   }
    // }
    // if(outputOption){
    //   cout << "Izlazni fajl je: " << outputFileName << endl;
    // }
    // if(placeOption){
    //   for(std::string elem:placeOptionStrings){
    //     cout << elem << endl;
    //   }
    // }
    // else{
    //   cout << "Ne postoji place opcija!" << endl;
    // }
    ld.readObjectFiles(inputFileNames);

    ld.makeMappingPlan(placeOptionStrings);

    ld.makeLinkerSymbolTable();

    ld.resolveRelocationRecords();

    ld.sortMappingPlanList();

    // ld.writeSymbolTable();

    // ld.writeMappingPlanList();

    // ld.writeSectionList();

    // ld.writeRelocationRecordList();

    // ld.writeLinkerSymbolTable();

    ld.writeExecutableCodeToHexFile(outputFileName);
    return 0;
  }
  catch (const std::exception& ex) {
    // Hvatanje izuzetka i ispisivanje greske
    std::cout << "Greska uhvacena: " << ex.what() << std::endl;
    exit(1);
  }
  
}