#include "../L-system/lsystem.h"
#include "../utils/MeasureTime.h"

int main(int argc, char const *argv[])
{
    // Pentaplexity
    lsystem pentaplexity("F++F++F++F++F", "F F++F++F+++++F-F++F");
    int iteration = 10;

    std::cout << "Executing CPU algorithm..." << std::endl;
    double time = MeasureTime(&pentaplexity, &lsystem::execute, iteration);

    std::cout << "Executing GPU algorithm..." << std::endl;
    double GPUtime = MeasureTime(&pentaplexity, &lsystem::executeOnGPU, iteration);

    std::cout << "Executing GPU algorithm with modules..." << std::endl;
    double GPUtimeModules = MeasureTime(&pentaplexity, &lsystem::executeOnGPUWithModules, iteration, 33);
    
    std::cout << "Pentaplexity" << "\t Iteration: " << iteration << "\tCPU Time: " << time << "\tGPU Time: " << GPUtime << "\tGPU modules time: " << GPUtimeModules << std::endl;

    return 0;
}
