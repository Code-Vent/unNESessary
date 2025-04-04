#include <iostream>
#include <fstream>
#include"nes.h"
#include "mapper.h"
#include<bitset>


int main() {
    Nes nes;
    nes.cpu_test();
    //nes.run("../mario.nes");
    return 0;
}
