#ifndef INCLUDE_FILELOADER_H
#define INCLUDE_FILELOADER_H

#include "pch.h"

using pelf = std::unique_ptr<const LIEF::ELF::Binary>;

namespace cmda
{

class FileLoader {
public:
    FileLoader() = delete;

    template <class T>
    explicit FileLoader(const T& file_path, bool map_file=true) {
        this->map_file = map_file;
        this->file_path = file_path;
        LoadFile();
    }

    explicit FileLoader(const std::vector<uint8_t>& raw_data, bool map_file=true);

    bool IsLoaded() { return (raw_data.size() & data.size()); }

    bool IsMapped() { return (map_file); }

    const auto& GetFilePath() const { return file_path; }

    const auto& GetRawData() const { return raw_data; }

    const auto& GetData() const { return data; }

    auto GetBaseAddress() { return image_base; }

    auto GetEntryPoint() { return entry_point; }

    auto GetFormat() { return binary_type; }

    auto Is64() { return is_64; }

    template<class T> T& GetBinary();

    template <class T>
    bool SaveData(const T& file_path)
    {
        if (data.size()) {
            std::ofstream outfile(file_path, std::ios::out | std::ios::binary);
            outfile.write(reinterpret_cast<const char*>(data.data()), data.size());
            outfile.close();

            if (outfile.good())
                return true;
        }
        return false;
    }

public:
    pelf elf_binary;

private:
    fs::path file_path;
    bool map_file;

    std::vector<uint8_t> raw_data, data;

    bool is_64; // TRUE -> 64-bit binary
    LIEF::EXE_FORMATS binary_type = LIEF::EXE_FORMATS::FORMAT_UNKNOWN;

    // assume we have a deal with a shellcode by default
    uint64_t entry_point = 0;
    uint64_t image_base = 0;

private:
    bool LoadFile();

};

} // namespace cmda

#endif // !INCLUDE_FILELOADER_H