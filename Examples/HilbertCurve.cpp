#include "../L-system/lsystem.h"

int main(int argc, char const *argv[])
{
    // Hilber Curve
    lsystem hilbert("LFL+F+LFL", "L -RF+LFL+FR- R +LF-RFR-FL+");
    hilbert.execute(5);
    hilbert.executeOnGPU(5);
    hilbert.write("Hilbert Curve");
    hilbert.draw("Hilbert Curve", 90, 10);

    return 0;
}
