#include "cartridge.h"
#include <cassert>

Cartridge::Cartridge(Bus& main_bus, Range pgr, Bus& ppu_bus, Range chr, Mapper* mapper)
{
    assert(mapper != nullptr);
    mp = mapper;
    main_bus.add(mp->get_prg_rom_conn(pgr));
    ppu_bus.add(mp->get_chr_ram_conn(chr));

    return;
}
