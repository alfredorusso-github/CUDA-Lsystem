#include "../L-system/lsystem.h"
#include "../utils/MeasureTime.h"

int main(int argc, char const *argv[])
{
    lsystem pentaplexity("F++F++F++F++F", "F F++F++F+++++F-F++F");
    int iteration = 11;

    pentaplexity.executeOnGPUWithModules(iteration, 33);

    return 0;
}