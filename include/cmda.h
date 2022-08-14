#ifndef INCLUDE_CMDA_H
#define INCLUDE_CMDA_H

#include "pch.h"
#include "FileLoader.h"
#include "CandidateManager.h"

namespace cmda
{

class Disassembler
{
public:
    Disassembler();
    Disassembler(Disassembler &&) = delete;
    Disassembler(const Disassembler &) = delete;
    Disassembler &operator=(Disassembler &&) = delete;
    Disassembler &operator=(const Disassembler &) = delete;
    ~Disassembler();

    template <class T>
    bool DisassembleFile(const T& filename)
    {
        // Load file
        loader = std::make_unique<FileLoader>(filename);
        if (!loader->IsLoaded())
            return false;

        // Get starting locations
        candidate_manager = std::make_unique<CandidateManager>(loader);

        // Setup disassembler
        Setup();

        // Start disassembling
        auto result = Disassemble();

        return true;
    }

private:
    std::unique_ptr<FileLoader> loader;
    std::unique_ptr<CandidateManager> candidate_manager;

    ZydisDecoder decoder;

    void Setup();
    bool Disassemble();
};


} // namespace cmda

#endif // !INCLUDE_CMDA_H

