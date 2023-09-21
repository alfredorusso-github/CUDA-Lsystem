#include "../L-system/lsystem.h"
#include "../utils/MeasureTime.h"

int main(int argc, char const *argv[])
{
    // Pentaplexity
    lsystem pentaplexity("F++F++F++F++F", "F F++F++F+++++F-F++F");
    int iteration = 11;

    std::cout << "Executing CPU algorithm..." << std::endl;
    double time = MeasureTime(&pentaplexity, &lsystem::execute, iteration);

    std::cout << "Executing GPU algorithm..." << std::endl;
    double GPUtime = MeasureTime(&pentaplexity, &lsystem::executeOnGPU, iteration);
    
    std::cout << "Pentaplexity" << "\t Iteration: " << iteration << "\tCPU Time: " << time << "\tGPU Time: " << GPUtime << std::endl;

    std::cout << "CPU size: " << pentaplexity.get_result().length() << "\tGPU size: " << pentaplexity.get_GPUResult().length() << std::endl;

    return 0;
}
