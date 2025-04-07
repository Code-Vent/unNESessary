#include <iostream>
#include <fstream>
#include"nes.h"
#include "mapper.h"
#include<bitset>


int main() {
    Nes nes;
    nes.cpu_test();
    //nes.run("../nestest.nes");
    return 0;
}
