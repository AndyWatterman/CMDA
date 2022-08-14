#include "cmda.h"

cmda::Disassembler::Disassembler()
{
}

cmda::Disassembler::~Disassembler()
{
}

void cmda::Disassembler::Setup()
{
    assert(loader != nullptr);

    // Initialize decoder context
    // Reference: https://github.com/HyperDbg/HyperDbg/blob/master/hyperdbg/hprdbgctrl/code/debugger/misc/disassembler.cpp
    if (loader->Is64())
        ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);
    else
        ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_COMPAT_32, ZYDIS_STACK_WIDTH_32);
}

bool cmda::Disassembler::Disassemble()
{
    assert(loader != nullptr && candidate_manager != nullptr);
}