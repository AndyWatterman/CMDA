#ifndef INCLUDE_ELFFILELOADER_H
#define INCLUDE_ELFFILELOADER_H

#include "pch.h"
#include "macro.h"

namespace cmda
{

class ElfFileLoader
{
public:
    static std::vector<uint8_t> MapBinary(const pelf& binary) {

        // reserve memory for mapped binary
        auto result = std::vector<uint8_t>(binary->virtual_size());

        // map binary
        for (const auto &segment : binary->segments()) {
            auto rva = segment.virtual_address() - binary->imagebase();
            auto sz = segment.virtual_size();

            // get segment data
            const std::vector<uint8_t> content = binary->get_content_from_virtual_address(
                segment.virtual_address(),
                segment.get_content_size()
            );

            // copy segment data to appropriate location
            std::copy(content.begin(), content.end(), result.begin() + rva);
        }

        return result;
    }
};

}

#endif // !INCLUDE_ELFFILELOADER_H