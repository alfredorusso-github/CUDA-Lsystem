#include "../L-system/lsystem.h"

int main(int argc, char const *argv[])
{
    // Island Curve
    lsystem island("F-F-F-F", "F F-b+FF-F-FF-Fb-FF+b-FF+F+FF+Fb+FFF b bbbbbb");
    island.execute(2);
    island.executeOnGPU(2);
    island.write("Island Curve");
    island.draw("Island Curve", 90, 10);

    return 0;
}
