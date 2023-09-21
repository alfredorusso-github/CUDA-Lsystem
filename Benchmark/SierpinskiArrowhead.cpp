#include "../L-system/lsystem.h"
#include "../utils/MeasureTime.h"

int main(int argc, char const *argv[])
{
    // Sierpinski arrowhead
    lsystem arrowhead("A", "A B-A-B B A+B+A");
    int iteration= 18;

    std::cout << "Executing CPU algorithm..." << std::endl;
    double time = MeasureTime(&arrowhead, &lsystem::execute, iteration);

    std::cout << "Executing GPU algorithm..." << std::endl;
    double GPUtime = MeasureTime(&arrowhead, &lsystem::executeOnGPU, iteration);
    
    std::cout << "Arrowhead" << "\t Iteration: " << iteration << "\tCPU Time: " << time << "\tGPU Time: " << GPUtime << std::endl;

    std::cout << "CPU size: " << arrowhead.get_result().length() << "\tGPU size: " << arrowhead.get_GPUResult().length() << std::endl;

    return 0;
}