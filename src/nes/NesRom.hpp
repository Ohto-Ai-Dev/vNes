#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

class NesRom {
public:
    NesRom& load(const std::string& filename) {
        auto& rom = *this;
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file");
        }

        // 读取头部信息
        file.read(reinterpret_cast<char*>(&rom.header_), sizeof(rom.header_));

        // 读取PRG数据
        rom.prg_rom_.resize(rom.header_.prg_rom_size * 16 * 1024);
        file.read(reinterpret_cast<char*>(rom.prg_rom_.data()), rom.prg_rom_.size());

        // 读取CHR数据
        rom.chr_rom_.resize(rom.header_.chr_rom_size * 8 * 1024);
        file.read(reinterpret_cast<char*>(rom.chr_rom_.data()), rom.chr_rom_.size());

        if (file.fail()) {
            std::cout << "Failed to open file." << std::endl;
            std::cout << "Error code: " << file.rdstate() << std::endl;
            if (file.eof()) {
                std::cout << "End of file reached." << std::endl;
            }
            if (file.bad()) {
                std::cout << "Fatal error occurred." << std::endl;
            }
        }
        return rom;
    }

    // 获取PRG数据
    const std::vector<uint8_t>& prg_rom() const {
        return prg_rom_;
    }

    // 获取CHR数据
    const std::vector<uint8_t>& chr_rom() const {
        return chr_rom_;
    }

    // 获取Mapper号
    //uint8_t mapper() const {
    //    return (header_.mapper_2 >> 4) | (header_.mapper_1 & 0xF0);
    //}

    // 获取PRG ROM的大小，单位为16KB
    uint8_t prg_rom_size() const {
        return header_.prg_rom_size;
    }

    // 获取CHR ROM的大小，单位为8KB
    uint8_t chr_rom_size() const {
        return header_.chr_rom_size;
    }

private:
    // NES ROM文件头部信息
    // flag_6
    // 76543210
    // ||||||||
    // |||||||+- Mirroring: 0: horizontal (vertical arrangement) (CIRAM A10 = PPU A11)
    // |||||||              1: vertical (horizontal arrangement) (CIRAM A10 = PPU A10)
    // ||||||+-- 1: Cartridge contains battery-backed PRG RAM ($6000-7FFF) or other persistent memory
    // |||||+--- 1: 512-byte trainer at $7000-$71FF (stored before PRG data)
    // ||||+---- 1: Ignore mirroring control or above mirroring bit; instead provide four-screen VRAM
    // ++++----- Lower nybble of ROM Mapper type
    // flag_7
    // 76543210
    // ||||||||
    // |||||||+- VS Unisystem
    // ||||||+-- PlayChoice-10 (8KB of Hint Screen data stored after CHR data)
    // |||||+--- If equal to 2, flags 8-15 are in NES 2.0 format
    // ++++----- Upper nybble of ROM Mapper type
    struct Header {
        char magic[4];
        uint8_t prg_rom_size;
        uint8_t chr_rom_size;
        uint8_t flags_6;
        uint8_t flags_7;
        char zeros[8];
    } header_;

    // PRG数据
    std::vector<uint8_t> prg_rom_;

    // CHR数据
    std::vector<uint8_t> chr_rom_;
};
