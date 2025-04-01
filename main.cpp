#include <iostream>
#include <fstream>
#include"nes.h"
#include "mapper.h"
#include<bitset>


int main() {
    Nes nes("../mario.nes");
    nes.cpu_test();
    return 0;
}
