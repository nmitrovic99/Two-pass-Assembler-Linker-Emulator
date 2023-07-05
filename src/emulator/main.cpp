#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#include "../../inc/emulator/emulator.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  Emulator emul;

  if(argc!=2){
    cout << "GRESKA: Neodgovarajuci broj argumenata!" << endl;
    return -1;
  }
  std::string inputHexFile=argv[1];
  emul.readHexFile(inputHexFile);
  
  // emul.removePageToMemoryFile("4000f");
  // // emul.displayPages();

  // emul.addPageFromMemoryFile("4000f");
  // // emul.displayPages();

  emul.emulationProcess();
  // emul.push4BytesToStack(0xaabbccdd);
  // cout << std::hex << emul.pop4BytesFromStack() << endl;

  emul.writeGeneralRegisters();
  // emul.displayPages();

  return 0;
}