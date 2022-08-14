#include "cmda.h"

int main(int, char**)
{
    cmda::Disassembler dism;
    dism.DisassembleFile("../tests/examples/simple/simple");
    //dism.DisassembleFile("../tests/examples/simple/simple_no_pie");
    //dism.DisassembleFile("../tests/examples/simple/simple.cpp");
}
