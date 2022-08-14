#include "pch.h"
#include "FileLoader.h"
#include "ElfFileLoader.hpp"

cmda::FileLoader::FileLoader(const std::vector<uint8_t>& raw_data, bool map_file){
    this->map_file = map_file;
    this->raw_data = raw_data;
    LoadFile();
}

bool cmda::FileLoader::LoadFile() {
    if (!raw_data.size()) {
        if (file_path.has_filename()) {

            std::ifstream file(file_path, std::ios::binary);
            if (file.is_open()) {
                // Reference:
                // https://stackoverflow.com/questions/15138353/how-to-read-a-binary-file-into-a-vector-of-unsigned-chars

                // stop eating new lines in binary mode
                file.unsetf(std::ios::skipws);

                // get file size
                std::streampos file_size;

                file.seekg(0, std::ios::end);
                file_size = file.tellg();
                file.seekg(0, std::ios::beg);

                // reserve buffer
                raw_data.resize(file_size);

                // read all file to buffer
                file.read(reinterpret_cast<std::ifstream::char_type*>(&raw_data.front()), file_size);
                file.close();
            }

            // failed to load file
            if (file.bad() || !raw_data.size())
                return false;
        }
    }

    if (!raw_data.size())
        return false;

    // if we don't need to map, then it is a shellcode
    if (!map_file) {
        data = raw_data;
        return true;
    }

    if (LIEF::ELF::is_elf(raw_data)) {
        // parse ELF file
        elf_binary = LIEF::ELF::Parser::parse(raw_data);
        if (!elf_binary)
            return false;

        // map file to memory
        data = cmda::ElfFileLoader::MapBinary(elf_binary);

        // save some binary information
        entry_point = elf_binary->entrypoint();
        image_base = elf_binary->imagebase();

        // check bitness
        if (elf_binary->type() == LIEF::ELF::ELF_CLASS::ELFCLASS64)
            is_64 = true;

        // it is an ELF file
        binary_type = elf_binary->format();
    }
    else if (LIEF::PE::is_pe(raw_data)) {
        //TODO: pe file
    }
    else if (LIEF::MachO::is_macho(raw_data)) {
        //TODO: macos
    }
    else
        return false;

    return true;
}

template<> pelf& cmda::FileLoader::GetBinary()
{
    return elf_binary;
    //return 1;
}