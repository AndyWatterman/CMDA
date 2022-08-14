#include "pch.h"
#include "CandidateManager.h"

cmda::CandidateManager::CandidateManager(const std::unique_ptr<cmda::FileLoader>& loader)
{
    assert(loader != nullptr);
    if (!loader->IsLoaded())
        return;

    // always add entry point
    candidates.try_emplace(loader->GetEntryPoint(), CANDIDATE::ENTRY_POINT);

    switch (loader->GetFormat())
    {
    case LIEF::EXE_FORMATS::FORMAT_ELF:
        SearchCandidates(loader->GetBinary<pelf>());
        break;

    case LIEF::EXE_FORMATS::FORMAT_PE:
        // TODO PE
        break;

    case LIEF::EXE_FORMATS::FORMAT_MACHO:
        // TODO MACHO
        break;

    default:
        return;
    }
}

void cmda::CandidateManager::SearchCandidates(const pelf& elf_binary)
{
    // add all exported functions
    for (const auto& func : elf_binary->exported_functions())
        candidates.try_emplace(func.address(), CANDIDATE::EXPORT_FUNC);

    //TODO: add more candidates
}