#include "../L-system/lsystem.h"

int main(int argc, char const *argv[])
{
    // Sticks
    lsystem sticks("X", "X F[+X]F[-X]+X F FF");
    sticks.execute(9);
    sticks.executeOnGPU(9);
    sticks.write("Sticks");
    sticks.draw("Sticks", 20, 10, lsystem::UP);

    return 0;
}
