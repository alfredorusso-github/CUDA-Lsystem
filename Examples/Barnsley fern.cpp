#include "../L-system/lsystem.h"

int main(int argc, char const *argv[])
{
    // Barnsley fern
    lsystem barnsley("X", "X F+[[X]-X]-F[-FX]+X F FF");
    barnsley.execute(7);
    barnsley.write("Barnsley Fern");
    barnsley.draw("Barnsley Fern", 25, 10);

    return 0;
}
