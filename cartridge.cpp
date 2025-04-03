#include "cartridge.h"
#include <cassert>
#include"nrom.h"


Cartridge::Cartridge(Bus& mb, Range pgr, Bus& pb, Range chr)
:main_bus(mb), prg_addr(pgr), ppu_bus(pb), chr_addr(chr)
{
    clear();
}

void Cartridge::clear() {
    mapper = nullptr;
    prg_rom = nullptr;
    prg_ram = nullptr;
    chr = nullptr;
    prg_rom_conn = nullptr;
    prg_ram_conn = nullptr;
    chr_conn = nullptr;
}

Cartridge::~Cartridge() {
    if(prg_rom)delete prg_rom;
    if(chr)delete chr;
    if(prg_rom_conn)delete prg_rom_conn;
    if(chr_conn)delete chr_conn;
    if(prg_ram_conn)delete prg_ram_conn;
    if(prg_ram)delete prg_ram;
}

void Cartridge::load(const std::string &file_name) {
    Header header;
    auto m_id = _load(file_name, header);
    switch (m_id) {
        case 0:
            mapper = new Mapper_NROM;
            break;
        default:
            mapper = new Mapper_Template;
    }
    prg_rom_conn = mapper->get_prg_rom_conn(prg_addr);
    if(header.prg_ram_size != 0)
        prg_ram_conn = mapper->get_prg_ram_conn(prg_addr);
    if(header.chr_rom_chunks == 0)
        chr_conn = mapper->get_chr_ram_conn(chr_addr);
    else
        chr_conn = mapper->get_chr_rom_conn(chr_addr);
    main_bus.add(*prg_rom_conn);
    if(prg_ram_conn)
        main_bus.add(*prg_rom_conn);
    ppu_bus.add(*chr_conn);

    prg_rom_conn->bytes = &prg_rom;
    if(prg_ram_conn)
        prg_ram_conn->bytes = &prg_ram;
    chr_conn->bytes = &chr;

    mapper->map(header);
    return;
}

uint8_t Cartridge::_load(const std::string &file_name, Header& header) {
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
        nMapperID = (header.mapper2 & 0xF0) | (header.mapper1 >> 4);
        //auto hw_mirror = (header.mapper1 & 0x01) ? VERTICAL : HORIZONTAL;


        int prg_rom_size = 0, prg_ram_size = 0, chr_size = 0;

        prg_rom_size = header.prg_rom_chunks * 16384;
        prg_ram_size = header.prg_ram_size * 8192;
        if(header.chr_rom_chunks != 0)
            chr_size = header.chr_rom_chunks * 8192;
        else
            chr_size = 8192;

        uint32_t prg_rom_upper = prg_rom_size - 1;
        uint32_t prg_ram_upper = prg_ram_size - 1;
        uint32_t chr_upper = chr_size - 1;

        prg_rom = new Memory(
        {.lower = 0, .upper = prg_rom_upper},
           prg_rom_size
        );

        if(prg_ram_size != 0)
            prg_ram = new Memory(
                    {.lower = 0, .upper = prg_ram_upper},
                    prg_ram_size
            );

        chr = new Memory(
        {.lower = 0, .upper = chr_upper},
           chr_size
        );

        ifs.read(prg_rom->ptr(), prg_rom_size);
        ifs.read(chr->ptr(), chr_size);

        ifs.close();
    }
    return nMapperID;
}