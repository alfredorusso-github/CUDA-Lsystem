#include "../L-system/lsystem.h"
#include "../utils/MeasureTime.h"

int main(int argc, char const *argv[])
{
    // Barnsley fern
    lsystem barnsley("X", "X F+[[X]-X]-F[-FX]+X F FF");
    int iteration = 14;

    barnsley.executeOnGPUWithModules(iteration, 35);

    return 0;
}