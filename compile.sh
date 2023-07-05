bison -d -o misc/parser.tab.cc misc/bison.y
flex -o misc/lex.yy.c --header-file=misc/lex.yy.h misc/flex.l
g++ -o asembler misc/parser.tab.cc misc/lex.yy.c src/assembler/*.cpp
g++ -o linker src/linker/*.cpp
g++ -o emulator src/emulator/*.cpp