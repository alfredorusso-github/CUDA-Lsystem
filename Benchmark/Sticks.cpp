#include "../L-system/lsystem.h"
#include "../utils/MeasureTime.h"

int main(int argc, char const *argv[])
{
    // Sticks
    lsystem sticks("X", "X F[+X]F[-X]+X F FF");
    int iteration = 17;

    std::cout << "Executing CPU algorithm..." << std::endl;
    double time = MeasureTime(&sticks, &lsystem::execute, iteration);

    std::cout << "Executing GPU algorithm..." << std::endl;
    double GPUtime = MeasureTime(&sticks, &lsystem::executeOnGPU, iteration);

    std::cout << "Executing GPU algorithm with modules..." << std::endl;
    double GPUtimeModules = MeasureTime(&sticks, &lsystem::executeOnGPUWithModules, iteration, 12);
    
    std::cout << "Arrowhead" << "\t Iteration: " << iteration << "\tCPU Time: " << time << "\tGPU Time: " << GPUtime << "\tGPU modules time: " << GPUtimeModules << std::endl;

    return 0;
}
