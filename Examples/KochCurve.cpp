#include "../L-system/lsystem.h"

int main(int argc, char const *argv[])
{
    // Koch Curve
    lsystem koch("F", "F F+F-F-F+F");
    koch.execute(4);
    koch.execute(4);
    koch.write("Koch Curve");
    koch.draw("Koch Curve", 90, 10);

    return 0;
}
