#include "cartridge.h"
#include <cassert>

typedef struct
{
    char name[4];
    uint8_t prg_rom_chunks;
    uint8_t chr_rom_chunks;
    uint8_t mapper1;
    uint8_t mapper2;
    uint8_t prg_ram_size;
    uint8_t tv_system1;
    uint8_t tv_system2;
    char unused[5];
} Header;
static Header header;

Cartridge::Cartridge(Bus& main_bus, Range pgr_addr, Bus& ppu_bus, Range chr_addr, const std::string& file_name)
{
    //assert(mapper != nullptr);
    static Mapper_Template mapper;
    mp = &mapper;
    auto m_id = load(file_name);
    prg_conn = mp->get_prg_rom_conn(pgr_addr);
    chr_conn = mp->get_chr_ram_conn(chr_addr);
    main_bus.add(*prg_conn);
    ppu_bus.add(*chr_conn);

    prg_conn->bytes = &prg;
    chr_conn->bytes = &chr;

    return;
}

Cartridge::~Cartridge() {
    delete prg;
    delete chr;
    delete prg_conn;
    delete chr_conn;
}

uint8_t Cartridge::load(const std::string &file_name) {
    uint8_t nMapperID = 99;
    std::ifstream ifs;
    ifs.open(file_name, std::ifstream::binary);
    if (ifs.is_open())
    {
        // Read file header
        ifs.read((char*)&header, sizeof(Header));

        // If a "trainer" exists we just need to read past
        // it before we get to the good stuff
        if (header.mapper1 & 0x04)
            ifs.seekg(512, std::ios_base::cur);

        // Determine Mapper ID
        nMapperID = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);
        //auto hw_mirror = (header.mapper1 & 0x01) ? VERTICAL : HORIZONTAL;

        // "Discover" File Format
        uint8_t nFileType = 1;
        if ((header.mapper2 & 0x0C) == 0x08) nFileType = 2;

        int prg_size = 0, chr_size = 0;
        if (nFileType == 0)
        {

        }
        else if (nFileType == 1) {
            prg_size = header.prg_rom_chunks * 16384;
            chr_size = header.chr_rom_chunks * 8192;
        }
        else if (nFileType == 2) {
            prg_size = (((header.prg_ram_size & 0x07) << 8) | header.prg_rom_chunks) * 16384;
            chr_size = (((header.prg_ram_size & 0x38) << 8) | header.chr_rom_chunks) * 8192;
        }
        else {
        }
        uint16_t prg_upper = prg_size - 1;
        uint16_t chr_upper = chr_size - 1;

        prg = new Memory({
                                             .lower = 0,
                                             .upper = prg_upper
                                     }, prg_size);
        chr = new Memory({
                                            .lower = 0,
                                            .upper = chr_upper
                                    }, chr_size);

        //auto len = main_bus->bytes->bytes.size();
        ifs.read(prg->ptr(), prg_size);
        ifs.read(chr->ptr(), chr_size);

        ifs.close();
    }
    return nMapperID;
}