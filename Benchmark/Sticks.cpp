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
    
    std::cout << "Arrowhead" << "\t Iteration: " << iteration << "\tCPU Time: " << time << "\tGPU Time: " << GPUtime << std::endl;

    std::cout << "CPU size: " << sticks.get_result().length() << "\tGPU size: " << sticks.get_GPUResult().length() << std::endl;

    return 0;
}
