#include "../L-system/lsystem.h"

int main(int argc, char const *argv[])
{
    // Dragon Curve
    lsystem dragon("FX", "X X+YF+ Y -FX-Y");
    dragon.execute(12);
    dragon.executeOnGPU(12);
    dragon.write("Dragon Curve");
    dragon.draw("Dragon Curve", 90, 10);

    return 0;
}
