#include <iostream>
#include <fstream>
#include <cstring>
#include "../../misc/parser.tab.hh"
#include "../../inc/assembler/assembler.hpp"

extern void yyset_in(FILE *);

int main(int argc, char *argv[]) {
    std::string outputFile;
    FILE* fp;
    if(argc<2 || argc>4){
        cout << "GRESKA: Neodgovarajuci broj argumenata!" << endl;
        return -1;
    }
    if(argc>2){
        if(argc<4){
            cout << "GRESKA: Neodgovarajuci broj argumenata!" << endl;
            return -1;
        }
        std::string argv1=argv[1];
        if(argv1!="-o"){
            cout << argv[1] << endl;
            cout << "GRESKA: Drugi argument mora biti opcija -o." << endl;
            return -1;
        }
        outputFile=argv[2];
        int size=std::strlen(argv[3]);
        char inputFile[size];
        std::strcpy(inputFile, argv[3]);
        fp = fopen(inputFile, "r");
    }
    else{
        int size=std::strlen(argv[1]);
        char inputFile[size];
        std::strcpy(inputFile, argv[1]);
        fp = fopen(inputFile, "r");
        outputFile=argv[1];
        outputFile+=".o";
    }
    
    // char filename[] = "./assembler/test/primer.s";
    // char filename[] = "./assembler/test/primerZad9.s";
    // char filename[] = "assembler/test/proba.s";
    

    // fp = fopen(filename, "r");
    if (fp == NULL) {
        cout << "GRESKA: Nije moguce otvoriti ulazni fajl!" << endl;
        return -1;
    }
    // rad sa fajlom

    // yyFlexLexer lexer;  // Instanciranje leksera
    // std::ifstream inputFile("input.txt");
    // if (inputFile.is_open()) {
    //   lexer.yyset_in(&inputFile);  // Postavljanje novog ulaznog toka za lekser
    //   lexer.yylex();  // Pokretanje leksera
    //   inputFile.close();
    // } else {
    //   std::cerr << "Unable to open input file." << std::endl;
    // }
    Assembler as;
    // Postavljamo tok za lexer
    yyset_in(fp);

    // Pokrecemo parsiranje
    yyparse();
    as.fillLiteralPool();
    fclose(fp);

    if(argc>2){
        int size=std::strlen(argv[3]);
        char inputFile[size];
        std::strcpy(inputFile, argv[3]);
        fp = fopen(inputFile, "r");
    }
    else{
        int size=std::strlen(argv[1]);
        char inputFile[size];
        std::strcpy(inputFile, argv[1]);
        fp = fopen(inputFile, "r");
    }
    // fp = fopen(filename, "r");
    if (fp == NULL) {
        cout << "GRESKA: Nije moguce otvoriti ulazni fajl!" << endl;
        return -1;
    }
    Assembler::secondPass = true;

    yyset_in(fp);
    yyparse();
    as.fillSectionWithContentFromLiteralPool();
    fclose(fp);

    as.writeSymbolTable(outputFile);

    as.writeSectionList(outputFile);

    as.writeRelocationRecordList(outputFile);

    // as.writeLiteralPoolList();
    
    
    return 0;
}