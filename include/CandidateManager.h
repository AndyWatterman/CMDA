#ifndef INCLUDE_CandidateManager_H
#define INCLUDE_CandidateManager_H

#include "pch.h"
#include "FileLoader.h"

namespace cmda
{

enum class CANDIDATE: uint8_t
{
    ENTRY_POINT,
    EXPORT_FUNC
};

struct TCandidate {
    CANDIDATE type;
};

class CandidateManager
{
public:
    CandidateManager() = delete;
    explicit CandidateManager(const std::unique_ptr<cmda::FileLoader>& loader);

    //uint64_t

private:
    std::map<uint64_t, TCandidate> candidates;

    void SearchCandidates(const pelf& elf_binary);
};

} // namespace cmda

#endif //!INCLUDE_CandidateManager_H