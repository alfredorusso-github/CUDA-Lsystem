#include "lsystem.h"

int main(int argc, char const *argv[])
{
    lsystem custom("F-G-G", "F F-G+F+G-F G GG");
    custom.setCustomMeaning("F", custom.DRAW);
    custom.setCustomMeaning("G", custom.DONOTHING);
    custom.setCustomMeaning("-", custom.TURNLEFT);
    custom.setCustomMeaning("+", custom.TURNRIGHT);

    custom.execute(7);
    custom.execute(7, lsystem::useGPU);

    std::cout << "Il risultato di CPU e GPU è uguale: " << (custom.get_result() == custom.get_GPUResult()) << std::endl;

    // custom.execute(7);
    // custom.write("Custom");
    // custom.draw("Custom", 20, 10);

    return 0;
}
